package alt

// #cgo windows CFLAGS: -I../../c-api/lib/win32
// #cgo windows LDFLAGS: -L../../c-api/lib/win32 -lcapi
// #cgo linux CFLAGS: -I../../c-api/lib/linux
// #cgo linux LDFLAGS: -L../../c-api/lib/linux -lcapi
// #include <stdlib.h>
// #include "../../c-api/build/out/capi.h"
import "C"
import (
	"fmt"
	"unsafe"
)

type ConnectionInfo struct {
	ptr           unsafe.Pointer
	Name          string
	SocialID      uint64
	HwidHash      uint64
	HwidExHash    uint64
	AuthToken     string
	IsDebug       bool
	Branch        string
	Build         uint32
	CDNUrl        string
	PasswordHash  uint64
	IP            string
	DiscordUserID string
}

func newConnectionInfo(cHandle unsafe.Pointer, cInfo C.struct_connectionInfo) ConnectionInfo {
	return ConnectionInfo{
		ptr:           cHandle,
		Branch:        C.GoString(cInfo.branch),
		Name:          C.GoString(cInfo.name),
		AuthToken:     C.GoString(cInfo.authToken),
		Build:         uint32(cInfo.build),
		CDNUrl:        C.GoString(cInfo.cdnUrl),
		HwidExHash:    uint64(cInfo.hwidExHash),
		HwidHash:      uint64(cInfo.hwidHash),
		SocialID:      uint64(cInfo.socialID),
		IsDebug:       uint8(cInfo.isDebug) == 1,
		IP:            C.GoString(cInfo.ip),
		DiscordUserID: C.GoString(cInfo.discordUserID),
		PasswordHash:  uint64(cInfo.passwordHash),
	}
}

func (c ConnectionInfo) Accept() {
	C.connection_accept(c.ptr)
}

func (c ConnectionInfo) Decline(reason string) {
	r := C.CString(reason)
	defer C.free(unsafe.Pointer(r))
	C.connection_decline(c.ptr, r)
}

func (c ConnectionInfo) Accepted() bool {
	return int(C.connection_is_accepted(c.ptr)) == 1
}

func (c ConnectionInfo) String() string {
	return fmt.Sprintf("ConnectionInfo{Name: %s, SocialID: %d, HwidHash: %d, HwidExHash: %d, AuthToken: %s, IsDebug: %t, Branch: %s, Build: %d, CDNUrl: %s, PasswordHash: %d, IP: %s, DiscordUserID: %s}", c.Name, c.SocialID, c.HwidHash, c.HwidExHash, c.AuthToken, c.IsDebug, c.Branch, c.Build, c.CDNUrl, c.PasswordHash, c.IP, c.DiscordUserID)
}
