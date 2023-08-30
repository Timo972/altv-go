package factory

import (
	"testing"
	"unsafe"

	"github.com/timo972/altv-go/entity"
)

type testPlayer struct {
	entity.Player
	username string
}

func testPlayerFactory(ptr unsafe.Pointer, id uint32) entity.Player {
	return &testPlayer{
		Player: entity.NewPlayer(ptr, id),
	}
}

func TestPlayerFactory(t *testing.T) {
	SetPlayerFactory(testPlayerFactory)
	p, ok := testPlayerFactory(nil, 1).(*testPlayer)
	if !ok {
		t.Error("testPlayerFactory returned wrong type")
	}

	p.username = "test"
}

type testVehicle struct {
	entity.Vehicle
}

func testVehicleFactory(ptr unsafe.Pointer, id uint32, model uint32) entity.Vehicle {
	return &testVehicle{
		Vehicle: entity.NewVehicle(ptr, id, model),
	}
}

func TestVehicleFactory(t *testing.T) {
	SetVehicleFactory(testVehicleFactory)
}
