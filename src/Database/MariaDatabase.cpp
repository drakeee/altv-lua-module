//#include <Main.h>
#include <mysql.h>
#include <Database/MariaDatabase.h>
#include <memory>

sql::MariaDatabase::MariaDatabase(const char* hostname, const char* user, const char* password, const char* database, int port)
{
	this->connection = mysql_init(NULL);
	if (!mysql_real_connect(this->connection, hostname, user, password, database, port, NULL, 0))
	{
		Core->LogError("[MariaDatabase] Couldn't connect to the server:");
		Core->LogError("[MariaDatabase]  Error Code: " + std::to_string(mysql_errno(this->connection)));
		Core->LogError("[MariaDatabase]  Error: " + alt::String(mysql_error(this->connection)));
		
		Core->LogInfo("ping1: " + std::to_string(mysql_ping(this->connection)));
		return;
	}

	Core->LogInfo("ping2: " + std::to_string(mysql_ping(this->connection)));
	//mysql_real_connect()
}

sql::MariaDatabase::~MariaDatabase()
{

}

std::unique_ptr<sql::QueryResult> sql::MariaDatabase::Query(const char* query, sql::BindParam...)
{
	if (mysql_ping(this->connection) != 0)
	{
		Core->LogError("[MariaDatabase] Couldn't execute the query: connection is dead.");
		return nullptr;
	}

	//Core->LogInfo("Running query: " + alt::String(query));

	MYSQL_STMT* stmt = mysql_stmt_init(this->connection);
	if (stmt == nullptr)
	{
		Core->LogError("[MariaDatabase] Couldn't create statement @ line " + std::to_string(__LINE__));
		return nullptr;
	}

	if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0)
	{
		Core->LogError("[MariaDatabase] Couldn't prepare statement: ");
		Core->LogError("[MariaDatabase]  Error Code: " + std::to_string(mysql_stmt_errno(stmt)));
		Core->LogError("[MariaDatabase]  Error: " + alt::String(mysql_stmt_error(stmt)));

		mysql_stmt_free_result(stmt);
		mysql_stmt_close(stmt);

		return nullptr;
	}

	MYSQL_RES* aRes = mysql_stmt_result_metadata(stmt);

	my_bool aBool = 1;
	mysql_stmt_attr_set(stmt, STMT_ATTR_UPDATE_MAX_LENGTH, &aBool);

	int result = mysql_stmt_execute(stmt);
	mysql_stmt_store_result(stmt);

	//Core->LogInfo("Row size: " + std::to_string(mysql_stmt_num_rows(stmt)));

	std::unique_ptr<QueryResult> queryResult(new QueryResult);
	queryResult->rowsNum = mysql_stmt_num_rows(stmt);
	queryResult->rows.reset(new RowData[queryResult->rowsNum]);

	uint32_t rowIndex = 0;
	while (!mysql_stmt_fetch(stmt))
	{
		for (int i = 0; i < stmt->field_count; i++)
		{
			std::unique_ptr<ResultData> resultData(new ResultData);

			MYSQL_FIELD* aField = &aRes->fields[i];

			MYSQL_BIND buffer;
			void* data = malloc(aField->max_length + 1UL);

			memset(data, 0, aField->max_length + 1UL);
			memset(&buffer, 0, sizeof(MYSQL_BIND));

			buffer.buffer_type = MYSQL_TYPE_STRING;
			buffer.buffer = data;
			buffer.buffer_length = aField->max_length;

			mysql_stmt_fetch_column(stmt, &buffer, i, 0);

			resultData->columnName = nullptr;
			resultData->buffer = buffer.buffer;
			resultData->buffer_size = buffer.buffer_length;
			resultData->buffer_type = ResultType::RESULT_TYPE_STRING;
		}

		rowIndex++;
	}

	queryResult->insertId = mysql_stmt_insert_id(stmt);
	queryResult->affectedRows = mysql_stmt_affected_rows(stmt);

	mysql_stmt_free_result(stmt);
	mysql_stmt_close(stmt);

	return std::move(queryResult);
	//return std::move(nullptr);
}

bool sql::MariaDatabase::BindParam()
{
	return true;
}

bool sql::MariaDatabase::Disconnect()
{
	if (mysql_ping(this->connection) != 0)
	{
		Core->LogError("[MariaDatabase] Couldn't disconnect from server: connection is dead.");
		return false;
	}

	mysql_close(this->connection);
	return true;
}