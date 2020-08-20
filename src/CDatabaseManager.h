#pragma once

#include <Main.h>
#include <mysql.h>

namespace sql
{
	enum class ResultType
	{
		RESULT_TYPE_NULL = 0,	//NULL
		RESULT_TYPE_TINY,		//signed char
		RESULT_TYPE_SHORT,		//short int
		RESULT_TYPE_LONG,		//int
		RESULT_TYPE_LONGLONG,	//long long int
		RESULT_TYPE_FLOAT,		//float
		RESULT_TYPE_DOUBLE,		//double
		RESULT_TYPE_TIME,		//MYSQL_TIME
		RESULT_TYPE_DATE,		//MYSQL_TIME
		RESULT_TYPE_DATETIME,	//MYSQL_TIME
		RESULT_TYPE_TIMESTAMP,	//MYSQL_TIME
		RESULT_TYPE_STRING,		//char[]
		RESULT_TYPE_BLOB,		//char[]
	};

	struct ResultData
	{
		char* columnName;
		void* buffer;
		ResultType buffer_type;
		uint32_t buffer_size;

		~ResultData()
		{
			delete[] columnName;
			delete[] buffer;

			//printf("~ResultData\n");
		}
	};

	struct RowData
	{
		std::map<std::string, std::unique_ptr<ResultData>> results2;
		//std::unique_ptr<ResultData[]> results;
		uint32_t resultsNum;

		~RowData()
		{
			//printf("~RowData\n");
		}
	};

	struct QueryResult
	{
		std::unique_ptr<RowData[]> rows;
		uint32_t rowsNum;

		uint32_t insertId;
		uint32_t affectedRows;

		~QueryResult()
		{
			//printf("~QueryResult\n");
		}
	};

	struct BindParam : public MYSQL_BIND
	{
		void* bufferData;
		BindParam(int value)
		{
			bufferData = malloc(sizeof(int));
			*(int*)bufferData = value;
			this->buffer = &bufferData;
			this->buffer_type = MYSQL_TYPE_LONG;
		}

		BindParam(char* data)
		{
			bufferData = malloc(strlen(data) + 1);
			memcpy(bufferData, data, strlen(data));
			this->buffer = bufferData;
			this->buffer_type = MYSQL_TYPE_STRING;
			this->buffer_length = strlen(data);
		}
	};

	class DatabaseBase
	{
	public:
		virtual std::unique_ptr<QueryResult> Query(const char* query, BindParam...) = 0;
		virtual bool Disconnect() = 0;
		virtual bool BindParam() = 0;
	};

	class DatabaseManager
	{
	public:
		static DatabaseBase* Connect(const char* driver, const char* hostname, const char* user = nullptr, const char* password = nullptr, const char* database = nullptr, int port = 3306);
	};
}