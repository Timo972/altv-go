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
EXPORT CBaseObject *Core_CreateVehicle(unsigned long model, float posX, float posY, float posZ,
                                float rotX, float rotY, float rotZ);
EXPORT CBaseObject
Core_CreateCheckpoint(unsigned char type, float x, float y, float z, float radius, float height, unsigned char r,
                      unsigned char g, unsigned char b, unsigned char a, unsigned long streamingDistance);
EXPORT CBaseObject Core_CreateVoiceChannel(int spacial, float maxDistance);
EXPORT const char *Core_GetVersion();
EXPORT const char *Core_GetBranch();
EXPORT int Core_IsDebug();
EXPORT unsigned long Core_Hash(const char *str);
EXPORT int Core_FileExists(const char *path);
EXPORT const char *Core_ReadFile(const char *path);
EXPORT CBaseObject *Core_GetEntityBySyncID(unsigned short id);
EXPORT CBaseObject *Core_GetBaseObjectByID(unsigned char type, unsigned int id);
EXPORT CArray Core_GetEntities();
EXPORT CArray Core_GetPlayers();
EXPORT CArray Core_GetVehicles();
EXPORT CArray Core_GetBlips();
EXPORT CArray Core_GetColShapes();
EXPORT CArray Core_GetCheckpoints();
EXPORT CArray Core_GetVirtualEntities();
EXPORT CArray Core_GetVirtualEntityGroups();
EXPORT CArray Core_GetMarkers();
EXPORT CArray Core_GetPeds();
EXPORT int Core_HasMetaData(const char *key);
EXPORT CArray Core_GetMetaData(const char *key);
EXPORT void Core_SetMetaData(const char *key, CArray data);
EXPORT void Core_DeleteMetaData(const char *key);
EXPORT int Core_HasSyncedMetaData(const char *key);
EXPORT CArray Core_GetSyncedMetaData(const char *key);
EXPORT CArray Core_GetRequiredPermissions();
EXPORT CArray Core_GetOptionalPermissions();
EXPORT void Core_DestroyBaseObject(void *h);
EXPORT const char *Core_GetRootDirectory();
EXPORT int Core_StartResource(const char *name);
EXPORT void Core_StopResource(const char *name);
EXPORT void Core_RestartResource(const char *name);
EXPORT void Core_SetSyncedMetaData(const char *key, CArray data);
EXPORT void Core_DeleteSyncedMetaData(const char *key);
EXPORT CArray Core_GetPlayersByName(const char *name);
EXPORT unsigned int Core_GetNetTime();
EXPORT void Core_SetPassword(const char *password);
EXPORT const char *Core_GetSDKHash();
EXPORT CBaseObject Core_CreateColShapeCylinder(float posX, float posY, float posZ, float radius, float height);
EXPORT CBaseObject Core_CreateColShapeCube(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2);
EXPORT CBaseObject Core_CreateColShapeRectangle(float x1, float y1, float x2, float y2, float z);
EXPORT CBaseObject Core_CreateColShapeCircle(float posX, float posY, float posZ, float radius);
EXPORT CBaseObject Core_CreateColShapeSphere(float posX, float posY, float posZ, float radius);
EXPORT void Core_TriggerLocalEvent(const char *ev, CArray args);
EXPORT void Core_TriggerLocalEventRaw(const char* ev, char* bytes, unsigned long long size);
EXPORT void Core_TriggerClientEvent(void *p, const char *ev, CArray args);
EXPORT void Core_TriggerClientEventFor(CArray clients, const char *ev, CArray args);
EXPORT void Core_TriggerClientEventForAll(const char *ev, CArray args);
EXPORT CBaseObject Core_CreatePointBlipPosition(float x, float y, float z, unsigned short global);
EXPORT CBaseObject Core_CreatePointBlipEntity(CBaseObject entity, unsigned short global);
EXPORT CBaseObject Core_CreateAreaBlip(float x, float y, float z, float width, float height, unsigned short global);
EXPORT CBaseObject Core_CreateRadiusBlip(float x, float y, float z, float radius, unsigned short global);
EXPORT CBaseObject Core_CreateColShapePolygon(float minZ, float maxZ, CArray points);
EXPORT CArray Core_GetAllResources();
EXPORT const char *Core_StringToSHA256(const char *str);
EXPORT void Core_StopServer();
EXPORT CVehicleModelInfo Core_GetVehicleModelByHash(unsigned int hash);
EXPORT CPedModelInfo Core_GetPedModelByHash(unsigned int hash);
EXPORT CArray Core_GetServerConfig();
EXPORT unsigned long long Core_HashServerPassword(const char *password);
EXPORT void* Core_GetResourceByName(const char *resourceName);
#ifdef __cplusplus
}
#endif
