package factory

import (
	"testing"
	"unsafe"

	"github.com/timo972/altv-go/entity"
)

type myPlayer struct {
	entity.Player
	username string
}

func myPlayerFactory(ptr unsafe.Pointer, id uint32) entity.Player {
	return &myPlayer{
		Player: entity.NewPlayer(ptr, id),
	}
}

func TestPlayerFactory(t *testing.T) {
	SetPlayerFactory(myPlayerFactory)
	p, ok := myPlayerFactory(nil, 1).(*myPlayer)
	if !ok {
		t.Error("testPlayerFactory returned wrong type")
	}

	p.username = "test"
}

type myVehicle struct {
	entity.Vehicle
}

func myVehicleFactory(ptr unsafe.Pointer, id uint32, model uint32) entity.Vehicle {
	return &myVehicle{
		Vehicle: entity.NewVehicle(ptr, id, model),
	}
}

func TestVehicleFactory(t *testing.T) {
	SetVehicleFactory(myVehicleFactory)
}
