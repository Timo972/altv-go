#pragma once

#include <iostream>
#include "Main.h"
#include "version/version.h"

#ifdef __cplusplus
extern "C"
{
#endif
EXPORT void Core_LogInfo(const char *message);
EXPORT void Core_LogDebug(const char *message);
EXPORT void Core_LogWarning(const char *message);
EXPORT void Core_LogError(const char *message);
EXPORT void Core_LogColored(const char *message);
EXPORT void *Core_CreateVehicle(unsigned long model, float posX, float posY, float posZ,
                                float rotX, float rotY, float rotZ);
EXPORT void *
Core_CreateCheckpoint(unsigned char type, float x, float y, float z, float radius, float height, unsigned char r,
                      unsigned char g, unsigned char b, unsigned char a);
EXPORT void *Core_CreateVoiceChannel(int spacial, float maxDistance);
EXPORT const char *Core_GetVersion();
EXPORT const char *Core_GetBranch();
EXPORT int Core_IsDebug();
EXPORT unsigned long Core_Hash(const char *str);
EXPORT int Core_FileExists(const char *path);
EXPORT const char *Core_ReadFile(const char *path);
EXPORT Entity Core_GetEntityByID(unsigned short id);
EXPORT Array Core_GetEntities();
EXPORT Array Core_GetPlayers();
EXPORT Array Core_GetVehicles();
EXPORT int Core_HasMetaData(const char *key);
EXPORT Array Core_GetMetaData(const char *key);
EXPORT void Core_SetMetaData(const char *key, unsigned char *data, unsigned long long size);
EXPORT void Core_DeleteMetaData(const char *key);
EXPORT int Core_HasSyncedMetaData(const char *key);
EXPORT Array Core_GetSyncedMetaData(const char *key);
EXPORT Array Core_GetRequiredPermissions();
EXPORT Array Core_GetOptionalPermissions();
EXPORT void Core_DestroyBaseObject(void *h);
EXPORT const char *Core_GetRootDirectory();
EXPORT int Core_StartResource(const char *name);
EXPORT void Core_StopResource(const char *name);
EXPORT void Core_RestartResource(const char *name);
EXPORT void Core_SetSyncedMetaData(const char *key, unsigned char* data, unsigned long long size);
EXPORT void Core_DeleteSyncedMetaData(const char *key);
EXPORT Array Core_GetPlayersByName(const char *name);
EXPORT unsigned int Core_GetNetTime();
EXPORT void Core_SetPassword(const char *password);
EXPORT const char *Core_GetSDKHash();
EXPORT void *Core_CreateColShapeCylinder(float posX, float posY, float posZ, float radius, float height);
EXPORT void *Core_CreateColShapeCube(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2);
EXPORT void *Core_CreateColShapeRectangle(float x1, float y1, float x2, float y2, float z);
EXPORT void *Core_CreateColShapeCircle(float posX, float posY, float posZ, float radius);
EXPORT void *Core_CreateColShapeSphere(float posX, float posY, float posZ, float radius);
EXPORT void Core_TriggerLocalEvent(const char *ev, Array args);
EXPORT void Core_TriggerClientEvent(void *p, const char *ev, Array args);
EXPORT void Core_TriggerClientEventFor(Array clients, const char *ev, Array args);
EXPORT void Core_TriggerClientEventForAll(const char *ev, Array args);
EXPORT void *Core_CreatePointBlipPosition(float x, float y, float z);
EXPORT void *Core_CreatePointBlipEntity(Entity entity);
EXPORT void *Core_CreateAreaBlip(float x, float y, float z, float width, float height);
EXPORT void *Core_CreateRadiusBlip(float x, float y, float z, float radius);
EXPORT void *Core_CreateColShapePolygon(float minZ, float maxZ, Array points);
EXPORT Array Core_GetBlips();
EXPORT Array Core_GetAllResources();
EXPORT const char *Core_StringToSHA256(const char *str);
EXPORT void Core_StopServer();
EXPORT VehicleModelInfo Core_GetVehicleModelByHash(unsigned int hash);
EXPORT Array Core_GetServerConfig();
EXPORT unsigned long long Core_HashServerPassword(const char *password);
EXPORT void* Core_GetResourceByName(const char *resourceName);
#ifdef __cplusplus
}
#endif
