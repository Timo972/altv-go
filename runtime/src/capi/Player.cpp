#include "Player.h"
#include "GoRuntime.h"
#include "GoResource.h"

EXPORT const char *Player_GetName(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetName().c_str();
}

EXPORT int Player_HasMetaData(void *base, const char *key) {
    auto baseObject = reinterpret_cast<alt::IPlayer *>(base);
    return baseObject->HasMetaData(key);
}

EXPORT Array Player_GetMetaData(void *base, const char *key) {
    auto baseObject = reinterpret_cast<alt::IPlayer *>(base);
    auto meta = baseObject->GetMetaData(key);
    return Go::Runtime::EncodeMValue(meta);
}

EXPORT void Player_SetMetaData(void *base, const char *key, Array data) {
    auto baseObject = reinterpret_cast<alt::IPlayer *>(base);
    auto value = Go::Runtime::DecodeMValue(data);

    baseObject->SetMetaData(key, value);
}

EXPORT void Player_DeleteMetaData(void *base, const char *key) {
    auto baseObject = reinterpret_cast<alt::IPlayer *>(base);
    baseObject->DeleteMetaData(key);
   // baseObject->RemoveRef();
}

EXPORT int Player_HasSyncedMetaData(void *base, const char *key) {
    auto baseObject = reinterpret_cast<alt::IPlayer *>(base);
    return baseObject->HasSyncedMetaData(key);
}


EXPORT Array Player_GetSyncedMetaData(void *base, const char *key) {
    auto baseObject = reinterpret_cast<alt::IPlayer *>(base);
    auto meta = baseObject->GetSyncedMetaData(key);
    return Go::Runtime::EncodeMValue(meta);
}

EXPORT void Player_SetSyncedMetaData(void *base, const char *key, Array data) {
    auto baseObject = reinterpret_cast<alt::IPlayer *>(base);
    auto value = Go::Runtime::DecodeMValue(data);

    baseObject->SetSyncedMetaData(key, value);
}

EXPORT void Player_DeleteSyncedMetaData(void *base, const char *key) {
    auto baseObject = reinterpret_cast<alt::IPlayer *>(base);
    baseObject->DeleteSyncedMetaData(key);
    // baseObject->RemoveRef();
}

EXPORT int Player_HasStreamSyncedMetaData(void *base, const char *key) {
    auto baseObject = reinterpret_cast<alt::IPlayer *>(base);
    return baseObject->HasStreamSyncedMetaData(key);
}


EXPORT Array Player_GetStreamSyncedMetaData(void *base, const char *key) {
    auto baseObject = reinterpret_cast<alt::IPlayer *>(base);
    auto meta = baseObject->GetStreamSyncedMetaData(key);
    return Go::Runtime::EncodeMValue(meta);
}

EXPORT void Player_SetStreamSyncedMetaData(void *base, const char *key, Array data) {
    auto baseObject = reinterpret_cast<alt::IPlayer *>(base);
    auto value = Go::Runtime::DecodeMValue(data);

    baseObject->SetStreamSyncedMetaData(key, value);
}

EXPORT void Player_DeleteStreamSyncedMetaData(void *base, const char *key) {
    auto baseObject = reinterpret_cast<alt::IPlayer *>(base);
    baseObject->DeleteStreamSyncedMetaData(key);
    // baseObject->RemoveRef();
}

EXPORT Position Player_GetPosition(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto pos = player->GetPosition();

    Position position;
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    return position;
}

EXPORT void Player_SetPosition(void *p, float x, float y, float z) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);

    alt::Position position(x,y,z);

    player->SetPosition(position);
}

EXPORT Rotation Player_GetRotation(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto rot = player->GetRotation();

    Rotation rotation;
    rotation.pitch = rot.pitch;
    rotation.yaw = rot.yaw;
    rotation.roll = rot.roll;

    return rotation;
}

EXPORT void Player_SetRotation(void *p, float roll, float pitch, float yaw) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);

    alt::Rotation rotation(roll, pitch, yaw);

    player->SetRotation(rotation);
}

EXPORT long Player_GetDimension(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetDimension();
}

EXPORT void Player_SetDimension(void *p, long dimension) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetDimension(dimension);
}

EXPORT void Player_Spawn(void *p, float x, float y, float z, unsigned long delay) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    alt::Position position(x,y,z);

    player->Spawn(position, delay);
}

EXPORT void Player_Despawn(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->Despawn();
}

EXPORT unsigned long Player_GetModel(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetModel();
}

EXPORT void Player_SetModel(void *p, unsigned long model) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetModel(model);
}

EXPORT unsigned int Player_GetHealth(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetHealth();
}

EXPORT void Player_SetHealth(void *p, unsigned int health) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetHealth(health);
}

EXPORT int Player_HasWeaponComponent(void *p, unsigned long weapon, unsigned long component) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->HasWeaponComponent(weapon, component);
}

EXPORT Array Player_GetCurrentWeaponComponents(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto components = player->GetCurrentWeaponComponents();
    return Go::Runtime::CreateArray<uint32_t, unsigned int>(components);
}

EXPORT unsigned int Player_GetWeaponTintIndex(void *p, unsigned long weapon) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetWeaponTintIndex(weapon);
}

EXPORT unsigned int Player_GetCurrentWeaponTintIndex(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetCurrentWeaponTintIndex();
}

EXPORT unsigned long Player_GetCurrentWeapon(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetCurrentWeapon();
}

EXPORT int Player_IsDead(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->IsDead();
}

EXPORT int Player_IsJumping(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->IsJumping();
}

EXPORT int Player_IsInRagdoll(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->IsInRagdoll();
}

EXPORT int Player_IsAiming(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->IsAiming();
}

EXPORT int Player_IsShooting(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->IsShooting();
}

EXPORT int Player_IsReloading(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->IsReloading();
}

EXPORT unsigned int Player_GetArmour(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetArmour();
}

EXPORT void Player_SetArmour(void *p, unsigned int armour) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetArmour(armour);
}

EXPORT float Player_GetMoveSpeed(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetMoveSpeed();
}

EXPORT Position Player_GetAimPos(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto pos = player->GetAimPos();

    Position position;
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    return position;
}

EXPORT Rotation Player_GetHeadRotation(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto rot = player->GetHeadRotation();

    Rotation rotation;
    rotation.pitch = rot.pitch;
    rotation.roll = rot.roll;
    rotation.yaw = rot.yaw;

    return rotation;
}

EXPORT int Player_IsInVehicle(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->IsInVehicle();
}

EXPORT Entity Player_GetVehicle(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return Go::Runtime::GetEntity(player->GetVehicle());
}

EXPORT unsigned int Player_GetSeat(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetSeat();
}

EXPORT Entity Player_GetEntityAimingAt(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto entity = player->GetEntityAimingAt();
    return Go::Runtime::GetEntity(entity);
}

EXPORT Position Player_GetEntityAimOffset(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto pos = player->GetEntityAimOffset();

    Position offset;
    offset.x = pos.x;
    offset.y = pos.y;
    offset.z = pos.z;

    return offset;
}

EXPORT int Player_IsFlashlightActive(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->IsFlashlightActive();
}

EXPORT int Player_IsConnected(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->IsConnected();
}

EXPORT unsigned long Player_GetPing(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetPing();
}

EXPORT const char *Player_GetIP(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetIP().c_str();
}

EXPORT unsigned long long Player_GetSocialID(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetSocialID();
}

EXPORT unsigned long long Player_GetHwidHash(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetHwidHash();
}

EXPORT unsigned long long Player_GetHwidExHash(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetHwidExHash();
}

EXPORT const char *Player_GetAuthToken(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetAuthToken().c_str();
}

EXPORT void Player_SetMaxArmour(void *p, unsigned int armour) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetMaxArmour(armour);
}

EXPORT void Player_SetCurrentWeapon(void *p, unsigned long weapon) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetCurrentWeapon(weapon);
}

EXPORT void Player_SetWeaponTintIndex(void *p, unsigned long weapon, unsigned int tintIndex) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetWeaponTintIndex(weapon, tintIndex);
}

EXPORT void Player_AddWeaponComponent(void *p, unsigned long weapon, unsigned long component) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->AddWeaponComponent(weapon, component);
}

EXPORT void Player_RemoveWeaponComponent(void *p, unsigned long weapon, unsigned long component) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->RemoveWeaponComponent(weapon, component);
}

EXPORT void Player_ClearBloodDamage(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->ClearBloodDamage();
}

EXPORT void Player_SetMaxHealth(void *p, unsigned int health) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetMaxHealth(health);
}

EXPORT void Player_GiveWeapon(void *p, unsigned long weapon, long ammo, int selectWeapon) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->GiveWeapon(weapon, ammo, selectWeapon);
}

EXPORT void Player_RemoveWeapon(void *p, unsigned long weapon) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->RemoveWeapon(weapon);
}

EXPORT void Player_RemoveAllWeapons(void *p, ushort removeAmmo) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->RemoveAllWeapons(removeAmmo);
}

EXPORT void Player_SetDateTime(void *p, int day, int month, int year, int hour, int minute, int second) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetDateTime(day, month, year, hour, minute, second);
}

EXPORT void Player_SetWeather(void *p, unsigned long weather) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetWeather(weather);
}

EXPORT void Player_Kick(void *p, const char *reason) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->Kick(reason);
}

EXPORT Cloth Player_GetClothes(void *p, unsigned int component) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto cloth = player->GetClothes(component);

    Cloth cCloth;
    cCloth.drawableId = cloth.drawableId;
    cCloth.textureId = cloth.textureId;
    cCloth.paletteId = cloth.paletteId;

    return cCloth;
}

EXPORT DlcCloth Player_GetDlcClothes(void *p, unsigned int component) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto cloth = player->GetDlcClothes(component);

    DlcCloth dlcCloth;
    dlcCloth.dlc = cloth.dlc;
    dlcCloth.drawableId = cloth.drawableId;
    dlcCloth.textureId = cloth.textureId;
    dlcCloth.paletteId = cloth.paletteId;

    return dlcCloth;
}

EXPORT Prop Player_GetProps(void *p, unsigned int component) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto prop = player->GetProps(component);

    Prop cProp;
    cProp.drawableId = prop.drawableId;
    cProp.textureId = prop.textureId;

    return cProp;
}

EXPORT DlcProp Player_GetDlcProps(void *p, unsigned int component) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto prop = player->GetDlcProps(component);

    DlcProp dlcProp;
    dlcProp.dlc = prop.dlc;
    dlcProp.drawableId = prop.drawableId;
    dlcProp.textureId = prop.textureId;

    return dlcProp;
}

EXPORT void
Player_SetClothes(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned int palette) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetClothes(component, drawable, texture, palette);
}

EXPORT void
Player_SetDlcClothes(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned int palette,
                     unsigned long dlc) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetDlcClothes(component, drawable, texture, palette, dlc);
}

EXPORT void Player_SetProps(void *p, unsigned int component, unsigned int drawable, unsigned int texture) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetProps(component, drawable, texture);
}

EXPORT void
Player_SetDlcProps(void *p, unsigned int component, unsigned int drawable, unsigned int texture, unsigned long dlc) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetDlcProps(component, drawable, texture, dlc);
}

EXPORT void Player_ClearProps(void *p, unsigned int component) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->ClearProps(component);
}

EXPORT int Player_IsEntityInStreamingRange(void *p, unsigned short id) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->IsEntityInStreamingRange(id);
}

EXPORT unsigned int Player_GetMaxHealth(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetMaxHealth();
}

EXPORT unsigned int Player_GetMaxArmour(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetMaxArmour();
}

EXPORT void Player_Detach(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->Detach();
}

EXPORT void
Player_AttachToEntity(void *p, Entity e, int otherBoneIndex, int myBoneIndex, Position pos, Rotation rot, int collision,
                      int noFixedRotation) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto entity = Go::Runtime::GetEntityRef(e);
    auto position = new alt::Position(pos.x, pos.y, pos.z);
    auto rotation = new alt::Rotation(rot.roll, rot.pitch, rot.yaw);
    player->AttachToEntity(entity, otherBoneIndex, myBoneIndex, *position, *rotation, collision, noFixedRotation);
}

EXPORT void Player_SetVisible(void *p, int toggle) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetVisible(toggle);
}

EXPORT int Player_GetVisible(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetVisible();
}

EXPORT unsigned long Player_GetID(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetID();
}

EXPORT Entity Player_GetNetworkOwner(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return Go::Runtime::GetEntity(player->GetNetworkOwner());
}

EXPORT void Player_SetNetworkOwner(void *p, void *o, int disableMigration) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto owner = reinterpret_cast<alt::IPlayer *>(o);
    player->SetNetworkOwner(owner, disableMigration);
}

EXPORT void Player_Destroy(void *b) {
    auto player = reinterpret_cast<alt::IPlayer *>(b);
    alt::ICore::Instance().DestroyBaseObject(player);
}

EXPORT int Player_IsValid(const char *resourceName, void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto resource = dynamic_cast<Go::Resource*>(Go::Runtime::GetInstance()->GetResource(resourceName));

    return resource->HasEntity(player);
}

EXPORT int Player_GetStreamed(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetStreamed();
}

EXPORT void Player_SetStreamed(void *p, int toggle) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetStreamed(toggle);
}

EXPORT int Player_GetInvincible(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetInvincible();
}

EXPORT void Player_SetInvincible(void *p, int toggle) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetInvincible(toggle);
}

EXPORT void Player_SetIntoVehicle(void *p, void *v, unsigned char seat) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto vehicle = reinterpret_cast<alt::IVehicle *>(v);

    player->SetIntoVehicle(vehicle, seat);
}

EXPORT int Player_IsFrozen(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->IsFrozen();
}

EXPORT void Player_SetFrozen(void *p, int state) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetFrozen(state);
}

EXPORT int Player_HasCollision(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->HasCollision();
}

EXPORT void Player_SetCollision(void *p, int state) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetCollision(state);
}

EXPORT void
Player_PlayAmbientSpeech(void *p, const char *speechName, const char *speechParam, unsigned int speechDictHash) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->PlayAmbientSpeech(speechName, speechParam, speechDictHash);
}

EXPORT int Player_SetHeadOverlay(void *p, unsigned char overlayID, unsigned char index, float opacity) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->SetHeadOverlay(overlayID, index, opacity);
}

EXPORT int Player_RemoveHeadOverlay(void *p, unsigned char overlayID) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->RemoveHeadOverlay(overlayID);
}

EXPORT int
Player_SetHeadOverlayColor(void *p, unsigned char overlayID, unsigned char colorType, unsigned char colorIndex,
                           unsigned char secondColorIndex) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->SetHeadOverlayColor(overlayID, colorType, colorIndex, secondColorIndex);
}

EXPORT HeadOverlay Player_GetHeadOverlay(void *p, unsigned char overlayID) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto overlay =  player->GetHeadOverlay(overlayID);

    HeadOverlay o;
    o.secondColorIndex = overlay.secondColorIndex;
    o.colorIndex = overlay.colorIndex;
    o.colorType = overlay.colorType;
    o.opacity = overlay.opacity;
    o.index = overlay.index;

    return o;
}

EXPORT int Player_SetFaceFeature(void *p, unsigned char index, float scale) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->SetFaceFeature(index, scale);
}

EXPORT float Player_GetFaceFeatureScale(void *p, unsigned char index) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetFaceFeatureScale(index);
}

EXPORT int Player_RemoveFaceFeature(void *p, unsigned char index) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->RemoveFaceFeature(index);
}

EXPORT int
Player_SetHeadBlendPaletteColor(void *p, unsigned char id, unsigned char red, unsigned char green, unsigned char blue) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->SetHeadBlendPaletteColor(id, red, green, blue);
}

EXPORT RGBA Player_GetHeadBlendPaletteColor(void *p, unsigned char id) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);

    alt::RGBA color = player->GetHeadBlendPaletteColor(id);
    RGBA c;
    c.r = color.r;
    c.g = color.g;
    c.b = color.b;
    c.a = color.a;

    return c;
}

EXPORT void
Player_SetHeadBlendData(void *p, unsigned int shapeFirstID, unsigned int shapeSecondID, unsigned int shapeThirdID,
                        unsigned int skinFirstID, unsigned int skinSecondID, unsigned int skinThirdID, float shapeMix,
                        float skinMix, float thirdMix) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetHeadBlendData(shapeFirstID, shapeSecondID, shapeThirdID, skinFirstID, skinSecondID, skinThirdID,
                             shapeMix, skinMix, thirdMix);
}

EXPORT HeadBlendData Player_GetHeadBlendData(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto headBlend = player->GetHeadBlendData();

    HeadBlendData h;
    h.skinFirstID = headBlend.skinFirstID;
    h.skinSecondID = headBlend.skinSecondID;
    h.skinThirdID = headBlend.skinThirdID;
    h.shapeFirstID = headBlend.shapeFirstID;
    h.shapeSecondID = headBlend.shapeSecondID;
    h.shapeThirdID = headBlend.shapeThirdID;
    h.shapeMix = headBlend.shapeMix;
    h.skinMix = headBlend.skinMix;
    h.thirdMix = headBlend.thirdMix;

    return h;
}

EXPORT int Player_SetEyeColor(void *p, short eyeColor) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->SetEyeColor(eyeColor);
}

EXPORT short Player_GetEyeColor(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetEyeColor();
}

EXPORT void Player_SetHairColor(void *p, unsigned char hairColor) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetHairColor(hairColor);
}

EXPORT unsigned char Player_GetHairColor(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetHairColor();
}

EXPORT void Player_SetHairHighlightColor(void *p, unsigned char hairHighlightColor) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetHairHighlightColor(hairHighlightColor);
}

EXPORT unsigned char Player_GetHairHighlightColor(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetHairHighlightColor();
}

EXPORT Array Player_GetWeapons(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto weapons = player->GetWeapons();

    auto size = weapons.size();
    auto cweaps = new Weapon[size];

    for (uint64_t i = 0; i < size; i++) {
        auto weapon = weapons[i];
        Weapon w;
        w.hash = weapon.hash;
        w.tintIndex = weapon.tintIndex;
        w.components = Go::Runtime::CreateArray<uint32_t, unsigned int>(weapon.components);

        cweaps[i] = w;
    }

    Array arr;
    arr.size = size;
    arr.array = cweaps;

    return arr;
}

EXPORT int Player_HasLocalMetaData(void *p, const char *key) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->HasLocalMetaData(key);
}

EXPORT void Player_SetLocalMetaData(void *p, const char *key, Array data) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto meta = Go::Runtime::DecodeMValue(data);

    player->SetLocalMetaData(key, meta);
}

EXPORT Array Player_GetLocalMetaData(void *p, const char *key) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    auto meta = player->GetLocalMetaData(key);
    return Go::Runtime::EncodeMValue(meta);
}

EXPORT void Player_DeleteLocalMetaData(void *p, const char *key) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->DeleteLocalMetaData(key);
}

EXPORT unsigned int Player_GetCurrentAnimationDict(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetCurrentAnimationDict();
}

EXPORT unsigned int Player_GetCurrentAnimationName(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetCurrentAnimationName();
}

EXPORT unsigned char Player_IsSpawned(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->IsSpawned();
}

EXPORT float Player_GetForwardSpeed(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetForwardSpeed();
}

EXPORT float Player_GetStrafeSpeed(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetStrafeSpeed();
}

EXPORT long long Player_GetDiscordId(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetDiscordId();
}

EXPORT unsigned int Player_GetInteriorLocation(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetInteriorLocation();
}

EXPORT unsigned int Player_GetLastDamagedBodyPart(void *p) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    return player->GetLastDamagedBodyPart();
}

EXPORT void Player_SetLastDamagedBodyPart(void *p, unsigned int bodyPart) {
    auto player = reinterpret_cast<alt::IPlayer *>(p);
    player->SetLastDamagedBodyPart(bodyPart);
}