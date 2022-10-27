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

EXPORT void *Core_CreateVehicle(unsigned long model, float posX, float posY, float posZ,
                                float rotX, float rotY, float rotZ) {
    alt::Position position(posX, posY, posZ);
    alt::Rotation rotation(rotX, rotY, rotZ);

    auto vehicle = alt::ICore::Instance().CreateVehicle(model, position, rotation);
    return vehicle.Get();
}

EXPORT void *Core_CreateCheckpoint(unsigned char type, float x, float y, float z, float radius, float height, unsigned char r,
                      unsigned char g, unsigned char b, unsigned char a) {
    alt::RGBA rgba(r, g, b, a);
    alt::Vector<float, 3, alt::PointLayout> pos;
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;

    auto checkpoint = alt::ICore::Instance().CreateCheckpoint(type, pos, radius, height, rgba);
    return checkpoint.Get();
}

EXPORT void *Core_CreateVoiceChannel(int spacial, float maxDistance) {
    auto voiceChannel = alt::ICore::Instance().CreateVoiceChannel(spacial, maxDistance);
    return voiceChannel.Get();
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
    auto entity = alt::ICore::Instance().GetEntityByID(id);

    return Go::Runtime::GetEntity(entity);
}

EXPORT Array Core_GetEntities() {
    auto entities = alt::ICore::Instance().GetEntities();
    Array arr;
    arr.size = entities.GetSize();

#ifdef _WIN32
    auto entityRefs = new Entity[arr.size];
#else
    Entity entityRefs[arr.size];
#endif

    for (uint64_t i = 0; i < arr.size; i++) {
        auto entity = entities[i];

        entityRefs[i] = Go::Runtime::GetEntity(entity);
    }

    arr.array = entityRefs;

    return arr;
}

EXPORT Array Core_GetPlayers() {
    auto entities = alt::ICore::Instance().GetPlayers();
    return Go::Runtime::GetInstance()->CreatePointerArray(entities);
}


EXPORT Array Core_GetVehicles() {
    auto entities = alt::ICore::Instance().GetVehicles();
    return Go::Runtime::CreatePointerArray(entities);
}

EXPORT int Core_HasMetaData(const char *key) {
    return alt::ICore::Instance().HasMetaData(key);
}

EXPORT GoValue Core_GetMetaData(const char *key) {
    auto meta = alt::ICore::Instance().GetMetaData(key);

    GoValue data{};
    Go::Runtime::MValueToGo(meta, &data);

    return data;
}

EXPORT void Core_SetMetaData(const char *key, GoValue data) {
    auto value = Go::Runtime::GoToMValue(data);
    alt::ICore::Instance().SetMetaData(key, value);
}

EXPORT void Core_DeleteMetaData(const char *key) {
    alt::ICore::Instance().DeleteMetaData(key);
}

EXPORT int Core_HasSyncedMetaData(const char *key) {
    return alt::ICore::Instance().HasSyncedMetaData(key);
}

EXPORT GoValue Core_GetSyncedMetaData(const char *key) {
    auto meta = alt::ICore::Instance().GetSyncedMetaData(key);
    GoValue data{};
    Go::Runtime::MValueToGo(meta, &data);

    return data;
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

EXPORT void Core_SetSyncedMetaData(const char *key, GoValue data) {
    auto value = Go::Runtime::GoToMValue(data);
    alt::ICore::Instance().SetSyncedMetaData(key, value);
}

EXPORT void Core_DeleteSyncedMetaData(const char *key) {
    alt::ICore::Instance().DeleteSyncedMetaData(key);
}

EXPORT Array Core_GetPlayersByName(const char *name) {
    auto players = alt::ICore::Instance().GetPlayersByName(name);

    return Go::Runtime::CreatePointerArray(players);
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

EXPORT void *Core_CreateColShapeSphere(float posX, float posY, float posZ, float radius) {
    alt::Position position(posX, posY, posZ);

    auto colShape = alt::ICore::Instance().CreateColShapeSphere(position, radius);
    return colShape.Get();
}

EXPORT void *Core_CreateColShapeCircle(float posX, float posY, float posZ, float radius) {
    alt::Position position(posX, posY, posZ);

    auto colShape = alt::ICore::Instance().CreateColShapeCircle(position, radius);
    return colShape.Get();
}

EXPORT void *Core_CreateColShapeRectangle(float x1, float y1, float x2, float y2, float z) {

    auto colShape = alt::ICore::Instance().CreateColShapeRectangle(x1, y1, x2, y2, z);
    return colShape.Get();
}

EXPORT void *Core_CreateColShapeCube(float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2) {
    alt::Position position(posX1, posY1, posZ1);
    alt::Position position2(posX2, posY2, posZ2);

    auto colShape = alt::ICore::Instance().CreateColShapeCube(position, position2);
    return colShape.Get();
}

EXPORT void *Core_CreateColShapeCylinder(float posX, float posY, float posZ, float radius, float height) {
    alt::Position position(posX, posY, posZ);

    auto colShape = alt::ICore::Instance().CreateColShapeCylinder(position, radius, height);
    return colShape.Get();
}

EXPORT void Core_TriggerLocalEvent(const char *ev, GoValueArgs data) {
    auto args = Go::Runtime::GoToMValueArgs(data);
    // call event
    alt::ICore::Instance().TriggerLocalEvent(ev, args);
}

EXPORT void Core_TriggerClientEvent(void *p, const char *ev, GoValueArgs data) {

    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto args = Go::Runtime::GoToMValueArgs(data);
    // call event
    alt::ICore::Instance().TriggerClientEvent(alt::Ref<alt::IPlayer>(player), ev, args);
}

EXPORT void Core_TriggerClientEventFor(Array clients, const char *ev, GoValueArgs data) {
    alt::Array<alt::Ref<alt::IPlayer>> players;

    auto playerRefs = reinterpret_cast<alt::IPlayer**>(clients.array);

    for (unsigned long long i = 0; i < clients.size; i++) {
        players.Push(alt::Ref<alt::IPlayer>(playerRefs[i]));
    }

    auto args = Go::Runtime::GoToMValueArgs(data);

    alt::ICore::Instance().TriggerClientEvent(players, ev, args);
}

EXPORT void Core_TriggerClientEventForAll(const char *ev, GoValueArgs data) {
    auto args = Go::Runtime::GoToMValueArgs(data);

    alt::ICore::Instance().TriggerClientEventForAll(ev, args);
}

EXPORT void *Core_CreatePointBlipPosition(float x, float y, float z) {
    auto blip = alt::ICore::Instance().CreateBlip(nullptr, alt::IBlip::BlipType::DESTINATION, alt::Position(x, y, z));
    return blip.Get();
}

EXPORT void *Core_CreatePointBlipEntity(Entity entity) {
    auto blip = alt::ICore::Instance().CreateBlip(nullptr, alt::IBlip::BlipType::DESTINATION, Go::Runtime::GetEntityRef(entity));
    return blip.Get();
}

EXPORT void *Core_CreateAreaBlip(float x, float y, float z, float width, float height) {
    auto blip = alt::ICore::Instance().CreateBlip(nullptr, alt::IBlip::BlipType::AREA, alt::Position(x, y, z));
    blip->SetScaleXY({width, height});

    return blip.Get();
}

EXPORT void *Core_CreateRadiusBlip(float x, float y, float z, float radius) {
    auto blip = alt::ICore::Instance().CreateBlip(nullptr, alt::IBlip::BlipType::RADIUS, alt::Position(x, y, z));
    blip->SetScaleXY({radius, radius});

    return blip.Get();
}

EXPORT void *Core_CreateColShapePolygon(float minZ, float maxZ, Array points) {
    std::vector<alt::Vector2f> p;
    auto data = reinterpret_cast<Vector2*>(points.array);

    for (uint64_t i = 0; i < points.size; i++) {
        Vector2 v = data[i];
        p.push_back(alt::Vector2f(v.x, v.y));
    }

    auto cs = alt::ICore::Instance().CreateColShapePolygon(minZ, maxZ, p);
    return cs.Get();
}

EXPORT Array Core_GetBlips() {
    auto blips = alt::ICore::Instance().GetBlips();
    return Go::Runtime::GetInstance()->CreatePointerArray(blips);
}

EXPORT Array Core_GetAllResources() {
    auto resources = alt::ICore::Instance().GetAllResources();
    Array arr;
    arr.size = resources.size();

#ifdef _WIN32
    auto entityRefs = new void *[arr.size];
#else
    void *entityRefs[arr.size];
#endif
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

EXPORT GoValue Core_GetServerConfig() {
    auto c = alt::ICore::Instance().GetServerConfig();

    // FIXME:
    GoValue config{};

    return config;//Go::Runtime::ConfigNodeToProtoBytes(config);
}

EXPORT unsigned long long Core_HashServerPassword(const char *password) {
    return alt::ICore::Instance().HashServerPassword(password);
}

EXPORT void* Core_GetResourceByName(const char* resourceName) {
    alt::IResource *r = alt::ICore::Instance().GetResource(resourceName);

    return r;
}