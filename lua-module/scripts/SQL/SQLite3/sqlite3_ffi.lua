local ffi = require("ffi")
local bit = require("bit")

ffi.cdef [[
	typedef struct sqlite3 sqlite3;
	typedef struct sqlite3_stmt sqlite3_stmt;
	typedef long long int sqlite3_int64;

	enum sqlite3_bit_flags {
		SQLITE_OPEN_READONLY = 0x00000001,  /* Ok for sqlite3_open_v2() */
		SQLITE_OPEN_READWRITE = 0x00000002,  /* Ok for sqlite3_open_v2() */
		SQLITE_OPEN_CREATE = 0x00000004,  /* Ok for sqlite3_open_v2() */
		SQLITE_OPEN_URI = 0x00000040,  /* Ok for sqlite3_open_v2() */
		SQLITE_OPEN_MEMORY = 0x00000080,  /* Ok for sqlite3_open_v2() */
		SQLITE_OPEN_NOMUTEX = 0x00008000,  /* Ok for sqlite3_open_v2() */
		SQLITE_OPEN_FULLMUTEX = 0x00010000,  /* Ok for sqlite3_open_v2() */
		SQLITE_OPEN_SHAREDCACHE = 0x00020000,  /* Ok for sqlite3_open_v2() */
		SQLITE_OPEN_PRIVATECACHE = 0x00040000,  /* Ok for sqlite3_open_v2() */
		SQLITE_OPEN_NOFOLLOW = 0x01000000  /* Ok for sqlite3_open_v2() */
	};

	enum sqlite3_error_codes {
		SQLITE_OK = 0,   /* Successful result */
		SQLITE_ERROR = 1,   /* Generic error */
		SQLITE_INTERNAL = 2,   /* Internal logic error in SQLite */
		SQLITE_PERM = 3,   /* Access permission denied */
		SQLITE_ABORT = 4,   /* Callback routine requested an abort */
		SQLITE_BUSY = 5,   /* The database file is locked */
		SQLITE_LOCKED = 6,   /* A table in the database is locked */
		SQLITE_NOMEM = 7,   /* A malloc() failed */
		SQLITE_READONLY = 8,   /* Attempt to write a readonly database */
		SQLITE_INTERRUPT = 9,   /* Operation terminated by sqlite3_interrupt()*/
		SQLITE_IOERR = 10,   /* Some kind of disk I/O error occurred */
		SQLITE_CORRUPT = 11,   /* The database disk image is malformed */
		SQLITE_NOTFOUND = 12,   /* Unknown opcode in sqlite3_file_control() */
		SQLITE_FULL = 13,   /* Insertion failed because database is full */
		SQLITE_CANTOPEN = 14,   /* Unable to open the database file */
		SQLITE_PROTOCOL = 15,   /* Database lock protocol error */
		SQLITE_EMPTY = 16,   /* Internal use only */
		SQLITE_SCHEMA = 17,   /* The database schema changed */
		SQLITE_TOOBIG = 18,   /* String or BLOB exceeds size limit */
		SQLITE_CONSTRAINT = 19,   /* Abort due to constraint violation */
		SQLITE_MISMATCH = 20,   /* Data type mismatch */
		SQLITE_MISUSE = 21,   /* Library used incorrectly */
		SQLITE_NOLFS = 22,   /* Uses OS features not supported on host */
		SQLITE_AUTH = 23,   /* Authorization denied */
		SQLITE_FORMAT = 24,   /* Not used */
		SQLITE_RANGE = 25,   /* 2nd parameter to sqlite3_bind out of range */
		SQLITE_NOTADB = 26,   /* File opened that is not a database file */
		SQLITE_NOTICE = 27,   /* Notifications from sqlite3_log() */
		SQLITE_WARNING = 28,   /* Warnings from sqlite3_log() */
		SQLITE_ROW = 100,  /* sqlite3_step() has another row ready */
		SQLITE_DONE = 101  /* sqlite3_step() has finished executing */
	};

	enum sqlite3_column_types {
		SQLITE_INTEGER = 1,
		SQLITE_FLOAT = 2,
		SQLITE_TEXT = 3,
		SQLITE_BLOB = 4,
		SQLITE_NULL = 5
	};

	int sqlite3_open_v2(
		const char *filename,   /* Database filename (UTF-8) */
		sqlite3 **ppDb,         /* OUT: SQLite db handle */
		int flags,              /* Flags */
		const char *zVfs        /* Name of VFS module to use */
	);
	int sqlite3_close_v2(sqlite3*);

	int sqlite3_errcode(sqlite3 *db);
	int sqlite3_extended_errcode(sqlite3 *db);
	const char *sqlite3_errmsg(sqlite3*);
	const char *sqlite3_errstr(int);

	int sqlite3_prepare_v2(
		sqlite3 *db,            /* Database handle */
		const char *zSql,       /* SQL statement, UTF-8 encoded */
		int nByte,              /* Maximum length of zSql in bytes. */
		sqlite3_stmt **ppStmt,  /* OUT: Statement handle */
		const char **pzTail     /* OUT: Pointer to unused portion of zSql */
	);

	int sqlite3_bind_double(sqlite3_stmt*, int, double);
	int sqlite3_bind_int(sqlite3_stmt*, int, int);
	//int sqlite3_bind_int64(sqlite3_stmt*, int, sqlite3_int64);
	int sqlite3_bind_null(sqlite3_stmt*, int);
	int sqlite3_bind_text(sqlite3_stmt*,int,const char*,int,void(*)(void*));

	int sqlite3_column_count(sqlite3_stmt *pStmt);
	int sqlite3_column_type(sqlite3_stmt*, int iCol);
	const char *sqlite3_column_name(sqlite3_stmt*, int N);
	const unsigned char *sqlite3_column_text(sqlite3_stmt*, int iCol);

	int sqlite3_step(sqlite3_stmt*);
	int sqlite3_finalize(sqlite3_stmt *pStmt);
	int sqlite3_bind_parameter_count(sqlite3_stmt*);
	sqlite3_int64 sqlite3_last_insert_rowid(sqlite3*);
	int sqlite3_changes(sqlite3*);
]]

local nullptr = ffi.cast("void*", 0)
local extension = (ffi.os == "Windows" and ".dll" or ".so")

-- logInfo(string.format("[MySQL] Try to load libmariadb%s", extension))
local lib = nil
local result = pcall(function()
	lib = ffi.load("sqlite3", true)
end)

if not result then
	logError(string.format("[SQLite3] Unable to load sqlite3: couldn't find \"sqlite3%s\" library", extension))
	logError(string.format("[SQLite3] Please make sure that \"sqlite3%s\" exists inside \"modules/lua-module\" folder.", extension))
	return false
end

return lib