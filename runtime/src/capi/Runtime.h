#pragma once

#include "Main.h"
#include "GoRuntime.h"
#include "GoResource.h"

#ifdef __cplusplus
extern "C"
{
#endif
    EXPORT int Runtime_RegisterAltEvent(const char *resourceName, unsigned short eventType);
    EXPORT int Runtime_UnregisterAltEvent(const char *resourceName, unsigned short eventType);
    EXPORT int Runtime_RegisterAltExport(const char *resourceName, const char *exportName, GoValue value);
    EXPORT GoValue Runtime_GetAltExport(const char *targetResourceName, const char *exportName);
    EXPORT void *Runtime_CreateMValueFunction(const char *resourceName, unsigned long long id);
    EXPORT GoValue Runtime_CallMValueFunction(void *ptr, GoValueArgs args);
    EXPORT void Connection_Accept(void *handle, unsigned char sendNames);
    EXPORT void Connection_Decline(void *handle, const char *reason);
    EXPORT int Connection_IsAccepted(void *handle);
#ifdef __cplusplus
}
#endif
