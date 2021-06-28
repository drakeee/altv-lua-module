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

  export class Voice {
    public readonly activityInputEnabled: boolean;

    public muteInput: boolean;

    public toggleControls(state: boolean): void;
  }

  //#region class Entity

  export function getEntityType(entity: side.Entity): number;
  export function hasEntityMetaData(entity: side.Entity, key: string): boolean;
  export function getEntityMetaData(entity: side.Entity, key: string): any;
  export function setEntityMetaData(entity: side.Entity, key: string, value: any): void;
  export function deleteEntityMetaData(entity: side.Entity, key: string): void;
  export function destroyEntity(entity: side.Entity): void;

  export function setEntityPosition(entity: side.Entity, position: side.Vector3): void;
  export function getEntityPosition(entity: side.Entity): side.Vector3;
  export function setEntityDimension(entity: side.Entity, dimension: number): void;
  export function getEntityDimension(entity: side.Entity): number;

  export function getEntityID(entity: side.Entity): number;
  export function getEntityNetworkOwner(entity: side.Entity): side.Player;
  export function getEntityModel(entity: side.Entity): number;
  export function setEntityRotation(entity: side.Entity, rotation: side.Vector3): void;
  export function getEntityRotation(entity: side.Entity): side.Vector3;
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

  export function getPlayerName(player: side.Player): string;
  export function getPlayerHealth(player: side.Player): number;
  export function getPlayerMaxHealth(player: side.Player): number;
  export function getPlayerCurrentWeaponComponents(player: side.Player): number[];
  export function getPlayerCurrentWeaponTintIndex(player: side.Player): number;
  export function getPlayerCurrentWeapon(player: side.Player): number;
  export function isPlayerDead(player: side.Player): boolean;
  export function isPlayerJumping(player: side.Player): boolean;
  export function isPlayerInRagdoll(player: side.Player): boolean;
  export function isPlayerAiming(player: side.Player): boolean;

  export function isPlayerShooting(player: side.Player): boolean;
  export function isPlayerReloading(player: side.Player): boolean;
  export function getPlayerArmour(player: side.Player): number;
  export function getPlayerMaxArmour(player: side.Player): number;
  export function getPlayerMoveSpeed(player: side.Player): number;
  export function getPlayerWeapon(player: side.Player): number;
  export function getPlayerAmmo(player: side.Player): number;
  export function getPlayerAimPos(player: side.Player): side.Vector3;

  export function getPlayerHeadRotation(player: side.Player): side.Vector3;
  export function isPlayerInVehicle(player: side.Player): boolean;
  export function getPlayerVehicle(player: side.Player): side.Vehicle;
  export function getPlayerSeat(player: side.Player): number;
  export function getPlayerEntityAimingAt(player: side.Player): side.Entity;
  export function getPlayerEntityAimOffset(player: side.Player): side.Vector3;
  export function isPlayerFlashlightActive(player: side.Player): boolean;
  export function getPlayerModel(player: side.Player): number;

  //#endregion

  //#region class Vehicle

  export function getVehicleWheelSpeed(vehicle: side.Vehicle): number;
  export function getVehicleCurrentGear(vehicle: side.Vehicle): number;
  export function getVehicleCurrentRPM(vehicle: side.Vehicle): number;
  export function getVehicleSpeedVector(vehicle: side.Vehicle): side.Vector3;

  export function isVehicleHandlingModified(vehicle: side.Vehicle): boolean;
  export function getVehicleHandling(vehicle: side.Vehicle): side.HandlingData;
  export function resetVehicleHandling(vehicle: side.Vehicle): void;

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

  export function setBlipScaleXY(blip: side.Blip, scaleXY: side.Vector2): void;
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
  export function setBlipShrinked(blip: side.Blip, shrinked: boolean): void;
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

  export function getMapDataZoomScale(mapZoomData: side.MapZoomData): number;
  export function getMapDataZoomSpeed(mapZoomData: side.MapZoomData): number;
  export function getMapDataScrollSpeed(mapZoomData: side.MapZoomData): number;
  export function getMapDataTilesCountX(mapZoomData: side.MapZoomData): number;
  export function getMapDataTilesCountY(mapZoomData: side.MapZoomData): number;

  export function setMapDataZoomScale(mapZoomData: side.MapZoomData, scale: number): void;
  export function setMapDataZoomSpeed(mapZoomData: side.MapZoomData, speed: number): void;
  export function setMapDataScrollSpeed(mapZoomData: side.MapZoomData, scrollSpeed: number): void;
  export function setMapDataTilesCountX(mapZoomData: side.MapZoomData, tilesCountX: number): void;
  export function setMapDataTilesCountY(mapZoomData: side.MapZoomData, tilesCountY: number): void;

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
