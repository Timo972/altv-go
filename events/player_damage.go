package events

import (
	"C"

	"github.com/timo972/altv-go"
	"golang.org/x/exp/slices"
)
import (
	"fmt"
	"unsafe"
)

type playerDamageListener = func(p altv.Player, attacker altv.Entity, healthDamage uint16, armourDamage uint16, weapon uint32)

func checkPlayerDamageEvent() {
	lisCount := len(on.playerDamageEvents) + len(once.playerDamageEvents)
	if lisCount < 1 {
		go unregisterOnEvent(serverScriptEvent)
	}
}

func (s *subscriber) PlayerDamage(listener playerDamageListener) int {
	s.playerDamageEvents = append(s.playerDamageEvents, listener)
	go registerOnEvent(playerDamage)
	return len(s.playerDamageEvents) - 1
}

func (unsub *unsubscriber) PlayerDamage(id int) error {
	if id < 0 || id >= len(unsub.sub.playerDamageEvents) {
		return ErrInvalidEventID
	}

	unsub.sub.playerDamageEvents = slices.Delete(unsub.sub.playerDamageEvents, id, 1)
	checkPlayerDamageEvent()
	return nil
}

//export altPlayerDamageEvent
func altPlayerDamageEvent(cp C.struct_entity, ce C.struct_entity, healthDmg C.ushort, armourDmg C.ushort, weap C.ulong) {
	p, err := altv.GetBaseObject[altv.Player](altv.BaseObjectType(cp.typ), unsafe.Pointer(cp.ptr), uint32(cp.id), 0)
	if err != nil {
		altv.LogError(fmt.Sprintf("[Go] PlayerDamage: %v", err))
		return
	}
	e, err := altv.GetBaseObject[altv.Entity](altv.BaseObjectType(ce.typ), unsafe.Pointer(ce.ptr), uint32(ce.id), uint32(ce.model))
	if err != nil {
		altv.LogError(fmt.Sprintf("[Go] PlayerDamage: %v", err))
		return
	}

	healthDamage := uint16(healthDmg)
	armourDamage := uint16(armourDmg)
	weapon := uint32(weap)

	for i, event := range once.playerDamageEvents {
		event(p, e, healthDamage, armourDamage, weapon)
		once.playerDamageEvents = slices.Delete(once.playerDamageEvents, i, 1)
	}

	for _, event := range on.playerDamageEvents {
		event(p, e, healthDamage, armourDamage, weapon)
	}

	checkPlayerDamageEvent()
}
