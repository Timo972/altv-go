#pragma once

#include "Main.h"

#ifdef __cplusplus
extern "C"
{
#endif
    EXPORT int VoiceChannel_IsValid(const char* resourceName, void *p);
    // BaseObject inherited
    EXPORT int VoiceChannel_GetType(void *c);
    EXPORT int VoiceChannel_HasMetaData(void* base, const char *key);
    EXPORT Array VoiceChannel_GetMetaData(void* base, const char *key);
    EXPORT void VoiceChannel_SetMetaData(void *base, const char *key, Array data);
    EXPORT void VoiceChannel_DeleteMetaData(void *base, const char *key);
    EXPORT void VoiceChannel_Destroy(void *b);

    // VoiceChannel methods
    EXPORT int VoiceChannel_IsSpatial(void *v);
    EXPORT float VoiceChannel_GetMaxDistance(void *v);
    EXPORT int VoiceChannel_HasPlayer(void *v, void *p);
    EXPORT void VoiceChannel_AddPlayer(void *v, void *p);
    EXPORT void VoiceChannel_RemovePlayer(void *v, void *p);
    EXPORT int VoiceChannel_IsPlayerMuted(void *v, void *p);
    EXPORT void VoiceChannel_MutePlayer(void *v, void *p);
    EXPORT void VoiceChannel_UnmutePlayer(void *v, void *p);

    EXPORT unsigned long long VoiceChannel_GetPlayerCount(void *v);
    EXPORT Array VoiceChannel_GetPlayers(void *v);
#ifdef __cplusplus
}
#endif
