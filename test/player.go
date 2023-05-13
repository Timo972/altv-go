package test

import "github.com/timo972/altv-go"

type Player struct {
	Entity
	name          string
	socialID      uint64
	discordUserID int64
	health        uint16
}

func (p *Player) Name() string {
	return p.name
}

func (p *Player) SetName(name string) *Player {
	p.name = name
	return p
}

func (p *Player) SocialID() uint64 {
	return p.socialID
}

func (p *Player) SetSocialID(id uint64) *Player {
	p.socialID = id
	return p
}

func (p *Player) DiscordUserID() int64 {
	return p.discordUserID
}

func (p *Player) SetDiscordUserID(id int64) *Player {
	p.discordUserID = id
	return p
}

func (p *Player) Health() uint16 {
	return 100
}

func (p *Player) SetHealth(health uint16) *Player {
	p.health = health
	return p
}

func NewPlayer(id uint32) *Player {
	return &Player{
		Entity: Entity{
			WorldObject: WorldObject{
				BaseObject: *NewBaseObject(id, altv.BaseTypePlayer),
			},
		},
	}
}
