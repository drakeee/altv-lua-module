#pragma once

#include <SDK.h>
#include <map>
#include <cstdio>
#include <string>

#define INVALID_MODKIT 0xFFFF
#ifndef FILE_VERSION
	#define FILE_VERSION 2
#endif

#ifndef FILE_MODS_VERSION
	#define FILE_MODS_VERSION 1
#endif

class VehicleMods
{
public:
#pragma pack(push, 1)
	struct ModHeader
	{
		char versionString[2];
		uint16_t versionNumber;
	};

	struct ModKit
	{
		uint16_t id = INVALID_MODKIT;
		std::string name;
		std::unordered_map<uint8_t, std::vector<uint16_t>> mods;
	};
#pragma pack(pop)

	inline ModKit* GetVehicleMod(uint16_t index)
	{
		return this->modKits.at(index);
	}

	static VehicleMods& Instance()
	{
		static VehicleMods instance;
		return instance;
	}

	VehicleMods(VehicleMods const&) = delete;
	void operator=(VehicleMods const&) = delete;

private:
	VehicleMods() : core(&alt::ICore::Instance())
	{
		this->filePtr = fopen(this->filePath, "rb");
		if (this->filePtr)
		{
			fread(&this->header, sizeof(ModHeader), 1, this->filePtr);

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

			for (;;)
			{
				ModKit* modKit = new ModKit;
				if (!fread(&modKit->id, sizeof(uint16_t), 1, this->filePtr))
					break;

				uint16_t nameLen = 0;
				fread(&nameLen, sizeof(uint16_t), 1, this->filePtr);

				modKit->name.resize(nameLen);
				fread(modKit->name.data(), sizeof(char), nameLen, this->filePtr);

				uint8_t modsCount = 0;
				fread(&modsCount, sizeof(uint8_t), 1, this->filePtr);

				for (uint8_t i = 0; i < modsCount; ++i)
				{
					uint8_t modCat = 0;
					fread(&modCat, sizeof(uint8_t), 1, this->filePtr);
					uint8_t count = 0;
					fread(&count, sizeof(uint8_t), 1, this->filePtr);

					std::vector<uint16_t>& comps = modKit->mods[modCat];

					//std::string modIDBuilder("[");
					for (uint8_t j = 0; j < count; ++j)
					{
						uint16_t compId = 0;
						fread(&compId, sizeof(uint16_t), 1, this->filePtr);
						comps.push_back(compId);

						//modIDBuilder.append(std::to_string(compId) + ", ");
					}
					//modIDBuilder.append("]");

					//this->core->LogInfo(modKit->name + " -> " + std::to_string(modsCount) + " -> " + std::to_string(modCat) + " -> " + std::to_string(count) + " -> " + modIDBuilder);
				}

				this->modKits[modKit->id] = modKit;
			}

#ifndef NDEBUG
			core->LogInfo("Loaded " + std::to_string(this->modKits.size()) + " modkits");
#endif

			fclose(this->filePtr);
		}
	}
	~VehicleMods() {}

	const char* filePath = "./data/vehmods.bin";
	FILE* filePtr;
	alt::ICore* core;

	ModHeader	header = ModHeader();
	std::map<uint16_t, ModKit*> modKits;
};

class VehicleModels
{
public:

	enum class VehicleType : uint8_t {
		INVALID,
		PED,
		AUTOMOBILE,
		PLANE,
		TRAILER,
		QUAD_BIKE,
		SUBMARINE_CAR,
		AMPHIBIOUS_AUTOMOBILE,
		AMPHIBIOUS_QUAD_BIKE,
		HELI,
		BLIMP,
		AUTOGYRO,
		BIKE,
		BMX,
		BOAT,
		TRAIN,
		SUBMARINE,
		OBJECT
	};

#pragma pack(push, 1)
	struct Header
	{
		char		versionString[2];
		uint16_t	versionNumber;
	};

	struct VehicleHeader
	{
		uint32_t	vehicleHash;
		uint8_t		vehicleNameLength;
	};

	struct VehicleInfo
	{
		VehicleInfo(size_t vehicleNameLength)
		{
			this->vehicleName = new char[vehicleNameLength];
			memset(this->vehicleName, '\0', (sizeof(char) * vehicleNameLength));
		}

		~VehicleInfo() { delete[] vehicleName; }

		uint32_t	vehicleHash;
		char*	vehicleName = nullptr;
		VehicleType	vehicleType = VehicleType::INVALID;
		uint8_t vehicleWheelsCount = -1;
		bool	vehicleHasArmoredWindows = false;
		uint8_t vehiclePrimaryColor = -1;
		uint8_t vehicleSecondaryColor = -1;
		uint8_t vehiclePearlColor = -1;
		uint8_t vehicleWheelsColor = -1;
		uint8_t vehicleInteriorColor = -1;
		uint8_t vehicleDashboardColor = -1;
		uint16_t vehicleModkitsTemp[2] = { 0 };
		uint16_t vehicleExtras = 0;
		uint16_t vehicleDefaultExtras = 0;
		VehicleMods::ModKit* vehicleModkits[2] = { nullptr };
	};
#pragma pack(pop)

	typedef std::map<int, VehicleInfo*> HashMap;
	typedef std::map<std::string, VehicleInfo*> StringMap;

	static VehicleModels& Instance()
	{
		static VehicleModels instance;
		return instance;
	}

	VehicleModels(VehicleModels const&)		= delete;
	void operator=(VehicleModels const&)	= delete;

	size_t GetVehicleCount(void) { return this->vehicleInfos_hashes.size(); }

	inline VehicleInfo* GetVehicleInfo(const char* name)
	{
		return this->vehicleInfos_strings[name];
	}

	inline VehicleInfo* GetVehicleInfo(int hash)
	{
		return this->vehicleInfos_hashes[hash];
	}

	inline VehicleInfo* GetVehicleInfo(alt::IVehicle* vehicle)
	{
		return this->GetVehicleInfo(vehicle->GetModel());
	}

	inline const HashMap& GetVehicleInfosByHash(void)		const { return this->vehicleInfos_hashes; }
	inline const StringMap& GetVehicleInfosByString(void)	const { return this->vehicleInfos_strings; }

	const VehicleInfo* operator[](int modelHash) { return this->GetVehicleInfo(modelHash); }
	const VehicleInfo* operator[](const char* name) { return this->GetVehicleInfo(name); }

private:
	VehicleModels(void) : core(&alt::ICore::Instance())
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
					sizeof(vehicleInfo->vehicleName) +
					sizeof(vehicleInfo->vehicleModkits)
					);

				//Read the rest of the struct
				fread(&(*vehicleInfo).vehicleType, sizeof(VehicleInfo) - skip, 1, this->filePtr); //skip 4 byte (vehicle hash) and 8 byte (pointer), then start reading from vehicleType address

				vehicleInfos_hashes[vehicleInfo->vehicleHash] = vehicleInfo;
				vehicleInfos_strings[vehicleInfo->vehicleName] = vehicleInfo;

				for (size_t i = 0; i < 2; i++)
				{
					if (vehicleInfo->vehicleModkitsTemp[i] == INVALID_MODKIT)
						break;

					vehicleInfo->vehicleModkits[i] = this->modKits->GetVehicleMod(vehicleInfo->vehicleModkitsTemp[i]);
				}

			}

#ifndef NDEBUG
			core->LogInfo("Loaded " + std::to_string(vehicleInfos_hashes.size()) + " vehicles information.");
#endif
			fclose(this->filePtr);
		}
	}
	~VehicleModels(){}

	alt::ICore*	core = nullptr;

	const char*	filePath = "./data/vehmodels.bin";
	FILE*		filePtr = nullptr;

	VehicleMods* modKits = &VehicleMods::Instance();

	Header		fileHeader = Header();
	HashMap		vehicleInfos_hashes;
	StringMap	vehicleInfos_strings;
};