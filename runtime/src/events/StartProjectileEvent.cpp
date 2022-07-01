#include "StartProjectileEvent.h"

Go::StartProjectileEvent::StartProjectileEvent(ModuleLibrary *module) : IEvent(module) { }

void Go::StartProjectileEvent::Call(const alt::CEvent *ev)
{
    static auto call = GET_FUNC(Library, "altStartProjectileEvent", int (*)(alt::IPlayer* player, Position pos, Position dir, unsigned int ammoHash, unsigned long weaponHash));

    if (call == nullptr)
    {
        alt::ICore::Instance().LogError("Couldn't not call StartProjectileEvent.");
        return;
    }

    auto event = dynamic_cast<const alt::CStartProjectileEvent *>(ev);
    auto player = event->GetSource().Get();
    auto pos = event->GetStartPosition();
    auto dir = event->GetDirection();
    auto ammo = event->GetAmmoHash();
    auto weapon = event->GetWeaponHash();

    Position position;
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;

    Position direction;
    direction.x = dir[0];
    direction.y = dir[1];
    direction.z = dir[2];

    auto cancel = call(player, position, direction, ammo, weapon);

    if(cancel == 0) {
        event->Cancel();
    }
}
