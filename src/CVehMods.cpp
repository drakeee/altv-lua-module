#include <Main.h>

CVehMods::CVehMods() :
	core(&alt::ICore::Instance())
{
	this->filePtr = fopen(this->filePath, "rb");
	if (this->filePtr)
	{
		fread(&this->header, sizeof(ModsHeader), 1, this->filePtr);

		if (header.versionString[0] != 'M' || header.versionString[1] != 'O')
		{
			this->core->LogError("Invalid vehmods.bin data file. Download new from altv.mp");
			return;
		}

		if (header.versionNumber != FILE_MODS_VERSION)
		{
			core->LogError("vehmods.bin structure (v." + std::to_string(this->header.versionNumber) + ") doesn't fit server structure (v." + std::to_string(FILE_MODS_VERSION) + ")");
			return;
		}

		ModsInfoHeader test;
		fread(&test, sizeof(ModsInfoHeader), 1, this->filePtr);

		core->LogInfo("Name size: " + std::to_string(test.modNameLength));
	}
}

CVehMods::~CVehMods()
{

}