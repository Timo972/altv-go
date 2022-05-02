# Events

For custom events see [Custom Events](custom-events.md).

Events can be registered dynamically via event delegates.

To add for example a player connect event handler dynamically you can just add the delegate that will be called when a player connects.

This is a example using the lambda operator to add a event handler.

```go
alt.On.PlayerConnect(func(player *alt.Player) {
    alt.LogInfo(fmt.Sprintf("%v connected", player.Name()))
})
```

```go
alt.On.PlayerConnect(OnPlayerConnect);
...
func OnPlayerConnect(player *alt.Player) {
  alt.LogInfo(fmt.Sprintf("%v connected", player.Name()))
}
```

<!--Below is a list of all event handlers.

[!code-go[Events](../../alt/events.go)]-->

The player event handler looks like this.

```go
alt.On.ClientEvent("eventName", func(player *alt.Player, args...interface{}){
	...
})
```

See how you can use [Custom Events](custom-events.md).