# GiveWeapon
##### Gives a player a Weapon.

```go
package main

//imports

//export OnStart
func OnStart() {
	alt.On.PlayerConnect(func (player *alt.Player) {
		//We spawn our Connected Client after 1 sec.
		player.Spawn(alt.Vector3{X:0,Y:0,Z:0}, 1000)
		
		// We set his Skin to the standard GTA Online Skin.
		player.SetModel(alt.Hash("FreemodeMale01"))

		// We give our Connected Player a Advanced Rifle with 90 Bullets! He should select his new Weapon Instantly.
		player.GiveWeapon(alt.Hash("advanced_rifle"), 90, true)
    })
}
```
# Syntax
```go
  //Parameter : (weaponModel uint32, ammo int64, selectWeapon bool)
  player.GiveWeapon(alt.Hash("weaponModel"), 90, true)
```