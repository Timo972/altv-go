package alt
import "C"
import "unsafe"

type Entity struct {
	WorldObject
}

func (e Entity) GetModel() uint32 {
	return uint32(C.player_get_model(e.Ptr))
}

func (e Entity) Detach() {
	C.player_detach(e.Ptr)
}

// TODO make capi accept x, y, z instead of Position and Rotation
func (e Entity) AttachToEntity(entity Entity, otherBoneIndex int16, myBoneIndex int16, position Position, rotation Rotation, collision bool, noFixedRotation bool) {
	//C.player_attach_to_entity(p.Ptr, entity.Ptr, C.int(otherBoneIndex), C.int(myBoneIndex), )
}

func (e Entity) SetVisible(toggle bool) {
	C.player_set_visible(e.Ptr, C.bool(toggle))
}

func (e Entity) IsVisible() bool {
	return bool(C.player_get_visible(e.Ptr))
}

func (e Entity) GetID() uint16 {
	return uint16(C.player_get_id(e.Ptr))
}

func (e Entity) GetNetworkOwner() *Player {
	cPtr := C.player_get_network_owner(e.Ptr)
	owner := NewPlayer(unsafe.Pointer(cPtr))
	return owner
}

func (e Entity) SetNetworkOwner(owner *Player, disableMigration bool) {
	C.player_set_network_owner(e.Ptr, owner.Ptr, C.bool(disableMigration))
}

func (e Entity) GetRotation() Rotation {
	cRot := C.player_get_entity_aim_offset(e.Ptr)
	return Rotation{X: float32(cRot.x), Y: float32(cRot.y), Z: float32(cRot.z)}
}

func (e Entity) SetRotation(rotation Rotation) {
	C.player_set_rotation(e.Ptr, C.float(rotation.X), C.float(rotation.Y), C.float(rotation.Z))
}

