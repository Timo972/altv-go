# Resource communication

This article will describe how to communicate between different server resources.

## Export data

Resources can define data that other resources can access while the resource is starting. This data is immutable after resource finished starting and can be accessed from any serverside resource.

```go
package main

// imports

//export OnStart
func OnStart() {
	value := "test"
	alt.Export("myDataKey", value)
}
```

You can export any data you can also send via events. Including: ```bool```, ```int```, ```uint```, ```float```, ```string```, ```Player```, ```Vehicle```, ```map[string](any type listed here)```, any type listed here as array e.g. int[].
<!--Also any dictionary in dictionary, array in array, ect. endless depth types are supported, because they are resolved recursively.-->

### Export functions

Functions are also possible to export. Supported function parameters are same types supported by events and exports.

```go
package main

// imports

//export OnStart
func OnStart() {
	alt.Export("myFunction", func(args...interface{}) interface{} {
		return nil
    })
}
```

## Import data

Resources can import data that got exported from other resources. Most likely you will define the resource where you import from as ```deps: [ myResource, myResource2 ]``` in your ```resource.cfg``` to make sure the resource is already started when your resource starts.
You also have to define the resource name where you import data from.

```go
package main

//imports

//export OnStart
func OnStart() {
	value := alt.Import("myResourceToImportFrom", "myVariable")
	alt.LogInfo(value.(string))
}
```

This works the same with functions that return data. The return type is always ```interface{}```.

```go
package main

//imports

//export OnStart
func OnStart() {
	myFunction2 := alt.Import("myResourceToImportFrom", "myFunction2")
	// convert interface to alt.MValueFunc that we can call the function
	func2, ok := myFunction2.(alt.MValueFunc)
	
	if !ok {
		alt.LogError("Export myFunction2 is not a function")
		return
    }
	
	value := func2("string param", 3, -3, 2.9)
	
	alt.LogInfo(value.(string))
}
```

## Events

Another way to communicate with resources is by sending events to them. The ```alt.EmitServer("eventName", values)``` works same as player events and supports all data types that are supported by exports.
Every resource will get notified about the event. You can listen explicit for server events via ```alt.On.ServerEvent("eventName", OnServerEvent)```.
The server event delegate needs to have to following signature.

```go
func OnServerEvent(args...interface{})
{
}
```

