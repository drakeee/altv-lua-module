#include <Main.h>

#ifdef ALT_CLIENT_API
namespace lua::Class
{
	const char* HandlingData::ClassName = "HandlingData";
	void HandlingData::Init(lua_State* L)
	{
		DEBUG_INFO("HandlingData::Init");

		lua_globalfunction(L, "getHandlingData", GetHandlingData);
		lua_globalfunction(L, "getHandlingHandlingNameHash", GetHandlingNameHash);
		lua_globalfunction(L, "getHandlingMass", GetMass);
		lua_globalfunction(L, "getHandlingInitialDragCoeff", GetInitialDragCoeff);
		lua_globalfunction(L, "getHandlingDownforceModifier", GetDownforceModifier);
		lua_globalfunction(L, "getHandlingunkFloat1", GetunkFloat1);
		lua_globalfunction(L, "getHandlingunkFloat2", GetunkFloat2);
		lua_globalfunction(L, "getHandlingCentreOfMassOffset", GetCentreOfMassOffset);
		lua_globalfunction(L, "getHandlingInertiaMultiplier", GetInertiaMultiplier);
		lua_globalfunction(L, "getHandlingPercentSubmerged", GetPercentSubmerged);
		lua_globalfunction(L, "getHandlingPercentSubmergedRatio", GetPercentSubmergedRatio);
		lua_globalfunction(L, "getHandlingDriveBiasFront", GetDriveBiasFront);
		lua_globalfunction(L, "getHandlingAcceleration", GetAcceleration);
		lua_globalfunction(L, "getHandlingInitialDriveGears", GetInitialDriveGears);
		lua_globalfunction(L, "getHandlingDriveInertia", GetDriveInertia);
		lua_globalfunction(L, "getHandlingClutchChangeRateScaleUpShift", GetClutchChangeRateScaleUpShift);
		lua_globalfunction(L, "getHandlingClutchChangeRateScaleDownShift", GetClutchChangeRateScaleDownShift);
		lua_globalfunction(L, "getHandlingInitialDriveForce", GetInitialDriveForce);
		lua_globalfunction(L, "getHandlingDriveMaxFlatVel", GetDriveMaxFlatVel);
		lua_globalfunction(L, "getHandlingInitialDriveMaxFlatVel", GetInitialDriveMaxFlatVel);
		lua_globalfunction(L, "getHandlingBrakeForce", GetBrakeForce);
		lua_globalfunction(L, "getHandlingunkFloat4", GetunkFloat4);
		lua_globalfunction(L, "getHandlingBrakeBiasFront", GetBrakeBiasFront);
		lua_globalfunction(L, "getHandlingBrakeBiasRear", GetBrakeBiasRear);
		lua_globalfunction(L, "getHandlingHandBrakeForce", GetHandBrakeForce);
		lua_globalfunction(L, "getHandlingSteeringLock", GetSteeringLock);
		lua_globalfunction(L, "getHandlingSteeringLockRatio", GetSteeringLockRatio);
		lua_globalfunction(L, "getHandlingTractionCurveMax", GetTractionCurveMax);
		lua_globalfunction(L, "getHandlingTractionCurveMaxRatio", GetTractionCurveMaxRatio);
		lua_globalfunction(L, "getHandlingTractionCurveMin", GetTractionCurveMin);
		lua_globalfunction(L, "getHandlingTractionCurveMinRatio", GetTractionCurveMinRatio);
		lua_globalfunction(L, "getHandlingTractionCurveLateral", GetTractionCurveLateral);
		lua_globalfunction(L, "getHandlingTractionCurveLateralRatio", GetTractionCurveLateralRatio);
		lua_globalfunction(L, "getHandlingTractionSpringDeltaMax", GetTractionSpringDeltaMax);
		lua_globalfunction(L, "getHandlingTractionSpringDeltaMaxRatio", GetTractionSpringDeltaMaxRatio);
		lua_globalfunction(L, "getHandlingLowSpeedTractionLossMult", GetLowSpeedTractionLossMult);
		lua_globalfunction(L, "getHandlingCamberStiffness", GetCamberStiffness);
		lua_globalfunction(L, "getHandlingTractionBiasFront", GetTractionBiasFront);
		lua_globalfunction(L, "getHandlingTractionBiasRear", GetTractionBiasRear);
		lua_globalfunction(L, "getHandlingTractionLossMult", GetTractionLossMult);
		lua_globalfunction(L, "getHandlingSuspensionForce", GetSuspensionForce);
		lua_globalfunction(L, "getHandlingSuspensionCompDamp", GetSuspensionCompDamp);
		lua_globalfunction(L, "getHandlingSuspensionReboundDamp", GetSuspensionReboundDamp);
		lua_globalfunction(L, "getHandlingSuspensionUpperLimit", GetSuspensionUpperLimit);
		lua_globalfunction(L, "getHandlingSuspensionLowerLimit", GetSuspensionLowerLimit);
		lua_globalfunction(L, "getHandlingSuspensionRaise", GetSuspensionRaise);
		lua_globalfunction(L, "getHandlingSuspensionBiasFront", GetSuspensionBiasFront);
		lua_globalfunction(L, "getHandlingSuspensionBiasRear", GetSuspensionBiasRear);
		lua_globalfunction(L, "getHandlingAntiRollBarForce", GetAntiRollBarForce);
		lua_globalfunction(L, "getHandlingAntiRollBarBiasFront", GetAntiRollBarBiasFront);
		lua_globalfunction(L, "getHandlingAntiRollBarBiasRear", GetAntiRollBarBiasRear);
		lua_globalfunction(L, "getHandlingRollCentreHeightFront", GetRollCentreHeightFront);
		lua_globalfunction(L, "getHandlingRollCentreHeightRear", GetRollCentreHeightRear);
		lua_globalfunction(L, "getHandlingCollisionDamageMult", GetCollisionDamageMult);
		lua_globalfunction(L, "getHandlingWeaponDamageMult", GetWeaponDamageMult);
		lua_globalfunction(L, "getHandlingDeformationDamageMult", GetDeformationDamageMult);
		lua_globalfunction(L, "getHandlingEngineDamageMult", GetEngineDamageMult);
		lua_globalfunction(L, "getHandlingPetrolTankVolume", GetPetrolTankVolume);
		lua_globalfunction(L, "getHandlingOilVolume", GetOilVolume);
		lua_globalfunction(L, "getHandlingunkFloat5", GetunkFloat5);
		lua_globalfunction(L, "getHandlingSeatOffsetDistX", GetSeatOffsetDistX);
		lua_globalfunction(L, "getHandlingSeatOffsetDistY", GetSeatOffsetDistY);
		lua_globalfunction(L, "getHandlingSeatOffsetDistZ", GetSeatOffsetDistZ);
		lua_globalfunction(L, "getHandlingMonetaryValue", GetMonetaryValue);
		lua_globalfunction(L, "getHandlingModelFlags", GetModelFlags);
		lua_globalfunction(L, "getHandlingHandlingFlags", GetHandlingFlags);
		lua_globalfunction(L, "getHandlingDamageFlags", GetDamageFlags);

		lua_globalfunction(L, "setHandlingMass", SetMass);
		lua_globalfunction(L, "setHandlingInitialDragCoeff", SetInitialDragCoeff);
		lua_globalfunction(L, "setHandlingDownforceModifier", SetDownforceModifier);
		lua_globalfunction(L, "setHandlingunkFloat1", SetunkFloat1);
		lua_globalfunction(L, "setHandlingunkFloat2", SetunkFloat2);
		lua_globalfunction(L, "setHandlingCentreOfMassOffset", SetCentreOfMassOffset);
		lua_globalfunction(L, "setHandlingInertiaMultiplier", SetInertiaMultiplier);
		lua_globalfunction(L, "setHandlingPercentSubmerged", SetPercentSubmerged);
		lua_globalfunction(L, "setHandlingPercentSubmergedRatio", SetPercentSubmergedRatio);
		lua_globalfunction(L, "setHandlingDriveBiasFront", SetDriveBiasFront);
		lua_globalfunction(L, "setHandlingAcceleration", SetAcceleration);
		lua_globalfunction(L, "setHandlingInitialDriveGears", SetInitialDriveGears);
		lua_globalfunction(L, "setHandlingDriveInertia", SetDriveInertia);
		lua_globalfunction(L, "setHandlingClutchChangeRateScaleUpShift", SetClutchChangeRateScaleUpShift);
		lua_globalfunction(L, "setHandlingClutchChangeRateScaleDownShift", SetClutchChangeRateScaleDownShift);
		lua_globalfunction(L, "setHandlingInitialDriveForce", SetInitialDriveForce);
		lua_globalfunction(L, "setHandlingDriveMaxFlatVel", SetDriveMaxFlatVel);
		lua_globalfunction(L, "setHandlingInitialDriveMaxFlatVel", SetInitialDriveMaxFlatVel);
		lua_globalfunction(L, "setHandlingBrakeForce", SetBrakeForce);
		lua_globalfunction(L, "setHandlingunkFloat4", SetunkFloat4);
		lua_globalfunction(L, "setHandlingBrakeBiasFront", SetBrakeBiasFront);
		lua_globalfunction(L, "setHandlingBrakeBiasRear", SetBrakeBiasRear);
		lua_globalfunction(L, "setHandlingHandBrakeForce", SetHandBrakeForce);
		lua_globalfunction(L, "setHandlingSteeringLock", SetSteeringLock);
		lua_globalfunction(L, "setHandlingSteeringLockRatio", SetSteeringLockRatio);
		lua_globalfunction(L, "setHandlingTractionCurveMax", SetTractionCurveMax);
		lua_globalfunction(L, "setHandlingTractionCurveMaxRatio", SetTractionCurveMaxRatio);
		lua_globalfunction(L, "setHandlingTractionCurveMin", SetTractionCurveMin);
		lua_globalfunction(L, "setHandlingTractionCurveMinRatio", SetTractionCurveMinRatio);
		lua_globalfunction(L, "setHandlingTractionCurveLateral", SetTractionCurveLateral);
		lua_globalfunction(L, "setHandlingTractionCurveLateralRatio", SetTractionCurveLateralRatio);
		lua_globalfunction(L, "setHandlingTractionSpringDeltaMax", SetTractionSpringDeltaMax);
		lua_globalfunction(L, "setHandlingTractionSpringDeltaMaxRatio", SetTractionSpringDeltaMaxRatio);
		lua_globalfunction(L, "setHandlingLowSpeedTractionLossMult", SetLowSpeedTractionLossMult);
		lua_globalfunction(L, "setHandlingCamberStiffness", SetCamberStiffness);
		lua_globalfunction(L, "setHandlingTractionBiasFront", SetTractionBiasFront);
		lua_globalfunction(L, "setHandlingTractionBiasRear", SetTractionBiasRear);
		lua_globalfunction(L, "setHandlingTractionLossMult", SetTractionLossMult);
		lua_globalfunction(L, "setHandlingSuspensionForce", SetSuspensionForce);
		lua_globalfunction(L, "setHandlingSuspensionCompDamp", SetSuspensionCompDamp);
		lua_globalfunction(L, "setHandlingSuspensionReboundDamp", SetSuspensionReboundDamp);
		lua_globalfunction(L, "setHandlingSuspensionUpperLimit", SetSuspensionUpperLimit);
		lua_globalfunction(L, "setHandlingSuspensionLowerLimit", SetSuspensionLowerLimit);
		lua_globalfunction(L, "setHandlingSuspensionRaise", SetSuspensionRaise);
		lua_globalfunction(L, "setHandlingSuspensionBiasFront", SetSuspensionBiasFront);
		lua_globalfunction(L, "setHandlingSuspensionBiasRear", SetSuspensionBiasRear);
		lua_globalfunction(L, "setHandlingAntiRollBarForce", SetAntiRollBarForce);
		lua_globalfunction(L, "setHandlingAntiRollBarBiasFront", SetAntiRollBarBiasFront);
		lua_globalfunction(L, "setHandlingAntiRollBarBiasRear", SetAntiRollBarBiasRear);
		lua_globalfunction(L, "setHandlingRollCentreHeightFront", SetRollCentreHeightFront);
		lua_globalfunction(L, "setHandlingRollCentreHeightRear", SetRollCentreHeightRear);
		lua_globalfunction(L, "setHandlingCollisionDamageMult", SetCollisionDamageMult);
		lua_globalfunction(L, "setHandlingWeaponDamageMult", SetWeaponDamageMult);
		lua_globalfunction(L, "setHandlingDeformationDamageMult", SetDeformationDamageMult);
		lua_globalfunction(L, "setHandlingEngineDamageMult", SetEngineDamageMult);
		lua_globalfunction(L, "setHandlingPetrolTankVolume", SetPetrolTankVolume);
		lua_globalfunction(L, "setHandlingOilVolume", SetOilVolume);
		lua_globalfunction(L, "setHandlingunkFloat5", SetunkFloat5);
		lua_globalfunction(L, "setHandlingSeatOffsetDistX", SetSeatOffsetDistX);
		lua_globalfunction(L, "setHandlingSeatOffsetDistY", SetSeatOffsetDistY);
		lua_globalfunction(L, "setHandlingSeatOffsetDistZ", SetSeatOffsetDistZ);
		lua_globalfunction(L, "setHandlingMonetaryValue", SetMonetaryValue);
		lua_globalfunction(L, "setHandlingModelFlags", SetModelFlags);
		lua_globalfunction(L, "setHandlingHandlingFlags", SetHandlingFlags);
		lua_globalfunction(L, "setHandlingDamageFlags", SetDamageFlags);

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

			lua_classvariable(L, "mass", "setMass", "getMass");
			lua_classvariable(L, "initialDragCoeff", "setInitialDragCoeff", "getInitialDragCoeff");
			lua_classvariable(L, "downforceModifier", "setDownforceModifier", "getDownforceModifier");
			lua_classvariable(L, "unkFloat1", "setunkFloat1", "getunkFloat1");
			lua_classvariable(L, "unkFloat2", "setunkFloat2", "getunkFloat2");
			lua_classvariable(L, "centreOfMassOffset", "setCentreOfMassOffset", "getCentreOfMassOffset");
			lua_classvariable(L, "inertiaMultiplier", "setInertiaMultiplier", "getInertiaMultiplier");
			lua_classvariable(L, "percentSubmerged", "setPercentSubmerged", "getPercentSubmerged");
			lua_classvariable(L, "percentSubmergedRatio", "setPercentSubmergedRatio", "getPercentSubmergedRatio");
			lua_classvariable(L, "driveBiasFront", "setDriveBiasFront", "getDriveBiasFront");
			lua_classvariable(L, "acceleration", "setAcceleration", "getAcceleration");
			lua_classvariable(L, "initialDriveGears", "setInitialDriveGears", "getInitialDriveGears");
			lua_classvariable(L, "driveInertia", "setDriveInertia", "getDriveInertia");
			lua_classvariable(L, "clutchChangeRateScaleUpShift", "setClutchChangeRateScaleUpShift", "getClutchChangeRateScaleUpShift");
			lua_classvariable(L, "clutchChangeRateScaleDownShift", "setClutchChangeRateScaleDownShift", "getClutchChangeRateScaleDownShift");
			lua_classvariable(L, "initialDriveForce", "setInitialDriveForce", "getInitialDriveForce");
			lua_classvariable(L, "driveMaxFlatVel", "setDriveMaxFlatVel", "getDriveMaxFlatVel");
			lua_classvariable(L, "initialDriveMaxFlatVel", "setInitialDriveMaxFlatVel", "getInitialDriveMaxFlatVel");
			lua_classvariable(L, "brakeForce", "setBrakeForce", "getBrakeForce");
			lua_classvariable(L, "unkFloat4", "setunkFloat4", "getunkFloat4");
			lua_classvariable(L, "brakeBiasFront", "setBrakeBiasFront", "getBrakeBiasFront");
			lua_classvariable(L, "brakeBiasRear", "setBrakeBiasRear", "getBrakeBiasRear");
			lua_classvariable(L, "handBrakeForce", "setHandBrakeForce", "getHandBrakeForce");
			lua_classvariable(L, "steeringLock", "setSteeringLock", "getSteeringLock");
			lua_classvariable(L, "steeringLockRatio", "setSteeringLockRatio", "getSteeringLockRatio");
			lua_classvariable(L, "tractionCurveMax", "setTractionCurveMax", "getTractionCurveMax");
			lua_classvariable(L, "tractionCurveMaxRatio", "setTractionCurveMaxRatio", "getTractionCurveMaxRatio");
			lua_classvariable(L, "tractionCurveMin", "setTractionCurveMin", "getTractionCurveMin");
			lua_classvariable(L, "tractionCurveMinRatio", "setTractionCurveMinRatio", "getTractionCurveMinRatio");
			lua_classvariable(L, "tractionCurveLateral", "setTractionCurveLateral", "getTractionCurveLateral");
			lua_classvariable(L, "tractionCurveLateralRatio", "setTractionCurveLateralRatio", "getTractionCurveLateralRatio");
			lua_classvariable(L, "tractionSpringDeltaMax", "setTractionSpringDeltaMax", "getTractionSpringDeltaMax");
			lua_classvariable(L, "tractionSpringDeltaMaxRatio", "setTractionSpringDeltaMaxRatio", "getTractionSpringDeltaMaxRatio");
			lua_classvariable(L, "lowSpeedTractionLossMult", "setLowSpeedTractionLossMult", "getLowSpeedTractionLossMult");
			lua_classvariable(L, "camberStiffness", "setCamberStiffness", "getCamberStiffness");
			lua_classvariable(L, "tractionBiasFront", "setTractionBiasFront", "getTractionBiasFront");
			lua_classvariable(L, "tractionBiasRear", "setTractionBiasRear", "getTractionBiasRear");
			lua_classvariable(L, "tractionLossMult", "setTractionLossMult", "getTractionLossMult");
			lua_classvariable(L, "suspensionForce", "setSuspensionForce", "getSuspensionForce");
			lua_classvariable(L, "suspensionCompDamp", "setSuspensionCompDamp", "getSuspensionCompDamp");
			lua_classvariable(L, "suspensionReboundDamp", "setSuspensionReboundDamp", "getSuspensionReboundDamp");
			lua_classvariable(L, "suspensionUpperLimit", "setSuspensionUpperLimit", "getSuspensionUpperLimit");
			lua_classvariable(L, "suspensionLowerLimit", "setSuspensionLowerLimit", "getSuspensionLowerLimit");
			lua_classvariable(L, "suspensionRaise", "setSuspensionRaise", "getSuspensionRaise");
			lua_classvariable(L, "suspensionBiasFront", "setSuspensionBiasFront", "getSuspensionBiasFront");
			lua_classvariable(L, "suspensionBiasRear", "setSuspensionBiasRear", "getSuspensionBiasRear");
			lua_classvariable(L, "antiRollBarForce", "setAntiRollBarForce", "getAntiRollBarForce");
			lua_classvariable(L, "antiRollBarBiasFront", "setAntiRollBarBiasFront", "getAntiRollBarBiasFront");
			lua_classvariable(L, "antiRollBarBiasRear", "setAntiRollBarBiasRear", "getAntiRollBarBiasRear");
			lua_classvariable(L, "rollCentreHeightFront", "setRollCentreHeightFront", "getRollCentreHeightFront");
			lua_classvariable(L, "rollCentreHeightRear", "setRollCentreHeightRear", "getRollCentreHeightRear");
			lua_classvariable(L, "collisionDamageMult", "setCollisionDamageMult", "getCollisionDamageMult");
			lua_classvariable(L, "weaponDamageMult", "setWeaponDamageMult", "getWeaponDamageMult");
			lua_classvariable(L, "deformationDamageMult", "setDeformationDamageMult", "getDeformationDamageMult");
			lua_classvariable(L, "engineDamageMult", "setEngineDamageMult", "getEngineDamageMult");
			lua_classvariable(L, "petrolTankVolume", "setPetrolTankVolume", "getPetrolTankVolume");
			lua_classvariable(L, "oilVolume", "setOilVolume", "getOilVolume");
			lua_classvariable(L, "unkFloat5", "setunkFloat5", "getunkFloat5");
			lua_classvariable(L, "seatOffsetDistX", "setSeatOffsetDistX", "getSeatOffsetDistX");
			lua_classvariable(L, "seatOffsetDistY", "setSeatOffsetDistY", "getSeatOffsetDistY");
			lua_classvariable(L, "seatOffsetDistZ", "setSeatOffsetDistZ", "getSeatOffsetDistZ");
			lua_classvariable(L, "monetaryValue", "setMonetaryValue", "getMonetaryValue");
			lua_classvariable(L, "modelFlags", "setModelFlags", "getModelFlags");
			lua_classvariable(L, "handlingFlags", "setHandlingFlags", "getHandlingFlags");
			lua_classvariable(L, "damageFlags", "setDamageFlags", "getDamageFlags");
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