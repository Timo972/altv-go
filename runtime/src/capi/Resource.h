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
	EXPORT CArray Resource_GetConfig(void *r);
	EXPORT CArray Resource_GetExports(void *r);
	EXPORT CArray Resource_GetDependencies(void *r);
	EXPORT CArray Resource_GetDependants(void *r);
	EXPORT CArray Resource_GetRequiredPermissions(void *r);
	EXPORT CArray Resource_GetOptionalPermissions(void *r);
	EXPORT const char *Resource_GetPath(void *r);
#ifdef __cplusplus
}
#endif
