package event

import (
	"C"

	"golang.org/x/exp/slices"
)
import (
	"fmt"
	"unsafe"

	"github.com/timo972/altv-go/altlog"
	"github.com/timo972/altv-go/entity"
	"github.com/timo972/altv-go/factory"
)

type playerDamageListener = func(p entity.Player, attacker entity.Entity, healthDamage uint16, armourDamage uint16, weapon uint32)

func checkPlayerDamageEvent() {
	lisCount := len(on.playerDamageEvents) + len(once.playerDamageEvents)
	if lisCount < 1 {
		unregisterOnEvent(serverScriptEvent)
	}
}

func (s *subscriber) PlayerDamage(listener playerDamageListener) int {
	s.playerDamageEvents = append(s.playerDamageEvents, listener)
	registerOnEvent(playerDamage)
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
func altPlayerDamageEvent(cp *C.struct_baseObject, ce *C.struct_baseObject, healthDmg C.ushort, armourDmg C.ushort, weap C.ulong) {
	p, err := factory.GetBaseObject[entity.Player](entity.BaseObjectType(cp.typ), unsafe.Pointer(cp.ptr), uint32(cp.id), 0)
	if err != nil {
		altlog.Errorln(fmt.Sprintf("[Go] PlayerDamage: %v", err))
		return
	}
	e, err := factory.GetBaseObject[entity.Entity](entity.BaseObjectType(ce.typ), unsafe.Pointer(ce.ptr), uint32(ce.id), uint32(ce.model))
	if err != nil {
		altlog.Errorln(fmt.Sprintf("[Go] PlayerDamage: %v", err))
		return
	}

	healthDamage := uint16(healthDmg)
	armourDamage := uint16(armourDmg)
	weapon := uint32(weap)

	for _, event := range once.playerDamageEvents {
		event(p, e, healthDamage, armourDamage, weapon)
	}
	clear(once.playerDamageEvents)

	for _, event := range on.playerDamageEvents {
		event(p, e, healthDamage, armourDamage, weapon)
	}

	checkPlayerDamageEvent()
}
