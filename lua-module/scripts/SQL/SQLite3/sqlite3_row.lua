local lib = require("SQL.SQLite3.sqlite3_ffi")

local read_funcs = {}
read_funcs[lib.SQLITE_INTEGER] = tonumber
read_funcs[lib.SQLITE_FLOAT] = tonumber
read_funcs[lib.SQLITE_TEXT] = tostring
read_funcs[lib.SQLITE_BLOB] = tostring
read_funcs[lib.SQLITE_NULL] = tostring

return read_funcs