//#include <Main.h>
#include <CDatabaseManager.h>
#include <Database/MariaDatabase.h>
#include <algorithm>

sql::DatabaseBase* sql::DatabaseManager::Connect(const char* driver, const char* hostname, const char* user, const char* password, const char* database, int port)
{
	std::string driverStr(driver);
	std::transform(driverStr.begin(), driverStr.end(), driverStr.begin(),
		[](unsigned char c) { return std::tolower(c); });

	DatabaseBase* driverPtr = nullptr;
	if (!driverStr.compare("mysql") || !driverStr.compare("mariadb"))
	{
		driverPtr = new MariaDatabase(hostname, user, password, database, port);
	}
	else if (!driverStr.compare("sqlite"))
	{
		Core->LogInfo("It is SQLite");
	}
	else if (!driverStr.compare("postgres"))
	{
		Core->LogInfo("It is postgres");
	}
	else
	{
		Core->LogError("[DatabaseBase::Connect] Couldn't identify the driver.");
		return driverPtr;
	}

	Core->LogInfo("MariaDatabase::Connect");
	Core->LogInfo("Connection info:");
	Core->LogInfo("\tdriver: " + driverStr);
	Core->LogInfo("\thostname: " + alt::String(hostname));
	Core->LogInfo("\tuser: " + alt::String(user));
	Core->LogInfo("\tpassword: " + alt::String(password));
	Core->LogInfo("\tport: " + std::to_string(port));

	return driverPtr;
}