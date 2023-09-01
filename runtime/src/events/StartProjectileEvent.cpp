#include "StartProjectileEvent.h"
#include "GoRuntime.h"

Go::StartProjectileEvent::StartProjectileEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::StartProjectileEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altStartProjectileEvent", int (*)(CBaseObject player, CPosition pos, CPosition dir, unsigned int ammoHash, unsigned long weaponHash));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call StartProjectileEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CStartProjectileEvent *>(ev);
    auto player = Go::Runtime::GetCBaseObject(event->GetSource());
    auto pos = event->GetStartPosition();
    auto dir = event->GetDirection();
    auto ammo = event->GetAmmoHash();
    auto weapon = event->GetWeaponHash();

    CPosition position;
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    CPosition direction;
    direction.x = dir[0];
    direction.y = dir[1];
    direction.z = dir[2];

    auto cancel = call(player, position, direction, ammo, weapon);

    if(cancel == 0) {
        event->Cancel();
    }
}
