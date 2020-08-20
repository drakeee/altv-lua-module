local ffi = require("ffi")
local lib = require("SQL.SQLite3.sqlite3_ffi")
local rowType = require("SQL.SQLite3.sqlite3_row")

local function isInteger(number)
	return math.floor(number) == number
end

local SQLite = {}
SQLite.__index = SQLite

function SQLite:connect(database, readOnly)

	assert(database, "[SQLite3:connect] Database is required. Line: " .. tostring(debug.getinfo(2).currentline))
	readOnly = readOnly or false
	local flags = readOnly and lib.SQLITE_OPEN_READONLY or bit.bor(lib.SQLITE_OPEN_READWRITE, lib.SQLITE_OPEN_CREATE)

	local obj = {}
	obj.__connection = ffi.new("sqlite3*[1]")

	if lib.sqlite3_open_v2(localResource.path .. "test.db", obj.__connection, flags, nil) ~= lib.SQLITE_OK then
		logError("[SQLite3] Could not open the database: ")
		logError(" Error Code: " .. tostring(lib.sqlite3_errcode(obj.__connection[0])))
		logError(" Error: " .. tostring(ffi.string(lib.sqlite3_errmsg(obj.__connection[0]))))

		lib.sqlite3_close_v2(obj.__connection[0])

		return false
	end

	setmetatable(obj, SQLite)
	return obj
end

function SQLite:query(query, ...)

	assert(query, "[SQLite3] Query parameter is required. Line: " .. tostring(debug.getinfo(2).currentline))

	if not self.__connection then
		logError("[SQLite3:query] Couldn't execute query: connection is probably dead. Line: " .. tostring(debug.getinfo(2).currentline))
		return false
	end

	local arguments = {select(1, ...)}

	local stmt = ffi.new("sqlite3_stmt*[1]")
	local result = lib.sqlite3_prepare_v2(self.__connection[0], query, -1, stmt, nil)

	if result ~= lib.SQLITE_OK then
		logError("[SQLite3:query] Could not prepare query @ line " .. tostring(debug.getinfo(2).currentline) .. ":")
		logError(" Error Code: " .. tostring(lib.sqlite3_errcode(self.__connection[0])))
		logError(" Error: " .. tostring(ffi.string(lib.sqlite3_errmsg(self.__connection[0]))))

		return false
	end

	local paramCount = lib.sqlite3_bind_parameter_count(stmt[0])
	if paramCount ~= #arguments then
		logError("[SQLite3:query] Function arguments count doesn't match query parameter count.")

		lib.sqlite3_finalize(stmt[0])
		return false
	end

	for index, argument in ipairs(arguments) do
		if type(argument) == "string" then
			lib.sqlite3_bind_text(stmt[0], index, argument, argument:len(), nil)
		elseif type(argument) == "number" then
			lib[isInteger(argument) and "sqlite3_bind_int" or "sqlite3_bind_double"](stmt[0], index, argument)
		elseif type(argument) == "nil" then
			lib.sqlite3_bind_null(stmt[0], index)
		end
	end

	local columnCount = tonumber(lib.sqlite3_column_count(stmt[0]))
	local processedRow = 0
	local resultSet = {}
	while lib.sqlite3_step(stmt[0]) == lib.SQLITE_ROW do
		processedRow = processedRow + 1
		local rowData = {}

		for i = 0, columnCount - 1 do
			local columnType = tonumber(lib.sqlite3_column_type(stmt[0], i))
			local columnName = tostring(ffi.string(lib.sqlite3_column_name(stmt[0], i)))
			local columnData = rowType[columnType](ffi.string(lib.sqlite3_column_text(stmt[0], i)))

			if columnName == "?" then columnName = columnData end

			rowData[columnName] = columnData
		end

		table.insert(resultSet, rowData)
	end

	if processedRow == 1 then
		resultSet = resultSet[1]
	elseif processedRow == 0 then
		resultSet = {
			lastInsertId = tonumber(lib.sqlite3_last_insert_rowid(self.__connection[0])),
			affectedRows = tonumber(lib.sqlite3_changes(self.__connection[0]))
		}
	end

	lib.sqlite3_finalize(stmt[0])

	return resultSet
end

function SQLite:close()

	if not self.__connection then
		logError("[SQLite3] Connection is not open")
		return false
	end

	lib.sqlite3_close_v2(self.__connection[0])

	return true
end

return SQLite