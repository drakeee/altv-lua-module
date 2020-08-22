local ffi = require('ffi')
ffi.cdef [[
	typedef void MYSQL;
	typedef char** MYSQL_ROW;
	typedef void MYSQL_RES;

	enum enum_field_types {
		MYSQL_TYPE_DECIMAL, MYSQL_TYPE_TINY,
		MYSQL_TYPE_SHORT,  MYSQL_TYPE_LONG,
		MYSQL_TYPE_FLOAT,  MYSQL_TYPE_DOUBLE,
		MYSQL_TYPE_NULL,   MYSQL_TYPE_TIMESTAMP,
		MYSQL_TYPE_LONGLONG,MYSQL_TYPE_INT24,
		MYSQL_TYPE_DATE,   MYSQL_TYPE_TIME,
		MYSQL_TYPE_DATETIME, MYSQL_TYPE_YEAR,
		MYSQL_TYPE_NEWDATE, MYSQL_TYPE_VARCHAR,
		MYSQL_TYPE_BIT,
		/*
			the following types are not used by client,
			only for mysqlbinlog!!
		*/
		MYSQL_TYPE_TIMESTAMP2,
		MYSQL_TYPE_DATETIME2,
		MYSQL_TYPE_TIME2,
		/* --------------------------------------------- */
		MYSQL_TYPE_JSON=245,
		MYSQL_TYPE_NEWDECIMAL=246,
		MYSQL_TYPE_ENUM=247,
		MYSQL_TYPE_SET=248,
		MYSQL_TYPE_TINY_BLOB=249,
		MYSQL_TYPE_MEDIUM_BLOB=250,
		MYSQL_TYPE_LONG_BLOB=251,
		MYSQL_TYPE_BLOB=252,
		MYSQL_TYPE_VAR_STRING=253,
		MYSQL_TYPE_STRING=254,
		MYSQL_TYPE_GEOMETRY=255,
		MAX_NO_FIELD_TYPES
	};

	typedef struct st_mysql_field {
		char *name;			/* Name of column */
		char *org_name;		/* Name of original column (added after 3.23.58) */
		char *table;			/* Table of column if column was a field */
		char *org_table;		/* Name of original table (added after 3.23.58 */
		char *db;                     /* table schema (added after 3.23.58) */
		char *catalog;                /* table catalog (added after 3.23.58) */
		char *def;			/* Default value (set by mysql_list_fields) */
		unsigned long length;		/* Width of column */
		unsigned long max_length;	/* Max width of selected set */
		/* added after 3.23.58 */
		unsigned int name_length;
		unsigned int org_name_length;
		unsigned int table_length;
		unsigned int org_table_length;
		unsigned int db_length;
		unsigned int catalog_length;
		unsigned int def_length;
		/***********************/
		unsigned int flags;		/* Div flags */
		unsigned int decimals;	/* Number of decimals in field */
		unsigned int charsetnr;       /* char set number (added in 4.1) */
		enum enum_field_types type;	/* Type of field. Se mysql_com.h for types */
		void *extension;              /* added in 4.1 */
	} MYSQL_FIELD;

	MYSQL *mysql_init(MYSQL *mysql);
	MYSQL *mysql_real_connect(
		MYSQL *mysql,
		const char *host,
		const char *user,
		const char *passwd,
		const char *db,
		unsigned int port,
		const char *unix_socket,
		unsigned long clientflag);
	int mysql_ping(MYSQL *mysql);
	unsigned int mysql_errno(MYSQL *mysql);
	const char * mysql_error(MYSQL *mysql);
	void mysql_close(MYSQL *sock);
	unsigned long mysql_real_escape_string(MYSQL *mysql, char *to, const char *from, unsigned long length);
	int mysql_query(MYSQL *mysql, const char *q);
	MYSQL_RES* mysql_store_result(MYSQL *mysql);
	MYSQL_RES* mysql_use_result(MYSQL *mysql);
	unsigned long long mysql_insert_id(MYSQL *mysql);
	unsigned long long mysql_affected_rows(MYSQL *mysql);
	unsigned long long mysql_num_rows(MYSQL_RES *res);
	unsigned int mysql_num_fields(MYSQL_RES *res);
	MYSQL_FIELD* mysql_fetch_fields(MYSQL_RES *result);
	unsigned int mysql_num_fields(MYSQL_RES *res);
	MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);
	void mysql_free_result(MYSQL_RES *result);
]]
local nullptr = ffi.cast("void*", 0)
local extension = (ffi.os == "Windows" and ".dll" or ".so")

function script_path()
	local str = debug.getinfo(1, "S").source:sub(2)

	if ffi.os == "Windows" then
		return str:match("(.*[/\\])")
	else
		return str:match("(.*/)")
	end
end

local lib = nil
local result = pcall(function()
	local library = string.format("%s/libs/%s/libmariadb%s", script_path(), (ffi.os == "Windows" and "win64" or "linux64"), extension)
	lib = ffi.load(library, true)
end)
 
logInfo(inspect(script_path()))

if not result then
	logError(string.format("[MySQL] Unable to load libmariadb: couldn't find \"libmariadb%s\" library", extension))
	logError(string.format("[MySQL] Please make sure that \"libmariadb%s\" exists inside \"modules/lua-module\" folder.", extension))
	return false
end

return lib