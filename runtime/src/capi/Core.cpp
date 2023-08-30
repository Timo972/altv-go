#include "Core.h"
#include "Runtime.h"

EXPORT void Core_LogInfo(const char *message) {
    alt::ICore::Instance().LogInfo(message);
}

EXPORT void Core_LogDebug(const char *message) {
    alt::ICore::Instance().LogDebug(message);
}

EXPORT void Core_LogWarning(const char *message) {
    alt::ICore::Instance().LogWarning(message);
}

EXPORT void Core_LogError(const char *message) {
    alt::ICore::Instance().LogError(message);
}

EXPORT void Core_LogColored(const char *message) {
    alt::ICore::Instance().LogColored(message);
}

EXPORT Entity Core_CreateVehicle(unsigned long model, float posX, float posY, float posZ,
                                float rotX, float rotY, float rotZ) {
    alt::Position position(posX, posY, posZ);
    alt::Rotation rotation(rotX, rotY, rotZ);

    auto vehicle = alt::ICore::Instance().CreateVehicle(model, position, rotation);
    return Go::Runtime::GetEntity(vehicle);
}

EXPORT Entity Core_CreateCheckpoint(unsigned char type, float x, float y, float z, float radius, float height, unsigned char r,
                      unsigned char g, unsigned char b, unsigned char a, unsigned long streamingDistance) {
    alt::RGBA rgba(r, g, b, a);
    alt::Vector<float, 3, alt::PointLayout> pos;
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;

    auto checkpoint = alt::ICore::Instance().CreateCheckpoint(type, pos, radius, height, rgba, streamingDistance);
    return Go::Runtime::GetBaseObject(checkpoint);
}

EXPORT Entity Core_CreateVoiceChannel(int spacial, float maxDistance) {
    auto voiceChannel = alt::ICore::Instance().CreateVoiceChannel(spacial, maxDistance);
    return Go::Runtime::GetBaseObject(voiceChannel);
}

EXPORT const char *Core_GetVersion() {
    static std::string ver = alt::ICore::Instance().GetVersion();
    return ver.c_str();
}

EXPORT const char *Core_GetBranch() {
    static std::string branch = alt::ICore::Instance().GetBranch();
    return branch.c_str();
}

EXPORT int Core_IsDebug() {
    return alt::ICore::Instance().IsDebug();
}

EXPORT unsigned long Core_Hash(const char *str) {
    return alt::ICore::Instance().Hash(str);
}

EXPORT int Core_FileExists(const char *path) {
    return alt::ICore::Instance().FileExists(path);
}

EXPORT const char *Core_ReadFile(const char *path) {
    static std::string content = alt::ICore::Instance().FileRead(path);
    return content.c_str();
}

EXPORT Entity Core_GetEntityByID(unsigned short id) {
    auto entity = alt::ICore::Instance().GetEntityBySyncID(id);

    return Go::Runtime::GetEntity(entity);
}

EXPORT Entity Core_GetBaseObjectByID(unsigned char type, unsigned int id) {
    auto baseObject = alt::ICore::Instance().GetBaseObjectByID(static_cast<alt::IBaseObject::Type>(type), id);

    return Go::Runtime::GetBaseObject(baseObject);
}

EXPORT Array Core_GetEntities() {
    auto entities = alt::ICore::Instance().GetEntities();
    return Go::Runtime::CreateEntityArray(entities);
}

EXPORT Array Core_GetPlayers() {
    auto entities = alt::ICore::Instance().GetBaseObjects(alt::IBaseObject::Type::PLAYER);
    return Go::Runtime::CreateEntityArray(entities);
}

EXPORT Array Core_GetVehicles() {
    auto entities = alt::ICore::Instance().GetBaseObjects(alt::IBaseObject::Type::VEHICLE);
    return Go::Runtime::CreateEntityArray(entities);
}

EXPORT Array Core_GetColShapes() {
    auto entities = alt::ICore::Instance().GetBaseObjects(alt::IBaseObject::Type::COLSHAPE);
    return Go::Runtime::CreateEntityArray(entities);
}

EXPORT Array Core_GetCheckpoints() {
    auto entities = alt::ICore::Instance().GetBaseObjects(alt::IBaseObject::Type::CHECKPOINT);
    return Go::Runtime::CreateEntityArray(entities);
}

EXPORT Array Core_GetVirtualEntities() {
    auto entities = alt::ICore::Instance().GetBaseObjects(alt::IBaseObject::Type::VIRTUAL_ENTITY);
    return Go::Runtime::CreateEntityArray(entities);
}

EXPORT Array Core_GetVirtualEntityGroups() {
    auto entities = alt::ICore::Instance().GetBaseObjects(alt::IBaseObject::Type::VIRTUAL_ENTITY_GROUP);
    return Go::Runtime::CreateEntityArray(entities);
}

EXPORT Array Core_GetMarkers() {
    auto entities = alt::ICore::Instance().GetBaseObjects(alt::IBaseObject::Type::MARKER);
    return Go::Runtime::CreateEntityArray(entities);
}

EXPORT Array Core_GetPeds() {
    auto entities = alt::ICore::Instance().GetBaseObjects(alt::IBaseObject::Type::PED);
    return Go::Runtime::CreateEntityArray(entities);
}

EXPORT int Core_HasMetaData(const char *key) {
    return alt::ICore::Instance().HasMetaData(key);
}

EXPORT Array Core_GetMetaData(const char *key) {
    auto meta = alt::ICore::Instance().GetMetaData(key);
    return Go::Runtime::EncodeMValue(meta);
}

EXPORT void Core_SetMetaData(const char *key, Array data) {
    auto value = Go::Runtime::DecodeMValue(data);
    alt::ICore::Instance().SetMetaData(key, value);
}

EXPORT void Core_DeleteMetaData(const char *key) {
    alt::ICore::Instance().DeleteMetaData(key);
}

EXPORT int Core_HasSyncedMetaData(const char *key) {
    return alt::ICore::Instance().HasSyncedMetaData(key);
}

EXPORT Array Core_GetSyncedMetaData(const char *key) {
    auto meta = alt::ICore::Instance().GetSyncedMetaData(key);
    return Go::Runtime::EncodeMValue(meta);
}

EXPORT Array Core_GetRequiredPermissions() {
    auto perms = alt::ICore::Instance().GetRequiredPermissions();
    return Go::Runtime::CreateArray<alt::Permission, unsigned char>(perms);
}

EXPORT Array Core_GetOptionalPermissions() {
    auto perms = alt::ICore::Instance().GetOptionalPermissions();
    return Go::Runtime::CreateArray<alt::Permission, unsigned char>(perms);
}

EXPORT void Core_DestroyBaseObject(void *h) {
    auto handle = reinterpret_cast<alt::IBaseObject *>(h);
    alt::ICore::Instance().DestroyBaseObject(handle);
}

EXPORT const char *Core_GetRootDirectory() {
    return alt::ICore::Instance().GetRootDirectory().c_str();
}

EXPORT int Core_StartResource(const char *name) {
    return alt::ICore::Instance().StartResource(name)->IsStarted();
}

EXPORT void Core_StopResource(const char *name) {
    alt::ICore::Instance().StopResource(name);
}

EXPORT void Core_RestartResource(const char *name) {
    alt::ICore::Instance().RestartResource(name);
}

EXPORT void Core_SetSyncedMetaData(const char *key, Array data) {
    auto value = Go::Runtime::DecodeMValue(data);
    alt::ICore::Instance().SetSyncedMetaData(key, value);
}

EXPORT void Core_DeleteSyncedMetaData(const char *key) {
    alt::ICore::Instance().DeleteSyncedMetaData(key);
}

EXPORT Array Core_GetPlayersByName(const char *name) {
    auto players = alt::ICore::Instance().GetPlayersByName(name);
    return Go::Runtime::CreateEntityArray(players);
}

EXPORT unsigned int Core_GetNetTime() {
    return alt::ICore::Instance().GetNetTime();
}

EXPORT void Core_SetPassword(const char *password) {
    alt::ICore::Instance().SetPassword(password);
}

EXPORT const char *Core_GetSDKHash() {
    return ALT_SDK_VERSION;
}

EXPORT Entity Core_CreateColShapeSphere(float posX, float posY, float posZ, float radius) {
    alt::Position position(posX, posY, posZ);

    auto colShape = alt::ICore::Instance().CreateColShapeSphere(position, radius);
    return Go::Runtime::GetBaseObject(colShape);
}

EXPORT Entity Core_CreateColShapeCircle(float posX, float posY, float posZ, float radius) {
    alt::Position position(posX, posY, posZ);

    auto colShape = alt::ICore::Instance().CreateColShapeCircle(position, radius);
    return Go::Runtime::GetBaseObject(colShape);
}

EXPORT Entity Core_CreateColShapeRectangle(float x1, float y1, float x2, float y2, float z) {

    auto colShape = alt::ICore::Instance().CreateColShapeRectangle(x1, y1, x2, y2, z);
    return Go::Runtime::GetBaseObject(colShape);
}

EXPORT Entity Core_CreateColShapeCube(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2) {
    alt::Position position(posX1, posY1, posZ1);
    alt::Position position2(posX2, posY2, posZ2);

    auto colShape = alt::ICore::Instance().CreateColShapeCube(position, position2);
    return Go::Runtime::GetBaseObject(colShape);
}

EXPORT Entity Core_CreateColShapeCylinder(float posX, float posY, float posZ, float radius, float height) {
    alt::Position position(posX, posY, posZ);

    auto colShape = alt::ICore::Instance().CreateColShapeCylinder(position, radius, height);
    return Go::Runtime::GetBaseObject(colShape);
}

EXPORT void Core_TriggerLocalEvent(const char *ev, Array data) {
    auto args = Go::Runtime::DecodeMValueArgs(data);
    // call event
    alt::ICore::Instance().TriggerLocalEvent(ev, args);
}

EXPORT void Core_TriggerLocalEventRaw(const char* ev, char* bytes, unsigned long long size) {
    alt::MValueArgs args;
    auto data = alt::ICore::Instance().CreateMValueByteArray(reinterpret_cast<uint8_t*>(bytes), static_cast<alt::Size>(size));
    args.push_back(data);
    alt::ICore::Instance().TriggerLocalEvent(ev, args);
}

EXPORT void Core_TriggerClientEvent(void *p, const char *ev, Array data) {

    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto args = Go::Runtime::DecodeMValueArgs(data);
    // call event
    alt::ICore::Instance().TriggerClientEvent(player, ev, args);
}

EXPORT void Core_TriggerClientEventFor(Array clients, const char *ev, Array data) {
    std::vector<alt::IPlayer*> players;

    auto playerRefs = reinterpret_cast<alt::IPlayer**>(clients.array);

    for (unsigned long long i = 0; i < clients.size; i++) {
        players.push_back(playerRefs[i]);
    }

    auto args = Go::Runtime::DecodeMValueArgs(data);

    alt::ICore::Instance().TriggerClientEvent(players, ev, args);
}

EXPORT void Core_TriggerClientEventForAll(const char *ev, Array data) {
    auto args = Go::Runtime::DecodeMValueArgs(data);

    alt::ICore::Instance().TriggerClientEventForAll(ev, args);
}

EXPORT Entity Core_CreatePointBlipPosition(float x, float y, float z, unsigned short global) {
    auto blip = alt::ICore::Instance().CreateBlip(global, alt::IBlip::BlipType::DESTINATION, alt::Position(x, y, z));
    return Go::Runtime::GetBaseObject(blip);
}

EXPORT Entity Core_CreatePointBlipEntity(Entity entity, unsigned short global) {
    auto blip = alt::ICore::Instance().CreateBlip(global, alt::IBlip::BlipType::DESTINATION, Go::Runtime::GetEntityRef(entity));
    return Go::Runtime::GetBaseObject(blip);
}

EXPORT Entity Core_CreateAreaBlip(float x, float y, float z, float width, float height, unsigned short global) {
    auto blip = alt::ICore::Instance().CreateBlip(global, alt::IBlip::BlipType::AREA, alt::Position(x, y, z));
    blip->SetScaleXY({width, height});

    return Go::Runtime::GetBaseObject(blip);
}

EXPORT Entity Core_CreateRadiusBlip(float x, float y, float z, float radius, unsigned short global) {
    auto blip = alt::ICore::Instance().CreateBlip(global, alt::IBlip::BlipType::RADIUS, alt::Position(x, y, z));
    blip->SetScaleXY({radius, radius});

    return Go::Runtime::GetBaseObject(blip);
}

EXPORT Entity Core_CreateColShapePolygon(float minZ, float maxZ, Array points) {
    std::vector<alt::Vector2f> p;
    auto data = reinterpret_cast<Vector2*>(points.array);

    for (uint64_t i = 0; i < points.size; i++) {
        Vector2 v = data[i];
        p.push_back(alt::Vector2f(v.x, v.y));
    }

    auto cs = alt::ICore::Instance().CreateColShapePolygon(minZ, maxZ, p);
    return Go::Runtime::GetBaseObject(cs);
}

EXPORT Array Core_GetBlips() {
    auto blips = alt::ICore::Instance().GetBaseObjects(alt::IBaseObject::Type::BLIP);
    return Go::Runtime::CreateEntityArray(blips);
}

EXPORT Array Core_GetAllResources() {
    auto resources = alt::ICore::Instance().GetAllResources();
    
    Array arr;
    arr.size = resources.size();
    auto entityRefs = new void*[arr.size];

    for (uint64_t i = 0; i < arr.size; i++) {
        entityRefs[i] = resources.at(i);
    }

    arr.array = entityRefs;

    return arr;
}

EXPORT const char *Core_StringToSHA256(const char *str) {
    static std::string hash = alt::ICore::Instance().StringToSHA256(str);
    return hash.c_str();
}

EXPORT void Core_StopServer() {
    alt::ICore::Instance().StopServer();
}

EXPORT VehicleModelInfo Core_GetVehicleModelByHash(unsigned int hash) {
    auto modelInfo = alt::ICore::Instance().GetVehicleModelByHash(hash);

    VehicleModelInfo m;

    m.title = modelInfo.title.c_str();
    m.modelType = static_cast<unsigned char>(modelInfo.modelType);
    m.hasAutoAttachTrailer = static_cast<unsigned char>(modelInfo.hasAutoAttachTrailer);
    m.wheelsCount = modelInfo.wheelsCount;
    m.hasArmoredWindows = modelInfo.hasArmoredWindows;
    m.primaryColor = modelInfo.primaryColor;
    m.secondaryColor = modelInfo.secondaryColor;
    m.pearlColor = modelInfo.pearlColor;
    m.wheelsColor = modelInfo.wheelsColor;
    m.interiorColor = modelInfo.interiorColor;
    m.dashboardColor = modelInfo.dashboardColor;

    m.modKits[0] = modelInfo.modkits[0];
    m.modKits[1] = modelInfo.modkits[1];

    m.extras = modelInfo.extras;
    m.defaultExtras = modelInfo.defaultExtras;

    m.bones = Go::Runtime::CreateBoneArray(modelInfo.bones);

    return m;
}

EXPORT PedModelInfo Core_GetPedModelByHash(unsigned int hash) {
    auto modelInfo = alt::ICore::Instance().GetPedModelByHash(hash);

    PedModelInfo m;
    m.bones = Go::Runtime::CreateBoneArray(modelInfo.bones);
    m.hash = modelInfo.hash;
    m.name = modelInfo.name.c_str();

    return m;
}

EXPORT Array Core_GetServerConfig() {
    auto c = alt::ICore::Instance().GetServerConfig();

    // FIXME:
    Array config{};

    return config;//Go::Runtime::ConfigNodeToProtoBytes(config);
}

EXPORT unsigned long long Core_HashServerPassword(const char *password) {
    return alt::ICore::Instance().HashServerPassword(password);
}

EXPORT void* Core_GetResourceByName(const char* resourceName) {
    alt::IResource *r = alt::ICore::Instance().GetResource(resourceName);

    return r;
}