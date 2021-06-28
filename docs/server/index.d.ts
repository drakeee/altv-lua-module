/// <reference types="@altv/types-server"/>
/**
 * @module lua-server
 */
declare module "lua-server" {
  import * as side from "alt-server";

  export class Resource {
    public readonly type: string;

    public readonly started: boolean;

    public readonly name: string;

    public readonly path: string;

    public readonly main: string;

    public readonly exports: string[];

    public readonly dependencies: string[];

    public readonly dependants: string[];

    public readonly config: Config;

    public readonly requiredPermissions: number[];

    public readonly optionalPermissions: number[];

    public static getFromName(resourceName: string): Resource;

    public static getConfig(resourceName: string): Config;

    [exportName: string]: Function | any;
  }

  export class Log {
    public info(...args: any[]): void;

    public debug(...args: any[]): void;

    public warning(...args: any[]): void;

    public error(...args: any[]): void;

    public colored(...args: any[]): void;
  }

  type ConfigNode = { [key: string]: ConfigNode; } | string[] | string | null;

  export class Config {
    public getKey(key: string): ConfigNode;
  }

  //#region class Player

  export function isPlayerConnected(player: side.Player): boolean;
  export function getPlayerPing(player: side.Player): number;
  export function getPlayerIP(player: side.Player): string;
  export function getPlayerSocialID(player: side.Player): string;
  export function getPlayerHwidHash(player: side.Player): string;
  export function getPlayerHwidExHash(player: side.Player): string;
  export function getPlayerAuthToken(player: side.Player): string;
  export function getPlayerClothes(player: side.Player, component: number, dlc?: boolean): side.ICloth;
  export function getPlayerProp(player: side.Player, component: number, dlc?: boolean): side.IProp;
  export function isEntityInStreamRange(player: side.Player, entity: side.Entity): boolean;

  export function spawnPlayer(player: side.Player, position: side.Vector3, delay: number): void;
  export function despawnPlayer(player: side.Player): void;
  export function setPlayerHealth(player: side.Player, health: number): void;
  export function setPlayerMaxHealth(player: side.Player, maxHealth: number): void;
  export function setPlayerArmour(player: side.Player, armour: number): void;
  export function setPlayerMaxArmour(player: side.Player, maxArmour: number): void;
  export function setPlayerDateTime(player: side.Player, day: side.DateTimeDay, month: side.DateTimeMonth, year: number, hour: side.DateTimeHour, minute: side.DateTimeMinute, second: side.DateTimeSecond): void;
  export function setPlayerWeather(player: side.Player, weatherType: side.WeatherType): void;
  export function givePlayerWeapon(player: side.Player, weaponHash: number, ammo: number, equipNow: boolean): void;
  export function removePlayerWeapon(player: side.Player, weaponHash: number): void;
  export function removePlayerAllWeapons(player: side.Player): void;
  export function addPlayerWeaponComponent(player: side.Player, weaponHash: number, component: number): void;
  export function removePlayerWeaponComponent(player: side.Player, weaponHash: number, component: number): void;
  export function setPlayerWeaponTintIndex(player: side.Player, weaponHash: number, tintIndex: number): void;
  export function setPlayerCurrentWeapon(player: side.Player, weaponHash: number): void;
  export function setPlayerClothes(player: side.Player, component: number, drawable: number, texture: number, palette?: number, dlc?: number): void;
  export function setPlayerProp(player: side.Player, component: number, drawable: number, texture: number, dlc?: number): void;
  export function clearPlayerProp(player: side.Player, component: number): void;
  export function kickPlayer(player: side.Player, reason: string): void;
  export function setPlayerModel(player: side.Player, model: number | string): void;

  //#endregion

  //#region class Vehicle

  export function createVehicle(model: string | number, x: number, y: number, z: number, rx: number, ry: number, rz: number): side.Vehicle;
  export function getVehicleDriver(vehicle: side.Vehicle): side.Player | null;
  export function isVehicleDestroyed(vehicle: side.Vehicle): boolean;
  export function getVehicleMod(vehicle: side.Vehicle): side.VehicleModType;
  export function getVehicleModsCount(vehicle: side.Vehicle, modType: side.VehicleModType): number;
  export function setVehicleMod(vehicle: side.Vehicle, modType: side.VehicleModType): void;
  export function getVehicleModKitsCount(vehicle: side.Vehicle): number;
  export function getVehicleModKit(vehicle: side.Vehicle): number;
  export function setVehicleModKit(vehicle: side.Vehicle, modKit: number): void;
  export function isVehiclePrimaryColorRGB(vehicle: side.Vehicle): boolean;
  export function getVehiclePrimaryColor(vehicle: side.Vehicle): number;
  export function getVehiclePrimaryColorRGB(vehicle: side.Vehicle): side.RGBA;
  export function setVehiclePrimaryColor(vehicle: side.Vehicle, colour: number): void;
  export function setVehiclePrimaryColorRGB(vehicle: side.Vehicle, colour: side.RGBA): void;
  export function isVehicleSecondaryColorRGB(vehicle: side.Vehicle): void;
  export function getVehicleSecondaryColor(vehicle: side.Vehicle): number;
  export function getVehicleSecondaryColorRGB(vehicle: side.Vehicle): side.RGBA;
  export function setVehicleSecondaryColor(vehicle: side.Vehicle, colour: number): void;
  export function setVehicleSecondaryColorRGB(vehicle: side.Vehicle, colour: side.RGBA): void;
  export function getVehiclePearlColor(vehicle: side.Vehicle): number;
  export function setVehiclePearlColor(vehicle: side.Vehicle, colour: number): void;
  export function getVehicleWheelColor(vehicle: side.Vehicle): number;
  export function setVehicleWheelColor(vehicle: side.Vehicle, colour: number): void;
  export function getVehicleInteriorColor(vehicle: side.Vehicle): number;
  export function setVehicleInteriorColor(vehicle: side.Vehicle, colour: number): void;
  export function getVehicleDashboardColor(vehicle: side.Vehicle): number;

  export function setVehicleDashboardColor(vehicle: side.Vehicle, colour: number): number;
  export function isVehicleTireSmokeColorCustom(vehicle: side.Vehicle): boolean;
  export function getVehicleTireSmokeColor(vehicle: side.Vehicle): number;
  export function setVehicleTireSmokeColor(vehicle: side.Vehicle, colour: number): void;
  export function getVehicleWheelType(vehicle: side.Vehicle): number;
  export function getVehicleWheelVariation(vehicle: side.Vehicle): number;
  export function getVehicleRearWheelVariation(vehicle: side.Vehicle): number;
  export function setVehicleWheels(vehicle: side.Vehicle, wheelType: number, wheelId: number): void;
  export function setVehicleRearWheels(vehicle: side.Vehicle, wheelId: number): void;
  export function getVehicleCustomTires(vehicle: side.Vehicle): number;
  export function setVehicleCustomTires(vehicle: side.Vehicle, tireId: number): void;
  export function getVehicleSpecialDarkness(vehicle: side.Vehicle): number;
  export function setVehicleSpecialDarkness(vehicle: side.Vehicle, darkness: number): void;
  export function getVehicleNumberplateIndex(vehicle: side.Vehicle): side.NumberPlateStyle;
  export function setVehicleNumberplateIndex(vehicle: side.Vehicle, numberplateId: side.NumberPlateStyle): void;
  export function getVehicleNumberplateText(vehicle: side.Vehicle): string;
  export function setVehicleNumberplateText(vehicle: side.Vehicle, numberplateText: string): void;
  export function getVehicleWindowTint(vehicle: side.Vehicle): number;
  export function setVehicleWindowTint(vehicle: side.Vehicle, colour: number): void;
  export function getVehicleDirtLevel(vehicle: side.Vehicle): number;
  export function setVehicleDirtLevel(vehicle: side.Vehicle, dirtLevel: number): void;
  export function isVehicleExtraOn(vehicle: side.Vehicle, extraId: number): boolean;  // Should be named getVehicleExtra
  export function toggleVehicleExtra(vehicle: side.Vehicle, extraId: number, state: boolean): any;  // Should be named setVehicleExtra
  export function isVehicleNeonActive(vehicle: side.Vehicle): boolean;
  export function getVehicleNeonActive(vehicle: side.Vehicle): [boolean, boolean, boolean, boolean];
  export function setVehicleNeonActive(vehicle: side.Vehicle, left: boolean, right: boolean, front: boolean, back: boolean): void;

  export function getVehicleNeonColor(vehicle: side.Vehicle): number;
  export function setVehicleNeonColor(vehicle: side.Vehicle, colour: number): void;
  export function getVehicleLivery(vehicle: side.Vehicle): number;
  export function setVehicleLivery(vehicle: side.Vehicle, liveryId: number): void;
  export function getVehicleRoofLivery(vehicle: side.Vehicle): number;
  export function getVehicleRoofLivery(vehicle: side.Vehicle, liveryId: number): void;
  export function getVehicleAppearanceDataBase64(vehicle: side.Vehicle): string;
  export function loadVehicleAppearanceDataFromBase64(vehicle: side.Vehicle, data: string): void;
  export function isVehicleEngineOn(vehicle: side.Vehicle): boolean;
  export function setVehicleEngineOn(vehicle: side.Vehicle, state: boolean): void;
  export function isVehicleHandbrakeActive(vehicle: side.Vehicle): boolean;
  export function getVehicleHeadlightColor(vehicle: side.Vehicle): number;
  export function setVehicleHeadlightColor(vehicle: side.Vehicle, colour: number): void;
  export function getVehicleRadioStationIndex(vehicle: side.Vehicle): side.RadioStation;
  export function setVehicleRadioStationIndex(vehicle: side.Vehicle, radioStation: side.RadioStation): void;
  export function isVehicleSirenActive(vehicle: side.Vehicle): boolean;
  export function setVehicleSirenActive(vehicle: side.Vehicle, state: boolean): void;
  export function getVehicleLockState(vehicle: side.Vehicle): side.VehicleLockState;
  export function setVehicleLockState(vehicle: side.Vehicle, state: side.VehicleLockState): void;
  export function getVehicleDoorState(vehicle: side.Vehicle, doorId: side.VehicleDoor): side.VehicleDoorState;
  export function setVehicleDoorState(vehicle: side.Vehicle, doorId: side.VehicleDoor, state: side.VehicleDoorState): void;
  export function isVehicleWindowOpened(vehicle: side.Vehicle, windowId: number): boolean;
  export function setVehicleWindowOpened(vehicle: side.Vehicle, windowId: number, state: boolean): void;
  export function isVehicleDaylightOn(vehicle: side.Vehicle): boolean;
  export function isVehicleNightlightOn(vehicle: side.Vehicle): boolean;
  export function isVehicleRoofOpened(vehicle: side.Vehicle): boolean;

  export function setVehicleRoofOpened(vehicle: side.Vehicle, state: boolean): void;
  export function isVehicleFlamethrowerActive(vehicle: side.Vehicle): boolean;
  export function getVehicleLightsMultiplier(vehicle: side.Vehicle): number;
  export function setVehicleLightsMultiplier(vehicle: side.Vehicle, multiplier: number): void;
  export function getVehicleGameStateBase64(vehicle: side.Vehicle): string;
  export function loadVehicleGameStateFromBase64(vehicle: side.Vehicle, data: string): void;
  export function getVehicleEngineHealth(vehicle: side.Vehicle): number;
  export function setVehicleEngineHealth(vehicle: side.Vehicle, health: number): void;
  export function getVehiclePetrolTankHealth(vehicle: side.Vehicle): number;
  export function setVehiclePetrolTankHealth(vehicle: side.Vehicle, health: number): void;
  export function getVehicleWheelsCount(vehicle: side.Vehicle): number;
  export function isVehicleWheelBurst(vehicle: side.Vehicle, wheelId: number): boolean;
  export function setVehicleWheelBurst(vehicle: side.Vehicle, wheelId: number): void;
  export function doesVehicleWheelHasTire(vehicle: side.Vehicle, wheelId: number): boolean;
  export function setVehicleWheelHasTire(vehicle: side.Vehicle, wheelId: number, state: boolean): void;
  export function isVehicleWheelDetached(vehicle: side.Vehicle, wheelId: number): boolean;
  export function setVehicleWheelDetached(vehicle: side.Vehicle, wheelId: number): void;
  export function isVehicleWheelOnFire(vehicle: side.Vehicle, wheelId: number): boolean;
  export function setVehicleWheelOnFire(vehicle: side.Vehicle, wheelId: number, state: boolean): void;
  export function getVehicleWheelHealth(vehicle: side.Vehicle, wheelId: number): number;
  export function setVehicleWheelHealth(vehicle: side.Vehicle, wheelId: number, health: boolean): void;
  export function getVehicleRepairsCount(vehicle: side.Vehicle): number;
  export function getVehicleBodyHealth(vehicle: side.Vehicle): number;
  export function setVehicleBodyHealth(vehicle: side.Vehicle, health: number): void;
  export function getVehicleBodyAdditionalHealth(vehicle: side.Vehicle): number;
  export function setVehicleBodyAdditionalHealth(vehicle: side.Vehicle, health: number): void;

  export function getVehicleHealthDataBase64(vehicle: side.Vehicle): string;
  export function loadVehicleHealthDataFromBase64(vehicle: side.Vehicle, data: string): void;
  export function getVehiclePartDamageLevel(vehicle: side.Vehicle, partId: side.VehiclePart): side.VehiclePartDamage;
  export function setVehiclePartDamageLevel(vehicle: side.Vehicle, partId: side.VehiclePart, level: side.VehiclePartDamage): void;
  export function getVehiclePartBulletHoles(vehicle: side.Vehicle, partId: side.VehiclePart): number;
  export function setVehiclePartBulletHoles(vehicle: side.Vehicle, partId: side.VehiclePart, count: number): void;
  export function isVehicleLightDamaged(vehicle: side.Vehicle, lightId: number): boolean;
  export function setVehicleLightDamaged(vehicle: side.Vehicle, lightId: number, state: boolean): void;
  export function isVehicleWindowDamaged(vehicle: side.Vehicle, windowId: number): boolean;
  export function setVehicleWindowDamaged(vehicle: side.Vehicle, windowId: number, state: boolean): void;
  export function isVehicleSpecialLightDamaged(vehicle: side.Vehicle, lightId: number): boolean;
  export function setVehicleSpecialLightDamaged(vehicle: side.Vehicle, lightId: number, state: boolean): void;
  export function hasVehicleArmoredWindows(vehicle: side.Vehicle): boolean;
  export function getVehicleArmoredWindowHealth(vehicle: side.Vehicle, windowId: number): number;
  export function setVehicleArmoredWindowHealth(vehicle: side.Vehicle, windowId: number, health: number): void;
  export function getVehicleArmoredWindowShootCount(vehicle: side.Vehicle, windowId: number): number;
  export function setVehicleArmoredWindowShootCount(vehicle: side.Vehicle, windowId: number, count: number): void;
  export function getVehicleBumperDamageLevel(vehicle: side.Vehicle, bumperId: side.VehicleBumper): side.VehicleBumperDamage;
  export function setVehicleBumperDamageLevel(vehicle: side.Vehicle, bumperId: side.VehicleBumper, level: side.VehicleBumperDamage): void;
  export function getVehicleDamageDataBase64(vehicle: side.Vehicle): string;
  export function loadVehicleDamageDataFromBase64(vehicle: side.Vehicle, data: string): void;
  export function setVehicleManualEngineControl(vehicle: side.Vehicle): void;
  export function isVehicleManualEngineControl(vehicle: side.Vehicle): void;
  export function getVehicleScriptDataBase64(vehicle: side.Vehicle): string;
  export function loadVehicleScriptDataFromBase64(vehicle: side.Vehicle, data: string): void;

  //#endregion

  //#region class Checkpoint

  export function createCheckpoint(type: number, x: number, y: number, z: number, radius: number, height: number, r: number, g: number, b: number, a: number): void;
  export function createCheckpoint(type: number, pos: side.Vector3, radius: number, height: number, r: number, g: number, b: number, a: number): void;
  export function getCheckpointType(checkpoint: side.Checkpoint): number;
  export function getCheckpointHeight(checkpoint: side.Checkpoint): number;
  export function getCheckpointRadius(checkpoint: side.Checkpoint): number;
  export function getCheckpointColor(checkpoint: side.Checkpoint): number;

  //#endregion

  //#region class ColShape

  export function createColShapeCircle(colshape: side.Colshape, x: number, y: number, radius: number): void;
  export function createColShapeCircle(colshape: side.Colshape, pos: side.Vector2, radius: number): void;
  export function createColShapeCube(colshape: side.Colshape, x1: number, y1: number, z1: number, x2: number, y2: number, z2: number): void;
  export function createColShapeCube(colshape: side.Colshape, pos1: side.Vector3, pos2: side.Vector3): void;
  export function createColShapeCylinder(colshape: side.Colshape, x: number, y: number, z: number, radius: number, height: number): void;
  export function createColShapeCylinder(colshape: side.Colshape, pos: side.Vector3, radius: number, height: number): void;
  export function createColShapeRectangle(colshape: side.Colshape, x1: number, y1: number, x2: number, y2: number): void;
  export function createColShapeRectangle(colshape: side.Colshape, pos1: side.Vector2, pos2: side.Vector2): void;
  export function createColShapeSphere(colshape: side.Colshape, x: number, y: number, z: number, radius: number): void;
  export function createColShapeSphere(colshape: side.Colshape, pos: side.Vector3, radius: number): void;
  export function getColShapeType(colshape: side.Colshape): side.ColShapeType;
  export function isEntityInColShape(colshape: side.Colshape, entity: side.Entity): boolean;
  export function isPointInColShape(colshape: side.Colshape, pos: side.Vector3): boolean;

  //#endregion

  //#region class VoiceChannel

  export function createVoiceChannel(voiceChannel: side.VoiceChannel, isSpatial: boolean, maxDistance: number): void;
  export function isVoiceChannelSpatial(voiceChannel: side.VoiceChannel): boolean;
  export function getVoiceChannelMaxDistance(voiceChannel: side.VoiceChannel): number;
  export function isPlayerInVoiceChannel(voiceChannel: side.VoiceChannel, player: side.Player): boolean;
  export function addPlayerToVoiceChannel(voiceChannel: side.VoiceChannel, player: side.Player): void;
  export function removePlayerFromVoiceChannel(voiceChannel: side.VoiceChannel, player: side.Player): void;
  export function isPlayerMutedInVoiceChannel(voiceChannel: side.VoiceChannel, player: side.Player): boolean;
  export function mutePlayerInVoiceChannel(voiceChannel: side.VoiceChannel, player: side.Player): void;
  export function unmutePlayerInVoiceChannel(voiceChannel: side.VoiceChannel, player: side.Player): void;

  //#endregion

  //#region class Resource

  export function getResourceFromName(resourceName: string): Resource;
  export function isResourceStarted(resource: Resource): boolean;
  export function getResourceConfig(resource: Resource): Config;
  export function getResourceType(resource: Resource): string;
  export function getResourceName(resource: Resource): string;
  export function getResourcePath(resource: Resource): string;
  export function getResourceMain(resource: Resource): string;
  export function getResourceExports(resource: Resource): string[];
  export function getResourceDependencies(resource: Resource): string[];
  export function getResourceDependants(resource: Resource): string[];
  export function getResourceRequiredPermissions(resource: Resource): number[];
  export function getResourceOptionalPermissions(resource: Resource): number[];

  //#endregion

  export function logInfo(...args: any[]): void;

  export function logDebug(...args: any[]): void;

  export function logColored(...args: any[]): void;

  export function hasMetaData(key: string): boolean;

  export function getMetaData(key: string): any;

  export function setMetaData(key: string, value: any): void;

  export function deleteMetaData(key: string): void;

  export function hasSyncedMetaData(key: string): boolean;

  export function getSyncedMetaData(key: string): any;

  export function setSyncedMetaData(key: string, value: any): void;

  export function deleteSyncedMetaData(key: string): void;

  export function require(path: string): Function;

  export function _import(importName: string): Resource;

  export function _export(exportName: string, callback: Function): void;

  export function inspect(obj: any): string;

  export function createThread(callback: (...args: any[]) => void): void;

  export function wait(milliseconds: number): void;

  export function wait(callback: Function, ...args: any[]): void;

  export * from "alt-server";
}
