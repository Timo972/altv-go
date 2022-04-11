package alt

import "C"

type ConnectionInfo struct {
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

func newConnectionInfo(cInfo C.struct_connectionInfo) ConnectionInfo {
	return ConnectionInfo{
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
