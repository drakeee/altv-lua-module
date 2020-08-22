local lib = require("MySQL.mysql_ffi")

if not lib then
	return false
end

-- Source: https://github.com/pguillory/luajit-mysql/blob/136a3f1833db68a608a56c662cda5f4c295a2395/src/mysql/st_mysql_field.lua#L7
local read_funcs = {}
read_funcs[lib.MYSQL_TYPE_DECIMAL]      = tonumber
read_funcs[lib.MYSQL_TYPE_TINY]         = tonumber
read_funcs[lib.MYSQL_TYPE_SHORT]        = tonumber
read_funcs[lib.MYSQL_TYPE_LONG]         = tonumber
read_funcs[lib.MYSQL_TYPE_FLOAT]        = tonumber
read_funcs[lib.MYSQL_TYPE_DOUBLE]       = tonumber
read_funcs[lib.MYSQL_TYPE_NULL]         = tostring
read_funcs[lib.MYSQL_TYPE_TIMESTAMP]    = tostring
read_funcs[lib.MYSQL_TYPE_LONGLONG]     = tostring
read_funcs[lib.MYSQL_TYPE_INT24]        = tonumber
read_funcs[lib.MYSQL_TYPE_DATE]         = tostring
read_funcs[lib.MYSQL_TYPE_TIME]         = tostring
read_funcs[lib.MYSQL_TYPE_DATETIME]     = tostring
read_funcs[lib.MYSQL_TYPE_YEAR]         = tostring
read_funcs[lib.MYSQL_TYPE_NEWDATE]      = tostring
read_funcs[lib.MYSQL_TYPE_VARCHAR]      = tostring
read_funcs[lib.MYSQL_TYPE_BIT]          = tostring
read_funcs[lib.MYSQL_TYPE_TIMESTAMP2]   = tostring
read_funcs[lib.MYSQL_TYPE_DATETIME2]    = tostring
read_funcs[lib.MYSQL_TYPE_TIME2]        = tostring
read_funcs[lib.MYSQL_TYPE_NEWDECIMAL]   = tonumber
read_funcs[lib.MYSQL_TYPE_ENUM]         = tostring
read_funcs[lib.MYSQL_TYPE_SET]          = tostring
read_funcs[lib.MYSQL_TYPE_TINY_BLOB]    = tostring
read_funcs[lib.MYSQL_TYPE_MEDIUM_BLOB]  = tostring
read_funcs[lib.MYSQL_TYPE_LONG_BLOB]    = tostring
read_funcs[lib.MYSQL_TYPE_BLOB]         = tostring
read_funcs[lib.MYSQL_TYPE_VAR_STRING]   = tostring
read_funcs[lib.MYSQL_TYPE_STRING]       = tostring
read_funcs[lib.MYSQL_TYPE_GEOMETRY]     = tostring

return read_funcs