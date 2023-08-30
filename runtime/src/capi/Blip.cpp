#include "Blip.h"
#include "GoRuntime.h"
#include "GoResource.h"

// BaseObject inherited
EXPORT int Blip_GetType(void *c)
{
    auto blip = reinterpret_cast<alt::IBlip*>(c);
    return static_cast<int>(blip->GetType());
}

EXPORT int Blip_HasMetaData(void* base, const char *key)
{
    auto baseObject = reinterpret_cast<alt::IBlip*>(base);
    return baseObject->HasMetaData(key);
}

EXPORT Array Blip_GetMetaData(void* base, const char *key)
{
    auto baseObject = reinterpret_cast<alt::IBlip*>(base);
    auto meta = baseObject->GetMetaData(key);

    return Go::Runtime::EncodeMValue(meta);
}

EXPORT void Blip_SetMetaData(void *base, const char *key, Array data)
{
    auto baseObject = reinterpret_cast<alt::IBlip*>(base);
    auto value = Go::Runtime::DecodeMValue(data);

    baseObject->SetMetaData(key, value);
}

EXPORT void Blip_DeleteMetaData(void *base, const char *key)
{
    auto baseObject = reinterpret_cast<alt::IBlip*>(base);
    baseObject->DeleteMetaData(key);
    // baseObject->RemoveRef();
}

EXPORT void Blip_Destroy(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    alt::ICore::Instance().DestroyBaseObject(blip);
}

EXPORT int Blip_IsValid(const char *resourceName, void* p)
{
    auto cs = reinterpret_cast<alt::IBlip*>(p);
    auto resource = dynamic_cast<Go::Resource*>(Go::Runtime::GetInstance()->GetResource(resourceName));

    return resource->HasEntity(cs);
}

// WorldObject inherited
EXPORT Position Blip_GetPosition(void *p)
{
    auto blip = reinterpret_cast<alt::IBlip*>(p);
    auto pos = blip->GetPosition();

    Position position;
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    return position;
}

EXPORT void Blip_SetPosition(void *p, float x, float y, float z)
{
    auto blip = reinterpret_cast<alt::IBlip*>(p);

    alt::Position position(x, y, z);

    blip->SetPosition(position);
}

EXPORT long Blip_GetDimension(void *p)
{
    auto blip = reinterpret_cast<alt::IBlip*>(p);
    return blip->GetDimension();
}

EXPORT void Blip_SetDimension(void *p, long dimension)
{
    auto blip = reinterpret_cast<alt::IBlip*>(p);
    blip->SetDimension(dimension);
}

// Blip methods
EXPORT int Blip_IsGlobal(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->IsGlobal();
}

EXPORT Array Blip_GetTargets(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return Go::Runtime::CreateEntityArray(blip->GetTargets());
}

EXPORT int Blip_IsAttached(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->IsAttached();
}

EXPORT Entity Blip_AttachedTo(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    auto entity = blip->AttachedTo();

    return Go::Runtime::GetEntity(entity);
}

EXPORT void Blip_AttachTo(void *b, Entity e)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    auto entity = Go::Runtime::GetEntityRef(e);
    blip->AttachTo(entity);
}

EXPORT unsigned char Blip_GetBlipType(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return static_cast<unsigned char>(blip->GetBlipType());
}

EXPORT Vector2 Blip_GetScaleXY(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    auto vector2 = blip->GetScaleXY();

    Vector2 v2;
    v2.x = vector2[0];
    v2.y = vector2[1];

    return v2;
}

EXPORT void Blip_SetScaleXY(void *b, Vector2 scale)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetScaleXY(alt::Vector2f(scale.x, scale.y));
}

EXPORT int Blip_GetDisplay(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetDisplay();
}

EXPORT void Blip_SetDisplay(void *b, int display)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetDisplay(display);
}

EXPORT int Blip_GetSprite(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetSprite();
}

EXPORT int Blip_GetColor(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetColor();
}

EXPORT RGBA Blip_GetSecondaryColor(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    auto color = blip->GetSecondaryColor();

    RGBA c;
    c.r = color.r;
    c.g = color.g;
    c.b = color.b;
    c.a = color.a;

    return c;
}

EXPORT int Blip_GetAlpha(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetAlpha();
}

EXPORT int Blip_GetFlashTimer(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetFlashTimer();
}

EXPORT int Blip_GetFlashInterval(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetFlashInterval();
}

EXPORT int Blip_GetAsFriendly(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetAsFriendly();
}

EXPORT int Blip_GetRoute(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetRoute();
}

EXPORT int Blip_GetBright(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetBright();
}

EXPORT int Blip_GetNumber(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetNumber();
}

EXPORT int Blip_GetShowCone(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetShowCone();
}

EXPORT int Blip_GetFlashes(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetFlashes();
}

EXPORT int Blip_GetFlashesAlternate(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetFlashesAlternate();
}

EXPORT int Blip_GetAsShortRange(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetAsShortRange();
}

EXPORT int Blip_GetPriority(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetPriority();
}

EXPORT float Blip_GetRotation(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetRotation();
}

EXPORT const char *Blip_GetGxtName(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetGxtName().c_str();
}

EXPORT const char *Blip_GetName(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetName().c_str();
}

EXPORT RGBA Blip_GetRouteColor(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    auto color = blip->GetRouteColor();

    RGBA c;
    c.r = color.r;
    c.g = color.g;
    c.b = color.b;
    c.a = color.a;

    return c;
}

EXPORT int Blip_GetPulse(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetPulse();
}

EXPORT int Blip_GetAsMissionCreator(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetAsMissionCreator();
}

EXPORT int Blip_GetTickVisible(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetTickVisible();
}

EXPORT int Blip_GetHeadingIndicatorVisible(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetHeadingIndicatorVisible();
}

EXPORT int Blip_GetOutlineIndicatorVisible(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetOutlineIndicatorVisible();
}

EXPORT int Blip_GetFriendIndicatorVisible(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetFriendIndicatorVisible();
}

EXPORT int Blip_GetCrewIndicatorVisible(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetCrewIndicatorVisible();
}

EXPORT int Blip_GetCategory(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetCategory();
}

EXPORT int Blip_GetAsHighDetail(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetAsHighDetail();
}

EXPORT int Blip_GetShrinked(void *b)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    return blip->GetShrinked();
}

EXPORT void Blip_SetSprite(void *b, int sprite)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetSprite(sprite);
}

EXPORT void Blip_SetColor(void *b, int color)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetColor(color);
}

EXPORT void Blip_SetRoute(void *b, int state)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetRoute(state);
}

EXPORT void Blip_SetRouteColor(void *b, RGBA color)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetRouteColor(alt::RGBA(color.r, color.g, color.b, color.a));
}

EXPORT void Blip_SetSecondaryColor(void *b, RGBA color)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetSecondaryColor(alt::RGBA(color.r, color.g, color.b, color.a));
}

EXPORT void Blip_SetAlpha(void *b, int alpha)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetAlpha(alpha);
}

EXPORT void Blip_SetFlashTimer(void *b, int timer)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetFlashTimer(timer);
}

EXPORT void Blip_SetFlashInterval(void *b, int interval)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetFlashInterval(interval);
}

EXPORT void Blip_SetAsFriendly(void *b, int friendly)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetAsFriendly(friendly);
}

EXPORT void Blip_SetBright(void *b, int bright)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetBright(bright);
}

EXPORT void Blip_SetNumber(void *b, int number)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetNumber(number);
}

EXPORT void Blip_SetShowCone(void *b, int state)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetShowCone(state);
}

EXPORT void Blip_SetFlashes(void *b, int state)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetFlashes(state);
}

EXPORT void Blip_SetFlashesAlternate(void *b, int state)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetFlashesAlternate(state);
}

EXPORT void Blip_SetAsShortRange(void *b, int state)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetAsShortRange(state);
}

EXPORT void Blip_SetPriority(void *b, int state)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetPriority(state);
}

EXPORT void Blip_SetRotation(void *b, float rot)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetRotation(rot);
}

EXPORT void Blip_SetGxtName(void *b, const char *name)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetGxtName(name);
}

EXPORT void Blip_SetName(void *b, const char *name)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetName(name);
}

EXPORT void Blip_SetPulse(void *b, int val)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetPulse(val);
}

EXPORT void Blip_SetAsMissionCreator(void *b, int val)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetAsMissionCreator(val);
}

EXPORT void Blip_SetTickVisible(void *b, int val)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetTickVisible(val);
}

EXPORT void Blip_SetHeadingIndicatorVisible(void *b, int val)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetHeadingIndicatorVisible(val);
}

EXPORT void Blip_SetOutlineIndicatorVisible(void *b, int val)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetOutlineIndicatorVisible(val);
}

EXPORT void Blip_SetFriendIndicatorVisible(void *b, int val)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetFriendIndicatorVisible(val);
}

EXPORT void Blip_SetCrewIndicatorVisible(void *b, int val)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetCrewIndicatorVisible(val);
}

EXPORT void Blip_SetCategory(void *b, int val)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetCategory(val);
}

EXPORT void Blip_SetAsHighDetail(void *b, int val)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetAsHighDetail(val);
}

EXPORT void Blip_SetShrinked(void *b, int val)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->SetShrinked(val);
}

EXPORT void Blip_Fade(void *b, unsigned int opacity, unsigned int duration)
{
    auto blip = reinterpret_cast<alt::IBlip*>(b);
    blip->Fade(opacity, duration);
}
