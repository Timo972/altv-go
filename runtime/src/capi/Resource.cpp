#include "Resource.h"
#include "GoRuntime.h"

EXPORT unsigned char Resource_IsStarted(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	return static_cast<unsigned char>(resource->IsStarted());
}

EXPORT const char* Resource_GetType(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	return resource->GetType().c_str();
}

EXPORT const char* Resource_GetName(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	return resource->GetName().c_str();
}

EXPORT const char* Resource_GetMain(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	return resource->GetMain().c_str();
}

EXPORT CArray Resource_GetConfig(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	//return Go::Runtime::ConfigNodeToProtoBytes(resource->GetConfig());
    // FIXME:
    CArray config{};
    return config;
}

EXPORT CArray Resource_GetExports(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	alt::MValue e = resource->GetExports();

    return Go::Runtime::EncodeMValue(e);
}

EXPORT CArray Resource_GetDependencies(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	auto deps = resource->GetDependencies();
	return Go::Runtime::CreateStringArray(deps);
}

EXPORT CArray Resource_GetDependants(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	auto deps = resource->GetDependants();
	return Go::Runtime::CreateStringArray(deps);
}

EXPORT CArray Resource_GetRequiredPermissions(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	return Go::Runtime::CreateArray<alt::Permission, unsigned char>(resource->GetRequiredPermissions());
}

EXPORT CArray Resource_GetOptionalPermissions(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	return Go::Runtime::CreateArray<alt::Permission, unsigned char>(resource->GetOptionalPermissions());
}

EXPORT const char* Resource_GetPath(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	return resource->GetPath().c_str();
}