#pragma once

#include "Main.h"

#ifdef __cplusplus
extern "C"
{
#endif
	EXPORT unsigned char Resource_IsStarted(void *r);
	EXPORT const char *Resource_GetType(void *r);
	EXPORT const char *Resource_GetName(void* r);
	EXPORT const char *Resource_GetMain(void *r);
	EXPORT GoValue Resource_GetConfig(void *r);
	EXPORT GoValue Resource_GetExports(void *r);
	EXPORT Array Resource_GetDependencies(void *r);
	EXPORT Array Resource_GetDependants(void *r);
	EXPORT Array Resource_GetRequiredPermissions(void *r);
	EXPORT Array Resource_GetOptionalPermissions(void *r);
	EXPORT const char *Resource_GetPath(void *r);
#ifdef __cplusplus
}
#endif
