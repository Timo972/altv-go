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

EXPORT Array Resource_GetConfig(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	//return Go::Runtime::ConfigNodeToProtoBytes(resource->GetConfig());
    // FIXME:
    Array config{};
    return config;
}

EXPORT Array Resource_GetExports(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	alt::MValue e = resource->GetExports();

    return Go::Runtime::EncodeMValue(e);
}

EXPORT Array Resource_GetDependencies(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	auto deps = resource->GetDependencies();

	Array arr;
	arr.size = deps.size();
	auto d = Go::Runtime::AllocateArray<const char*>(arr.size);

	for (auto i = 0; i < arr.size; i++) {
		d[i] = deps[i].c_str();
	}

	arr.array = d;

	return arr;
}

EXPORT Array Resource_GetDependants(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	auto deps = resource->GetDependants();

	Array arr;
	arr.size = deps.size();
	auto d = Go::Runtime::AllocateArray<const char*>(arr.size);

	for (auto i = 0; i < arr.size; i++) {
		d[i] = deps[i].c_str();
	}

	arr.array = d;

	return arr;
}

EXPORT Array Resource_GetRequiredPermissions(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	return Go::Runtime::CreateArray<alt::Permission, unsigned char>(resource->GetRequiredPermissions());
}

EXPORT Array Resource_GetOptionalPermissions(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	return Go::Runtime::CreateArray<alt::Permission, unsigned char>(resource->GetOptionalPermissions());
}

EXPORT const char* Resource_GetPath(void* r) {
	auto resource = reinterpret_cast<alt::IResource*>(r);
	return resource->GetPath().c_str();
}