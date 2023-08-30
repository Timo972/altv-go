package entity

type Entity interface {
	WorldObject
}

type entity struct {
	worldObject
}
