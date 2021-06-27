/// <reference types="@altv/types-client"/>
/**
 * @module lua-client
 */
declare module "lua-client" {
  import * as side from "alt-client";

  export class Resource {
    public readonly type: string;

    public readonly started: boolean;

    public readonly name: string;

    public readonly path: string;

    public readonly main: string;

    public readonly exports: string[];

    public readonly dependencies: string[];

    public readonly dependants: string[];

    public static getFromName(resourceName: string): Resource;

    public static getResourceConfig(resourceName: string): Resource;

    [exportName: string]: Function;
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

  export class Voice {
    public readonly activityInputEnabled: boolean;

    public muteInput: boolean;

    public toggleControls(state: boolean);
  }

  //#region class Entity

  export function getEntityType(entity: side.Entity): number;
  export function hasEntityMetaData(entity: side.Entity, key: string): boolean;
  export function getEntityMetaData(entity: side.Entity, key: string): any;
  export function setEntityMetaData(entity: side.Entity, key: string, value: any): void;
  export function deleteEntityMetaData(entity: side.Entity, key: string): void;
  export function destroyEntity(entity: side.Entity): void;

  export function setEntityPosition(entity: side.Entity, position: Vector3): void;
  export function getEntityPosition(entity: side.Entity): Vector3;
  export function setEntityDimension(entity: side.Entity, dimension: number): void;
  export function getEntityDimension(entity: side.Entity): number;

  export function getEntityID(entity: side.Entity): number;
  export function getEntityNetworkOwner(entity: side.Entity): side.Player;
  export function getEntityModel(entity: side.Entity): number;
  export function setEntityRotation(entity: side.Entity, rotation: Vector3): void;
  export function getEntityRotation(entity: side.Entity): Vector3;
  export function hasEntitySyncedMetaData(entity: side.Entity, key: string): boolean;
  export function getEntitySyncedMetaData(entity: side.Entity, key: string): any;
  export function hasEntityStreamSyncedMetaData(entity: side.Entity, key: string): boolean;
  export function getEntityStreamSyncedMetaData(entity: side.Entity, key: string): any;
  export function setEntitySyncedMetaData(entity: side.Entity, key: string, value: any): void;
  export function deleteEntitySyncedMetaData(entity: side.Entity, key: string): void;
  export function setEntityStreamSyncedMetaData(entity: side.Entity, key: string, value: any): void;
  export function deleteEntityStreamSyncedMetaData(entity: side.Entity, key: string): void;

  //#endregion

  //#region class Player

  export function isPlayerConnected(player: side.Player): boolean;
  export function getPlayerPing(player: side.Player): number;
  export function getPlayerIP(player: side.Player): string;
  export function spawnPlayer(player: side.Player, position: Vector3, delay: number): void;
  export function despawnPlayer(player: side.Player): void;
  export function getPlayerName(player: side.Player): string;
  export function getPlayerSocialID(player: side.Player): string;
  export function getPlayerHwidHash(player: side.Player): string;
  export function getPlayerHwidExHash(player: side.Player): string;
  export function getPlayerAuthToken(player: side.Player): string;

  export function getPlayerHealth(player: side.Player): number;
  export function setPlayerHealth(player: side.Player, health: number): void;
  export function getPlayerMaxHealth(player: side.Player): number;
  export function setPlayerMaxHealth(player: side.Player, maxHealth: number): void;
  export function setPlayerDateTime(player: side.Player, day: DateTimeDay, month: DateTimeMonth, year: number, hour: DateTimeHour, minute: DateTimeMinute, second: DateTimeSecond): void;
  export function setPlayerWeather(player: side.Player, weatherType: WeatherType): void;
  export function givePlayerWeapon(player: side.Player, weaponHash: number, ammo: number, equipNow: boolean): void;
  export function removePlayerWeapon(player: side.Player, weaponHash: number): void;
  export function removePlayerAllWeapons(player: side.Player): void;
  export function addPlayerWeaponComponent(player: side.Player, weaponHash: number, component: number): void;

  export function removePlayerWeaponComponent(player: side.Player, weaponHash: number, component: number): void;
  export function getPlayerCurrentWeaponComponents(player: side.Player): number[];
  export function setPlayerWeaponTintIndex(player: side.Player, weaponHash: number, tintIndex: number): void;
  export function getPlayerCurrentWeaponTintIndex(player: side.Player): number;
  export function getPlayerCurrentWeapon(player: side.Player): number;
  export function setPlayerCurrentWeapon(player: side.Player, weaponHash: number): void;
  export function isPlayerDead(player: side.Player): boolean;
  export function isPlayerJumping(player: side.Player): boolean;
  export function isPlayerInRagdoll(player: side.Player): boolean;
  export function isPlayerAiming(player: side.Player): boolean;

  export function isPlayerShooting(player: side.Player): boolean;
  export function isPlayerReloading(player: side.Player): boolean;
  export function getPlayerArmour(player: side.Player): number;
  export function setPlayerArmour(player: side.Player, armour: number): void;
  export function getPlayerMaxArmour(player: side.Player): number;
  export function setPlayerMaxArmour(player: side.Player, maxArmour: number): void;
  export function getPlayerMoveSpeed(player: side.Player): number;
  export function getPlayerWeapon(player: side.Player): number;
  export function getPlayerAmmo(player: side.Player): number;
  export function getPlayerAimPos(player: side.Player): Vector3;

  export function getPlayerHeadRotation(player: side.Player): Vector3;
  export function isPlayerInVehicle(player: side.Player): boolean;
  export function getPlayerVehicle(player: side.Player): side.Vehicle;
  export function getPlayerSeat(player: side.Player): number;
  export function getPlayerEntityAimingAt(player: side.Player): side.Entity;
  export function getPlayerEntityAimOffset(player: side.Player): Vector3;
  export function isPlayerFlashlightActive(player: side.Player): boolean;
  export function kickPlayer(player: side.Player, reason: string): void;
  export function setPlayerModel(player: side.Player, model: number | string): void;
  export function getPlayerModel(player: side.Player): number;

  //#endregion

  //#region class Vehicle

  export function createVehicle(model: string | number, x: number, y: number, z: number, rx: number, ry: number, rz: number): side.Vehicle;
  export function getVehicleDriver(vehicle: side.Vehicle): Player | null;
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
  export function getVehicleDoorState(vehicle: side.Vehicle, doorId: VehicleDoor): side.VehicleDoorState;
  export function setVehicleDoorState(vehicle: side.Vehicle, doorId: VehicleDoor, state: side.VehicleDoorState): void;
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
  export function getVehicleBumperDamageLevel(vehicle: side.Vehicle, bumperId: VehicleBumper): side.VehicleBumperDamage;
  export function setVehicleBumperDamageLevel(vehicle: side.Vehicle, bumperId: VehicleBumper, level: side.VehicleBumperDamage): void;
  export function getVehicleDamageDataBase64(vehicle: side.Vehicle): string;
  export function loadVehicleDamageDataFromBase64(vehicle: side.Vehicle, data: string): void;
  export function setVehicleManualEngineControl(vehicle: side.Vehicle): void;
  export function isVehicleManualEngineControl(vehicle: side.Vehicle): void;
  export function getVehicleScriptDataBase64(vehicle: side.Vehicle): string;
  export function loadVehicleScriptDataFromBase64(vehicle: side.Vehicle, data: string): void;

  //#endregion

  //#region class Blip

  export function createAreaBlip(x: number, y: number, z: number, width: number, height: number): void;
  export function createAreaBlip(x: number, y: number, z: number, width: number, height: number): void;
  export function createRadiusBlip(x: number, y: number, z: number, radius: number): void;
  export function createPointBlip(x: number, y: number, z: number): void;
  export function createPedBlip(ped: number): void;
  export function createVehicleBlip(vehicle: number): void;

  export function getBlipScaleXY(blip: side.Blip): side.Vector2;
  export function getBlipDisplay(blip: side.Blip): number;
  export function getBlipSprite(blip: side.Blip): number;
  export function getBlipColor(blip: side.Blip): number;
  export function getBlipSecondaryColor(blip: side.Blip): number | side.RGBA;
  export function getBlipAlpha(blip: side.Blip): number;
  export function getBlipFlashTimer(blip: side.Blip): number;
  export function getBlipFlashInterval(blip: side.Blip): number;
  export function getBlipAsFriendly(blip: side.Blip): boolean;
  export function getBlipRoute(blip: side.Blip): boolean;
  export function getBlipBright(blip: side.Blip): boolean;
  export function getBlipNumber(blip: side.Blip): number;
  export function getBlipShowCone(blip: side.Blip): boolean;
  export function getBlipFlashes(blip: side.Blip): boolean;
  export function getBlipFlashesAlternate(blip: side.Blip): boolean;
  export function getBlipAsShortRange(blip: side.Blip): boolean;
  export function getBlipPriority(blip: side.Blip): number;
  export function getBlipRotation(blip: side.Blip): number;
  export function getBlipGxtName(blip: side.Blip): string;
  export function getBlipName(blip: side.Blip): string;
  export function getBlipPulse(blip: side.Blip): boolean;
  export function getBlipAsMissionCreator(blip: side.Blip): boolean;
  export function getBlipTickVisible(blip: side.Blip): boolean;
  export function getBlipHeadingIndicatorVisible(blip: side.Blip): boolean;
  export function getBlipOutlineIndicatorVisible(blip: side.Blip): boolean;
  export function getBlipFriendIndicatorVisible(blip: side.Blip): boolean;
  export function getBlipCrewIndicatorVisible(blip: side.Blip): boolean;
  export function getBlipCategory(blip: side.Blip): number;
  export function getBlipAsHighDetail(blip: side.Blip): boolean;
  export function getBlipShrinked(blip: side.Blip): boolean;

  export function setBlipScaleXY(blip: side.Blip, scaleXY: number): void;
  export function setBlipDisplay(blip: side.Blip, display: number): void;
  export function setBlipSprite(blip: side.Blip, sprite: number): void;
  export function setBlipColor(blip: side.Blip, color: number): void;
  export function setBlipRoute(blip: side.Blip, state: boolean): void;
  export function setBlipSecondaryColor(blip: side.Blip, secondaryColor: number | side.RGBA): void;
  export function setBlipAlpha(blip: side.Blip, alpha: number): void;
  export function setBlipFlashTimer(blip: side.Blip, flashTimer: number): void;
  export function setBlipFlashInterval(blip: side.Blip, flashInterval: number): void;
  export function setBlipAsFriendly(blip: side.Blip, state: boolean): void;
  export function setBlipBright(blip: side.Blip, bright: boolean): void;
  export function setBlipNumber(blip: side.Blip, number: number): void;
  export function setBlipShowCone(blip: side.Blip, state: boolean): void;
  export function setBlipFlashes(blip: side.Blip, state: boolean): void;
  export function setBlipFlashesAlternate(blip: side.Blip, flashesAlternate: number): void;
  export function setBlipAsShortRange(blip: side.Blip, state: boolean): void;
  export function setBlipPriority(blip: side.Blip, priority: number): void;
  export function setBlipRotation(blip: side.Blip, rotation: number): void;
  export function setBlipGxtName(blip: side.Blip, gxtName: string): void;
  export function setBlipName(blip: side.Blip, name: string): void;
  export function setBlipPulse(blip: side.Blip, state: boolean): void;
  export function setBlipAsMissionCreator(blip: side.Blip, state: boolean): void;
  export function setBlipTickVisible(blip: side.Blip, state: boolean): void;
  export function setBlipHeadingIndicatorVisible(blip: side.Blip, state: boolean): void;
  export function setBlipOutlineIndicatorVisible(blip: side.Blip, state: boolean): void;
  export function setBlipFriendIndicatorVisible(blip: side.Blip, state: boolean): void;
  export function setBlipCrewIndicatorVisible(blip: side.Blip, state: boolean): void;
  export function setBlipCategory(blip: side.Blip, category: number): void;
  export function setBlipAsHighDetail(blip: side.Blip, state: boolean): void;
  export function setBlipShrinked(blip: side.Blip, shrinked: boolaean): void;
  export function fadeBlip(blip: side.Blip, opacity: number, duration: number): void;

  //#endregion

  //#region class Checkpoint

  export function createCheckpoint(type: number, x: number, y: number, z: number, x2: number, y2: number, z2: number, radius: number, height: number, r: number, g: number, b: number, a: number): void;
  export function createCheckpoint(type: number, pos: side.Vector3, pos2: side.Vector3, radius: number, height: number, r: number, g: number, b: number, a: number): void;
  export function getCheckpointType(checkpoint: side.Checkpoint): number;
  export function getCheckpointHeight(checkpoint: side.Checkpoint): number;
  export function getCheckpointRadius(checkpoint: side.Checkpoint): number;
  export function getCheckpointColor(checkpoint: side.Checkpoint): number;

  //#endregion

  //#region class Voice

  export function setVoiceInputMuted(state: boolean): void;
  export function isVoiceInputMuted(): boolean;
  export function isVoiceActivationEnabled(): boolean;
  export function toggleVoiceControls(state: boolean): void;

  //#endregion

  //#region class WebView

  export function createWebView(url: string, isOverlay?: boolean): side.WebView;
  export function createWebView(url: string, pos: side.IVector2): side.WebView;
  export function createWebView(url: string, pos: side.IVector2, size: side.IVector2): side.WebView;
  export function createWebView(url: string, isOverlay: boolean, pos: side.IVector2, size: side.IVector2): side.WebView;
  export function createWebView(url: string, propHash: number, targetTexture: string): side.WebView;
  export function emitWebView(webView: side.WebView, eventName: string, ...args: any[]): void;
  export function focusWebView(webView: side.WebView): void;
  export function unfocusWebView(webView: side.WebView): void;
  export function isWebViewFocused(webView: side.WebView): boolean;
  export function getWebViewUrl(webView: side.WebView): string;
  export function setWebViewUrl(webView: side.WebView): void;
  export function isWebViewVisible(webView: side.WebView): boolean;
  export function setWebViewVisible(webView: side.WebView): void;
  export function isWebViewOverlay(webView: side.WebView): boolean;
  export function isWebViewReady(webView: side.WebView): boolean;

  //#endregion

  //#region class MapZoomData

  export function getMapDataZoomScale(mapZoomData: MapZoomData): number;
  export function getMapDataZoomSpeed(mapZoomData: MapZoomData): number;
  export function getMapDataScrollSpeed(mapZoomData: MapZoomData): number;
  export function getMapDataTilesCountX(mapZoomData: MapZoomData): number;
  export function getMapDataTilesCountY(mapZoomData: MapZoomData): number;

  export function setMapDataZoomScale(mapZoomData: MapZoomData, scale: number): void;
  export function setMapDataZoomSpeed(mapZoomData: MapZoomData, speed: number): void;
  export function setMapDataScrollSpeed(mapZoomData: MapZoomData, scrollSpeed: number): void;
  export function setMapDataTilesCountX(mapZoomData: MapZoomData, tilesCountX: number): void;
  export function setMapDataTilesCountY(mapZoomData: MapZoomData, tilesCountY: number): void;

  //#endregion

  //#region class Resource

  export function getResourceFromName(resourceName: string): Resource;
  export function isResourceStarted(resource: Resource): boolean;
  export function getResourceType(resource: Resource): string;
  export function getResourceName(resource: Resource): string;
  export function getResourcePath(resource: Resource): string;
  export function getResourceMain(resource: Resource): string;
  export function getResourceExports(resource: Resource): string[];
  export function getResourceDependencies(resource: Resource): string[];
  export function getResourceDependants(resource: Resource): string[];

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

  export function require(path: string): Function;

  export function _import(importName: string): Resource;

  export function _export(exportName: string, callback: Function): void;

  export function inspect(obj: any): string;

  export function createThread(callback: (...args: any[]) => void): void;

  export function wait(milliseconds: number): void;

  export function wait(callback: Function, ...args: any[]): void;

  export * from "alt-client";
}
