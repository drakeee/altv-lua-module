#pragma once

#include <Main.h>

#ifndef FILE_MODS_VERSION
	#define FILE_MODS_VERSION 1
#endif

class CVehMods
{
public:
#pragma pack(push, 1)
	struct ModsHeader
	{
		char versionString[2];
		uint32_t versionNumber;
	};

	struct ModsInfoHeader
	{
		uint16_t modNameLength;
	};
#pragma pack(pop)

	static CVehMods& Instance()
	{
		static CVehMods instance;
		return instance;
	}

	CVehMods(CVehMods const&) = delete;
	void operator=(CVehMods const&) = delete;

private:
	CVehMods();
	~CVehMods();

	const char* filePath = "./data/vehmods.bin";
	FILE*		filePtr;
	alt::ICore*	core;

	ModsHeader	header = ModsHeader();
};