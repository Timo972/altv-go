# CreateVehicle
This is a little example how to create Vehicles Serverside in Go.

# First Example
This example will spawn a Adder near you after you died!
```go
package main

//imports

//export OnStart
func OnStart() {
	alt.On.PlayerDeath(func (player *alt.Player, killer interface{}, weapon uint32) {
		//We spawn the dead Player
		player.Spawn(alt.Vector3{X:0, Y:0, Z:72}, 0)
		//We Create a Adder near the local player.
		veh, err := alt.CreateVehicle(alt.Hash("adder"), alt.Vector3{X:0,Y:1.5,Z:72}, alt.Vector3{X:0,Y:0,Z:0})
		
		if err != nil {
			alt.LogError(err.Error())
			alt.LogError("could not create vehicle")
			return
        }
        
        alt.LogInfo(fmt.Sprintf("Spawned vehicle with numberplate: %v", veh.NumberPlateText()))
    })
}
```

# Usage

```go
  //Parameter : (model uint32, pos Vector3, rotation Vector3)
  vehicle, error := alt.CreateVehicle(alt.Hash("model"), alt.Vector3{X:0,Y:0,Z:0}, alt.Vector3{X:0,Y:0,Z:0})
```