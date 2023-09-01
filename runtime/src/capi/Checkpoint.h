#pragma once

#include <iostream>
#include "Main.h"

#ifdef __cplusplus
extern "C"
{
#endif
    // BaseObject inherited
    EXPORT int Checkpoint_GetType(void *c);
    EXPORT int Checkpoint_HasMetaData(void* base, const char *key);
    EXPORT CArray Checkpoint_GetMetaData(void* base, const char *key);
    EXPORT void Checkpoint_SetMetaData(void *base, const char *key, CArray data);
    EXPORT void Checkpoint_DeleteMetaData(void *base, const char *key);
    EXPORT void Checkpoint_Destroy(void *b);
    EXPORT int Checkpoint_IsValid(const char* resourceName, void *p);

    // WorldObject inherited
    EXPORT CPosition Checkpoint_GetPosition(void *p);
    EXPORT void Checkpoint_SetPosition(void* p, float x, float y, float z);
    EXPORT long Checkpoint_GetDimension(void* p);
    EXPORT void Checkpoint_SetDimension(void* p, long dimension);

    // ColShape inherited
    EXPORT int Checkpoint_GetColShapeType(void *c);
    EXPORT int Checkpoint_IsEntityIn(void *c, CBaseObject e);
    EXPORT int Checkpoint_IsPointIn(void *c, float x, float y, float z);
    EXPORT void Checkpoint_SetPlayersOnly(void *c, int state);
    EXPORT int Checkpoint_IsPlayersOnly(void *c);
    EXPORT unsigned char Checkpoint_IsEntityIdIn(void *c, unsigned short id);

    // Checkpoint methods
    EXPORT unsigned char Checkpoint_GetCheckpointType(void *c);
    EXPORT float Checkpoint_GetHeight(void *c);
    EXPORT float Checkpoint_GetRadius(void *c);
    EXPORT CRGBA Checkpoint_GetColor(void *c);
    EXPORT CPosition Checkpoint_GetNextPosition(void *c);
    EXPORT void Checkpoint_SetCheckpointType(void *c, unsigned char type);
    EXPORT void Checkpoint_SetHeight(void *c, float height);
    EXPORT void Checkpoint_SetRadius(void *c, float radius);
    EXPORT void Checkpoint_SetColor(void *c, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    EXPORT void Checkpoint_SetNextPosition(void *c, float x, float y, float z);

#ifdef __cplusplus
}
#endif