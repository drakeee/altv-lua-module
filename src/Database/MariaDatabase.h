#pragma once

#include <Main.h>
#include <CDatabaseManager.h>

namespace sql
{
	class MariaDatabase : public DatabaseBase
	{
	public:
		MariaDatabase(const char* hostname, const char* user, const char* password, const char* database, int port);
		~MariaDatabase();

		//bool Connect(const char* driver, const char* hostname, const char* user = nullptr, const char* password = nullptr, const char* database = nullptr, int port = 3306) override;
		std::unique_ptr<QueryResult> Query(const char* query, sql::BindParam...) override;
		bool BindParam() override;
		bool Disconnect() override;

	private:
		MYSQL* connection;
	};
}