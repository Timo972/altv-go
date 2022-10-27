#pragma once

#include <iostream>
#include "Main.h"

#ifdef __cplusplus
extern "C"
{
#endif
// BaseObject inherited
EXPORT int Blip_GetType(void *c);
EXPORT int Blip_HasMetaData(void *base, const char *key);
EXPORT GoValue Blip_GetMetaData(void *base, const char *key);
EXPORT void Blip_SetMetaData(void *base, const char *key, GoValue data);
EXPORT void Blip_DeleteMetaData(void *base, const char *key);
EXPORT void Blip_Destroy(void *b);
EXPORT int Blip_IsValid(const char *resourceName, void *p);

// WorldObject inherited
EXPORT Position Blip_GetPosition(void *p);
EXPORT void Blip_SetPosition(void *p, float x, float y, float z);
EXPORT long Blip_GetDimension(void *p);
EXPORT void Blip_SetDimension(void *p, long dimension);

// Blip methods
EXPORT int Blip_IsGlobal(void *b);
EXPORT void *Blip_GetTarget(void *b);
EXPORT int Blip_IsAttached(void *b);
EXPORT Entity Blip_AttachedTo(void *b);
EXPORT void Blip_AttachTo(void *b, Entity e);
EXPORT unsigned char Blip_GetBlipType(void *b);

EXPORT Vector2 Blip_GetScaleXY(void *b);
EXPORT void Blip_SetScaleXY(void *b, Vector2 scale);
EXPORT int Blip_GetDisplay(void *b);
EXPORT void Blip_SetDisplay(void *b, int display);
EXPORT int Blip_GetSprite(void *b);
EXPORT int Blip_GetColor(void *b);
EXPORT RGBA Blip_GetSecondaryColor(void *b);
EXPORT int Blip_GetAlpha(void *b);
EXPORT int Blip_GetFlashTimer(void *b);
EXPORT int Blip_GetFlashInterval(void *b);
EXPORT int Blip_GetAsFriendly(void *b);
EXPORT int Blip_GetRoute(void *b);
EXPORT int Blip_GetBright(void *b);
EXPORT int Blip_GetNumber(void *b);
EXPORT int Blip_GetShowCone(void *b);
EXPORT int Blip_GetFlashes(void *b);
EXPORT int Blip_GetFlashesAlternate(void *b);
EXPORT int Blip_GetAsShortRange(void *b);
EXPORT int Blip_GetPriority(void *b);
EXPORT float Blip_GetRotation(void *b);
EXPORT const char *Blip_GetGxtName(void *b);
EXPORT const char *Blip_GetName(void *b);
EXPORT RGBA Blip_GetRouteColor(void *b);
EXPORT int Blip_GetPulse(void *b);
EXPORT int Blip_GetAsMissionCreator(void *b);
EXPORT int Blip_GetTickVisible(void *b);
EXPORT int Blip_GetHeadingIndicatorVisible(void *b);
EXPORT int Blip_GetOutlineIndicatorVisible(void *b);
EXPORT int Blip_GetFriendIndicatorVisible(void *b);
EXPORT int Blip_GetCrewIndicatorVisible(void *b);
EXPORT int Blip_GetCategory(void *b);
EXPORT int Blip_GetAsHighDetail(void *b);
EXPORT int Blip_GetShrinked(void *b);

EXPORT void Blip_SetSprite(void *b, int sprite);
EXPORT void Blip_SetColor(void *b, int color);
EXPORT void Blip_SetRoute(void *b, int state);
EXPORT void Blip_SetRouteColor(void *b, RGBA color);
EXPORT void Blip_SetSecondaryColor(void *b, RGBA color);
EXPORT void Blip_SetAlpha(void *b, int alpha);
EXPORT void Blip_SetFlashTimer(void *b, int timer);
EXPORT void Blip_SetFlashInterval(void *b, int interval);
EXPORT void Blip_SetAsFriendly(void *b, int friendly);
EXPORT void Blip_SetBright(void *b, int bright);
EXPORT void Blip_SetNumber(void *b, int number);
EXPORT void Blip_SetShowCone(void *b, int state);
EXPORT void Blip_SetFlashes(void *b, int state);
EXPORT void Blip_SetFlashesAlternate(void *b, int state);
EXPORT void Blip_SetAsShortRange(void *b, int state);
EXPORT void Blip_SetPriority(void *b, int state);
EXPORT void Blip_SetRotation(void *b, float rot);
EXPORT void Blip_SetGxtName(void *b, const char *name);
EXPORT void Blip_SetName(void *b, const char *name);
EXPORT void Blip_SetPulse(void *b, int val);
EXPORT void Blip_SetAsMissionCreator(void *b, int val);
EXPORT void Blip_SetTickVisible(void *b, int val);
EXPORT void Blip_SetHeadingIndicatorVisible(void *b, int val);
EXPORT void Blip_SetOutlineIndicatorVisible(void *b, int val);
EXPORT void Blip_SetFriendIndicatorVisible(void *b, int val);
EXPORT void Blip_SetCrewIndicatorVisible(void *b, int val);
EXPORT void Blip_SetCategory(void *b, int val);
EXPORT void Blip_SetAsHighDetail(void *b, int val);
EXPORT void Blip_SetShrinked(void *b, int val);
EXPORT void Blip_Fade(void *b, unsigned int opacity, unsigned int duration);

#ifdef __cplusplus
}
#endif