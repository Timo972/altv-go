package altv

/*
#include <stdlib.h>
#include "capi.h"
*/
import "C"
import (
	"unsafe"

	"github.com/timo972/altv-go/internal/lib"
)

/*type ConnectionInfo interface {
	// ID returns the id of the connecting player
	ID() uint32
	// Name returns the name of the connecting player
	Name() string
	// SocialID returns the social id of the connecting player
	SocialID() uint64
	// SocialName returns the social name of the connecting player
	SocialName() string
	// HwIdHash returns the harware id hash of the connecting player
	HwIdHash() uint64
	// HwIdExHash returns the extended harware id hash of the connecting player
	HwIdExHash() uint64
	// AuthToken returns the auth token of the connecting player
	AuthToken() string
	// Debug returns if the connecting player uses debug mode
	Debug() bool
	// Branch returns the branch of the connecting player's client
	Branch() string
	// Build returns the build of the connecting player's client
	Build() uint32
	// CDNUrl returns the cdn url
	CDNUrl() string
	// PasswordHash returns the hash of the password the player entered
	PasswordHash() uint64
	// IP returns the ip of the connecting player
	IP() string
	// DiscordUserID returns the discord user id of the connecting player
	DiscordUserID() int64
	// CloudAuthHash returns the cloud auth hash of the connecting player
	CloudAuthHash() string

	// Accept accepts the connection and lets the player join
	Accept(sendNames bool)
	// Decline declines the connection and disconnects the player
	Decline(reason string)
	// Accepted returns if the connection was accepted
	Accepted() bool
}*/

type ConnectionInfo struct {
	ptr           unsafe.Pointer
	id            uint32
	name          string
	socialID      uint64
	socialName    string
	hwidHash      uint64
	hwidExHash    uint64
	authToken     string
	isDebug       bool
	branch        string
	build         uint32
	cdnUrl        string
	passwordHash  uint64
	ip            string
	discordUserID int64
	cloudAuthHash string
}

// NewConnectionInfo ! INTERNAL ONLY !
func NewConnectionInfo(ptr unsafe.Pointer, id uint32, name string, socialID uint64, socialName string, hwidHash uint64, hwidExHash uint64, authToken string, debug bool, branch string, build uint32, cdnUrl string, passwordHash uint64, ip string, discordUserId int64, cloudAuthHash string) *ConnectionInfo {
	return &ConnectionInfo{
		ptr:           ptr,
		id:            id,
		name:          name,
		socialID:      socialID,
		socialName:    socialName,
		hwidHash:      hwidHash,
		hwidExHash:    hwidExHash,
		authToken:     authToken,
		isDebug:       debug,
		branch:        branch,
		build:         build,
		cdnUrl:        cdnUrl,
		passwordHash:  passwordHash,
		ip:            ip,
		discordUserID: discordUserId,
		cloudAuthHash: cloudAuthHash,
	}
}

func (c *ConnectionInfo) ID() uint32 {
	return c.id
}

func (c *ConnectionInfo) Name() string {
	return c.name
}

func (c *ConnectionInfo) SocialID() uint64 {
	return c.socialID
}

func (c *ConnectionInfo) SocialName() string {
	return c.socialName
}

func (c *ConnectionInfo) HwIdHash() uint64 {
	return c.hwidHash
}

func (c *ConnectionInfo) HwIdExHash() uint64 {
	return c.hwidExHash
}

func (c *ConnectionInfo) AuthToken() string {
	return c.authToken
}

func (c *ConnectionInfo) Debug() bool {
	return c.isDebug
}

func (c *ConnectionInfo) Branch() string {
	return c.branch
}

func (c *ConnectionInfo) Build() uint32 {
	return c.build
}

func (c *ConnectionInfo) CDNUrl() string {
	return c.cdnUrl
}

func (c *ConnectionInfo) PasswordHash() uint64 {
	return c.passwordHash
}

func (c *ConnectionInfo) IP() string {
	return c.ip
}

func (c *ConnectionInfo) DiscordUserID() int64 {
	return c.discordUserID
}

func (c *ConnectionInfo) CloudAuthHash() string {
	return c.cloudAuthHash
}

func (c *ConnectionInfo) Accept(sendNames bool) {
	C.connection_accept(c.ptr, C.uchar(lib.Bool2int(sendNames)))
}

func (c *ConnectionInfo) Decline(reason string) {
	r := C.CString(reason)
	defer C.free(unsafe.Pointer(r))
	C.connection_decline(c.ptr, r)
}

func (c *ConnectionInfo) Accepted() bool {
	return int(C.connection_is_accepted(c.ptr)) == 1
}
