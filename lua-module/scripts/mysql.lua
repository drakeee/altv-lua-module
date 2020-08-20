local ffi = 	require("ffi")
local lib = 	require("SQL.MySQL.mysql_ffi")
local rowType = require("SQL.MySQL.mysql_row")

local MySQL = {}
MySQL.__index = MySQL

function MySQL:connect(host, user, passwd, db, port)

	assert(host, "[MySQL:connect] Hostname is required. Line: " .. tostring(debug.getinfo(2).currentline))
	assert(user, "[MySQL:connect] Username is required. Line: " .. tostring(debug.getinfo(2).currentline))
	assert(passwd, "[MySQL:connect] Password is required. Line: " .. tostring(debug.getinfo(2).currentline))
	assert(db, "[MySQL:connect] Database is required. Line: " .. tostring(debug.getinfo(2).currentline))

	port = port or 3306

	local obj = {}
	obj.__connection = lib.mysql_init(nil)
	
	if lib.mysql_real_connect(obj.__connection, host, user, passwd, db, port, nil, 0) == nullptr then
		logError("[MySQL] Could not connect to the database: ")
		logError(" Error Code: " .. tostring(lib.mysql_errno(obj.__connection)))
		logError(" Error: " .. tostring(ffi.string(lib.mysql_error(obj.__connection))))

		lib.mysql_close(obj.__connection)

		return false
	end
	
	setmetatable(obj, MySQL)
	return obj
end

function MySQL:ping()
	return lib.mysql_ping(self.__connection)
end

function MySQL:query(query, ...)

	assert(query, "[MySQL:query] Query is required. Line: " .. tostring(debug.getinfo(2).currentline))

	if self:ping() ~= 0 then
		logError("[MySQL:query] Couldn't execute query: connection is probably dead. Line: " .. tostring(debug.getinfo(2).currentline))
		return false
	end

	local arguments = {select(1, ...)}
	if type(arguments[1]) == "table" then
		for key, value in pairs(arguments[1]) do
			query = query:gsub(string.format(":%s", key), self:escape(value)[1], 1)
		end
	else
		local escapedArguments = self:escape(unpack(arguments))
		for i, argument in ipairs(escapedArguments) do
			if type(argument) == "string" then argument = string.format('"%s"', argument) end
			query = query:gsub("?", argument, 1)
		end
	end

	local result = lib.mysql_query(self.__connection, query)
	if result ~= 0 then
		logError("[MySQL] Could not execute query @ line " .. tostring(debug.getinfo(2).currentline) .. ":")
		logError(" Error Code: " .. tostring(lib.mysql_errno(self.__connection)))
		logError(" Error: " .. tostring(ffi.string(lib.mysql_error(self.__connection))))

		return false
	end

	local result = lib.mysql_store_result(self.__connection)
	if result == nullptr then
		return {
			insertId = tonumber(lib.mysql_insert_id(self.__connection)),
			affectedRows = tonumber(lib.mysql_affected_rows(self.__connection))
		}
	end

	local fieldsNum = lib.mysql_num_fields(result)
	local fields = lib.mysql_fetch_fields(result)
	local fieldTable = {}

	for i = 0, fieldsNum - 1 do
		local field = fields[i]
		table.insert(fieldTable, {name = ffi.string(field.name), func = rowType[tonumber(field.type)]})
	end

	local resultSet = {}
	local rowsNum = tonumber(lib.mysql_num_rows(result))
	for i = 0, rowsNum - 1 do
		local row = lib.mysql_fetch_row(result)
		local rowData = {}

		for i = 1, fieldsNum do
			local field = fieldTable[i]

			rowData[field.name] = field.func(ffi.string(row[i - 1]))
		end

		if rowsNum == 1 then
			resultSet = rowData
		else
			table.insert(resultSet, rowData)
		end
	end

	lib.mysql_free_result(result)

	return resultSet
end

function MySQL:escape(...)

	local result = {}
	for _, v in ipairs({select(1, ...)}) do
		local insert = nil

		if(type(v) == "string") then
			local source = ffi.new("char[?]", v:len())
			ffi.copy(source, v)

			local destination = ffi.new("char[?]", v:len() * 2 + 1)
			lib.mysql_real_escape_string(self.__connection, destination, source, v:len())

			insert = ffi.string(destination)
		elseif type(v) == "number" then
			insert = v
		end
		
		table.insert(result, insert)
	end

	return result
end

function MySQL:close()
	if self.__connection then
		lib.mysql_close(self.__connection)

		return true
	end

	return false
end

return MySQL