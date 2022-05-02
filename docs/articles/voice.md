# General Alt:V Voice

### Note :
______________________________
- You can´t use the Alt:V Voice without editing your Server.cfg!

# Before we start...
___________________________________________

##### Before we start, we have to edit our Server.CFG File!
##### So we add : voice: {} to initialize our Voice.
##### this would look like that :
```javascript
name: 'alt:V Server'
host: 0.0.0.0
port: 7788
players: 128
#password: ultra-password
announce: false
#token: YOUR_TOKEN
gamemode: Freeroam
website: example.com
language: en

// The Voice Initialization
voice: {} //  <---- We add this to our server.cfg File

description: 'alt:V Sample Server'
modules: [ 
	csharp-module
	node-module
]
resources: []
```

# Create a Voice Channel & Add Players to it [3D]
_____________________________________________________
```go
package main

import "C"
import "github.com/shockdev04/altv-go-pkg/alt"

//export OnStart
func OnStart() {
	// We Create a Voicechat-Channel & set it to 3D by setting ,,spatial" to true.
	channel := alt.CreateVoiceChannel(true, 20)

	/* We declare & Create our Event Handler. */
	/* When a Player connects... it should put the Player into the VoiceChannel. */
	alt.On.PlayerConnect(func (player *alt.Player) {
		/* If a Player Connects... he will be added to our Voice Channel. */
		channel.AddPlayer(player)
    })

	/* We declare & Create our Event Handler. */
	/* When a Player disconnects... it should remove the Player from the VoiceChannel. */
	alt.On.PlayerDisconnect(func (player *alt.Player, reason string) {
		/* If a Player Disconnects... he will be removed from our Voice Channel. */
		channel.RemovePlayer(player)
    })
	
}
```
# How use the Voice now?
[Read more here](https://docs.altv.mp/cs/articles/voice.html#open-your-altv-and-go-to-the-header-point-called-settings)