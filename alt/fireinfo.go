package alt

import "fmt"

type FireInfo struct {
	WeaponHash uint32
	Position   Vector3
}

func (f FireInfo) String() string {
	return fmt.Sprintf("FireInfo{WeaponHash: %d, Position: %v}", f.WeaponHash, f.Position)
}
