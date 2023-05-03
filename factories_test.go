package altv

import (
	"testing"
	"unsafe"
)

type testPlayer struct {
	Player
	username string
}

func testPlayerFactory(ptr unsafe.Pointer, id uint32) Player {
	return &testPlayer{
		Player: NewPlayer(ptr, id),
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
	Vehicle
}

func testVehicleFactory(ptr unsafe.Pointer, id uint32, model uint32) Vehicle {
	return &testVehicle{
		Vehicle: NewVehicle(ptr, id, model),
	}
}

func TestVehicleFactory(t *testing.T) {
	SetVehicleFactory(testVehicleFactory)
}
