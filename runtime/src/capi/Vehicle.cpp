#include "Vehicle.h"
#include "GoRuntime.h"
#include "GoResource.h"

EXPORT int Vehicle_HasMetaData(void *base, const char *key) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(base);
    return vehicle->HasMetaData(key);
}

EXPORT Array Vehicle_GetMetaData(void *base, const char *key) {

    auto vehicle = reinterpret_cast<alt::IVehicle *>(base);
    auto meta = vehicle->GetMetaData(key);

    auto metaData = Go::Runtime::MValueToProtoBytes(meta);

    return metaData;
}

EXPORT void Vehicle_SetMetaData(void *base, const char *key, unsigned char* data, unsigned long long size) {

    auto vehicle = reinterpret_cast<alt::IVehicle *>(base);
    auto value = Go::Runtime::ProtoToMValue(data, size);

    vehicle->SetMetaData(key, value);
}

EXPORT void Vehicle_DeleteMetaData(void *base, const char *key) {

    auto vehicle = reinterpret_cast<alt::IVehicle *>(base);
    vehicle->DeleteMetaData(key);
    // vehicle->RemoveRef();
}

EXPORT int Vehicle_HasSyncedMetaData(void *base, const char *key) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(base);
    return vehicle->HasSyncedMetaData(key);
}

EXPORT Array Vehicle_GetSyncedMetaData(void *base, const char *key) {

    auto vehicle = reinterpret_cast<alt::IVehicle *>(base);
    auto meta = vehicle->GetSyncedMetaData(key);

    auto metaData = Go::Runtime::MValueToProtoBytes(meta);

    return metaData;
}

EXPORT void Vehicle_SetSyncedMetaData(void *base, const char *key, unsigned char* data, unsigned long long size) {

    auto vehicle = reinterpret_cast<alt::IVehicle *>(base);
    auto value = Go::Runtime::ProtoToMValue(data, size);

    vehicle->SetSyncedMetaData(key, value);
}

EXPORT void Vehicle_DeleteSyncedMetaData(void *base, const char *key) {

    auto vehicle = reinterpret_cast<alt::IVehicle *>(base);
    vehicle->DeleteSyncedMetaData(key);
    // vehicle->RemoveRef();
}

EXPORT int Vehicle_HasStreamSyncedMetaData(void *base, const char *key) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(base);
    return vehicle->HasStreamSyncedMetaData(key);
}

EXPORT Array Vehicle_GetStreamSyncedMetaData(void *base, const char *key) {

    auto vehicle = reinterpret_cast<alt::IVehicle *>(base);
    auto meta = vehicle->GetStreamSyncedMetaData(key);

    auto metaData = Go::Runtime::MValueToProtoBytes(meta);

    return metaData;
}

EXPORT void Vehicle_SetStreamSyncedMetaData(void *base, const char *key, unsigned char* data, unsigned long long size) {

    auto vehicle = reinterpret_cast<alt::IVehicle *>(base);
    auto value = Go::Runtime::ProtoToMValue(data, size);

    vehicle->SetStreamSyncedMetaData(key, value);
}

EXPORT void Vehicle_DeleteStreamSyncedMetaData(void *base, const char *key) {

    auto vehicle = reinterpret_cast<alt::IVehicle *>(base);
    vehicle->DeleteStreamSyncedMetaData(key);
    // vehicle->RemoveRef();
}

EXPORT Position Vehicle_GetPosition(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    auto pos = vehicle->GetPosition();

    Position position;
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    return position;
}

EXPORT void Vehicle_SetPosition(void *v, float x, float y, float z) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);

    alt::Position pos(x,y,z);

    vehicle->SetPosition(pos);
}

EXPORT Rotation Vehicle_GetRotation(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    auto rot = vehicle->GetRotation();

    Rotation rotation;
    rotation.pitch = rot.pitch;
    rotation.yaw = rot.yaw;
    rotation.roll = rot.roll;

    return rotation;
}

EXPORT void Vehicle_SetRotation(void *v, float roll, float pitch, float yaw) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    alt::Rotation rot(roll, pitch, yaw);

    vehicle->SetRotation(rot);
}

EXPORT long Vehicle_GetDimension(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetDimension();
}

EXPORT void Vehicle_SetDimension(void *v, long dimension) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetDimension(dimension);
}

EXPORT unsigned long Vehicle_GetID(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetID();
}

EXPORT unsigned long Vehicle_GetModel(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetModel();
}

EXPORT void Vehicle_Detach(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->Detach();
}

EXPORT void Vehicle_AttachToEntity(void *v, Entity e, int otherBoneIndex, int myBoneIndex, Position pos, Rotation rot,
                                   int collision, int noFixedRotation) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    auto entity = Go::Runtime::GetEntityRef(e);

    auto position = alt::Position(pos.x, pos.y, pos.z);
    auto rotation = alt::Rotation(rot.roll, rot.pitch, rot.yaw);

    vehicle->AttachToEntity(entity, otherBoneIndex, myBoneIndex, position, rotation, collision, noFixedRotation);
}

EXPORT void Vehicle_SetVisible(void *v, int toggle) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetVisible(toggle);
}

EXPORT int Vehicle_GetVisible(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetVisible();
}

EXPORT void *Vehicle_GetNetworkOwner(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetNetworkOwner().Get();
}

EXPORT void Vehicle_SetNetworkOwner(void *v, void *o, int disableMigration) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    auto owner = reinterpret_cast<alt::IPlayer *>(o);
    vehicle->SetNetworkOwner(owner, disableMigration);
}

EXPORT void *Vehicle_GetDriver(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetDriver().Get();
}

EXPORT int Vehicle_IsDestroyed(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsDestroyed();
}

EXPORT unsigned long Vehicle_GetMod(void *v, unsigned int category) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetMod(category);
}

EXPORT unsigned long Vehicle_GetModsCount(void *v, unsigned int category) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetModsCount(category);
}

EXPORT unsigned long Vehicle_GetModKitsCount(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetModKitsCount();
}

EXPORT unsigned long Vehicle_GetModKit(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetModKit();
}

EXPORT int Vehicle_IsPrimaryColorRGB(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsPrimaryColorRGB();
}

EXPORT unsigned long Vehicle_GetPrimaryColor(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetPrimaryColor();
}

EXPORT RGBA Vehicle_GetPrimaryColorRGB(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    auto rgb = vehicle->GetPrimaryColorRGB();

    RGBA rgba;
    rgba.r = rgb.r;
    rgba.g = rgb.g;
    rgba.b = rgb.b;
    rgba.a = rgb.a;

    return rgba;
}

EXPORT int Vehicle_IsSecondaryColorRGB(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsSecondaryColorRGB();
}

EXPORT unsigned long Vehicle_GetSecondaryColor(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetSecondaryColor();
}

EXPORT RGBA Vehicle_GetSecondaryColorRGB(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    auto rgb = vehicle->GetSecondaryColorRGB();

    RGBA rgba;
    rgba.r = rgb.r;
    rgba.g = rgb.g;
    rgba.b = rgb.b;
    rgba.a = rgb.a;

    return rgba;
}

EXPORT unsigned long Vehicle_GetPearlColor(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetPearlColor();
}

EXPORT unsigned long Vehicle_GetWheelColor(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetWheelColor();
}

EXPORT unsigned long Vehicle_GetInteriorColor(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetInteriorColor();
}

EXPORT unsigned long Vehicle_GetDashboardColor(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetDashboardColor();
}

EXPORT int Vehicle_IsTireSmokeColorCustom(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsTireSmokeColorCustom();
}

EXPORT RGBA Vehicle_GetTireSmokeColor(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    auto rgb = vehicle->GetTireSmokeColor();

    RGBA rgba;
    rgba.r = rgb.r;
    rgba.g = rgb.g;
    rgba.b = rgb.b;
    rgba.a = rgb.a;

    return rgba;
}

EXPORT unsigned long Vehicle_GetWheelType(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetWheelType();
}

EXPORT unsigned long Vehicle_GetWheelVariation(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetWheelVariation();
}

EXPORT unsigned long Vehicle_GetRearWheelVariation(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetRearWheelVariation();
}

EXPORT int Vehicle_GetCustomTires(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetCustomTires();
}

EXPORT unsigned long Vehicle_GetSpecialDarkness(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetSpecialDarkness();
}

EXPORT unsigned long Vehicle_GetNumberplateIndex(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetNumberplateIndex();
}

EXPORT const char *Vehicle_GetNumberplateText(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetNumberplateText().c_str();
}

EXPORT unsigned long Vehicle_GetWindowTint(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetWindowTint();
}

EXPORT unsigned long Vehicle_GetDirtLevel(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetDirtLevel();
}

EXPORT int Vehicle_IsExtraOn(void *v, unsigned int extraID) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsExtraOn(extraID);
}

EXPORT int Vehicle_IsNeonActive(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsNeonActive();
}

EXPORT VehicleNeonState Vehicle_GetNeonActive(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);

    bool frontBool;
    bool leftBool;
    bool rightBool;
    bool backBool;

    vehicle->GetNeonActive(&leftBool, &rightBool, &frontBool, &backBool);

    VehicleNeonState state;
    state.front = frontBool;
    state.left = leftBool;
    state.right = rightBool;
    state.back = backBool;

    return state;
}

EXPORT RGBA Vehicle_GetNeonColor(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    auto rgb = vehicle->GetNeonColor();

    RGBA rgba;
    rgba.r = rgb.r;
    rgba.g = rgb.g;
    rgba.b = rgb.b;
    rgba.a = rgb.a;

    return rgba;
}

EXPORT unsigned long Vehicle_GetLivery(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetLivery();
}

EXPORT unsigned long Vehicle_GetRoofLivery(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetRoofLivery();
}

EXPORT const char *Vehicle_GetAppearanceDataBase64(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetAppearanceDataBase64().c_str();
}

EXPORT int Vehicle_IsEngineOn(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsEngineOn();
}

EXPORT int Vehicle_IsHandbrakeActive(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsHandbrakeActive();
}

EXPORT unsigned long Vehicle_GetHeadlightColor(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetHeadlightColor();
}

EXPORT unsigned long Vehicle_GetRadioStationIndex(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetRadioStationIndex();
}

EXPORT int Vehicle_IsSirenActive(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsSirenActive();
}

EXPORT unsigned long Vehicle_GetLockState(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetLockState();
}

EXPORT unsigned long Vehicle_GetDoorState(void *v, unsigned int doorId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetDoorState(doorId);
}

EXPORT int Vehicle_IsWindowOpened(void *v, unsigned int windowId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsWindowOpened(windowId);
}

EXPORT int Vehicle_IsDaylightOn(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsDaylightOn();
}

EXPORT int Vehicle_IsNightlightOn(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsNightlightOn();
}

EXPORT unsigned long Vehicle_GetRoofState(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetRoofState();
}

EXPORT int Vehicle_IsFlamethrowerActive(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsFlamethrowerActive();
}

EXPORT float Vehicle_GetLightsMultiplier(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetLightsMultiplier();
}

EXPORT const char *Vehicle_GetGameStateBase64(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetGameStateBase64().c_str();
}

EXPORT long Vehicle_GetEngineHealth(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetEngineHealth();
}

EXPORT long Vehicle_GetPetrolTankHealth(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetPetrolTankHealth();
}

EXPORT unsigned long Vehicle_GetWheelsCount(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetWheelsCount();
}

EXPORT int Vehicle_IsWheelBurst(void *v, unsigned int wheelId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsWheelBurst(wheelId);
}

EXPORT int Vehicle_DoesWheelHasTire(void *v, unsigned int wheelId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->DoesWheelHasTire(wheelId);
}

EXPORT int Vehicle_IsWheelDetached(void *v, unsigned int wheelId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsWheelDetached(wheelId);
}

EXPORT int Vehicle_IsWheelOnFire(void *v, unsigned int wheelId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsWheelOnFire(wheelId);
}

EXPORT float Vehicle_GetWheelHealth(void *v, unsigned int wheelId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetWheelHealth(wheelId);
}

EXPORT unsigned long Vehicle_GetRepairsCount(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetRepairsCount();
}

EXPORT unsigned long Vehicle_GetBodyHealth(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetBodyHealth();
}

EXPORT unsigned long Vehicle_GetBodyAdditionalHealth(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetBodyAdditionalHealth();
}

EXPORT const char *Vehicle_GetHealthDataBase64(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetHealthDataBase64().c_str();
}

EXPORT unsigned long Vehicle_GetPartDamageLevel(void *v, unsigned int partId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetPartDamageLevel(partId);
}

EXPORT unsigned long Vehicle_GetPartBulletHoles(void *v, unsigned int partId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetPartBulletHoles(partId);
}

EXPORT int Vehicle_IsLightDamaged(void *v, unsigned int lightId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsLightDamaged(lightId);
}

EXPORT int Vehicle_IsWindowDamaged(void *v, unsigned int windowId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsWindowDamaged(windowId);
}

EXPORT int Vehicle_IsSpecialLightDamaged(void *v, unsigned int specialLightId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsSpecialLightDamaged(specialLightId);
}

EXPORT int Vehicle_HasArmoredWindows(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->HasArmoredWindows();
}

EXPORT float Vehicle_GetArmoredWindowHealth(void *v, unsigned int windowId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetArmoredWindowHealth(windowId);
}

EXPORT unsigned long Vehicle_GetArmoredWindowShootCount(void *v, unsigned int windowId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetArmoredWindowShootCount(windowId);
}

EXPORT unsigned long Vehicle_GetBumperDamageLevel(void *v, unsigned int bumperId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetBumperDamageLevel(bumperId);
}

EXPORT const char *Vehicle_GetDamageDataBase64(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetDamageDataBase64().c_str();
}

EXPORT int Vehicle_IsManualEngineControl(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsManualEngineControl();
}

EXPORT const char *Vehicle_GetScriptDataBase64(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetScriptDataBase64().c_str();
}

EXPORT void Vehicle_ToggleExtra(void *v, unsigned int extraID, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->ToggleExtra(extraID, state);
}

EXPORT void Vehicle_SetFixed(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetFixed();
}

EXPORT int Vehicle_SetMod(void *v, unsigned int category, unsigned int id) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->SetMod(category, id);
}

EXPORT int Vehicle_SetModKit(void *v, unsigned int id) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->SetModKit(id);
}

EXPORT void Vehicle_SetPrimaryColor(void *v, unsigned int color) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetPrimaryColor(color);
}

EXPORT void Vehicle_SetPrimaryColorRGB(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    alt::RGBA rgba(r,g,b,a);

    vehicle->SetPrimaryColorRGB(rgba);
}

EXPORT void Vehicle_SetSecondaryColor(void *v, unsigned int color) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetSecondaryColor(color);
}

EXPORT void Vehicle_SetSecondaryColorRGB(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    alt::RGBA rgba(r,g,b,a);

    vehicle->SetSecondaryColorRGB(rgba);
}

EXPORT void Vehicle_SetPearlColor(void *v, unsigned int color) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetPearlColor(color);
}

EXPORT void Vehicle_SetWheelColor(void *v, unsigned int color) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetWheelColor(color);
}

EXPORT void Vehicle_SetInteriorColor(void *v, unsigned int color) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetInteriorColor(color);
}

EXPORT void Vehicle_SetDashboardColor(void *v, unsigned int color) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetDashboardColor(color);
}

EXPORT void Vehicle_SetTireSmokeColor(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    alt::RGBA rgba(r,g,b,a);

    vehicle->SetTireSmokeColor(rgba);
}

EXPORT void Vehicle_SetWheels(void *v, unsigned int type, unsigned int variation) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetWheels(type, variation);
}

EXPORT void Vehicle_SetRearWheels(void *v, unsigned int variation) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetRearWheels(variation);
}

EXPORT void Vehicle_SetCustomTires(void *v, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetCustomTires(state);
}

EXPORT void Vehicle_SetSpecialDarkness(void *v, unsigned int value) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetSpecialDarkness(value);
}

EXPORT void Vehicle_SetNumberplateIndex(void *v, unsigned int index) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetNumberplateIndex(index);
}

EXPORT void Vehicle_SetNumberplateText(void *v, const char *text) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetNumberplateText(text);
}

EXPORT void Vehicle_SetWindowTint(void *v, unsigned int tint) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetWindowTint(tint);
}

EXPORT void Vehicle_SetDirtLevel(void *v, unsigned int level) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetDirtLevel(level);
}

EXPORT void Vehicle_SetNeonActive(void *v, int left, int right, int front, int back) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetNeonActive(left, right, front, back);
}

EXPORT void Vehicle_SetNeonColor(void *v, unsigned int r, unsigned int g, unsigned int b, unsigned int a) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    alt::RGBA rgba(r,g,b,a);

    vehicle->SetNeonColor(rgba);
}

EXPORT void Vehicle_SetLivery(void *v, unsigned int livery) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetLivery(livery);
}

EXPORT void Vehicle_SetRoofLivery(void *v, unsigned int roofLivery) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetRoofLivery(roofLivery);
}

EXPORT void Vehicle_SetEngineOn(void *v, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetEngineOn(state);
}

EXPORT void Vehicle_SetHeadlightColor(void *v, unsigned int color) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetHeadlightColor(color);
}

EXPORT void Vehicle_SetRadioStationIndex(void *v, unsigned int stationIndex) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetRadioStationIndex(stationIndex);
}

EXPORT void Vehicle_SetSirenActive(void *v, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetSirenActive(state);
}

EXPORT void Vehicle_SetLockState(void *v, unsigned int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetLockState(state);
}

EXPORT void Vehicle_SetDoorState(void *v, unsigned int doorId, unsigned int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetDoorState(doorId, state);
}

EXPORT void Vehicle_SetWindowOpened(void *v, unsigned int windowId, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetWindowOpened(windowId, state);
}

EXPORT void Vehicle_SetRoofState(void *v, unsigned int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetRoofState(state);
}

EXPORT void Vehicle_SetLightsMultiplier(void *v, float multiplier) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetLightsMultiplier(multiplier);
}

EXPORT void Vehicle_SetEngineHealth(void *v, unsigned long health) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetEngineHealth(health);
}

EXPORT void Vehicle_SetPetrolTankHealth(void *v, unsigned long health) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetPetrolTankHealth(health);
}

EXPORT void Vehicle_SetWheelBurst(void *v, unsigned int wheelId, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetWheelBurst(wheelId, state);
}

EXPORT void Vehicle_SetWheelHasTire(void *v, unsigned int wheelId, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetWheelHasTire(wheelId, state);
}

EXPORT void Vehicle_SetWheelDetached(void *v, unsigned int wheelId, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetWheelDetached(wheelId, state);
}

EXPORT void Vehicle_SetWheelOnFire(void *v, unsigned int wheelId, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetWheelOnFire(wheelId, state);
}

EXPORT void Vehicle_SetWheelHealth(void *v, unsigned int wheelId, float health) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetWheelHealth(wheelId, health);
}

EXPORT void Vehicle_SetWheelFixed(void *v, unsigned int wheelId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetWheelFixed(wheelId);
}

EXPORT void Vehicle_SetBodyHealth(void *v, unsigned long health) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetBodyHealth(health);
}

EXPORT void Vehicle_SetBodyAdditionalHealth(void *v, unsigned long health) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetBodyAdditionalHealth(health);
}

EXPORT void Vehicle_SetPartDamageLevel(void *v, unsigned int partId, unsigned int damage) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetPartDamageLevel(partId, damage);
}

EXPORT void Vehicle_SetPartBulletHoles(void *v, unsigned int partId, unsigned int shootsCount) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetPartBulletHoles(partId, shootsCount);
}

EXPORT void Vehicle_SetLightDamaged(void *v, unsigned int lightId, int isDamaged) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetLightDamaged(lightId, isDamaged);
}

EXPORT void Vehicle_SetWindowDamaged(void *v, unsigned int windowId, int isDamaged) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetWindowDamaged(windowId, isDamaged);
}

EXPORT void Vehicle_SetSpecialLightDamaged(void *v, unsigned int specialLightId, int isDamaged) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetSpecialLightDamaged(specialLightId, isDamaged);
}

EXPORT void Vehicle_SetArmoredWindowHealth(void *v, unsigned int windowId, float health) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetArmoredWindowHealth(windowId, health);
}

EXPORT void Vehicle_SetArmoredWindowShootCount(void *v, unsigned int windowId, unsigned int count) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetArmoredWindowShootCount(windowId, count);
}

EXPORT void Vehicle_SetBumperDamageLevel(void *v, unsigned int bumperId, unsigned int damageLevel) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetBumperDamageLevel(bumperId, damageLevel);
}

EXPORT void Vehicle_SetManualEngineControl(void *v, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetManualEngineControl(state);
}

EXPORT void *Vehicle_GetAttached(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetAttached().Get();
}

EXPORT void *Vehicle_GetAttachedTo(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetAttachedTo().Get();
}

EXPORT void Vehicle_Destroy(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    alt::ICore::Instance().DestroyBaseObject(vehicle);
}

EXPORT int Vehicle_IsValid(const char *resourceName, void *p) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(p);
    auto resource = dynamic_cast<Go::Resource*>(Go::Runtime::GetInstance()->GetResource(resourceName));

    return resource->HasEntity(vehicle);
}

EXPORT int Vehicle_GetStreamed(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetStreamed();
}

EXPORT void Vehicle_SetStreamed(void *v, int toggle) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetStreamed(toggle);
}

EXPORT int Vehicle_IsFrozen(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsFrozen();
}

EXPORT void Vehicle_SetFrozen(void *v, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetFrozen(state);
}

EXPORT int Vehicle_HasCollision(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->HasCollision();
}

EXPORT void Vehicle_SetCollision(void *v, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetCollision(state);
}

EXPORT void Vehicle_LoadDamageDataFromBase64(void *v, const char *base64) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->LoadDamageDataFromBase64(base64);
}

EXPORT void Vehicle_LoadScriptDataFromBase64(void *v, const char *base64) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->LoadScriptDataFromBase64(base64);
}

EXPORT void Vehicle_LoadGameStateFromBase64(void *v, const char *base64) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->LoadGameStateFromBase64(base64);
}

EXPORT void Vehicle_LoadHealthDataFromBase64(void *v, const char *base64) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->LoadHealthDataFromBase64(base64);
}

EXPORT int Vehicle_IsDriftMode(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsDriftMode();
}

EXPORT void Vehicle_SetDriftMode(void *v, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetDriftMode(state);
}

EXPORT int Vehicle_IsTrainMissionTrain(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsTrainMissionTrain();
}

EXPORT void Vehicle_SetTrainMissionTrain(void *v, int value) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainMissionTrain(value);
}

EXPORT char Vehicle_GetTrainTrackId(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainTrackId();
}

EXPORT void Vehicle_SetTrainTrackId(void *v, char trackId) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainTrackId(trackId);
}

EXPORT void *Vehicle_GetTrainEngineId(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainEngineId().Get();
}

EXPORT void Vehicle_SetTrainEngineId(void *v, void *e) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    auto engine = reinterpret_cast<alt::IVehicle *>(e);
    vehicle->SetTrainEngineId(engine);
}

EXPORT char Vehicle_GetTrainConfigIndex(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainConfigIndex();
}

EXPORT void Vehicle_SetTrainConfigIndex(void *v, char trainConfigIndex) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainConfigIndex(trainConfigIndex);
}

EXPORT float Vehicle_GetTrainDistanceFromEngine(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainDistanceFromEngine();
}

EXPORT void Vehicle_SetTrainDistanceFromEngine(void *v, float distanceFromEngine) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainDistanceFromEngine(distanceFromEngine);
}

EXPORT int Vehicle_IsTrainEngine(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsTrainEngine();
}

EXPORT void Vehicle_SetTrainIsEngine(void *v, int isEngine) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainIsEngine(isEngine);
}

EXPORT int Vehicle_IsTrainCaboose(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsTrainCaboose();
}

EXPORT void Vehicle_SetTrainIsCaboose(void *v, int isCaboose) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainIsCaboose(isCaboose);
}

EXPORT int Vehicle_GetTrainDirection(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainDirection();
}

EXPORT void Vehicle_SetTrainDirection(void *v, int direction) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainDirection(direction);
}

EXPORT int Vehicle_HasTrainPassengerCarriages(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->HasTrainPassengerCarriages();
}

EXPORT void Vehicle_SetTrainHasPassengerCarriages(void *v, int hasPassengerCarriages) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainHasPassengerCarriages(hasPassengerCarriages);
}

EXPORT int Vehicle_GetTrainRenderDerailed(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainRenderDerailed();
}

EXPORT void Vehicle_SetTrainRenderDerailed(void *v, int renderDerailed) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainRenderDerailed(renderDerailed);
}

EXPORT int Vehicle_GetTrainForceDoorsOpen(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainForceDoorsOpen();
}

EXPORT void Vehicle_SetTrainForceDoorsOpen(void *v, int forceDoorsOpen) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainForceDoorsOpen(forceDoorsOpen);
}

EXPORT float Vehicle_GetTrainCruiseSpeed(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainCruiseSpeed();
}

EXPORT void Vehicle_SetTrainCruiseSpeed(void *v, float cruiseSpeed) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainCruiseSpeed(cruiseSpeed);
}

EXPORT char Vehicle_GetTrainCarriageConfigIndex(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainCarriageConfigIndex();
}

EXPORT void Vehicle_SetTrainCarriageConfigIndex(void *v, char carriageConfigIndex) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainCarriageConfigIndex(carriageConfigIndex);
}

EXPORT void *Vehicle_GetTrainLinkedToBackwardId(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainLinkedToBackwardId().Get();
}

EXPORT void Vehicle_SetTrainLinkedToBackwardId(void *v, void *e) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    auto train = reinterpret_cast<alt::IVehicle *>(e);
    vehicle->SetTrainLinkedToBackwardId(train);
}

EXPORT void *Vehicle_GetTrainLinkedToForwardId(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainLinkedToForwardId().Get();
}

EXPORT void Vehicle_SetTrainLinkedToForwardId(void *v, void *e) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    auto train = reinterpret_cast<alt::IVehicle *>(e);
    vehicle->SetTrainLinkedToForwardId(train);
}

EXPORT void Vehicle_SetTrainUnk1(void *v, int unk1) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainUnk1(unk1);
}

EXPORT int Vehicle_GetTrainUnk1(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainUnk1();
}

EXPORT void Vehicle_SetTrainUnk2(void *v, int unk2) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainUnk2(unk2);
}

EXPORT int Vehicle_GetTrainUnk2(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainUnk2();
}

EXPORT void Vehicle_SetTrainUnk3(void *v, int unk3) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTrainUnk3(unk3);
}

EXPORT int Vehicle_GetTrainUnk3(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTrainUnk3();
}


EXPORT int Vehicle_IsBoatAnchorActive(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsBoatAnchorActive();
}

EXPORT void Vehicle_SetBoatAnchorActive(void *v, int state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetBoatAnchorActive(state);
}

EXPORT int Vehicle_SetSearchLight(void *v, int state, Entity e) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    auto target = Go::Runtime::GetEntityRef(e);
    return vehicle->SetSearchLight(state, target);
}

EXPORT unsigned char Vehicle_GetLightState(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetLightState();
}

EXPORT void Vehicle_SetLightState(void *v, unsigned char state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetLightState(state);
}

EXPORT unsigned char Vehicle_HasTimedExplosion(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->HasTimedExplosion();
}

EXPORT void *Vehicle_GetTimedExplosionCulprit(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTimedExplosionCulprit().Get();
}

EXPORT unsigned int Vehicle_GetTimedExplosionTime(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetTimedExplosionTime();
}

EXPORT void Vehicle_SetTimedExplosion(void *v, unsigned char state, void *culprit, unsigned int time) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    auto player = reinterpret_cast<alt::IPlayer *>(culprit);
    vehicle->SetTimedExplosion(state, player, time);
}

EXPORT unsigned char Vehicle_IsTowingDisabled(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->IsTowingDisabled();
}

EXPORT void Vehicle_SetTowingDisabled(void *v, unsigned char state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetTowingDisabled(state);
}

EXPORT float Vehicle_GetRocketRefuelSpeed(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetRocketRefuelSpeed();
}

EXPORT void Vehicle_SetRocketRefuelSpeed(void *v, float speed) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetRocketRefuelSpeed(speed);
}

EXPORT unsigned int Vehicle_GetBombCount(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetBombCount();
}

EXPORT void Vehicle_SetBombCount(void *v, unsigned int count) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetBombCount(count);
}

EXPORT unsigned int Vehicle_GetCounterMeasureCount(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetCounterMeasureCount();
}

EXPORT void Vehicle_SetCounterMeasureCount(void *v, unsigned int count) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetCounterMeasureCount(count);
}

EXPORT float Vehicle_GetScriptMaxSpeed(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetScriptMaxSpeed();
}

EXPORT void Vehicle_SetScriptMaxSpeed(void *v, float speed) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetScriptMaxSpeed(speed);
}

EXPORT unsigned char Vehicle_GetWeaponsDisabled(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetWeaponsDisabled();
}

EXPORT void Vehicle_SetWeaponsDisabled(void *v, unsigned char state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetWeaponsDisabled(state);
}

EXPORT int Vehicle_GetWeaponCapacity(void *v, unsigned char index) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetWeaponCapacity(index);
}

EXPORT void Vehicle_SetWeaponCapacity(void *v, unsigned char index, int capacity) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetWeaponCapacity(index, capacity);
}

EXPORT unsigned char Vehicle_GetHybridExtraActive(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetHybridExtraActive();
}

EXPORT void Vehicle_SetHybridExtraActive(void *v, unsigned char state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetHybridExtraActive(state);
}

EXPORT unsigned char Vehicle_GetHybridExtraState(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetHybridExtraState();
}

EXPORT void Vehicle_SetHybridExtraState(void *v, unsigned char state) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetHybridExtraState(state);
}

EXPORT float Vehicle_GetDamageModifier(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetDamageModifier();
}

EXPORT void Vehicle_SetDamageModifier(void *v, float damageModifier) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetDamageModifier(damageModifier);
}

EXPORT float Veheicle_GetDamageMultiplier(void *v) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    return vehicle->GetDamageMultiplier();
}

EXPORT void Vehicle_SetDamageMultiplier(void *v, float damageMultiplier) {
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);
    vehicle->SetDamageMultiplier(damageMultiplier);
}