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

type ConnectionInfo interface {
	ID() uint32
	Name() string
	SocialID() uint64
	SocialName() string
	HwIdHash() uint64
	HwIdExHash() uint64
	AuthToken() string
	Debug() bool
	Branch() string
	Build() uint32
	CDNUrl() string
	PasswordHash() uint64
	IP() string
	DiscordUserID() int64
	CloudAuthHash() string

	Accept(sendNames bool)
	Decline(reason string)
	Accepted() bool
}

type connInfo struct {
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

func newConnectionInfo(cHandle unsafe.Pointer, cInfo C.struct_connectionInfo) ConnectionInfo {
	return &connInfo{
		ptr:           cHandle,
		id:            uint32(cInfo.id),
		socialName:    C.GoString(cInfo.socialName),
		cloudAuthHash: C.GoString(cInfo.cloudAuthHash),
		branch:        C.GoString(cInfo.branch),
		name:          C.GoString(cInfo.name),
		authToken:     C.GoString(cInfo.authToken),
		build:         uint32(cInfo.build),
		cdnUrl:        C.GoString(cInfo.cdnUrl),
		hwidExHash:    uint64(cInfo.hwidExHash),
		hwidHash:      uint64(cInfo.hwidHash),
		socialID:      uint64(cInfo.socialID),
		isDebug:       uint8(cInfo.isDebug) == 1,
		ip:            C.GoString(cInfo.ip),
		discordUserID: int64(cInfo.discordUserID),
		passwordHash:  uint64(cInfo.passwordHash),
	}
}

func (c *connInfo) ID() uint32 {
	return c.id
}

func (c *connInfo) Name() string {
	return c.name
}

func (c *connInfo) SocialID() uint64 {
	return c.socialID
}

func (c *connInfo) SocialName() string {
	return c.socialName
}

func (c *connInfo) HwIdHash() uint64 {
	return c.hwidHash
}

func (c *connInfo) HwIdExHash() uint64 {
	return c.hwidExHash
}

func (c *connInfo) AuthToken() string {
	return c.authToken
}

func (c *connInfo) Debug() bool {
	return c.isDebug
}

func (c *connInfo) Branch() string {
	return c.branch
}

func (c *connInfo) Build() uint32 {
	return c.build
}

func (c *connInfo) CDNUrl() string {
	return c.cdnUrl
}

func (c *connInfo) PasswordHash() uint64 {
	return c.passwordHash
}

func (c *connInfo) IP() string {
	return c.ip
}

func (c *connInfo) DiscordUserID() int64 {
	return c.discordUserID
}

func (c *connInfo) CloudAuthHash() string {
	return c.cloudAuthHash
}

func (c *connInfo) Accept(sendNames bool) {
	C.connection_accept(c.ptr, C.uchar(lib.Bool2int(sendNames)))
}

func (c *connInfo) Decline(reason string) {
	r := C.CString(reason)
	defer C.free(unsafe.Pointer(r))
	C.connection_decline(c.ptr, r)
}

func (c *connInfo) Accepted() bool {
	return int(C.connection_is_accepted(c.ptr)) == 1
}
