#ifndef CAPI_MODULE
#define CAPI_MODULE

#ifndef __linux__
#include <Windows.h>

#define SEPARATOR "\\"
#define LOAD_LIB(path) LoadLibrary(path)
#define GET_FUNC(module, name, type) (type) GetProcAddress(module, name);

typedef HINSTANCE Module;
#else
#include <stddef.h>
#include <dlfcn.h>

#define SEPARATOR "/"
#define LOAD_LIB(name) dlopen(name, RTLD_NOW);
#define GET_FUNC(module, name, type) (type) dlsym(module, name);

typedef void *Module;
#endif

int load_module(const char *path);


typedef struct pos {
    float x;
    float y;
    float z;
} Position;

typedef struct rot {
    float roll;
    float pitch;
    float yaw;
} Rotation;

typedef struct rgba {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} RGBA;

typedef struct cloth {
    unsigned int drawableId;
    unsigned int textureId;
    unsigned int paletteId;
} Cloth;

typedef struct dlcCloth {
    unsigned long dlc;
    unsigned int drawableId;
    unsigned int textureId;
    unsigned int paletteId;
} DlcCloth;

typedef struct prop {
    unsigned int drawableId;
    unsigned int textureId;
} Prop;

typedef struct dlcProp {
    unsigned long dlc;
    unsigned int drawableId;
    unsigned int textureId;
} DlcProp;

typedef struct fireInfo {
    Position position;
    unsigned long weaponHash;
} FireInfo;

typedef struct neonState {
    unsigned char left;
    unsigned char right;
    unsigned char front;
    unsigned char back;
} VehicleNeonState;

typedef struct entity {
    unsigned char typ;
    void *ptr;
    unsigned int id;
    unsigned int model;
} Entity;

typedef struct array {
    unsigned long long size;
    void *array;
} Array;

typedef struct connectionInfo {
    unsigned int id;
    const char *name;
    unsigned long long socialID;
    const char *socialName;
    unsigned long long hwidHash;
    unsigned long long hwidExHash;
    const char *authToken;
    unsigned char isDebug;
    const char *branch;
    unsigned int build;
    const char *cdnUrl;
    unsigned long long passwordHash;
    const char *ip;
    long long discordUserID;
    const char *cloudAuthHash;
} ConnectionInfo;

typedef struct weapon {
    unsigned int hash;
    unsigned char tintIndex;
    Array components;
} Weapon;

typedef struct headBlendData {
    unsigned int shapeFirstID;
    unsigned int shapeSecondID;
    unsigned int shapeThirdID;
    unsigned int skinFirstID;
    unsigned int skinSecondID;
    unsigned int skinThirdID;
    float shapeMix;
    float skinMix;
    float thirdMix;
} HeadBlendData;

typedef struct headOverlay {
    unsigned char index;
    float opacity;
    unsigned char colorType;
    unsigned char colorIndex;
    unsigned char secondColorIndex;
} HeadOverlay;

typedef struct vector2 {
    float x;
    float y;
} Vector2;

typedef struct vehicleModelInfo {
   const char *title;
   unsigned char modelType;
   unsigned char wheelsCount;
   // bool
   unsigned char hasArmoredWindows;
   unsigned char hasAutoAttachTrailer;
   Array bones;

   unsigned char primaryColor;
   unsigned char secondaryColor;
   unsigned char pearlColor;
   unsigned char wheelsColor;
   unsigned char interiorColor;
   unsigned char dashboardColor;

   unsigned short modKits[2];
   unsigned short extras;
   unsigned short defaultExtras;
} VehicleModelInfo;

typedef struct pedModelInfo {
    unsigned int hash;
    const char* name;
    Array bones;
} PedModelInfo;

typedef struct boneInfo {
    unsigned short id;
    unsigned short index;
    const char* name;
} BoneInfo;



typedef int (*capi_ColShape_GetType)(void *c);

typedef int (*capi_ColShape_HasMetaData)(void* base,  const char *key);

typedef Array (*capi_ColShape_GetMetaData)(void* base,  const char *key);

typedef void (*capi_ColShape_SetMetaData)(void *base,  const char *key,  Array data);

typedef void (*capi_ColShape_DeleteMetaData)(void *base,  const char *key);

typedef void (*capi_ColShape_Destroy)(void *b);

typedef int (*capi_ColShape_IsValid)(const char* resourceName,  void *p);

typedef Position (*capi_ColShape_GetPosition)(void *p);

typedef void (*capi_ColShape_SetPosition)(void* p,  float x,  float y,  float z);

typedef long (*capi_ColShape_GetDimension)(void* p);

typedef void (*capi_ColShape_SetDimension)(void* p,  long dimension);

typedef int (*capi_ColShape_GetColShapeType)(void *c);

typedef int (*capi_ColShape_IsEntityIn)(void *c,  Entity e);

typedef int (*capi_ColShape_IsPointIn)(void *c,  float x,  float y,  float z);

typedef void (*capi_ColShape_SetPlayersOnly)(void *c,  int state);

typedef int (*capi_ColShape_IsPlayersOnly)(void *c);

typedef unsigned char (*capi_ColShape_IsEntityIdIn)(void *c,  unsigned short id);

typedef void (*capi_Core_LogInfo)(const char *message);

typedef void (*capi_Core_LogDebug)(const char *message);

typedef void (*capi_Core_LogWarning)(const char *message);

typedef void (*capi_Core_LogError)(const char *message);

typedef void (*capi_Core_LogColored)(const char *message);

typedef Entity (*capi_Core_CreateVehicle)(unsigned long model,  float posX,  float posY,  float posZ, 
                                float rotX,  float rotY,  float rotZ);

typedef Entity
 (*capi_Core_CreateCheckpoint)(unsigned char type,  float x,  float y,  float z,  float radius,  float height,  unsigned char r, 
                      unsigned char g,  unsigned char b,  unsigned char a,  unsigned long streamingDistance);

typedef Entity (*capi_Core_CreateVoiceChannel)(int spacial,  float maxDistance);

typedef const char * (*capi_Core_GetVersion)();

typedef const char * (*capi_Core_GetBranch)();

typedef int (*capi_Core_IsDebug)();

typedef unsigned long (*capi_Core_Hash)(const char *str);

typedef int (*capi_Core_FileExists)(const char *path);

typedef const char * (*capi_Core_ReadFile)(const char *path);

typedef Entity (*capi_Core_GetEntityByID)(unsigned short id);

typedef Entity (*capi_Core_GetBaseObjectByID)(unsigned char type,  unsigned int id);

typedef Array (*capi_Core_GetEntities)();

typedef Array (*capi_Core_GetPlayers)();

typedef Array (*capi_Core_GetVehicles)();

typedef Array (*capi_Core_GetBlips)();

typedef Array (*capi_Core_GetColShapes)();

typedef Array (*capi_Core_GetCheckpoints)();

typedef Array (*capi_Core_GetVirtualEntities)();

typedef Array (*capi_Core_GetVirtualEntityGroups)();

typedef Array (*capi_Core_GetMarkers)();

typedef Array (*capi_Core_GetPeds)();

typedef int (*capi_Core_HasMetaData)(const char *key);

typedef Array (*capi_Core_GetMetaData)(const char *key);

typedef void (*capi_Core_SetMetaData)(const char *key,  Array data);

typedef void (*capi_Core_DeleteMetaData)(const char *key);

typedef int (*capi_Core_HasSyncedMetaData)(const char *key);

typedef Array (*capi_Core_GetSyncedMetaData)(const char *key);

typedef Array (*capi_Core_GetRequiredPermissions)();

typedef Array (*capi_Core_GetOptionalPermissions)();

typedef void (*capi_Core_DestroyBaseObject)(void *h);

typedef const char * (*capi_Core_GetRootDirectory)();

typedef int (*capi_Core_StartResource)(const char *name);

typedef void (*capi_Core_StopResource)(const char *name);

typedef void (*capi_Core_RestartResource)(const char *name);

typedef void (*capi_Core_SetSyncedMetaData)(const char *key,  Array data);

typedef void (*capi_Core_DeleteSyncedMetaData)(const char *key);

typedef Array (*capi_Core_GetPlayersByName)(const char *name);

typedef unsigned int (*capi_Core_GetNetTime)();

typedef void (*capi_Core_SetPassword)(const char *password);

typedef const char * (*capi_Core_GetSDKHash)();

typedef Entity (*capi_Core_CreateColShapeCylinder)(float posX,  float posY,  float posZ,  float radius,  float height);

typedef Entity (*capi_Core_CreateColShapeCube)(float posX1,  float posY1,  float posZ1,  float posX2,  float posY2,  float posZ2);

typedef Entity (*capi_Core_CreateColShapeRectangle)(float x1,  float y1,  float x2,  float y2,  float z);

typedef Entity (*capi_Core_CreateColShapeCircle)(float posX,  float posY,  float posZ,  float radius);

typedef Entity (*capi_Core_CreateColShapeSphere)(float posX,  float posY,  float posZ,  float radius);

typedef void (*capi_Core_TriggerLocalEvent)(const char *ev,  Array args);

typedef void (*capi_Core_TriggerLocalEventRaw)(const char* ev,  char* bytes,  unsigned long long size);

typedef void (*capi_Core_TriggerClientEvent)(void *p,  const char *ev,  Array args);

typedef void (*capi_Core_TriggerClientEventFor)(Array clients,  const char *ev,  Array args);

typedef void (*capi_Core_TriggerClientEventForAll)(const char *ev,  Array args);

typedef Entity (*capi_Core_CreatePointBlipPosition)(float x,  float y,  float z,  unsigned short global);

typedef Entity (*capi_Core_CreatePointBlipEntity)(Entity entity,  unsigned short global);

typedef Entity (*capi_Core_CreateAreaBlip)(float x,  float y,  float z,  float width,  float height,  unsigned short global);

typedef Entity (*capi_Core_CreateRadiusBlip)(float x,  float y,  float z,  float radius,  unsigned short global);

typedef Entity (*capi_Core_CreateColShapePolygon)(float minZ,  float maxZ,  Array points);

typedef Array (*capi_Core_GetAllResources)();

typedef const char * (*capi_Core_StringToSHA256)(const char *str);

typedef void (*capi_Core_StopServer)();

typedef VehicleModelInfo (*capi_Core_GetVehicleModelByHash)(unsigned int hash);

typedef PedModelInfo (*capi_Core_GetPedModelByHash)(unsigned int hash);

typedef Array (*capi_Core_GetServerConfig)();

typedef unsigned long long (*capi_Core_HashServerPassword)(const char *password);

typedef void* (*capi_Core_GetResourceByName)(const char *resourceName);

typedef const char * (*capi_Player_GetName)(void *p);

typedef int (*capi_Player_HasMetaData)(void *base,  const char *key);

typedef Array (*capi_Player_GetMetaData)(void *base,  const char *key);

typedef void (*capi_Player_SetMetaData)(void *base,  const char *key,  Array data);

typedef void (*capi_Player_DeleteMetaData)(void *base,  const char *key);

typedef int (*capi_Player_HasSyncedMetaData)(void *base,  const char *key);

typedef Array (*capi_Player_GetSyncedMetaData)(void *base,  const char *key);

typedef void (*capi_Player_SetSyncedMetaData)(void *base,  const char *key,  Array data);

typedef void (*capi_Player_DeleteSyncedMetaData)(void *base,  const char *key);

typedef int (*capi_Player_HasStreamSyncedMetaData)(void *base,  const char *key);

typedef Array (*capi_Player_GetStreamSyncedMetaData)(void *base,  const char *key);

typedef void (*capi_Player_SetStreamSyncedMetaData)(void *base,  const char *key,  Array data);

typedef void (*capi_Player_DeleteStreamSyncedMetaData)(void *base,  const char *key);

typedef Position (*capi_Player_GetPosition)(void *p);

typedef void (*capi_Player_SetPosition)(void *p,  float x,  float y,  float z);

typedef Rotation (*capi_Player_GetRotation)(void *p);

typedef void (*capi_Player_SetRotation)(void *p,  float roll,  float pitch,  float yaw);

typedef long (*capi_Player_GetDimension)(void *p);

typedef void (*capi_Player_SetDimension)(void *p,  long dimension);

typedef void (*capi_Player_Spawn)(void *p,  float x,  float y,  float z,  unsigned long delay);

typedef void (*capi_Player_Despawn)(void *p);

typedef void (*capi_Player_SetModel)(void *p,  unsigned long model);

typedef unsigned long (*capi_Player_GetModel)(void *p);

typedef unsigned int (*capi_Player_GetHealth)(void *p);

typedef void (*capi_Player_SetHealth)(void *p,  unsigned int health);

typedef int (*capi_Player_HasWeaponComponent)(void *p,  unsigned long weapon,  unsigned long component);

typedef Array (*capi_Player_GetCurrentWeaponComponents)(void *p);

typedef unsigned int (*capi_Player_GetWeaponTintIndex)(void *p,  unsigned long weapon);

typedef unsigned int (*capi_Player_GetCurrentWeaponTintIndex)(void *p);

typedef unsigned long (*capi_Player_GetCurrentWeapon)(void *p);

typedef int (*capi_Player_IsDead)(void *p);

typedef int (*capi_Player_IsJumping)(void *p);

typedef int (*capi_Player_IsInRagdoll)(void *p);

typedef int (*capi_Player_IsAiming)(void *p);

typedef int (*capi_Player_IsShooting)(void *p);

typedef int (*capi_Player_IsReloading)(void *p);

typedef unsigned int (*capi_Player_GetArmour)(void *p);

typedef void (*capi_Player_SetArmour)(void *p,  unsigned int armour);

typedef float (*capi_Player_GetMoveSpeed)(void *p);

typedef Position (*capi_Player_GetAimPos)(void *p);

typedef Rotation (*capi_Player_GetHeadRotation)(void *p);

typedef int (*capi_Player_IsInVehicle)(void *p);

typedef Entity (*capi_Player_GetVehicle)(void *p);

typedef unsigned int (*capi_Player_GetSeat)(void *p);

typedef Entity (*capi_Player_GetEntityAimingAt)(void *p);

typedef Position (*capi_Player_GetEntityAimOffset)(void *p);

typedef int (*capi_Player_IsFlashlightActive)(void *p);

typedef int (*capi_Player_IsConnected)(void *p);

typedef unsigned long (*capi_Player_GetPing)(void *p);

typedef const char * (*capi_Player_GetIP)(void *p);

typedef unsigned long long (*capi_Player_GetSocialID)(void *p);

typedef unsigned long long (*capi_Player_GetHwidHash)(void *p);

typedef unsigned long long (*capi_Player_GetHwidExHash)(void *p);

typedef const char * (*capi_Player_GetAuthToken)(void *p);

typedef void (*capi_Player_SetMaxArmour)(void *p,  unsigned int armour);

typedef void (*capi_Player_SetCurrentWeapon)(void *p,  unsigned long weapon);

typedef void (*capi_Player_SetWeaponTintIndex)(void *p,  unsigned long weapon,  unsigned int tintIndex);

typedef void (*capi_Player_AddWeaponComponent)(void *p,  unsigned long weapon,  unsigned long component);

typedef void (*capi_Player_RemoveWeaponComponent)(void *p,  unsigned long weapon,  unsigned long component);

typedef void (*capi_Player_ClearBloodDamage)(void *p);

typedef void (*capi_Player_SetMaxHealth)(void *p,  unsigned int health);

typedef void (*capi_Player_GiveWeapon)(void *p,  unsigned long weapon,  long ammo,  int selectWeapon);

typedef void (*capi_Player_RemoveWeapon)(void *p,  unsigned long weapon);

typedef void (*capi_Player_RemoveAllWeapons)(void *p,  unsigned short removeAmmo);

typedef void (*capi_Player_SetDateTime)(void *p,  int day,  int month,  int year,  int hour,  int minute,  int second);

typedef void (*capi_Player_SetWeather)(void *p,  unsigned long weather);

typedef void (*capi_Player_Kick)(void *p,  const char *reason);

typedef Cloth (*capi_Player_GetClothes)(void *p,  unsigned int component);

typedef DlcCloth (*capi_Player_GetDlcClothes)(void *p,  unsigned int component);

typedef Prop (*capi_Player_GetProps)(void *p,  unsigned int component);

typedef DlcProp (*capi_Player_GetDlcProps)(void *p,  unsigned int component);

typedef void
 (*capi_Player_SetClothes)(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture,  unsigned int palette);

typedef void
 (*capi_Player_SetDlcClothes)(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture,  unsigned int palette, 
                     unsigned long dlc);

typedef void (*capi_Player_SetProps)(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture);

typedef void
 (*capi_Player_SetDlcProps)(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture,  unsigned long dlc);

typedef void (*capi_Player_ClearProps)(void *p,  unsigned int component);

typedef int (*capi_Player_IsEntityInStreamingRange)(void *p,  unsigned short entityId);

typedef unsigned int (*capi_Player_GetMaxHealth)(void *p);

typedef unsigned int (*capi_Player_GetMaxArmour)(void *p);

typedef void (*capi_Player_Detach)(void *p);

typedef void
 (*capi_Player_AttachToEntity)(void *p,  Entity e,  int otherBoneIndex,  int myBoneIndex,  Position position,  Rotation rotation, 
                      int collision,  int noFixedRotation);

typedef void (*capi_Player_SetVisible)(void *p,  int toggle);

typedef int (*capi_Player_GetVisible)(void *p);

typedef unsigned long (*capi_Player_GetID)(void *p);

typedef Entity (*capi_Player_GetNetworkOwner)(void *p);

typedef void (*capi_Player_SetNetworkOwner)(void *p,  void *owner,  int disableMigration);

typedef void (*capi_Player_Destroy)(void *p);

typedef int (*capi_Player_IsValid)(const char* resourceName,  void *p);

typedef int (*capi_Player_GetStreamed)(void *p);

typedef void (*capi_Player_SetStreamed)(void *p,  int toggle);

typedef int (*capi_Player_GetInvincible)(void *p);

typedef void (*capi_Player_SetInvincible)(void *p,  int toggle);

typedef void (*capi_Player_SetIntoVehicle)(void *p,  void *v,  unsigned char seat);

typedef int (*capi_Player_IsFrozen)(void *p);

typedef void (*capi_Player_SetFrozen)(void *p,  int state);

typedef int (*capi_Player_HasCollision)(void *p);

typedef void (*capi_Player_SetCollision)(void *p,  int state);

typedef void
 (*capi_Player_PlayAmbientSpeech)(void *p,  const char *speechName,  const char *speechParam,  unsigned int speechDictHash);

typedef int (*capi_Player_SetHeadOverlay)(void *p,  unsigned char overlayID,  unsigned char index,  float opacity);

typedef int (*capi_Player_RemoveHeadOverlay)(void *p,  unsigned char overlayID);

typedef int
 (*capi_Player_SetHeadOverlayColor)(void *p,  unsigned char overlayID,  unsigned char colorType,  unsigned char colorIndex, 
                           unsigned char secondColorIndex);

typedef HeadOverlay (*capi_Player_GetHeadOverlay)(void *p,  unsigned char overlayID);

typedef int (*capi_Player_SetFaceFeature)(void *p,  unsigned char index,  float scale);

typedef float (*capi_Player_GetFaceFeatureScale)(void *p,  unsigned char index);

typedef int (*capi_Player_RemoveFaceFeature)(void *p,  unsigned char index);

typedef int
 (*capi_Player_SetHeadBlendPaletteColor)(void *p,  unsigned char id,  unsigned char red,  unsigned char green,  unsigned char blue);

typedef RGBA (*capi_Player_GetHeadBlendPaletteColor)(void *p,  unsigned char id);

typedef void
 (*capi_Player_SetHeadBlendData)(void *p,  unsigned int shapeFirstID,  unsigned int shapeSecondID,  unsigned int shapeThirdID, 
                        unsigned int skinFirstID,  unsigned int skinSecondID,  unsigned int skinThirdID, 
                        float shapeMix,  float skinMix,  float thirdMix);

typedef HeadBlendData (*capi_Player_GetHeadBlendData)(void *p);

typedef int (*capi_Player_SetEyeColor)(void *p,  short eyeColor);

typedef short (*capi_Player_GetEyeColor)(void *p);

typedef void (*capi_Player_SetHairColor)(void *p,  unsigned char hairColor);

typedef unsigned char (*capi_Player_GetHairColor)(void *p);

typedef void (*capi_Player_SetHairHighlightColor)(void *p,  unsigned char hairHighlightColor);

typedef unsigned char (*capi_Player_GetHairHighlightColor)(void *p);

typedef Array (*capi_Player_GetWeapons)(void *p);

typedef int (*capi_Player_HasLocalMetaData)(void *p,  const char *key);

typedef void (*capi_Player_SetLocalMetaData)(void *p,  const char *key,  Array data);

typedef Array (*capi_Player_GetLocalMetaData)(void *p,  const char *key);

typedef void (*capi_Player_DeleteLocalMetaData)(void *p,  const char *key);

typedef unsigned int (*capi_Player_GetCurrentAnimationDict)(void *p);

typedef unsigned int (*capi_Player_GetCurrentAnimationName)(void *p);

typedef unsigned char (*capi_Player_IsSpawned)(void *p);

typedef float (*capi_Player_GetForwardSpeed)(void *p);

typedef float (*capi_Player_GetStrafeSpeed)(void *p);

typedef long long (*capi_Player_GetDiscordId)(void *p);

typedef unsigned int (*capi_Player_GetInteriorLocation)(void *p);

typedef unsigned int (*capi_Player_GetLastDamagedBodyPart)(void *p);

typedef void (*capi_Player_SetLastDamagedBodyPart)(void *p,  unsigned int bodyPart);

typedef int (*capi_Runtime_RegisterAltEvent)(const char *resourceName,  unsigned short eventType);

typedef int (*capi_Runtime_UnregisterAltEvent)(const char *resourceName,  unsigned short eventType);

typedef int (*capi_Runtime_RegisterAltExport)(const char *resourceName,  const char *exportName,  Array value);

typedef Array (*capi_Runtime_GetAltExport)(const char *targetResourceName,  const char *exportName);

typedef void * (*capi_Runtime_CreateMValueFunction)(const char *resourceName,  unsigned long long id);

typedef Array (*capi_Runtime_CallMValueFunction)(void *ptr,  Array args);

typedef void (*capi_Connection_Accept)(void *handle,  unsigned char sendNames);

typedef void (*capi_Connection_Decline)(void *handle,  const char *reason);

typedef int (*capi_Connection_IsAccepted)(void *handle);

typedef int (*capi_Blip_GetType)(void *c);

typedef int (*capi_Blip_HasMetaData)(void *base,  const char *key);

typedef Array (*capi_Blip_GetMetaData)(void *base,  const char *key);

typedef void (*capi_Blip_SetMetaData)(void *base,  const char *key,  Array data);

typedef void (*capi_Blip_DeleteMetaData)(void *base,  const char *key);

typedef void (*capi_Blip_Destroy)(void *b);

typedef int (*capi_Blip_IsValid)(const char *resourceName,  void *p);

typedef Position (*capi_Blip_GetPosition)(void *p);

typedef void (*capi_Blip_SetPosition)(void *p,  float x,  float y,  float z);

typedef long (*capi_Blip_GetDimension)(void *p);

typedef void (*capi_Blip_SetDimension)(void *p,  long dimension);

typedef int (*capi_Blip_IsGlobal)(void *b);

typedef Array (*capi_Blip_GetTargets)(void *b);

typedef int (*capi_Blip_IsAttached)(void *b);

typedef Entity (*capi_Blip_AttachedTo)(void *b);

typedef void (*capi_Blip_AttachTo)(void *b,  Entity e);

typedef unsigned char (*capi_Blip_GetBlipType)(void *b);

typedef Vector2 (*capi_Blip_GetScaleXY)(void *b);

typedef void (*capi_Blip_SetScaleXY)(void *b,  Vector2 scale);

typedef int (*capi_Blip_GetDisplay)(void *b);

typedef void (*capi_Blip_SetDisplay)(void *b,  int display);

typedef int (*capi_Blip_GetSprite)(void *b);

typedef int (*capi_Blip_GetColor)(void *b);

typedef RGBA (*capi_Blip_GetSecondaryColor)(void *b);

typedef int (*capi_Blip_GetAlpha)(void *b);

typedef int (*capi_Blip_GetFlashTimer)(void *b);

typedef int (*capi_Blip_GetFlashInterval)(void *b);

typedef int (*capi_Blip_GetAsFriendly)(void *b);

typedef int (*capi_Blip_GetRoute)(void *b);

typedef int (*capi_Blip_GetBright)(void *b);

typedef int (*capi_Blip_GetNumber)(void *b);

typedef int (*capi_Blip_GetShowCone)(void *b);

typedef int (*capi_Blip_GetFlashes)(void *b);

typedef int (*capi_Blip_GetFlashesAlternate)(void *b);

typedef int (*capi_Blip_GetAsShortRange)(void *b);

typedef int (*capi_Blip_GetPriority)(void *b);

typedef float (*capi_Blip_GetRotation)(void *b);

typedef const char * (*capi_Blip_GetGxtName)(void *b);

typedef const char * (*capi_Blip_GetName)(void *b);

typedef RGBA (*capi_Blip_GetRouteColor)(void *b);

typedef int (*capi_Blip_GetPulse)(void *b);

typedef int (*capi_Blip_GetAsMissionCreator)(void *b);

typedef int (*capi_Blip_GetTickVisible)(void *b);

typedef int (*capi_Blip_GetHeadingIndicatorVisible)(void *b);

typedef int (*capi_Blip_GetOutlineIndicatorVisible)(void *b);

typedef int (*capi_Blip_GetFriendIndicatorVisible)(void *b);

typedef int (*capi_Blip_GetCrewIndicatorVisible)(void *b);

typedef int (*capi_Blip_GetCategory)(void *b);

typedef int (*capi_Blip_GetAsHighDetail)(void *b);

typedef int (*capi_Blip_GetShrinked)(void *b);

typedef void (*capi_Blip_SetSprite)(void *b,  int sprite);

typedef void (*capi_Blip_SetColor)(void *b,  int color);

typedef void (*capi_Blip_SetRoute)(void *b,  int state);

typedef void (*capi_Blip_SetRouteColor)(void *b,  RGBA color);

typedef void (*capi_Blip_SetSecondaryColor)(void *b,  RGBA color);

typedef void (*capi_Blip_SetAlpha)(void *b,  int alpha);

typedef void (*capi_Blip_SetFlashTimer)(void *b,  int timer);

typedef void (*capi_Blip_SetFlashInterval)(void *b,  int interval);

typedef void (*capi_Blip_SetAsFriendly)(void *b,  int friendly);

typedef void (*capi_Blip_SetBright)(void *b,  int bright);

typedef void (*capi_Blip_SetNumber)(void *b,  int number);

typedef void (*capi_Blip_SetShowCone)(void *b,  int state);

typedef void (*capi_Blip_SetFlashes)(void *b,  int state);

typedef void (*capi_Blip_SetFlashesAlternate)(void *b,  int state);

typedef void (*capi_Blip_SetAsShortRange)(void *b,  int state);

typedef void (*capi_Blip_SetPriority)(void *b,  int state);

typedef void (*capi_Blip_SetRotation)(void *b,  float rot);

typedef void (*capi_Blip_SetGxtName)(void *b,  const char *name);

typedef void (*capi_Blip_SetName)(void *b,  const char *name);

typedef void (*capi_Blip_SetPulse)(void *b,  int val);

typedef void (*capi_Blip_SetAsMissionCreator)(void *b,  int val);

typedef void (*capi_Blip_SetTickVisible)(void *b,  int val);

typedef void (*capi_Blip_SetHeadingIndicatorVisible)(void *b,  int val);

typedef void (*capi_Blip_SetOutlineIndicatorVisible)(void *b,  int val);

typedef void (*capi_Blip_SetFriendIndicatorVisible)(void *b,  int val);

typedef void (*capi_Blip_SetCrewIndicatorVisible)(void *b,  int val);

typedef void (*capi_Blip_SetCategory)(void *b,  int val);

typedef void (*capi_Blip_SetAsHighDetail)(void *b,  int val);

typedef void (*capi_Blip_SetShrinked)(void *b,  int val);

typedef void (*capi_Blip_Fade)(void *b,  unsigned int opacity,  unsigned int duration);

typedef int (*capi_Checkpoint_GetType)(void *c);

typedef int (*capi_Checkpoint_HasMetaData)(void* base,  const char *key);

typedef Array (*capi_Checkpoint_GetMetaData)(void* base,  const char *key);

typedef void (*capi_Checkpoint_SetMetaData)(void *base,  const char *key,  Array data);

typedef void (*capi_Checkpoint_DeleteMetaData)(void *base,  const char *key);

typedef void (*capi_Checkpoint_Destroy)(void *b);

typedef int (*capi_Checkpoint_IsValid)(const char* resourceName,  void *p);

typedef Position (*capi_Checkpoint_GetPosition)(void *p);

typedef void (*capi_Checkpoint_SetPosition)(void* p,  float x,  float y,  float z);

typedef long (*capi_Checkpoint_GetDimension)(void* p);

typedef void (*capi_Checkpoint_SetDimension)(void* p,  long dimension);

typedef int (*capi_Checkpoint_GetColShapeType)(void *c);

typedef int (*capi_Checkpoint_IsEntityIn)(void *c,  Entity e);

typedef int (*capi_Checkpoint_IsPointIn)(void *c,  float x,  float y,  float z);

typedef void (*capi_Checkpoint_SetPlayersOnly)(void *c,  int state);

typedef int (*capi_Checkpoint_IsPlayersOnly)(void *c);

typedef unsigned char (*capi_Checkpoint_IsEntityIdIn)(void *c,  unsigned short id);

typedef unsigned char (*capi_Checkpoint_GetCheckpointType)(void *c);

typedef float (*capi_Checkpoint_GetHeight)(void *c);

typedef float (*capi_Checkpoint_GetRadius)(void *c);

typedef RGBA (*capi_Checkpoint_GetColor)(void *c);

typedef Position (*capi_Checkpoint_GetNextPosition)(void *c);

typedef void (*capi_Checkpoint_SetCheckpointType)(void *c,  unsigned char type);

typedef void (*capi_Checkpoint_SetHeight)(void *c,  float height);

typedef void (*capi_Checkpoint_SetRadius)(void *c,  float radius);

typedef void (*capi_Checkpoint_SetColor)(void *c,  unsigned char r,  unsigned char g,  unsigned char b,  unsigned char a);

typedef void (*capi_Checkpoint_SetNextPosition)(void *c,  float x,  float y,  float z);

typedef unsigned char (*capi_Resource_IsStarted)(void *r);

typedef const char * (*capi_Resource_GetType)(void *r);

typedef const char * (*capi_Resource_GetName)(void* r);

typedef const char * (*capi_Resource_GetMain)(void *r);

typedef Array (*capi_Resource_GetConfig)(void *r);

typedef Array (*capi_Resource_GetExports)(void *r);

typedef Array (*capi_Resource_GetDependencies)(void *r);

typedef Array (*capi_Resource_GetDependants)(void *r);

typedef Array (*capi_Resource_GetRequiredPermissions)(void *r);

typedef Array (*capi_Resource_GetOptionalPermissions)(void *r);

typedef const char * (*capi_Resource_GetPath)(void *r);

typedef int (*capi_Vehicle_HasMetaData)(void *base,  const char *key);

typedef Array (*capi_Vehicle_GetMetaData)(void *base,  const char *key);

typedef void (*capi_Vehicle_SetMetaData)(void *base,  const char *key,  Array data);

typedef void (*capi_Vehicle_DeleteMetaData)(void *base,  const char *key);

typedef int (*capi_Vehicle_HasSyncedMetaData)(void *base,  const char *key);

typedef Array (*capi_Vehicle_GetSyncedMetaData)(void *base,  const char *key);

typedef void (*capi_Vehicle_SetSyncedMetaData)(void *base,  const char *key,  Array data);

typedef void (*capi_Vehicle_DeleteSyncedMetaData)(void *base,  const char *key);

typedef int (*capi_Vehicle_HasStreamSyncedMetaData)(void *base,  const char *key);

typedef Array (*capi_Vehicle_GetStreamSyncedMetaData)(void *base,  const char *key);

typedef void (*capi_Vehicle_SetStreamSyncedMetaData)(void *base,  const char *key,  Array data);

typedef void (*capi_Vehicle_DeleteStreamSyncedMetaData)(void *base,  const char *key);

typedef Position (*capi_Vehicle_GetPosition)(void *v);

typedef void (*capi_Vehicle_SetPosition)(void *v,  float x,  float y,  float z);

typedef Rotation (*capi_Vehicle_GetRotation)(void *v);

typedef void (*capi_Vehicle_SetRotation)(void *v,  float roll,  float pitch,  float yaw);

typedef long (*capi_Vehicle_GetDimension)(void *v);

typedef void (*capi_Vehicle_SetDimension)(void *v,  long dimension);

typedef unsigned long (*capi_Vehicle_GetID)(void *v);

typedef unsigned long (*capi_Vehicle_GetModel)(void *v);

typedef void (*capi_Vehicle_Detach)(void *v);

typedef void
 (*capi_Vehicle_AttachToEntity)(void *v,  Entity e,  int otherBoneIndex,  int myBoneIndex,  Position position,  Rotation rotation, 
                       int collision,  int noFixedRotation);

typedef void (*capi_Vehicle_SetVisible)(void *v,  int toggle);

typedef int (*capi_Vehicle_GetVisible)(void *v);

typedef Entity (*capi_Vehicle_GetNetworkOwner)(void *v);

typedef void (*capi_Vehicle_SetNetworkOwner)(void *v,  void *owner,  int disableMigration);

typedef Entity (*capi_Vehicle_GetDriver)(void *v);

typedef int (*capi_Vehicle_IsDestroyed)(void *v);

typedef unsigned long (*capi_Vehicle_GetMod)(void *v,  unsigned int category);

typedef unsigned long (*capi_Vehicle_GetModsCount)(void *v,  unsigned int category);

typedef unsigned long (*capi_Vehicle_GetModKitsCount)(void *v);

typedef unsigned long (*capi_Vehicle_GetModKit)(void *v);

typedef int (*capi_Vehicle_IsPrimaryColorRGB)(void *v);

typedef unsigned long (*capi_Vehicle_GetPrimaryColor)(void *v);

typedef RGBA (*capi_Vehicle_GetPrimaryColorRGB)(void *v);

typedef int (*capi_Vehicle_IsSecondaryColorRGB)(void *v);

typedef unsigned long (*capi_Vehicle_GetSecondaryColor)(void *v);

typedef RGBA (*capi_Vehicle_GetSecondaryColorRGB)(void *v);

typedef unsigned long (*capi_Vehicle_GetPearlColor)(void *v);

typedef unsigned long (*capi_Vehicle_GetWheelColor)(void *v);

typedef unsigned long (*capi_Vehicle_GetInteriorColor)(void *v);

typedef unsigned long (*capi_Vehicle_GetDashboardColor)(void *v);

typedef int (*capi_Vehicle_IsTireSmokeColorCustom)(void *v);

typedef RGBA (*capi_Vehicle_GetTireSmokeColor)(void *v);

typedef unsigned long (*capi_Vehicle_GetWheelType)(void *v);

typedef unsigned long (*capi_Vehicle_GetWheelVariation)(void *v);

typedef unsigned long (*capi_Vehicle_GetRearWheelVariation)(void *v);

typedef int (*capi_Vehicle_GetCustomTires)(void *v);

typedef unsigned long (*capi_Vehicle_GetSpecialDarkness)(void *v);

typedef unsigned long (*capi_Vehicle_GetNumberplateIndex)(void *v);

typedef const char * (*capi_Vehicle_GetNumberplateText)(void *v);

typedef unsigned long (*capi_Vehicle_GetWindowTint)(void *v);

typedef unsigned long (*capi_Vehicle_GetDirtLevel)(void *v);

typedef int (*capi_Vehicle_IsExtraOn)(void *v,  unsigned int extraID);

typedef int (*capi_Vehicle_IsNeonActive)(void *v);

typedef VehicleNeonState (*capi_Vehicle_GetNeonActive)(void *v);

typedef RGBA (*capi_Vehicle_GetNeonColor)(void *v);

typedef unsigned long (*capi_Vehicle_GetLivery)(void *v);

typedef unsigned long (*capi_Vehicle_GetRoofLivery)(void *v);

typedef const char * (*capi_Vehicle_GetAppearanceDataBase64)(void *v);

typedef int (*capi_Vehicle_IsEngineOn)(void *v);

typedef int (*capi_Vehicle_IsHandbrakeActive)(void *v);

typedef unsigned long (*capi_Vehicle_GetHeadlightColor)(void *v);

typedef unsigned long (*capi_Vehicle_GetRadioStationIndex)(void *v);

typedef int (*capi_Vehicle_IsSirenActive)(void *v);

typedef unsigned long (*capi_Vehicle_GetLockState)(void *v);

typedef unsigned long (*capi_Vehicle_GetDoorState)(void *v,  unsigned int doorId);

typedef int (*capi_Vehicle_IsWindowOpened)(void *v,  unsigned int windowId);

typedef int (*capi_Vehicle_IsDaylightOn)(void *v);

typedef int (*capi_Vehicle_IsNightlightOn)(void *v);

typedef unsigned long (*capi_Vehicle_GetRoofState)(void *v);

typedef int (*capi_Vehicle_IsFlamethrowerActive)(void *v);

typedef float (*capi_Vehicle_GetLightsMultiplier)(void *v);

typedef const char * (*capi_Vehicle_GetGameStateBase64)(void *v);

typedef long (*capi_Vehicle_GetEngineHealth)(void *v);

typedef long (*capi_Vehicle_GetPetrolTankHealth)(void *v);

typedef unsigned long (*capi_Vehicle_GetWheelsCount)(void *v);

typedef int (*capi_Vehicle_IsWheelBurst)(void *v,  unsigned int wheelId);

typedef int (*capi_Vehicle_DoesWheelHasTire)(void *v,  unsigned int wheelId);

typedef int (*capi_Vehicle_IsWheelDetached)(void *v,  unsigned int wheelId);

typedef int (*capi_Vehicle_IsWheelOnFire)(void *v,  unsigned int wheelId);

typedef float (*capi_Vehicle_GetWheelHealth)(void *v,  unsigned int wheelId);

typedef unsigned long (*capi_Vehicle_GetRepairsCount)(void *v);

typedef unsigned long (*capi_Vehicle_GetBodyHealth)(void *v);

typedef unsigned long (*capi_Vehicle_GetBodyAdditionalHealth)(void *v);

typedef const char * (*capi_Vehicle_GetHealthDataBase64)(void *v);

typedef unsigned long (*capi_Vehicle_GetPartDamageLevel)(void *v,  unsigned int partId);

typedef unsigned long (*capi_Vehicle_GetPartBulletHoles)(void *v,  unsigned int partId);

typedef int (*capi_Vehicle_IsLightDamaged)(void *v,  unsigned int lightId);

typedef int (*capi_Vehicle_IsWindowDamaged)(void *v,  unsigned int windowId);

typedef int (*capi_Vehicle_IsSpecialLightDamaged)(void *v,  unsigned int specialLightId);

typedef int (*capi_Vehicle_HasArmoredWindows)(void *v);

typedef float (*capi_Vehicle_GetArmoredWindowHealth)(void *v,  unsigned int windowId);

typedef unsigned long (*capi_Vehicle_GetArmoredWindowShootCount)(void *v,  unsigned int windowId);

typedef unsigned long (*capi_Vehicle_GetBumperDamageLevel)(void *v,  unsigned int bumperId);

typedef const char * (*capi_Vehicle_GetDamageDataBase64)(void *v);

typedef int (*capi_Vehicle_IsManualEngineControl)(void *v);

typedef const char * (*capi_Vehicle_GetScriptDataBase64)(void *v);

typedef void (*capi_Vehicle_ToggleExtra)(void *v,  unsigned int extraID,  int state);

typedef void (*capi_Vehicle_SetFixed)(void *v);

typedef int (*capi_Vehicle_SetMod)(void *v,  unsigned int category,  unsigned int id);

typedef int (*capi_Vehicle_SetModKit)(void *v,  unsigned int id);

typedef void (*capi_Vehicle_SetPrimaryColor)(void *v,  unsigned int color);

typedef void (*capi_Vehicle_SetPrimaryColorRGB)(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

typedef void (*capi_Vehicle_SetSecondaryColor)(void *v,  unsigned int color);

typedef void (*capi_Vehicle_SetSecondaryColorRGB)(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

typedef void (*capi_Vehicle_SetPearlColor)(void *v,  unsigned int color);

typedef void (*capi_Vehicle_SetWheelColor)(void *v,  unsigned int color);

typedef void (*capi_Vehicle_SetInteriorColor)(void *v,  unsigned int color);

typedef void (*capi_Vehicle_SetDashboardColor)(void *v,  unsigned int color);

typedef void (*capi_Vehicle_SetTireSmokeColor)(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

typedef void (*capi_Vehicle_SetWheels)(void *v,  unsigned int type,  unsigned int variation);

typedef void (*capi_Vehicle_SetRearWheels)(void *v,  unsigned int variation);

typedef void (*capi_Vehicle_SetCustomTires)(void *v,  int state);

typedef void (*capi_Vehicle_SetSpecialDarkness)(void *v,  unsigned int value);

typedef void (*capi_Vehicle_SetNumberplateIndex)(void *v,  unsigned int index);

typedef void (*capi_Vehicle_SetNumberplateText)(void *v,  const char *text);

typedef void (*capi_Vehicle_SetWindowTint)(void *v,  unsigned int tint);

typedef void (*capi_Vehicle_SetDirtLevel)(void *v,  unsigned int level);

typedef void (*capi_Vehicle_SetNeonActive)(void *v,  int left,  int right,  int front,  int back);

typedef void (*capi_Vehicle_SetNeonColor)(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

typedef void (*capi_Vehicle_SetLivery)(void *v,  unsigned int livery);

typedef void (*capi_Vehicle_SetRoofLivery)(void *v,  unsigned int roofLivery);

typedef void (*capi_Vehicle_LoadAppearanceDataFromBase64)(void *v,  const char *base64);

typedef void (*capi_Vehicle_SetEngineOn)(void *v,  int state);

typedef void (*capi_Vehicle_SetHeadlightColor)(void *v,  unsigned int color);

typedef void (*capi_Vehicle_SetRadioStationIndex)(void *v,  unsigned int stationIndex);

typedef void (*capi_Vehicle_SetSirenActive)(void *v,  int state);

typedef void (*capi_Vehicle_SetLockState)(void *v,  unsigned int state);

typedef void (*capi_Vehicle_SetDoorState)(void *v,  unsigned int doorId,  unsigned int state);

typedef void (*capi_Vehicle_SetWindowOpened)(void *v,  unsigned int windowId,  int state);

typedef void (*capi_Vehicle_SetRoofState)(void *v,  unsigned int state);

typedef void (*capi_Vehicle_SetLightsMultiplier)(void *v,  float multiplier);

typedef void (*capi_Vehicle_SetEngineHealth)(void *v,  unsigned long health);

typedef void (*capi_Vehicle_SetPetrolTankHealth)(void *v,  unsigned long health);

typedef void (*capi_Vehicle_SetWheelBurst)(void *v,  unsigned int wheelId,  int state);

typedef void (*capi_Vehicle_SetWheelHasTire)(void *v,  unsigned int wheelId,  int state);

typedef void (*capi_Vehicle_SetWheelDetached)(void *v,  unsigned int wheelId,  int state);

typedef void (*capi_Vehicle_SetWheelOnFire)(void *v,  unsigned int wheelId,  int state);

typedef void (*capi_Vehicle_SetWheelHealth)(void *v,  unsigned int wheelId,  float health);

typedef void (*capi_Vehicle_SetWheelFixed)(void *v,  unsigned int wheelId);

typedef void (*capi_Vehicle_SetBodyHealth)(void *v,  unsigned long health);

typedef void (*capi_Vehicle_SetBodyAdditionalHealth)(void *v,  unsigned long health);

typedef void (*capi_Vehicle_SetPartDamageLevel)(void *v,  unsigned int partId,  unsigned int damage);

typedef void (*capi_Vehicle_SetPartBulletHoles)(void *v,  unsigned int partId,  unsigned int shootsCount);

typedef void (*capi_Vehicle_SetLightDamaged)(void *v,  unsigned int lightId,  int isDamaged);

typedef void (*capi_Vehicle_SetWindowDamaged)(void *v,  unsigned int windowId,  int isDamaged);

typedef void (*capi_Vehicle_SetSpecialLightDamaged)(void *v,  unsigned int specialLightId,  int isDamaged);

typedef void (*capi_Vehicle_SetArmoredWindowHealth)(void *v,  unsigned int windowId,  float health);

typedef void (*capi_Vehicle_SetArmoredWindowShootCount)(void *v,  unsigned int windowId,  unsigned int count);

typedef void (*capi_Vehicle_SetBumperDamageLevel)(void *v,  unsigned int bumperId,  unsigned int damageLevel);

typedef void (*capi_Vehicle_SetManualEngineControl)(void *v,  int state);

typedef void (*capi_Vehicle_LoadDamageDataFromBase64)(void *v,  const char *base64);

typedef void (*capi_Vehicle_LoadScriptDataFromBase64)(void *v,  const char *base64);

typedef void (*capi_Vehicle_LoadGameStateFromBase64)(void *v,  const char *base64);

typedef void (*capi_Vehicle_LoadHealthDataFromBase64)(void *v,  const char *base64);

typedef Entity (*capi_Vehicle_GetAttached)(void *v);

typedef Entity (*capi_Vehicle_GetAttachedTo)(void *v);

typedef void (*capi_Vehicle_Destroy)(void *v);

typedef int (*capi_Vehicle_IsValid)(const char *resourceName,  void *p);

typedef int (*capi_Vehicle_GetStreamed)(void *v);

typedef void (*capi_Vehicle_SetStreamed)(void *v,  int toggle);

typedef int (*capi_Vehicle_IsFrozen)(void *v);

typedef void (*capi_Vehicle_SetFrozen)(void *v,  int state);

typedef int (*capi_Vehicle_HasCollision)(void *v);

typedef void (*capi_Vehicle_SetCollision)(void *v,  int state);

typedef int (*capi_Vehicle_IsDriftMode)(void *v);

typedef void (*capi_Vehicle_SetDriftMode)(void *v,  int state);

typedef int (*capi_Vehicle_IsTrainMissionTrain)(void *v);

typedef void (*capi_Vehicle_SetTrainMissionTrain)(void *v,  int value);

typedef char (*capi_Vehicle_GetTrainTrackId)(void *v);

typedef void (*capi_Vehicle_SetTrainTrackId)(void *v,  char trackId);

typedef Entity (*capi_Vehicle_GetTrainEngineId)(void *v);

typedef void (*capi_Vehicle_SetTrainEngineId)(void *v,  void *e);

typedef char (*capi_Vehicle_GetTrainConfigIndex)(void *v);

typedef void (*capi_Vehicle_SetTrainConfigIndex)(void *v,  char trainConfigIndex);

typedef float (*capi_Vehicle_GetTrainDistanceFromEngine)(void *v);

typedef void (*capi_Vehicle_SetTrainDistanceFromEngine)(void *v,  float distanceFromEngine);

typedef int (*capi_Vehicle_IsTrainEngine)(void *v);

typedef void (*capi_Vehicle_SetTrainIsEngine)(void *v,  int isEngine);

typedef int (*capi_Vehicle_IsTrainCaboose)(void *v);

typedef void (*capi_Vehicle_SetTrainIsCaboose)(void *v,  int isCaboose);

typedef int (*capi_Vehicle_GetTrainDirection)(void *v);

typedef void (*capi_Vehicle_SetTrainDirection)(void *v,  int direction);

typedef int (*capi_Vehicle_HasTrainPassengerCarriages)(void *v);

typedef void (*capi_Vehicle_SetTrainHasPassengerCarriages)(void *v,  int hasPassengerCarriages);

typedef int (*capi_Vehicle_GetTrainRenderDerailed)(void *v);

typedef void (*capi_Vehicle_SetTrainRenderDerailed)(void *v,  int renderDerailed);

typedef int (*capi_Vehicle_GetTrainForceDoorsOpen)(void *v);

typedef void (*capi_Vehicle_SetTrainForceDoorsOpen)(void *v,  int forceDoorsOpen);

typedef float (*capi_Vehicle_GetTrainCruiseSpeed)(void *v);

typedef void (*capi_Vehicle_SetTrainCruiseSpeed)(void *v,  float cruiseSpeed);

typedef char (*capi_Vehicle_GetTrainCarriageConfigIndex)(void *v);

typedef void (*capi_Vehicle_SetTrainCarriageConfigIndex)(void *v,  char carriageConfigIndex);

typedef Entity (*capi_Vehicle_GetTrainLinkedToBackwardId)(void *v);

typedef void (*capi_Vehicle_SetTrainLinkedToBackwardId)(void *v,  void *e);

typedef Entity (*capi_Vehicle_GetTrainLinkedToForwardId)(void *v);

typedef void (*capi_Vehicle_SetTrainLinkedToForwardId)(void *v,  void *e);

typedef void (*capi_Vehicle_SetTrainUnk1)(void *v,  int unk1);

typedef int (*capi_Vehicle_GetTrainUnk1)(void *v);

typedef void (*capi_Vehicle_SetTrainUnk2)(void *v,  int unk2);

typedef int (*capi_Vehicle_GetTrainUnk2)(void *v);

typedef void (*capi_Vehicle_SetTrainUnk3)(void *v,  int unk3);

typedef int (*capi_Vehicle_GetTrainUnk3)(void *v);

typedef int (*capi_Vehicle_IsBoatAnchorActive)(void *v);

typedef void (*capi_Vehicle_SetBoatAnchorActive)(void *v,  int state);

typedef int (*capi_Vehicle_SetSearchLight)(void *v,  int state,  Entity e);

typedef unsigned char (*capi_Vehicle_GetLightState)(void *v);

typedef void (*capi_Vehicle_SetLightState)(void *v,  unsigned char state);

typedef unsigned char (*capi_Vehicle_HasTimedExplosion)(void *v);

typedef Entity (*capi_Vehicle_GetTimedExplosionCulprit)(void *v);

typedef unsigned int (*capi_Vehicle_GetTimedExplosionTime)(void *v);

typedef void (*capi_Vehicle_SetTimedExplosion)(void *v,  unsigned char state,  void *culprit,  unsigned int time);

typedef unsigned char (*capi_Vehicle_IsTowingDisabled)(void *v);

typedef void (*capi_Vehicle_SetTowingDisabled)(void *v,  unsigned char state);

typedef float (*capi_Vehicle_GetRocketRefuelSpeed)(void *v);

typedef void (*capi_Vehicle_SetRocketRefuelSpeed)(void *v,  float speed);

typedef unsigned int (*capi_Vehicle_GetCounterMeasureCount)(void *v);

typedef void (*capi_Vehicle_SetCounterMeasureCount)(void *v,  unsigned int count);

typedef float (*capi_Vehicle_GetScriptMaxSpeed)(void *v);

typedef void (*capi_Vehicle_SetScriptMaxSpeed)(void *v,  float speed);

typedef int (*capi_Vehicle_GetWeaponCapacity)(void *v,  unsigned char index);

typedef void (*capi_Vehicle_SetWeaponCapacity)(void *v,  unsigned char index,  int capacity);

typedef unsigned char (*capi_Vehicle_GetHybridExtraActive)(void *v);

typedef void (*capi_Vehicle_SetHybridExtraActive)(void *v,  unsigned char state);

typedef unsigned char (*capi_Vehicle_GetHybridExtraState)(void *v);

typedef void (*capi_Vehicle_SetHybridExtraState)(void *v,  unsigned char state);

typedef int (*capi_VoiceChannel_IsValid)(const char* resourceName,  void *p);

typedef int (*capi_VoiceChannel_GetType)(void *c);

typedef int (*capi_VoiceChannel_HasMetaData)(void* base,  const char *key);

typedef Array (*capi_VoiceChannel_GetMetaData)(void* base,  const char *key);

typedef void (*capi_VoiceChannel_SetMetaData)(void *base,  const char *key,  Array data);

typedef void (*capi_VoiceChannel_DeleteMetaData)(void *base,  const char *key);

typedef void (*capi_VoiceChannel_Destroy)(void *b);

typedef int (*capi_VoiceChannel_IsSpatial)(void *v);

typedef float (*capi_VoiceChannel_GetMaxDistance)(void *v);

typedef int (*capi_VoiceChannel_HasPlayer)(void *v,  void *p);

typedef void (*capi_VoiceChannel_AddPlayer)(void *v,  void *p);

typedef void (*capi_VoiceChannel_RemovePlayer)(void *v,  void *p);

typedef int (*capi_VoiceChannel_IsPlayerMuted)(void *v,  void *p);

typedef void (*capi_VoiceChannel_MutePlayer)(void *v,  void *p);

typedef void (*capi_VoiceChannel_UnmutePlayer)(void *v,  void *p);

typedef unsigned long long (*capi_VoiceChannel_GetPlayerCount)(void *v);

typedef Array (*capi_VoiceChannel_GetPlayers)(void *v);



int ColShape_GetType(void *c);

int ColShape_HasMetaData(void* base,  const char *key);

Array ColShape_GetMetaData(void* base,  const char *key);

void ColShape_SetMetaData(void *base,  const char *key,  Array data);

void ColShape_DeleteMetaData(void *base,  const char *key);

void ColShape_Destroy(void *b);

int ColShape_IsValid(const char* resourceName,  void *p);

Position ColShape_GetPosition(void *p);

void ColShape_SetPosition(void* p,  float x,  float y,  float z);

long ColShape_GetDimension(void* p);

void ColShape_SetDimension(void* p,  long dimension);

int ColShape_GetColShapeType(void *c);

int ColShape_IsEntityIn(void *c,  Entity e);

int ColShape_IsPointIn(void *c,  float x,  float y,  float z);

void ColShape_SetPlayersOnly(void *c,  int state);

int ColShape_IsPlayersOnly(void *c);

unsigned char ColShape_IsEntityIdIn(void *c,  unsigned short id);

void Core_LogInfo(const char *message);

void Core_LogDebug(const char *message);

void Core_LogWarning(const char *message);

void Core_LogError(const char *message);

void Core_LogColored(const char *message);

Entity Core_CreateVehicle(unsigned long model,  float posX,  float posY,  float posZ, 
                                float rotX,  float rotY,  float rotZ);

Entity
 Core_CreateCheckpoint(unsigned char type,  float x,  float y,  float z,  float radius,  float height,  unsigned char r, 
                      unsigned char g,  unsigned char b,  unsigned char a,  unsigned long streamingDistance);

Entity Core_CreateVoiceChannel(int spacial,  float maxDistance);

const char * Core_GetVersion();

const char * Core_GetBranch();

int Core_IsDebug();

unsigned long Core_Hash(const char *str);

int Core_FileExists(const char *path);

const char * Core_ReadFile(const char *path);

Entity Core_GetEntityByID(unsigned short id);

Entity Core_GetBaseObjectByID(unsigned char type,  unsigned int id);

Array Core_GetEntities();

Array Core_GetPlayers();

Array Core_GetVehicles();

Array Core_GetBlips();

Array Core_GetColShapes();

Array Core_GetCheckpoints();

Array Core_GetVirtualEntities();

Array Core_GetVirtualEntityGroups();

Array Core_GetMarkers();

Array Core_GetPeds();

int Core_HasMetaData(const char *key);

Array Core_GetMetaData(const char *key);

void Core_SetMetaData(const char *key,  Array data);

void Core_DeleteMetaData(const char *key);

int Core_HasSyncedMetaData(const char *key);

Array Core_GetSyncedMetaData(const char *key);

Array Core_GetRequiredPermissions();

Array Core_GetOptionalPermissions();

void Core_DestroyBaseObject(void *h);

const char * Core_GetRootDirectory();

int Core_StartResource(const char *name);

void Core_StopResource(const char *name);

void Core_RestartResource(const char *name);

void Core_SetSyncedMetaData(const char *key,  Array data);

void Core_DeleteSyncedMetaData(const char *key);

Array Core_GetPlayersByName(const char *name);

unsigned int Core_GetNetTime();

void Core_SetPassword(const char *password);

const char * Core_GetSDKHash();

Entity Core_CreateColShapeCylinder(float posX,  float posY,  float posZ,  float radius,  float height);

Entity Core_CreateColShapeCube(float posX1,  float posY1,  float posZ1,  float posX2,  float posY2,  float posZ2);

Entity Core_CreateColShapeRectangle(float x1,  float y1,  float x2,  float y2,  float z);

Entity Core_CreateColShapeCircle(float posX,  float posY,  float posZ,  float radius);

Entity Core_CreateColShapeSphere(float posX,  float posY,  float posZ,  float radius);

void Core_TriggerLocalEvent(const char *ev,  Array args);

void Core_TriggerLocalEventRaw(const char* ev,  char* bytes,  unsigned long long size);

void Core_TriggerClientEvent(void *p,  const char *ev,  Array args);

void Core_TriggerClientEventFor(Array clients,  const char *ev,  Array args);

void Core_TriggerClientEventForAll(const char *ev,  Array args);

Entity Core_CreatePointBlipPosition(float x,  float y,  float z,  unsigned short global);

Entity Core_CreatePointBlipEntity(Entity entity,  unsigned short global);

Entity Core_CreateAreaBlip(float x,  float y,  float z,  float width,  float height,  unsigned short global);

Entity Core_CreateRadiusBlip(float x,  float y,  float z,  float radius,  unsigned short global);

Entity Core_CreateColShapePolygon(float minZ,  float maxZ,  Array points);

Array Core_GetAllResources();

const char * Core_StringToSHA256(const char *str);

void Core_StopServer();

VehicleModelInfo Core_GetVehicleModelByHash(unsigned int hash);

PedModelInfo Core_GetPedModelByHash(unsigned int hash);

Array Core_GetServerConfig();

unsigned long long Core_HashServerPassword(const char *password);

void* Core_GetResourceByName(const char *resourceName);

const char * Player_GetName(void *p);

int Player_HasMetaData(void *base,  const char *key);

Array Player_GetMetaData(void *base,  const char *key);

void Player_SetMetaData(void *base,  const char *key,  Array data);

void Player_DeleteMetaData(void *base,  const char *key);

int Player_HasSyncedMetaData(void *base,  const char *key);

Array Player_GetSyncedMetaData(void *base,  const char *key);

void Player_SetSyncedMetaData(void *base,  const char *key,  Array data);

void Player_DeleteSyncedMetaData(void *base,  const char *key);

int Player_HasStreamSyncedMetaData(void *base,  const char *key);

Array Player_GetStreamSyncedMetaData(void *base,  const char *key);

void Player_SetStreamSyncedMetaData(void *base,  const char *key,  Array data);

void Player_DeleteStreamSyncedMetaData(void *base,  const char *key);

Position Player_GetPosition(void *p);

void Player_SetPosition(void *p,  float x,  float y,  float z);

Rotation Player_GetRotation(void *p);

void Player_SetRotation(void *p,  float roll,  float pitch,  float yaw);

long Player_GetDimension(void *p);

void Player_SetDimension(void *p,  long dimension);

void Player_Spawn(void *p,  float x,  float y,  float z,  unsigned long delay);

void Player_Despawn(void *p);

void Player_SetModel(void *p,  unsigned long model);

unsigned long Player_GetModel(void *p);

unsigned int Player_GetHealth(void *p);

void Player_SetHealth(void *p,  unsigned int health);

int Player_HasWeaponComponent(void *p,  unsigned long weapon,  unsigned long component);

Array Player_GetCurrentWeaponComponents(void *p);

unsigned int Player_GetWeaponTintIndex(void *p,  unsigned long weapon);

unsigned int Player_GetCurrentWeaponTintIndex(void *p);

unsigned long Player_GetCurrentWeapon(void *p);

int Player_IsDead(void *p);

int Player_IsJumping(void *p);

int Player_IsInRagdoll(void *p);

int Player_IsAiming(void *p);

int Player_IsShooting(void *p);

int Player_IsReloading(void *p);

unsigned int Player_GetArmour(void *p);

void Player_SetArmour(void *p,  unsigned int armour);

float Player_GetMoveSpeed(void *p);

Position Player_GetAimPos(void *p);

Rotation Player_GetHeadRotation(void *p);

int Player_IsInVehicle(void *p);

Entity Player_GetVehicle(void *p);

unsigned int Player_GetSeat(void *p);

Entity Player_GetEntityAimingAt(void *p);

Position Player_GetEntityAimOffset(void *p);

int Player_IsFlashlightActive(void *p);

int Player_IsConnected(void *p);

unsigned long Player_GetPing(void *p);

const char * Player_GetIP(void *p);

unsigned long long Player_GetSocialID(void *p);

unsigned long long Player_GetHwidHash(void *p);

unsigned long long Player_GetHwidExHash(void *p);

const char * Player_GetAuthToken(void *p);

void Player_SetMaxArmour(void *p,  unsigned int armour);

void Player_SetCurrentWeapon(void *p,  unsigned long weapon);

void Player_SetWeaponTintIndex(void *p,  unsigned long weapon,  unsigned int tintIndex);

void Player_AddWeaponComponent(void *p,  unsigned long weapon,  unsigned long component);

void Player_RemoveWeaponComponent(void *p,  unsigned long weapon,  unsigned long component);

void Player_ClearBloodDamage(void *p);

void Player_SetMaxHealth(void *p,  unsigned int health);

void Player_GiveWeapon(void *p,  unsigned long weapon,  long ammo,  int selectWeapon);

void Player_RemoveWeapon(void *p,  unsigned long weapon);

void Player_RemoveAllWeapons(void *p,  unsigned short removeAmmo);

void Player_SetDateTime(void *p,  int day,  int month,  int year,  int hour,  int minute,  int second);

void Player_SetWeather(void *p,  unsigned long weather);

void Player_Kick(void *p,  const char *reason);

Cloth Player_GetClothes(void *p,  unsigned int component);

DlcCloth Player_GetDlcClothes(void *p,  unsigned int component);

Prop Player_GetProps(void *p,  unsigned int component);

DlcProp Player_GetDlcProps(void *p,  unsigned int component);

void
 Player_SetClothes(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture,  unsigned int palette);

void
 Player_SetDlcClothes(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture,  unsigned int palette, 
                     unsigned long dlc);

void Player_SetProps(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture);

void
 Player_SetDlcProps(void *p,  unsigned int component,  unsigned int drawable,  unsigned int texture,  unsigned long dlc);

void Player_ClearProps(void *p,  unsigned int component);

int Player_IsEntityInStreamingRange(void *p,  unsigned short entityId);

unsigned int Player_GetMaxHealth(void *p);

unsigned int Player_GetMaxArmour(void *p);

void Player_Detach(void *p);

void
 Player_AttachToEntity(void *p,  Entity e,  int otherBoneIndex,  int myBoneIndex,  Position position,  Rotation rotation, 
                      int collision,  int noFixedRotation);

void Player_SetVisible(void *p,  int toggle);

int Player_GetVisible(void *p);

unsigned long Player_GetID(void *p);

Entity Player_GetNetworkOwner(void *p);

void Player_SetNetworkOwner(void *p,  void *owner,  int disableMigration);

void Player_Destroy(void *p);

int Player_IsValid(const char* resourceName,  void *p);

int Player_GetStreamed(void *p);

void Player_SetStreamed(void *p,  int toggle);

int Player_GetInvincible(void *p);

void Player_SetInvincible(void *p,  int toggle);

void Player_SetIntoVehicle(void *p,  void *v,  unsigned char seat);

int Player_IsFrozen(void *p);

void Player_SetFrozen(void *p,  int state);

int Player_HasCollision(void *p);

void Player_SetCollision(void *p,  int state);

void
 Player_PlayAmbientSpeech(void *p,  const char *speechName,  const char *speechParam,  unsigned int speechDictHash);

int Player_SetHeadOverlay(void *p,  unsigned char overlayID,  unsigned char index,  float opacity);

int Player_RemoveHeadOverlay(void *p,  unsigned char overlayID);

int
 Player_SetHeadOverlayColor(void *p,  unsigned char overlayID,  unsigned char colorType,  unsigned char colorIndex, 
                           unsigned char secondColorIndex);

HeadOverlay Player_GetHeadOverlay(void *p,  unsigned char overlayID);

int Player_SetFaceFeature(void *p,  unsigned char index,  float scale);

float Player_GetFaceFeatureScale(void *p,  unsigned char index);

int Player_RemoveFaceFeature(void *p,  unsigned char index);

int
 Player_SetHeadBlendPaletteColor(void *p,  unsigned char id,  unsigned char red,  unsigned char green,  unsigned char blue);

RGBA Player_GetHeadBlendPaletteColor(void *p,  unsigned char id);

void
 Player_SetHeadBlendData(void *p,  unsigned int shapeFirstID,  unsigned int shapeSecondID,  unsigned int shapeThirdID, 
                        unsigned int skinFirstID,  unsigned int skinSecondID,  unsigned int skinThirdID, 
                        float shapeMix,  float skinMix,  float thirdMix);

HeadBlendData Player_GetHeadBlendData(void *p);

int Player_SetEyeColor(void *p,  short eyeColor);

short Player_GetEyeColor(void *p);

void Player_SetHairColor(void *p,  unsigned char hairColor);

unsigned char Player_GetHairColor(void *p);

void Player_SetHairHighlightColor(void *p,  unsigned char hairHighlightColor);

unsigned char Player_GetHairHighlightColor(void *p);

Array Player_GetWeapons(void *p);

int Player_HasLocalMetaData(void *p,  const char *key);

void Player_SetLocalMetaData(void *p,  const char *key,  Array data);

Array Player_GetLocalMetaData(void *p,  const char *key);

void Player_DeleteLocalMetaData(void *p,  const char *key);

unsigned int Player_GetCurrentAnimationDict(void *p);

unsigned int Player_GetCurrentAnimationName(void *p);

unsigned char Player_IsSpawned(void *p);

float Player_GetForwardSpeed(void *p);

float Player_GetStrafeSpeed(void *p);

long long Player_GetDiscordId(void *p);

unsigned int Player_GetInteriorLocation(void *p);

unsigned int Player_GetLastDamagedBodyPart(void *p);

void Player_SetLastDamagedBodyPart(void *p,  unsigned int bodyPart);

int Runtime_RegisterAltEvent(const char *resourceName,  unsigned short eventType);

int Runtime_UnregisterAltEvent(const char *resourceName,  unsigned short eventType);

int Runtime_RegisterAltExport(const char *resourceName,  const char *exportName,  Array value);

Array Runtime_GetAltExport(const char *targetResourceName,  const char *exportName);

void * Runtime_CreateMValueFunction(const char *resourceName,  unsigned long long id);

Array Runtime_CallMValueFunction(void *ptr,  Array args);

void Connection_Accept(void *handle,  unsigned char sendNames);

void Connection_Decline(void *handle,  const char *reason);

int Connection_IsAccepted(void *handle);

int Blip_GetType(void *c);

int Blip_HasMetaData(void *base,  const char *key);

Array Blip_GetMetaData(void *base,  const char *key);

void Blip_SetMetaData(void *base,  const char *key,  Array data);

void Blip_DeleteMetaData(void *base,  const char *key);

void Blip_Destroy(void *b);

int Blip_IsValid(const char *resourceName,  void *p);

Position Blip_GetPosition(void *p);

void Blip_SetPosition(void *p,  float x,  float y,  float z);

long Blip_GetDimension(void *p);

void Blip_SetDimension(void *p,  long dimension);

int Blip_IsGlobal(void *b);

Array Blip_GetTargets(void *b);

int Blip_IsAttached(void *b);

Entity Blip_AttachedTo(void *b);

void Blip_AttachTo(void *b,  Entity e);

unsigned char Blip_GetBlipType(void *b);

Vector2 Blip_GetScaleXY(void *b);

void Blip_SetScaleXY(void *b,  Vector2 scale);

int Blip_GetDisplay(void *b);

void Blip_SetDisplay(void *b,  int display);

int Blip_GetSprite(void *b);

int Blip_GetColor(void *b);

RGBA Blip_GetSecondaryColor(void *b);

int Blip_GetAlpha(void *b);

int Blip_GetFlashTimer(void *b);

int Blip_GetFlashInterval(void *b);

int Blip_GetAsFriendly(void *b);

int Blip_GetRoute(void *b);

int Blip_GetBright(void *b);

int Blip_GetNumber(void *b);

int Blip_GetShowCone(void *b);

int Blip_GetFlashes(void *b);

int Blip_GetFlashesAlternate(void *b);

int Blip_GetAsShortRange(void *b);

int Blip_GetPriority(void *b);

float Blip_GetRotation(void *b);

const char * Blip_GetGxtName(void *b);

const char * Blip_GetName(void *b);

RGBA Blip_GetRouteColor(void *b);

int Blip_GetPulse(void *b);

int Blip_GetAsMissionCreator(void *b);

int Blip_GetTickVisible(void *b);

int Blip_GetHeadingIndicatorVisible(void *b);

int Blip_GetOutlineIndicatorVisible(void *b);

int Blip_GetFriendIndicatorVisible(void *b);

int Blip_GetCrewIndicatorVisible(void *b);

int Blip_GetCategory(void *b);

int Blip_GetAsHighDetail(void *b);

int Blip_GetShrinked(void *b);

void Blip_SetSprite(void *b,  int sprite);

void Blip_SetColor(void *b,  int color);

void Blip_SetRoute(void *b,  int state);

void Blip_SetRouteColor(void *b,  RGBA color);

void Blip_SetSecondaryColor(void *b,  RGBA color);

void Blip_SetAlpha(void *b,  int alpha);

void Blip_SetFlashTimer(void *b,  int timer);

void Blip_SetFlashInterval(void *b,  int interval);

void Blip_SetAsFriendly(void *b,  int friendly);

void Blip_SetBright(void *b,  int bright);

void Blip_SetNumber(void *b,  int number);

void Blip_SetShowCone(void *b,  int state);

void Blip_SetFlashes(void *b,  int state);

void Blip_SetFlashesAlternate(void *b,  int state);

void Blip_SetAsShortRange(void *b,  int state);

void Blip_SetPriority(void *b,  int state);

void Blip_SetRotation(void *b,  float rot);

void Blip_SetGxtName(void *b,  const char *name);

void Blip_SetName(void *b,  const char *name);

void Blip_SetPulse(void *b,  int val);

void Blip_SetAsMissionCreator(void *b,  int val);

void Blip_SetTickVisible(void *b,  int val);

void Blip_SetHeadingIndicatorVisible(void *b,  int val);

void Blip_SetOutlineIndicatorVisible(void *b,  int val);

void Blip_SetFriendIndicatorVisible(void *b,  int val);

void Blip_SetCrewIndicatorVisible(void *b,  int val);

void Blip_SetCategory(void *b,  int val);

void Blip_SetAsHighDetail(void *b,  int val);

void Blip_SetShrinked(void *b,  int val);

void Blip_Fade(void *b,  unsigned int opacity,  unsigned int duration);

int Checkpoint_GetType(void *c);

int Checkpoint_HasMetaData(void* base,  const char *key);

Array Checkpoint_GetMetaData(void* base,  const char *key);

void Checkpoint_SetMetaData(void *base,  const char *key,  Array data);

void Checkpoint_DeleteMetaData(void *base,  const char *key);

void Checkpoint_Destroy(void *b);

int Checkpoint_IsValid(const char* resourceName,  void *p);

Position Checkpoint_GetPosition(void *p);

void Checkpoint_SetPosition(void* p,  float x,  float y,  float z);

long Checkpoint_GetDimension(void* p);

void Checkpoint_SetDimension(void* p,  long dimension);

int Checkpoint_GetColShapeType(void *c);

int Checkpoint_IsEntityIn(void *c,  Entity e);

int Checkpoint_IsPointIn(void *c,  float x,  float y,  float z);

void Checkpoint_SetPlayersOnly(void *c,  int state);

int Checkpoint_IsPlayersOnly(void *c);

unsigned char Checkpoint_IsEntityIdIn(void *c,  unsigned short id);

unsigned char Checkpoint_GetCheckpointType(void *c);

float Checkpoint_GetHeight(void *c);

float Checkpoint_GetRadius(void *c);

RGBA Checkpoint_GetColor(void *c);

Position Checkpoint_GetNextPosition(void *c);

void Checkpoint_SetCheckpointType(void *c,  unsigned char type);

void Checkpoint_SetHeight(void *c,  float height);

void Checkpoint_SetRadius(void *c,  float radius);

void Checkpoint_SetColor(void *c,  unsigned char r,  unsigned char g,  unsigned char b,  unsigned char a);

void Checkpoint_SetNextPosition(void *c,  float x,  float y,  float z);

unsigned char Resource_IsStarted(void *r);

const char * Resource_GetType(void *r);

const char * Resource_GetName(void* r);

const char * Resource_GetMain(void *r);

Array Resource_GetConfig(void *r);

Array Resource_GetExports(void *r);

Array Resource_GetDependencies(void *r);

Array Resource_GetDependants(void *r);

Array Resource_GetRequiredPermissions(void *r);

Array Resource_GetOptionalPermissions(void *r);

const char * Resource_GetPath(void *r);

int Vehicle_HasMetaData(void *base,  const char *key);

Array Vehicle_GetMetaData(void *base,  const char *key);

void Vehicle_SetMetaData(void *base,  const char *key,  Array data);

void Vehicle_DeleteMetaData(void *base,  const char *key);

int Vehicle_HasSyncedMetaData(void *base,  const char *key);

Array Vehicle_GetSyncedMetaData(void *base,  const char *key);

void Vehicle_SetSyncedMetaData(void *base,  const char *key,  Array data);

void Vehicle_DeleteSyncedMetaData(void *base,  const char *key);

int Vehicle_HasStreamSyncedMetaData(void *base,  const char *key);

Array Vehicle_GetStreamSyncedMetaData(void *base,  const char *key);

void Vehicle_SetStreamSyncedMetaData(void *base,  const char *key,  Array data);

void Vehicle_DeleteStreamSyncedMetaData(void *base,  const char *key);

Position Vehicle_GetPosition(void *v);

void Vehicle_SetPosition(void *v,  float x,  float y,  float z);

Rotation Vehicle_GetRotation(void *v);

void Vehicle_SetRotation(void *v,  float roll,  float pitch,  float yaw);

long Vehicle_GetDimension(void *v);

void Vehicle_SetDimension(void *v,  long dimension);

unsigned long Vehicle_GetID(void *v);

unsigned long Vehicle_GetModel(void *v);

void Vehicle_Detach(void *v);

void
 Vehicle_AttachToEntity(void *v,  Entity e,  int otherBoneIndex,  int myBoneIndex,  Position position,  Rotation rotation, 
                       int collision,  int noFixedRotation);

void Vehicle_SetVisible(void *v,  int toggle);

int Vehicle_GetVisible(void *v);

Entity Vehicle_GetNetworkOwner(void *v);

void Vehicle_SetNetworkOwner(void *v,  void *owner,  int disableMigration);

Entity Vehicle_GetDriver(void *v);

int Vehicle_IsDestroyed(void *v);

unsigned long Vehicle_GetMod(void *v,  unsigned int category);

unsigned long Vehicle_GetModsCount(void *v,  unsigned int category);

unsigned long Vehicle_GetModKitsCount(void *v);

unsigned long Vehicle_GetModKit(void *v);

int Vehicle_IsPrimaryColorRGB(void *v);

unsigned long Vehicle_GetPrimaryColor(void *v);

RGBA Vehicle_GetPrimaryColorRGB(void *v);

int Vehicle_IsSecondaryColorRGB(void *v);

unsigned long Vehicle_GetSecondaryColor(void *v);

RGBA Vehicle_GetSecondaryColorRGB(void *v);

unsigned long Vehicle_GetPearlColor(void *v);

unsigned long Vehicle_GetWheelColor(void *v);

unsigned long Vehicle_GetInteriorColor(void *v);

unsigned long Vehicle_GetDashboardColor(void *v);

int Vehicle_IsTireSmokeColorCustom(void *v);

RGBA Vehicle_GetTireSmokeColor(void *v);

unsigned long Vehicle_GetWheelType(void *v);

unsigned long Vehicle_GetWheelVariation(void *v);

unsigned long Vehicle_GetRearWheelVariation(void *v);

int Vehicle_GetCustomTires(void *v);

unsigned long Vehicle_GetSpecialDarkness(void *v);

unsigned long Vehicle_GetNumberplateIndex(void *v);

const char * Vehicle_GetNumberplateText(void *v);

unsigned long Vehicle_GetWindowTint(void *v);

unsigned long Vehicle_GetDirtLevel(void *v);

int Vehicle_IsExtraOn(void *v,  unsigned int extraID);

int Vehicle_IsNeonActive(void *v);

VehicleNeonState Vehicle_GetNeonActive(void *v);

RGBA Vehicle_GetNeonColor(void *v);

unsigned long Vehicle_GetLivery(void *v);

unsigned long Vehicle_GetRoofLivery(void *v);

const char * Vehicle_GetAppearanceDataBase64(void *v);

int Vehicle_IsEngineOn(void *v);

int Vehicle_IsHandbrakeActive(void *v);

unsigned long Vehicle_GetHeadlightColor(void *v);

unsigned long Vehicle_GetRadioStationIndex(void *v);

int Vehicle_IsSirenActive(void *v);

unsigned long Vehicle_GetLockState(void *v);

unsigned long Vehicle_GetDoorState(void *v,  unsigned int doorId);

int Vehicle_IsWindowOpened(void *v,  unsigned int windowId);

int Vehicle_IsDaylightOn(void *v);

int Vehicle_IsNightlightOn(void *v);

unsigned long Vehicle_GetRoofState(void *v);

int Vehicle_IsFlamethrowerActive(void *v);

float Vehicle_GetLightsMultiplier(void *v);

const char * Vehicle_GetGameStateBase64(void *v);

long Vehicle_GetEngineHealth(void *v);

long Vehicle_GetPetrolTankHealth(void *v);

unsigned long Vehicle_GetWheelsCount(void *v);

int Vehicle_IsWheelBurst(void *v,  unsigned int wheelId);

int Vehicle_DoesWheelHasTire(void *v,  unsigned int wheelId);

int Vehicle_IsWheelDetached(void *v,  unsigned int wheelId);

int Vehicle_IsWheelOnFire(void *v,  unsigned int wheelId);

float Vehicle_GetWheelHealth(void *v,  unsigned int wheelId);

unsigned long Vehicle_GetRepairsCount(void *v);

unsigned long Vehicle_GetBodyHealth(void *v);

unsigned long Vehicle_GetBodyAdditionalHealth(void *v);

const char * Vehicle_GetHealthDataBase64(void *v);

unsigned long Vehicle_GetPartDamageLevel(void *v,  unsigned int partId);

unsigned long Vehicle_GetPartBulletHoles(void *v,  unsigned int partId);

int Vehicle_IsLightDamaged(void *v,  unsigned int lightId);

int Vehicle_IsWindowDamaged(void *v,  unsigned int windowId);

int Vehicle_IsSpecialLightDamaged(void *v,  unsigned int specialLightId);

int Vehicle_HasArmoredWindows(void *v);

float Vehicle_GetArmoredWindowHealth(void *v,  unsigned int windowId);

unsigned long Vehicle_GetArmoredWindowShootCount(void *v,  unsigned int windowId);

unsigned long Vehicle_GetBumperDamageLevel(void *v,  unsigned int bumperId);

const char * Vehicle_GetDamageDataBase64(void *v);

int Vehicle_IsManualEngineControl(void *v);

const char * Vehicle_GetScriptDataBase64(void *v);

void Vehicle_ToggleExtra(void *v,  unsigned int extraID,  int state);

void Vehicle_SetFixed(void *v);

int Vehicle_SetMod(void *v,  unsigned int category,  unsigned int id);

int Vehicle_SetModKit(void *v,  unsigned int id);

void Vehicle_SetPrimaryColor(void *v,  unsigned int color);

void Vehicle_SetPrimaryColorRGB(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

void Vehicle_SetSecondaryColor(void *v,  unsigned int color);

void Vehicle_SetSecondaryColorRGB(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

void Vehicle_SetPearlColor(void *v,  unsigned int color);

void Vehicle_SetWheelColor(void *v,  unsigned int color);

void Vehicle_SetInteriorColor(void *v,  unsigned int color);

void Vehicle_SetDashboardColor(void *v,  unsigned int color);

void Vehicle_SetTireSmokeColor(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

void Vehicle_SetWheels(void *v,  unsigned int type,  unsigned int variation);

void Vehicle_SetRearWheels(void *v,  unsigned int variation);

void Vehicle_SetCustomTires(void *v,  int state);

void Vehicle_SetSpecialDarkness(void *v,  unsigned int value);

void Vehicle_SetNumberplateIndex(void *v,  unsigned int index);

void Vehicle_SetNumberplateText(void *v,  const char *text);

void Vehicle_SetWindowTint(void *v,  unsigned int tint);

void Vehicle_SetDirtLevel(void *v,  unsigned int level);

void Vehicle_SetNeonActive(void *v,  int left,  int right,  int front,  int back);

void Vehicle_SetNeonColor(void *v,  unsigned int r,  unsigned int g,  unsigned int b,  unsigned int a);

void Vehicle_SetLivery(void *v,  unsigned int livery);

void Vehicle_SetRoofLivery(void *v,  unsigned int roofLivery);

void Vehicle_LoadAppearanceDataFromBase64(void *v,  const char *base64);

void Vehicle_SetEngineOn(void *v,  int state);

void Vehicle_SetHeadlightColor(void *v,  unsigned int color);

void Vehicle_SetRadioStationIndex(void *v,  unsigned int stationIndex);

void Vehicle_SetSirenActive(void *v,  int state);

void Vehicle_SetLockState(void *v,  unsigned int state);

void Vehicle_SetDoorState(void *v,  unsigned int doorId,  unsigned int state);

void Vehicle_SetWindowOpened(void *v,  unsigned int windowId,  int state);

void Vehicle_SetRoofState(void *v,  unsigned int state);

void Vehicle_SetLightsMultiplier(void *v,  float multiplier);

void Vehicle_SetEngineHealth(void *v,  unsigned long health);

void Vehicle_SetPetrolTankHealth(void *v,  unsigned long health);

void Vehicle_SetWheelBurst(void *v,  unsigned int wheelId,  int state);

void Vehicle_SetWheelHasTire(void *v,  unsigned int wheelId,  int state);

void Vehicle_SetWheelDetached(void *v,  unsigned int wheelId,  int state);

void Vehicle_SetWheelOnFire(void *v,  unsigned int wheelId,  int state);

void Vehicle_SetWheelHealth(void *v,  unsigned int wheelId,  float health);

void Vehicle_SetWheelFixed(void *v,  unsigned int wheelId);

void Vehicle_SetBodyHealth(void *v,  unsigned long health);

void Vehicle_SetBodyAdditionalHealth(void *v,  unsigned long health);

void Vehicle_SetPartDamageLevel(void *v,  unsigned int partId,  unsigned int damage);

void Vehicle_SetPartBulletHoles(void *v,  unsigned int partId,  unsigned int shootsCount);

void Vehicle_SetLightDamaged(void *v,  unsigned int lightId,  int isDamaged);

void Vehicle_SetWindowDamaged(void *v,  unsigned int windowId,  int isDamaged);

void Vehicle_SetSpecialLightDamaged(void *v,  unsigned int specialLightId,  int isDamaged);

void Vehicle_SetArmoredWindowHealth(void *v,  unsigned int windowId,  float health);

void Vehicle_SetArmoredWindowShootCount(void *v,  unsigned int windowId,  unsigned int count);

void Vehicle_SetBumperDamageLevel(void *v,  unsigned int bumperId,  unsigned int damageLevel);

void Vehicle_SetManualEngineControl(void *v,  int state);

void Vehicle_LoadDamageDataFromBase64(void *v,  const char *base64);

void Vehicle_LoadScriptDataFromBase64(void *v,  const char *base64);

void Vehicle_LoadGameStateFromBase64(void *v,  const char *base64);

void Vehicle_LoadHealthDataFromBase64(void *v,  const char *base64);

Entity Vehicle_GetAttached(void *v);

Entity Vehicle_GetAttachedTo(void *v);

void Vehicle_Destroy(void *v);

int Vehicle_IsValid(const char *resourceName,  void *p);

int Vehicle_GetStreamed(void *v);

void Vehicle_SetStreamed(void *v,  int toggle);

int Vehicle_IsFrozen(void *v);

void Vehicle_SetFrozen(void *v,  int state);

int Vehicle_HasCollision(void *v);

void Vehicle_SetCollision(void *v,  int state);

int Vehicle_IsDriftMode(void *v);

void Vehicle_SetDriftMode(void *v,  int state);

int Vehicle_IsTrainMissionTrain(void *v);

void Vehicle_SetTrainMissionTrain(void *v,  int value);

char Vehicle_GetTrainTrackId(void *v);

void Vehicle_SetTrainTrackId(void *v,  char trackId);

Entity Vehicle_GetTrainEngineId(void *v);

void Vehicle_SetTrainEngineId(void *v,  void *e);

char Vehicle_GetTrainConfigIndex(void *v);

void Vehicle_SetTrainConfigIndex(void *v,  char trainConfigIndex);

float Vehicle_GetTrainDistanceFromEngine(void *v);

void Vehicle_SetTrainDistanceFromEngine(void *v,  float distanceFromEngine);

int Vehicle_IsTrainEngine(void *v);

void Vehicle_SetTrainIsEngine(void *v,  int isEngine);

int Vehicle_IsTrainCaboose(void *v);

void Vehicle_SetTrainIsCaboose(void *v,  int isCaboose);

int Vehicle_GetTrainDirection(void *v);

void Vehicle_SetTrainDirection(void *v,  int direction);

int Vehicle_HasTrainPassengerCarriages(void *v);

void Vehicle_SetTrainHasPassengerCarriages(void *v,  int hasPassengerCarriages);

int Vehicle_GetTrainRenderDerailed(void *v);

void Vehicle_SetTrainRenderDerailed(void *v,  int renderDerailed);

int Vehicle_GetTrainForceDoorsOpen(void *v);

void Vehicle_SetTrainForceDoorsOpen(void *v,  int forceDoorsOpen);

float Vehicle_GetTrainCruiseSpeed(void *v);

void Vehicle_SetTrainCruiseSpeed(void *v,  float cruiseSpeed);

char Vehicle_GetTrainCarriageConfigIndex(void *v);

void Vehicle_SetTrainCarriageConfigIndex(void *v,  char carriageConfigIndex);

Entity Vehicle_GetTrainLinkedToBackwardId(void *v);

void Vehicle_SetTrainLinkedToBackwardId(void *v,  void *e);

Entity Vehicle_GetTrainLinkedToForwardId(void *v);

void Vehicle_SetTrainLinkedToForwardId(void *v,  void *e);

void Vehicle_SetTrainUnk1(void *v,  int unk1);

int Vehicle_GetTrainUnk1(void *v);

void Vehicle_SetTrainUnk2(void *v,  int unk2);

int Vehicle_GetTrainUnk2(void *v);

void Vehicle_SetTrainUnk3(void *v,  int unk3);

int Vehicle_GetTrainUnk3(void *v);

int Vehicle_IsBoatAnchorActive(void *v);

void Vehicle_SetBoatAnchorActive(void *v,  int state);

int Vehicle_SetSearchLight(void *v,  int state,  Entity e);

unsigned char Vehicle_GetLightState(void *v);

void Vehicle_SetLightState(void *v,  unsigned char state);

unsigned char Vehicle_HasTimedExplosion(void *v);

Entity Vehicle_GetTimedExplosionCulprit(void *v);

unsigned int Vehicle_GetTimedExplosionTime(void *v);

void Vehicle_SetTimedExplosion(void *v,  unsigned char state,  void *culprit,  unsigned int time);

unsigned char Vehicle_IsTowingDisabled(void *v);

void Vehicle_SetTowingDisabled(void *v,  unsigned char state);

float Vehicle_GetRocketRefuelSpeed(void *v);

void Vehicle_SetRocketRefuelSpeed(void *v,  float speed);

unsigned int Vehicle_GetCounterMeasureCount(void *v);

void Vehicle_SetCounterMeasureCount(void *v,  unsigned int count);

float Vehicle_GetScriptMaxSpeed(void *v);

void Vehicle_SetScriptMaxSpeed(void *v,  float speed);

int Vehicle_GetWeaponCapacity(void *v,  unsigned char index);

void Vehicle_SetWeaponCapacity(void *v,  unsigned char index,  int capacity);

unsigned char Vehicle_GetHybridExtraActive(void *v);

void Vehicle_SetHybridExtraActive(void *v,  unsigned char state);

unsigned char Vehicle_GetHybridExtraState(void *v);

void Vehicle_SetHybridExtraState(void *v,  unsigned char state);

int VoiceChannel_IsValid(const char* resourceName,  void *p);

int VoiceChannel_GetType(void *c);

int VoiceChannel_HasMetaData(void* base,  const char *key);

Array VoiceChannel_GetMetaData(void* base,  const char *key);

void VoiceChannel_SetMetaData(void *base,  const char *key,  Array data);

void VoiceChannel_DeleteMetaData(void *base,  const char *key);

void VoiceChannel_Destroy(void *b);

int VoiceChannel_IsSpatial(void *v);

float VoiceChannel_GetMaxDistance(void *v);

int VoiceChannel_HasPlayer(void *v,  void *p);

void VoiceChannel_AddPlayer(void *v,  void *p);

void VoiceChannel_RemovePlayer(void *v,  void *p);

int VoiceChannel_IsPlayerMuted(void *v,  void *p);

void VoiceChannel_MutePlayer(void *v,  void *p);

void VoiceChannel_UnmutePlayer(void *v,  void *p);

unsigned long long VoiceChannel_GetPlayerCount(void *v);

Array VoiceChannel_GetPlayers(void *v);

#endif