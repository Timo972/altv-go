# Custom events

Custom events are registered via ```alt.On.ServerEvent(eventName, delegate)```.

Here is a very basic sample that expects just a single ```string``` from a client event named ```myMessage```.

We register it via ```alt.On.ClientEvent```.

```go
alt.On.ClientEvent("myMessage", MyMessageHandler)
```

And the method is defined as this.
```go
func MyMessageHandler(player *alt.Player, args interface{})
{            
	alt.LogInfo(args.(string))
}
```

The method will be called like this from client
```js
alt.emitServer("myMessage", "my test message")
```

The method name doesn't really matter in this case and i just named it similar to the event name.

## Maps

Any js object send via ```alt.emitServer``` will be a map.

```go
alt.On.ClientEvent("myBigObject", MyBigObjectHandler)
...
func MyBigObjectHandler(player *alt.Player, myBigObject interface{})
{
    myMap, ok := myBigObject.(map[string]string)
    if !ok {
		alt.LogError("myBigObject can not be converted to type map[string]string")
	    return	
    }
    eyeColor := myMap["eyeColor"]
	if eyeColor == nil {
		alt.LogError("myBigObject has no property called eyeColor")
		return
    }    
    alt.LogInfo(fmt.Sprintf("EyeColor: %v", eyeColor));
}
```
And this is the client code.
```js
const myBigObject = {firstName:"John", lastName:"Doe", eyeColor:"blue"};
alt.emitServer("myBigObject", myBigObject);
```