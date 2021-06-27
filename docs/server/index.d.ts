/// <reference types="@altv/types-server"/>
/**
 * @module lua-server
 */
declare module "lua-server" {
  import * as side from "alt-server";

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

  //#region class Checkpoint

  export function createCheckpoint(type: number, x: number, y: number, z: number, radius: number, height: number, r: number, g: number, b: number, a: number): void;
  export function createCheckpoint(type: number, pos: side.Vector3, radius: number, height: number, r: number, g: number, b: number, a: number): void;
  export function getCheckpointType(checkpoint: side.Checkpoint): number;
  export function getCheckpointHeight(checkpoint: side.Checkpoint): number;
  export function getCheckpointRadius(checkpoint: side.Checkpoint): number;
  export function getCheckpointColor(checkpoint: side.Checkpoint): number;

  //#endregion

  //#region class ColShape

  export function createColShapeCircle(colShape: side.ColShape, x: number, y: number, radius: number): void;
  export function createColShapeCircle(colShape: side.ColShape, pos: side.Vector2, radius: number): void;
  export function createColShapeCube(colShape: side.ColShape, x1: number, y1: number, z1: number, x2: number, y2: number, z2: number): void;
  export function createColShapeCube(colShape: side.ColShape, pos1: side.Vector3, pos2: side.Vector3): void;
  export function createColShapeCylinder(colShape: side.ColShape, x: number, y: number, z: number, radius: number, height: number): void;
  export function createColShapeCylinder(colShape: side.ColShape, pos: side.Vector3, radius: number, height: number): void;
  export function createColShapeRectangle(colShape: side.ColShape, x1: number, y1: number, x2: number, y2: number): void;
  export function createColShapeRectangle(colShape: side.ColShape, pos1: side.Vector2, pos2: side.Vector2): void;
  export function createColShapeSphere(colShape: side.ColShape, x: number, y: number, z: number, radius: number): void;
  export function createColShapeSphere(colShape: side.ColShape, pos: side.Vector3, radius: number): void;
  export function getColShapeType(colShape: side.ColShape): side.ColshapeType;
  export function isEntityInColShape(colShape: side.ColShape, entity: Entity): boolean;
  export function isPointInColShape(colShape: side.ColShape, pos: side.Vector3): boolean;

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
