#pragma once

#include <Main.h>

#ifdef ALT_CLIENT_API
namespace lua::Class
{
    class HandlingData
    {
    public:
	    static const char* ClassName;
	    static void Init(lua_State* L);

    private:
        static int GetHandlingData(lua_State* L);
        static int GetHandlingNameHash(lua_State* L);
        static int GetMass(lua_State* L);
        static int GetInitialDragCoeff(lua_State* L);
        static int GetDownforceModifier(lua_State* L);
        static int GetunkFloat1(lua_State* L);
        static int GetunkFloat2(lua_State* L);
        static int GetCentreOfMassOffset(lua_State* L);
        static int GetInertiaMultiplier(lua_State* L);
        static int GetPercentSubmerged(lua_State* L);
        static int GetPercentSubmergedRatio(lua_State* L);
        static int GetDriveBiasFront(lua_State* L);
        static int GetAcceleration(lua_State* L);
        static int GetInitialDriveGears(lua_State* L);
        static int GetDriveInertia(lua_State* L);
        static int GetClutchChangeRateScaleUpShift(lua_State* L);
        static int GetClutchChangeRateScaleDownShift(lua_State* L);
        static int GetInitialDriveForce(lua_State* L);
        static int GetDriveMaxFlatVel(lua_State* L);
        static int GetInitialDriveMaxFlatVel(lua_State* L);
        static int GetBrakeForce(lua_State* L);
        static int GetunkFloat4(lua_State* L);
        static int GetBrakeBiasFront(lua_State* L);
        static int GetBrakeBiasRear(lua_State* L);
        static int GetHandBrakeForce(lua_State* L);
        static int GetSteeringLock(lua_State* L);
        static int GetSteeringLockRatio(lua_State* L);
        static int GetTractionCurveMax(lua_State* L);
        static int GetTractionCurveMaxRatio(lua_State* L);
        static int GetTractionCurveMin(lua_State* L);
        static int GetTractionCurveMinRatio(lua_State* L);
        static int GetTractionCurveLateral(lua_State* L);
        static int GetTractionCurveLateralRatio(lua_State* L);
        static int GetTractionSpringDeltaMax(lua_State* L);
        static int GetTractionSpringDeltaMaxRatio(lua_State* L);
        static int GetLowSpeedTractionLossMult(lua_State* L);
        static int GetCamberStiffness(lua_State* L);
        static int GetTractionBiasFront(lua_State* L);
        static int GetTractionBiasRear(lua_State* L);
        static int GetTractionLossMult(lua_State* L);
        static int GetSuspensionForce(lua_State* L);
        static int GetSuspensionCompDamp(lua_State* L);
        static int GetSuspensionReboundDamp(lua_State* L);
        static int GetSuspensionUpperLimit(lua_State* L);
        static int GetSuspensionLowerLimit(lua_State* L);
        static int GetSuspensionRaise(lua_State* L);
        static int GetSuspensionBiasFront(lua_State* L);
        static int GetSuspensionBiasRear(lua_State* L);
        static int GetAntiRollBarForce(lua_State* L);
        static int GetAntiRollBarBiasFront(lua_State* L);
        static int GetAntiRollBarBiasRear(lua_State* L);
        static int GetRollCentreHeightFront(lua_State* L);
        static int GetRollCentreHeightRear(lua_State* L);
        static int GetCollisionDamageMult(lua_State* L);
        static int GetWeaponDamageMult(lua_State* L);
        static int GetDeformationDamageMult(lua_State* L);
        static int GetEngineDamageMult(lua_State* L);
        static int GetPetrolTankVolume(lua_State* L);
        static int GetOilVolume(lua_State* L);
        static int GetunkFloat5(lua_State* L);
        static int GetSeatOffsetDistX(lua_State* L);
        static int GetSeatOffsetDistY(lua_State* L);
        static int GetSeatOffsetDistZ(lua_State* L);
        static int GetMonetaryValue(lua_State* L);
        static int GetModelFlags(lua_State* L);
        static int GetHandlingFlags(lua_State* L);
        static int GetDamageFlags(lua_State* L);

        static int SetMass(lua_State* L);
        static int SetInitialDragCoeff(lua_State* L);
        static int SetDownforceModifier(lua_State* L);
        static int SetunkFloat1(lua_State* L);
        static int SetunkFloat2(lua_State* L);
        static int SetCentreOfMassOffset(lua_State* L);
        static int SetInertiaMultiplier(lua_State* L);
        static int SetPercentSubmerged(lua_State* L);
        static int SetPercentSubmergedRatio(lua_State* L);
        static int SetDriveBiasFront(lua_State* L);
        static int SetAcceleration(lua_State* L);
        static int SetInitialDriveGears(lua_State* L);
        static int SetDriveInertia(lua_State* L);
        static int SetClutchChangeRateScaleUpShift(lua_State* L);
        static int SetClutchChangeRateScaleDownShift(lua_State* L);
        static int SetInitialDriveForce(lua_State* L);
        static int SetDriveMaxFlatVel(lua_State* L);
        static int SetInitialDriveMaxFlatVel(lua_State* L);
        static int SetBrakeForce(lua_State* L);
        static int SetunkFloat4(lua_State* L);
        static int SetBrakeBiasFront(lua_State* L);
        static int SetBrakeBiasRear(lua_State* L);
        static int SetHandBrakeForce(lua_State* L);
        static int SetSteeringLock(lua_State* L);
        static int SetSteeringLockRatio(lua_State* L);
        static int SetTractionCurveMax(lua_State* L);
        static int SetTractionCurveMaxRatio(lua_State* L);
        static int SetTractionCurveMin(lua_State* L);
        static int SetTractionCurveMinRatio(lua_State* L);
        static int SetTractionCurveLateral(lua_State* L);
        static int SetTractionCurveLateralRatio(lua_State* L);
        static int SetTractionSpringDeltaMax(lua_State* L);
        static int SetTractionSpringDeltaMaxRatio(lua_State* L);
        static int SetLowSpeedTractionLossMult(lua_State* L);
        static int SetCamberStiffness(lua_State* L);
        static int SetTractionBiasFront(lua_State* L);
        static int SetTractionBiasRear(lua_State* L);
        static int SetTractionLossMult(lua_State* L);
        static int SetSuspensionForce(lua_State* L);
        static int SetSuspensionCompDamp(lua_State* L);
        static int SetSuspensionReboundDamp(lua_State* L);
        static int SetSuspensionUpperLimit(lua_State* L);
        static int SetSuspensionLowerLimit(lua_State* L);
        static int SetSuspensionRaise(lua_State* L);
        static int SetSuspensionBiasFront(lua_State* L);
        static int SetSuspensionBiasRear(lua_State* L);
        static int SetAntiRollBarForce(lua_State* L);
        static int SetAntiRollBarBiasFront(lua_State* L);
        static int SetAntiRollBarBiasRear(lua_State* L);
        static int SetRollCentreHeightFront(lua_State* L);
        static int SetRollCentreHeightRear(lua_State* L);
        static int SetCollisionDamageMult(lua_State* L);
        static int SetWeaponDamageMult(lua_State* L);
        static int SetDeformationDamageMult(lua_State* L);
        static int SetEngineDamageMult(lua_State* L);
        static int SetPetrolTankVolume(lua_State* L);
        static int SetOilVolume(lua_State* L);
        static int SetunkFloat5(lua_State* L);
        static int SetSeatOffsetDistX(lua_State* L);
        static int SetSeatOffsetDistY(lua_State* L);
        static int SetSeatOffsetDistZ(lua_State* L);
        static int SetMonetaryValue(lua_State* L);
        static int SetModelFlags(lua_State* L);
        static int SetHandlingFlags(lua_State* L);
        static int SetDamageFlags(lua_State* L);
    };
}
#endif