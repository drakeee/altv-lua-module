#include "Main.h"
#include <chrono>

//#include <WinSock2.h>
//#undef min
//#undef max
//
//#include <qtl_mysql.hpp>

alt::ICore* Core;

EXPORT bool altMain(alt::ICore* _core)
{
	alt::ICore::SetInstance(_core);

	auto& runtime = CLuaScriptRuntime::Instance();

	_core->LogInfo(alt::String("Lua module. Version: v" + runtime.GetVersion().to_string()));
	_core->RegisterScriptRuntime("lua", &runtime);

	Core = _core;

	//qtl::mysql::database db;
	//db.open("localhost", "root", "", "riserpg", 0, 3307);

	//auto start = std::chrono::high_resolution_clock::now();
	//for (int i = 0; i < 1000; i++)
	//{
	//	db.query("SELECT * FROM `accounts`", [](uint32_t id, const std::string& name)
	//	{
	//		//printf("ID=\"%d\", Name=\"%s\"\n", id, name.data());
	//	});
	//}
	//auto stop = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	//printf("qtl: Query took %dms\n", duration.count());


	/*sql::DatabaseBase *connection = sql::DatabaseManager::Connect("mariadb", "localhost", "root", "", "riserpg", 3307);
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000; i++)
	{
		auto qResult = connection->Query("SELECT * FROM `accounts`");
		//Core->LogInfo("rowsnum: " + std::to_string(qResult->rowsNum));
		/*for (uint32_t i = 0; i < qResult->rowsNum; i++)
		{
			auto& b = qResult->rows[i];
			for (auto& [key, value] : qResult->rows[i].results2)
			{
				auto key1 = key;
				auto &value1 = value;
				//Core->LogInfo("Key: " + key);
				//Core->LogInfo("Value: " + alt::String((char*)value->buffer));
			}
		}
	}*/
	/*stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	printf("LuaSQL: Query took %dms\n", duration.count());*/

	//Core->LogInfo("qResult: " + std::to_string(qResult));


	return true;
}

EXPORT uint32_t GetSDKVersion()
{
	return alt::ICore::SDK_VERSION;
}