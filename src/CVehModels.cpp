#include <CVehModels.h>

CVehModels::CVehModels(void) :
	core(&alt::ICore::Instance())
{
	//Try to read the file
	this->filePtr = fopen(filePath, "rb");
	if (this->filePtr != NULL)
	{
		//Read file version string and number
		fread(&this->fileHeader, sizeof(Header), 1, this->filePtr);

		//Check if first two byte is correct
		if (this->fileHeader.versionString[0] != 'V' || this->fileHeader.versionString[1] != 'E')
		{
			this->core->LogError("Invalid vehmodels.bin data file. Download new from altv.mp");
			return;
		}

		//Check if FILE_VERSIOn is correct
		if (this->fileHeader.versionNumber != FILE_VERSION)
		{
			core->LogError("vehmodels.bin structure (v." + std::to_string(this->fileHeader.versionNumber) + ") doesn't fit server structure (v." + std::to_string(FILE_VERSION) + ")");
			return;
		}

		//Loop till we can read data
		for (;;)
		{
			//Try to read the vehicle header
			VehicleHeader vehicleHeader;

			//If there are no information break the loop
			if (!fread(&vehicleHeader, sizeof(VehicleHeader), 1, this->filePtr))
				break;

			//Create a pointer which will hold the datas
			VehicleInfo* vehicleInfo = new VehicleInfo(vehicleHeader.vehicleNameLength + (size_t)1);
			fread((*vehicleInfo).vehicleName, sizeof(char) * vehicleHeader.vehicleNameLength, 1, this->filePtr); //read vehicle name first because its length changing
			vehicleInfo->vehicleHash = vehicleHeader.vehicleHash;

			//Skip some bytes
			int skip = (
				sizeof(vehicleInfo->vehicleHash) +
				sizeof(vehicleInfo->vehicleName)
			);

			//Read the rest of the struct
			fread(&(*vehicleInfo).vehicleType, sizeof(VehicleInfo) - skip, 1, this->filePtr); //skip 4 byte (vehicle hash) and 8 byte (pointer), then start reading from vehicleType address

			vehicleInfos_hashes[vehicleInfo->vehicleHash] = vehicleInfo;
			vehicleInfos_strings[vehicleInfo->vehicleName] = vehicleInfo;

			//core->LogInfo("ModKits: " + std::string(vehicleInfo->vehicleName) + " - " + std::to_string(vehicleInfo->vehicleModkits[0]) + " - " + std::to_string(vehicleInfo->vehicleModkits[1]));
		}
	}
}

CVehModels::~CVehModels()
{
	
}