#pragma once

#include <SDK.h>
#include <map>
#include <cstdio>
#include <string>

#ifndef FILE_VERSION
	#define FILE_VERSION 2
#endif

class CVehModels
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
		uint16_t vehicleModkits[2] = { 0 };
		uint16_t vehicleExtras = 0;
		uint16_t vehicleDefaultExtras = 0;
	};
#pragma pack(pop)

	typedef std::map<int, VehicleInfo*> HashMap;
	typedef std::map<std::string, VehicleInfo*> StringMap;

	static CVehModels& Instance()
	{
		static CVehModels instance;
		return instance;
	}

	CVehModels(CVehModels const&)		= delete;
	void operator=(CVehModels const&)	= delete;

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
	CVehModels(void);
	~CVehModels();

	alt::ICore*	core = nullptr;

	const char*	filePath = "./data/vehmodels.bin";
	FILE*		filePtr = nullptr;

	Header		fileHeader = Header();
	HashMap		vehicleInfos_hashes;
	StringMap	vehicleInfos_strings;
};