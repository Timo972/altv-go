#include "ColShape.h"
#include "GoRuntime.h"
#include "GoResource.h"

// BaseObject inherited
EXPORT int ColShape_GetType(void *c)
{
    auto colShape = reinterpret_cast<alt::IColShape*>(c);
    return static_cast<int>(colShape->GetType());
}

EXPORT int ColShape_HasMetaData(void* base, const char *key)
{
    auto baseObject = reinterpret_cast<alt::IColShape*>(base);
    return baseObject->HasMetaData(key);
}

EXPORT GoValue ColShape_GetMetaData(void* base, const char *key)
{
    auto baseObject = reinterpret_cast<alt::IColShape*>(base);
    auto meta = baseObject->GetMetaData(key);

    GoValue data{};
    Go::Runtime::MValueToGo(meta, &data);

    return data;
}

EXPORT void ColShape_SetMetaData(void *base, const char *key, GoValue data)
{
    auto baseObject = reinterpret_cast<alt::IColShape*>(base);
    auto value = Go::Runtime::GoToMValue(data);

    baseObject->SetMetaData(key, value);
}

EXPORT void ColShape_DeleteMetaData(void *base, const char *key)
{
    auto baseObject = reinterpret_cast<alt::IColShape*>(base);
    baseObject->DeleteMetaData(key);
    // baseObject->RemoveRef();
}

EXPORT void ColShape_Destroy(void *b)
{
    auto colShape = reinterpret_cast<alt::IColShape*>(b);
    alt::ICore::Instance().DestroyBaseObject(colShape);
}

EXPORT int ColShape_IsValid(const char *resourceName, void *p)
{
    auto cs = reinterpret_cast<alt::IColShape*>(p);
    auto resource = dynamic_cast<Go::Resource*>(Go::Runtime::GetInstance()->GetResource(resourceName));

    return resource->HasEntity(cs);
}

// WorldObject inherited
EXPORT Position ColShape_GetPosition(void *p)
{
    auto colShape = reinterpret_cast<alt::IColShape*>(p);
    auto pos = colShape->GetPosition();

    Position position;
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    return position;
}

EXPORT void ColShape_SetPosition(void *p, float x, float y, float z)
{
    auto colShape = reinterpret_cast<alt::IColShape*>(p);

    alt::Position position(x, y, z);

    colShape->SetPosition(position);
}

EXPORT long ColShape_GetDimension(void *p)
{
    auto colShape = reinterpret_cast<alt::IColShape*>(p);
    return colShape->GetDimension();
}

EXPORT void ColShape_SetDimension(void *p, long dimension)
{
    auto colShape = reinterpret_cast<alt::IColShape*>(p);
    colShape->SetDimension(dimension);
}

// ColShape inherited
EXPORT int ColShape_GetColShapeType(void *c)
{
    auto colShape = reinterpret_cast<alt::IColShape*>(c);
    return static_cast<int>(colShape->GetColshapeType());
}

EXPORT int ColShape_IsEntityIn(void *c, Entity e)
{
    auto colShape = reinterpret_cast<alt::IColShape*>(c);
    auto entity = Go::Runtime::GetEntityRef(e);
    return colShape->IsEntityIn(entity);
}

EXPORT int ColShape_IsPointIn(void *c, float x, float y, float z)
{
    auto colShape = reinterpret_cast<alt::IColShape*>(c);

    alt::Position pos(x,y,z);

    return colShape->IsPointIn(pos);
}

EXPORT void ColShape_SetPlayersOnly(void *c, int state)
{
    auto colShape = reinterpret_cast<alt::IColShape*>(c);
    colShape->SetPlayersOnly(state);
}

EXPORT int ColShape_IsPlayersOnly(void *c)
{
    auto colShape = reinterpret_cast<alt::IColShape*>(c);
    return colShape->IsPlayersOnly();
}

EXPORT unsigned char ColShape_IsEntityIdIn(void *c, unsigned short id) 
{
    auto colShape = reinterpret_cast<alt::IColShape*>(c);
    return colShape->IsEntityIdIn(id);
}