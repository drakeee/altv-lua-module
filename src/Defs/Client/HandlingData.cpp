#include <Main.h>

#ifdef ALT_CLIENT_API
namespace lua::Class
{
	const char* HandlingData::ClassName = "HandlingData";
	void HandlingData::Init(lua_State* L)
	{
		DEBUG_INFO("HandlingData::Init");

		lua_beginclass(L, HandlingData::ClassName);
		{
			lua_classfunction(L, "new", GetHandlingData);
			lua_classfunction(L, "getHandlingNameHash", GetHandlingNameHash);
			lua_classfunction(L, "getMass", GetMass);
			lua_classfunction(L, "getInitialDragCoeff", GetInitialDragCoeff);
			lua_classfunction(L, "getDownforceModifier", GetDownforceModifier);
			lua_classfunction(L, "getunkFloat1", GetunkFloat1);
			lua_classfunction(L, "getunkFloat2", GetunkFloat2);
			lua_classfunction(L, "getCentreOfMassOffset", GetCentreOfMassOffset);
			lua_classfunction(L, "getInertiaMultiplier", GetInertiaMultiplier);
			lua_classfunction(L, "getPercentSubmerged", GetPercentSubmerged);
			lua_classfunction(L, "getPercentSubmergedRatio", GetPercentSubmergedRatio);
			lua_classfunction(L, "getDriveBiasFront", GetDriveBiasFront);
			lua_classfunction(L, "getAcceleration", GetAcceleration);
			lua_classfunction(L, "getInitialDriveGears", GetInitialDriveGears);
			lua_classfunction(L, "getDriveInertia", GetDriveInertia);
			lua_classfunction(L, "getClutchChangeRateScaleUpShift", GetClutchChangeRateScaleUpShift);
			lua_classfunction(L, "getClutchChangeRateScaleDownShift", GetClutchChangeRateScaleDownShift);
			lua_classfunction(L, "getInitialDriveForce", GetInitialDriveForce);
			lua_classfunction(L, "getDriveMaxFlatVel", GetDriveMaxFlatVel);
			lua_classfunction(L, "getInitialDriveMaxFlatVel", GetInitialDriveMaxFlatVel);
			lua_classfunction(L, "getBrakeForce", GetBrakeForce);
			lua_classfunction(L, "getunkFloat4", GetunkFloat4);
			lua_classfunction(L, "getBrakeBiasFront", GetBrakeBiasFront);
			lua_classfunction(L, "getBrakeBiasRear", GetBrakeBiasRear);
			lua_classfunction(L, "getHandBrakeForce", GetHandBrakeForce);
			lua_classfunction(L, "getSteeringLock", GetSteeringLock);
			lua_classfunction(L, "getSteeringLockRatio", GetSteeringLockRatio);
			lua_classfunction(L, "getTractionCurveMax", GetTractionCurveMax);
			lua_classfunction(L, "getTractionCurveMaxRatio", GetTractionCurveMaxRatio);
			lua_classfunction(L, "getTractionCurveMin", GetTractionCurveMin);
			lua_classfunction(L, "getTractionCurveMinRatio", GetTractionCurveMinRatio);
			lua_classfunction(L, "getTractionCurveLateral", GetTractionCurveLateral);
			lua_classfunction(L, "getTractionCurveLateralRatio", GetTractionCurveLateralRatio);
			lua_classfunction(L, "getTractionSpringDeltaMax", GetTractionSpringDeltaMax);
			lua_classfunction(L, "getTractionSpringDeltaMaxRatio", GetTractionSpringDeltaMaxRatio);
			lua_classfunction(L, "getLowSpeedTractionLossMult", GetLowSpeedTractionLossMult);
			lua_classfunction(L, "getCamberStiffness", GetCamberStiffness);
			lua_classfunction(L, "getTractionBiasFront", GetTractionBiasFront);
			lua_classfunction(L, "getTractionBiasRear", GetTractionBiasRear);
			lua_classfunction(L, "getTractionLossMult", GetTractionLossMult);
			lua_classfunction(L, "getSuspensionForce", GetSuspensionForce);
			lua_classfunction(L, "getSuspensionCompDamp", GetSuspensionCompDamp);
			lua_classfunction(L, "getSuspensionReboundDamp", GetSuspensionReboundDamp);
			lua_classfunction(L, "getSuspensionUpperLimit", GetSuspensionUpperLimit);
			lua_classfunction(L, "getSuspensionLowerLimit", GetSuspensionLowerLimit);
			lua_classfunction(L, "getSuspensionRaise", GetSuspensionRaise);
			lua_classfunction(L, "getSuspensionBiasFront", GetSuspensionBiasFront);
			lua_classfunction(L, "getSuspensionBiasRear", GetSuspensionBiasRear);
			lua_classfunction(L, "getAntiRollBarForce", GetAntiRollBarForce);
			lua_classfunction(L, "getAntiRollBarBiasFront", GetAntiRollBarBiasFront);
			lua_classfunction(L, "getAntiRollBarBiasRear", GetAntiRollBarBiasRear);
			lua_classfunction(L, "getRollCentreHeightFront", GetRollCentreHeightFront);
			lua_classfunction(L, "getRollCentreHeightRear", GetRollCentreHeightRear);
			lua_classfunction(L, "getCollisionDamageMult", GetCollisionDamageMult);
			lua_classfunction(L, "getWeaponDamageMult", GetWeaponDamageMult);
			lua_classfunction(L, "getDeformationDamageMult", GetDeformationDamageMult);
			lua_classfunction(L, "getEngineDamageMult", GetEngineDamageMult);
			lua_classfunction(L, "getPetrolTankVolume", GetPetrolTankVolume);
			lua_classfunction(L, "getOilVolume", GetOilVolume);
			lua_classfunction(L, "getunkFloat5", GetunkFloat5);
			lua_classfunction(L, "getSeatOffsetDistX", GetSeatOffsetDistX);
			lua_classfunction(L, "getSeatOffsetDistY", GetSeatOffsetDistY);
			lua_classfunction(L, "getSeatOffsetDistZ", GetSeatOffsetDistZ);
			lua_classfunction(L, "getMonetaryValue", GetMonetaryValue);
			lua_classfunction(L, "getModelFlags", GetModelFlags);
			lua_classfunction(L, "getHandlingFlags", GetHandlingFlags);
			lua_classfunction(L, "getDamageFlags", GetDamageFlags);

			lua_classfunction(L, "setMass", SetMass);
			lua_classfunction(L, "setInitialDragCoeff", SetInitialDragCoeff);
			lua_classfunction(L, "setDownforceModifier", SetDownforceModifier);
			lua_classfunction(L, "setunkFloat1", SetunkFloat1);
			lua_classfunction(L, "setunkFloat2", SetunkFloat2);
			lua_classfunction(L, "setCentreOfMassOffset", SetCentreOfMassOffset);
			lua_classfunction(L, "setInertiaMultiplier", SetInertiaMultiplier);
			lua_classfunction(L, "setPercentSubmerged", SetPercentSubmerged);
			lua_classfunction(L, "setPercentSubmergedRatio", SetPercentSubmergedRatio);
			lua_classfunction(L, "setDriveBiasFront", SetDriveBiasFront);
			lua_classfunction(L, "setAcceleration", SetAcceleration);
			lua_classfunction(L, "setInitialDriveGears", SetInitialDriveGears);
			lua_classfunction(L, "setDriveInertia", SetDriveInertia);
			lua_classfunction(L, "setClutchChangeRateScaleUpShift", SetClutchChangeRateScaleUpShift);
			lua_classfunction(L, "setClutchChangeRateScaleDownShift", SetClutchChangeRateScaleDownShift);
			lua_classfunction(L, "setInitialDriveForce", SetInitialDriveForce);
			lua_classfunction(L, "setDriveMaxFlatVel", SetDriveMaxFlatVel);
			lua_classfunction(L, "setInitialDriveMaxFlatVel", SetInitialDriveMaxFlatVel);
			lua_classfunction(L, "setBrakeForce", SetBrakeForce);
			lua_classfunction(L, "setunkFloat4", SetunkFloat4);
			lua_classfunction(L, "setBrakeBiasFront", SetBrakeBiasFront);
			lua_classfunction(L, "setBrakeBiasRear", SetBrakeBiasRear);
			lua_classfunction(L, "setHandBrakeForce", SetHandBrakeForce);
			lua_classfunction(L, "setSteeringLock", SetSteeringLock);
			lua_classfunction(L, "setSteeringLockRatio", SetSteeringLockRatio);
			lua_classfunction(L, "setTractionCurveMax", SetTractionCurveMax);
			lua_classfunction(L, "setTractionCurveMaxRatio", SetTractionCurveMaxRatio);
			lua_classfunction(L, "setTractionCurveMin", SetTractionCurveMin);
			lua_classfunction(L, "setTractionCurveMinRatio", SetTractionCurveMinRatio);
			lua_classfunction(L, "setTractionCurveLateral", SetTractionCurveLateral);
			lua_classfunction(L, "setTractionCurveLateralRatio", SetTractionCurveLateralRatio);
			lua_classfunction(L, "setTractionSpringDeltaMax", SetTractionSpringDeltaMax);
			lua_classfunction(L, "setTractionSpringDeltaMaxRatio", SetTractionSpringDeltaMaxRatio);
			lua_classfunction(L, "setLowSpeedTractionLossMult", SetLowSpeedTractionLossMult);
			lua_classfunction(L, "setCamberStiffness", SetCamberStiffness);
			lua_classfunction(L, "setTractionBiasFront", SetTractionBiasFront);
			lua_classfunction(L, "setTractionBiasRear", SetTractionBiasRear);
			lua_classfunction(L, "setTractionLossMult", SetTractionLossMult);
			lua_classfunction(L, "setSuspensionForce", SetSuspensionForce);
			lua_classfunction(L, "setSuspensionCompDamp", SetSuspensionCompDamp);
			lua_classfunction(L, "setSuspensionReboundDamp", SetSuspensionReboundDamp);
			lua_classfunction(L, "setSuspensionUpperLimit", SetSuspensionUpperLimit);
			lua_classfunction(L, "setSuspensionLowerLimit", SetSuspensionLowerLimit);
			lua_classfunction(L, "setSuspensionRaise", SetSuspensionRaise);
			lua_classfunction(L, "setSuspensionBiasFront", SetSuspensionBiasFront);
			lua_classfunction(L, "setSuspensionBiasRear", SetSuspensionBiasRear);
			lua_classfunction(L, "setAntiRollBarForce", SetAntiRollBarForce);
			lua_classfunction(L, "setAntiRollBarBiasFront", SetAntiRollBarBiasFront);
			lua_classfunction(L, "setAntiRollBarBiasRear", SetAntiRollBarBiasRear);
			lua_classfunction(L, "setRollCentreHeightFront", SetRollCentreHeightFront);
			lua_classfunction(L, "setRollCentreHeightRear", SetRollCentreHeightRear);
			lua_classfunction(L, "setCollisionDamageMult", SetCollisionDamageMult);
			lua_classfunction(L, "setWeaponDamageMult", SetWeaponDamageMult);
			lua_classfunction(L, "setDeformationDamageMult", SetDeformationDamageMult);
			lua_classfunction(L, "setEngineDamageMult", SetEngineDamageMult);
			lua_classfunction(L, "setPetrolTankVolume", SetPetrolTankVolume);
			lua_classfunction(L, "setOilVolume", SetOilVolume);
			lua_classfunction(L, "setunkFloat5", SetunkFloat5);
			lua_classfunction(L, "setSeatOffsetDistX", SetSeatOffsetDistX);
			lua_classfunction(L, "setSeatOffsetDistY", SetSeatOffsetDistY);
			lua_classfunction(L, "setSeatOffsetDistZ", SetSeatOffsetDistZ);
			lua_classfunction(L, "setMonetaryValue", SetMonetaryValue);
			lua_classfunction(L, "setModelFlags", SetModelFlags);
			lua_classfunction(L, "setHandlingFlags", SetHandlingFlags);
			lua_classfunction(L, "setDamageFlags", SetDamageFlags);

			lua_classvariable(L, "mass", SetMass, GetMass);
			lua_classvariable(L, "initialDragCoeff", SetInitialDragCoeff, GetInitialDragCoeff);
			lua_classvariable(L, "downforceModifier", SetDownforceModifier, GetDownforceModifier);
			lua_classvariable(L, "unkFloat1", SetunkFloat1, GetunkFloat1);
			lua_classvariable(L, "unkFloat2", SetunkFloat2, GetunkFloat2);
			lua_classvariable(L, "centreOfMassOffset", SetCentreOfMassOffset, GetCentreOfMassOffset);
			lua_classvariable(L, "inertiaMultiplier", SetInertiaMultiplier, GetInertiaMultiplier);
			lua_classvariable(L, "percentSubmerged", SetPercentSubmerged, GetPercentSubmerged);
			lua_classvariable(L, "percentSubmergedRatio", SetPercentSubmergedRatio, GetPercentSubmergedRatio);
			lua_classvariable(L, "driveBiasFront", SetDriveBiasFront, GetDriveBiasFront);
			lua_classvariable(L, "acceleration", SetAcceleration, GetAcceleration);
			lua_classvariable(L, "initialDriveGears", SetInitialDriveGears, GetInitialDriveGears);
			lua_classvariable(L, "driveInertia", SetDriveInertia, GetDriveInertia);
			lua_classvariable(L, "clutchChangeRateScaleUpShift", SetClutchChangeRateScaleUpShift, GetClutchChangeRateScaleUpShift);
			lua_classvariable(L, "clutchChangeRateScaleDownShift", SetClutchChangeRateScaleDownShift, GetClutchChangeRateScaleDownShift);
			lua_classvariable(L, "initialDriveForce", SetInitialDriveForce, GetInitialDriveForce);
			lua_classvariable(L, "driveMaxFlatVel", SetDriveMaxFlatVel, GetDriveMaxFlatVel);
			lua_classvariable(L, "initialDriveMaxFlatVel", SetInitialDriveMaxFlatVel, GetInitialDriveMaxFlatVel);
			lua_classvariable(L, "brakeForce", SetBrakeForce, GetBrakeForce);
			lua_classvariable(L, "unkFloat4", SetunkFloat4, GetunkFloat4);
			lua_classvariable(L, "brakeBiasFront", SetBrakeBiasFront, GetBrakeBiasFront);
			lua_classvariable(L, "brakeBiasRear", SetBrakeBiasRear, GetBrakeBiasRear);
			lua_classvariable(L, "handBrakeForce", SetHandBrakeForce, GetHandBrakeForce);
			lua_classvariable(L, "steeringLock", SetSteeringLock, GetSteeringLock);
			lua_classvariable(L, "steeringLockRatio", SetSteeringLockRatio, GetSteeringLockRatio);
			lua_classvariable(L, "tractionCurveMax", SetTractionCurveMax, GetTractionCurveMax);
			lua_classvariable(L, "tractionCurveMaxRatio", SetTractionCurveMaxRatio, GetTractionCurveMaxRatio);
			lua_classvariable(L, "tractionCurveMin", SetTractionCurveMin, GetTractionCurveMin);
			lua_classvariable(L, "tractionCurveMinRatio", SetTractionCurveMinRatio, GetTractionCurveMinRatio);
			lua_classvariable(L, "tractionCurveLateral", SetTractionCurveLateral, GetTractionCurveLateral);
			lua_classvariable(L, "tractionCurveLateralRatio", SetTractionCurveLateralRatio, GetTractionCurveLateralRatio);
			lua_classvariable(L, "tractionSpringDeltaMax", SetTractionSpringDeltaMax, GetTractionSpringDeltaMax);
			lua_classvariable(L, "tractionSpringDeltaMaxRatio", SetTractionSpringDeltaMaxRatio, GetTractionSpringDeltaMaxRatio);
			lua_classvariable(L, "lowSpeedTractionLossMult", SetLowSpeedTractionLossMult, GetLowSpeedTractionLossMult);
			lua_classvariable(L, "camberStiffness", SetCamberStiffness, GetCamberStiffness);
			lua_classvariable(L, "tractionBiasFront", SetTractionBiasFront, GetTractionBiasFront);
			lua_classvariable(L, "tractionBiasRear", SetTractionBiasRear, GetTractionBiasRear);
			lua_classvariable(L, "tractionLossMult", SetTractionLossMult, GetTractionLossMult);
			lua_classvariable(L, "suspensionForce", SetSuspensionForce, GetSuspensionForce);
			lua_classvariable(L, "suspensionCompDamp", SetSuspensionCompDamp, GetSuspensionCompDamp);
			lua_classvariable(L, "suspensionReboundDamp", SetSuspensionReboundDamp, GetSuspensionReboundDamp);
			lua_classvariable(L, "suspensionUpperLimit", SetSuspensionUpperLimit, GetSuspensionUpperLimit);
			lua_classvariable(L, "suspensionLowerLimit", SetSuspensionLowerLimit, GetSuspensionLowerLimit);
			lua_classvariable(L, "suspensionRaise", SetSuspensionRaise, GetSuspensionRaise);
			lua_classvariable(L, "suspensionBiasFront", SetSuspensionBiasFront, GetSuspensionBiasFront);
			lua_classvariable(L, "suspensionBiasRear", SetSuspensionBiasRear, GetSuspensionBiasRear);
			lua_classvariable(L, "antiRollBarForce", SetAntiRollBarForce, GetAntiRollBarForce);
			lua_classvariable(L, "antiRollBarBiasFront", SetAntiRollBarBiasFront, GetAntiRollBarBiasFront);
			lua_classvariable(L, "antiRollBarBiasRear", SetAntiRollBarBiasRear, GetAntiRollBarBiasRear);
			lua_classvariable(L, "rollCentreHeightFront", SetRollCentreHeightFront, GetRollCentreHeightFront);
			lua_classvariable(L, "rollCentreHeightRear", SetRollCentreHeightRear, GetRollCentreHeightRear);
			lua_classvariable(L, "collisionDamageMult", SetCollisionDamageMult, GetCollisionDamageMult);
			lua_classvariable(L, "weaponDamageMult", SetWeaponDamageMult, GetWeaponDamageMult);
			lua_classvariable(L, "deformationDamageMult", SetDeformationDamageMult, GetDeformationDamageMult);
			lua_classvariable(L, "engineDamageMult", SetEngineDamageMult, GetEngineDamageMult);
			lua_classvariable(L, "petrolTankVolume", SetPetrolTankVolume, GetPetrolTankVolume);
			lua_classvariable(L, "oilVolume", SetOilVolume, GetOilVolume);
			lua_classvariable(L, "unkFloat5", SetunkFloat5, GetunkFloat5);
			lua_classvariable(L, "seatOffsetDistX", SetSeatOffsetDistX, GetSeatOffsetDistX);
			lua_classvariable(L, "seatOffsetDistY", SetSeatOffsetDistY, GetSeatOffsetDistY);
			lua_classvariable(L, "seatOffsetDistZ", SetSeatOffsetDistZ, GetSeatOffsetDistZ);
			lua_classvariable(L, "monetaryValue", SetMonetaryValue, GetMonetaryValue);
			lua_classvariable(L, "modelFlags", SetModelFlags, GetModelFlags);
			lua_classvariable(L, "handlingFlags", SetHandlingFlags, GetHandlingFlags);
			lua_classvariable(L, "damageFlags", SetDamageFlags, GetDamageFlags);
		}
		lua_endclass(L);

		DEBUG_INFO("HandlingData::Init ...done");
	}

	int HandlingData::GetHandlingData(lua_State* L)
	{
		uint32_t modelHash;

		ArgumentReader argReader(L);
		argReader.ReadNumber(modelHash);

		if (argReader.HasAnyError())
		{
			argReader.GetErrorMessages();
			return 0;
		}

		auto handlingData = Core->GetHandlingData(modelHash);
		if (handlingData.IsEmpty())
		{
			lua_pushnil(L);
		}
		else {
			lua_pushhandlingdata(L, handlingData);
		}

		return 1;
	}

	#define HANDLING_GET_DEFINE(PUSH, GET) \
	int HandlingData::GET(lua_State* L) { alt::IHandlingData* handlingData; ArgumentReader argReader(L); argReader.ReadUserData(handlingData); if (argReader.HasAnyError()) { argReader.GetErrorMessages(); return 0; } PUSH(L, handlingData->GET()); return 1;}

	#define HANDLING_SET_DEFINE(TYPE, READ, SET) \
	int HandlingData::SET(lua_State* L) { alt::IHandlingData* handlingData; TYPE value; ArgumentReader argReader(L); argReader.ReadUserData(handlingData); argReader.READ(value); if (argReader.HasAnyError()) { argReader.GetErrorMessages(); return 0; } handlingData->SET(value); return 0; }

	HANDLING_GET_DEFINE(lua_pushnumber, GetHandlingNameHash)
	HANDLING_GET_DEFINE(lua_pushnumber, GetMass)
	HANDLING_GET_DEFINE(lua_pushnumber, GetInitialDragCoeff)
	HANDLING_GET_DEFINE(lua_pushnumber, GetDownforceModifier)
	HANDLING_GET_DEFINE(lua_pushnumber, GetunkFloat1)
	HANDLING_GET_DEFINE(lua_pushnumber, GetunkFloat2)
	HANDLING_GET_DEFINE(lua_pushvector3, GetCentreOfMassOffset)
	HANDLING_GET_DEFINE(lua_pushvector3, GetInertiaMultiplier)
	HANDLING_GET_DEFINE(lua_pushnumber, GetPercentSubmerged)
	HANDLING_GET_DEFINE(lua_pushnumber, GetPercentSubmergedRatio)
	HANDLING_GET_DEFINE(lua_pushnumber, GetDriveBiasFront)
	HANDLING_GET_DEFINE(lua_pushnumber, GetAcceleration)
	HANDLING_GET_DEFINE(lua_pushnumber, GetInitialDriveGears)
	HANDLING_GET_DEFINE(lua_pushnumber, GetDriveInertia)
	HANDLING_GET_DEFINE(lua_pushnumber, GetClutchChangeRateScaleUpShift)
	HANDLING_GET_DEFINE(lua_pushnumber, GetClutchChangeRateScaleDownShift)
	HANDLING_GET_DEFINE(lua_pushnumber, GetInitialDriveForce)
	HANDLING_GET_DEFINE(lua_pushnumber, GetDriveMaxFlatVel)
	HANDLING_GET_DEFINE(lua_pushnumber, GetInitialDriveMaxFlatVel)
	HANDLING_GET_DEFINE(lua_pushnumber, GetBrakeForce)
	HANDLING_GET_DEFINE(lua_pushnumber, GetunkFloat4)
	HANDLING_GET_DEFINE(lua_pushnumber, GetBrakeBiasFront)
	HANDLING_GET_DEFINE(lua_pushnumber, GetBrakeBiasRear)
	HANDLING_GET_DEFINE(lua_pushnumber, GetHandBrakeForce)
	HANDLING_GET_DEFINE(lua_pushnumber, GetSteeringLock)
	HANDLING_GET_DEFINE(lua_pushnumber, GetSteeringLockRatio)
	HANDLING_GET_DEFINE(lua_pushnumber, GetTractionCurveMax)
	HANDLING_GET_DEFINE(lua_pushnumber, GetTractionCurveMaxRatio)
	HANDLING_GET_DEFINE(lua_pushnumber, GetTractionCurveMin)
	HANDLING_GET_DEFINE(lua_pushnumber, GetTractionCurveMinRatio)
	HANDLING_GET_DEFINE(lua_pushnumber, GetTractionCurveLateral)
	HANDLING_GET_DEFINE(lua_pushnumber, GetTractionCurveLateralRatio)
	HANDLING_GET_DEFINE(lua_pushnumber, GetTractionSpringDeltaMax)
	HANDLING_GET_DEFINE(lua_pushnumber, GetTractionSpringDeltaMaxRatio)
	HANDLING_GET_DEFINE(lua_pushnumber, GetLowSpeedTractionLossMult)
	HANDLING_GET_DEFINE(lua_pushnumber, GetCamberStiffness)
	HANDLING_GET_DEFINE(lua_pushnumber, GetTractionBiasFront)
	HANDLING_GET_DEFINE(lua_pushnumber, GetTractionBiasRear)
	HANDLING_GET_DEFINE(lua_pushnumber, GetTractionLossMult)
	HANDLING_GET_DEFINE(lua_pushnumber, GetSuspensionForce)
	HANDLING_GET_DEFINE(lua_pushnumber, GetSuspensionCompDamp)
	HANDLING_GET_DEFINE(lua_pushnumber, GetSuspensionReboundDamp)
	HANDLING_GET_DEFINE(lua_pushnumber, GetSuspensionUpperLimit)
	HANDLING_GET_DEFINE(lua_pushnumber, GetSuspensionLowerLimit)
	HANDLING_GET_DEFINE(lua_pushnumber, GetSuspensionRaise)
	HANDLING_GET_DEFINE(lua_pushnumber, GetSuspensionBiasFront)
	HANDLING_GET_DEFINE(lua_pushnumber, GetSuspensionBiasRear)
	HANDLING_GET_DEFINE(lua_pushnumber, GetAntiRollBarForce)
	HANDLING_GET_DEFINE(lua_pushnumber, GetAntiRollBarBiasFront)
	HANDLING_GET_DEFINE(lua_pushnumber, GetAntiRollBarBiasRear)
	HANDLING_GET_DEFINE(lua_pushnumber, GetRollCentreHeightFront)
	HANDLING_GET_DEFINE(lua_pushnumber, GetRollCentreHeightRear)
	HANDLING_GET_DEFINE(lua_pushnumber, GetCollisionDamageMult)
	HANDLING_GET_DEFINE(lua_pushnumber, GetWeaponDamageMult)
	HANDLING_GET_DEFINE(lua_pushnumber, GetDeformationDamageMult)
	HANDLING_GET_DEFINE(lua_pushnumber, GetEngineDamageMult)
	HANDLING_GET_DEFINE(lua_pushnumber, GetPetrolTankVolume)
	HANDLING_GET_DEFINE(lua_pushnumber, GetOilVolume)
	HANDLING_GET_DEFINE(lua_pushnumber, GetunkFloat5)
	HANDLING_GET_DEFINE(lua_pushnumber, GetSeatOffsetDistX)
	HANDLING_GET_DEFINE(lua_pushnumber, GetSeatOffsetDistY)
	HANDLING_GET_DEFINE(lua_pushnumber, GetSeatOffsetDistZ)
	HANDLING_GET_DEFINE(lua_pushnumber, GetMonetaryValue)
	HANDLING_GET_DEFINE(lua_pushnumber, GetModelFlags)
	HANDLING_GET_DEFINE(lua_pushnumber, GetHandlingFlags)
	HANDLING_GET_DEFINE(lua_pushnumber, GetDamageFlags)


	HANDLING_SET_DEFINE(float, ReadNumber, SetMass)
	HANDLING_SET_DEFINE(float, ReadNumber, SetInitialDragCoeff)
	HANDLING_SET_DEFINE(float, ReadNumber, SetDownforceModifier)
	HANDLING_SET_DEFINE(float, ReadNumber, SetunkFloat1)
	HANDLING_SET_DEFINE(float, ReadNumber, SetunkFloat2)
	HANDLING_SET_DEFINE(Vector3fp, ReadVector, SetCentreOfMassOffset)
	HANDLING_SET_DEFINE(Vector3fp, ReadVector, SetInertiaMultiplier)
	HANDLING_SET_DEFINE(float, ReadNumber, SetPercentSubmerged)
	HANDLING_SET_DEFINE(float, ReadNumber, SetPercentSubmergedRatio)
	HANDLING_SET_DEFINE(float, ReadNumber, SetDriveBiasFront)
	HANDLING_SET_DEFINE(float, ReadNumber, SetAcceleration)
	HANDLING_SET_DEFINE(float, ReadNumber, SetInitialDriveGears)
	HANDLING_SET_DEFINE(float, ReadNumber, SetDriveInertia)
	HANDLING_SET_DEFINE(float, ReadNumber, SetClutchChangeRateScaleUpShift)
	HANDLING_SET_DEFINE(float, ReadNumber, SetClutchChangeRateScaleDownShift)
	HANDLING_SET_DEFINE(float, ReadNumber, SetInitialDriveForce)
	HANDLING_SET_DEFINE(float, ReadNumber, SetDriveMaxFlatVel)
	HANDLING_SET_DEFINE(float, ReadNumber, SetInitialDriveMaxFlatVel)
	HANDLING_SET_DEFINE(float, ReadNumber, SetBrakeForce)
	HANDLING_SET_DEFINE(float, ReadNumber, SetunkFloat4)
	HANDLING_SET_DEFINE(float, ReadNumber, SetBrakeBiasFront)
	HANDLING_SET_DEFINE(float, ReadNumber, SetBrakeBiasRear)
	HANDLING_SET_DEFINE(float, ReadNumber, SetHandBrakeForce)
	HANDLING_SET_DEFINE(float, ReadNumber, SetSteeringLock)
	HANDLING_SET_DEFINE(float, ReadNumber, SetSteeringLockRatio)
	HANDLING_SET_DEFINE(float, ReadNumber, SetTractionCurveMax)
	HANDLING_SET_DEFINE(float, ReadNumber, SetTractionCurveMaxRatio)
	HANDLING_SET_DEFINE(float, ReadNumber, SetTractionCurveMin)
	HANDLING_SET_DEFINE(float, ReadNumber, SetTractionCurveMinRatio)
	HANDLING_SET_DEFINE(float, ReadNumber, SetTractionCurveLateral)
	HANDLING_SET_DEFINE(float, ReadNumber, SetTractionCurveLateralRatio)
	HANDLING_SET_DEFINE(float, ReadNumber, SetTractionSpringDeltaMax)
	HANDLING_SET_DEFINE(float, ReadNumber, SetTractionSpringDeltaMaxRatio)
	HANDLING_SET_DEFINE(float, ReadNumber, SetLowSpeedTractionLossMult)
	HANDLING_SET_DEFINE(float, ReadNumber, SetCamberStiffness)
	HANDLING_SET_DEFINE(float, ReadNumber, SetTractionBiasFront)
	HANDLING_SET_DEFINE(float, ReadNumber, SetTractionBiasRear)
	HANDLING_SET_DEFINE(float, ReadNumber, SetTractionLossMult)
	HANDLING_SET_DEFINE(float, ReadNumber, SetSuspensionForce)
	HANDLING_SET_DEFINE(float, ReadNumber, SetSuspensionCompDamp)
	HANDLING_SET_DEFINE(float, ReadNumber, SetSuspensionReboundDamp)
	HANDLING_SET_DEFINE(float, ReadNumber, SetSuspensionUpperLimit)
	HANDLING_SET_DEFINE(float, ReadNumber, SetSuspensionLowerLimit)
	HANDLING_SET_DEFINE(float, ReadNumber, SetSuspensionRaise)
	HANDLING_SET_DEFINE(float, ReadNumber, SetSuspensionBiasFront)
	HANDLING_SET_DEFINE(float, ReadNumber, SetSuspensionBiasRear)
	HANDLING_SET_DEFINE(float, ReadNumber, SetAntiRollBarForce)
	HANDLING_SET_DEFINE(float, ReadNumber, SetAntiRollBarBiasFront)
	HANDLING_SET_DEFINE(float, ReadNumber, SetAntiRollBarBiasRear)
	HANDLING_SET_DEFINE(float, ReadNumber, SetRollCentreHeightFront)
	HANDLING_SET_DEFINE(float, ReadNumber, SetRollCentreHeightRear)
	HANDLING_SET_DEFINE(float, ReadNumber, SetCollisionDamageMult)
	HANDLING_SET_DEFINE(float, ReadNumber, SetWeaponDamageMult)
	HANDLING_SET_DEFINE(float, ReadNumber, SetDeformationDamageMult)
	HANDLING_SET_DEFINE(float, ReadNumber, SetEngineDamageMult)
	HANDLING_SET_DEFINE(float, ReadNumber, SetPetrolTankVolume)
	HANDLING_SET_DEFINE(float, ReadNumber, SetOilVolume)
	HANDLING_SET_DEFINE(float, ReadNumber, SetunkFloat5)
	HANDLING_SET_DEFINE(float, ReadNumber, SetSeatOffsetDistX)
	HANDLING_SET_DEFINE(float, ReadNumber, SetSeatOffsetDistY)
	HANDLING_SET_DEFINE(float, ReadNumber, SetSeatOffsetDistZ)
	HANDLING_SET_DEFINE(float, ReadNumber, SetMonetaryValue)
	HANDLING_SET_DEFINE(float, ReadNumber, SetModelFlags)
	HANDLING_SET_DEFINE(float, ReadNumber, SetHandlingFlags)
	HANDLING_SET_DEFINE(float, ReadNumber, SetDamageFlags)
}
#endif