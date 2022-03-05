#pragma once

#include <stdint.h>
#include <string>
#include <sstream>

namespace semver {
	enum branch {
		dev = 0,
		rc,
		release
	};

	inline std::ostream& operator<<(std::ostream& os, const branch& branchType)
	{
		switch (branchType)
		{
		case branch::dev:
			os << "dev";
			break;
		case branch::rc:
			os << "rc";
			break;
		case branch::release:
			os << "release";
			break;
		}

		return os;
	}

	struct version {
		uint8_t major;
		uint8_t minor;
		uint8_t patch;
		char* sdkVersion;
		branch releaseType = branch::dev;

		constexpr version(std::uint8_t major,
			std::uint8_t minor,
			std::uint8_t patch,
			char* sdkVersion,
			branch releaseType = branch::dev) noexcept
			: major{ major },
			minor{ minor },
			patch{ patch },
			sdkVersion{ sdkVersion },
			releaseType{ releaseType }
		{

		}

		std::string to_string(void) const {
			std::ostringstream stringStream;
			stringStream << std::to_string(major) << "." << std::to_string(minor) << "." << std::to_string(patch) << "." << sdkVersion << "-" << releaseType;
			return stringStream.str();
		}
	};
}