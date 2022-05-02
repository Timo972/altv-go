# Player communication

On serverside exists four ways to send data to clients.

The first way is to use ```alt.EmitAllClients(eventName, args)``` to send data to all connected clients.
The second way sends data to specific players via ```alt.EmitClients([]*alt.Player, eventName, args)```
The third way sends data to a specific player directly via ```alt.EmitClient(player, eventName, args)```.
The fourth way is ```player.Emit(eventName, args)``` which just a wrapper to ```alt.EmitClient(player, eventName, args)```

args expects a ```...interface{}```.

Supported arguments types inside the array are ```[]byte```, ```map```, ```bool```, ```int``` (8-64), ```uint``` (16-64), ```float``` (32,64), ```string```, ```Player```, ```Vehicle```,
```Vector3```, ```Vector2```, ```Blip```, ```VoiceChannel```, ```ColShape```, ```Checkpoint```, any type listed here as array e.g. int[].
Its recommended to serialize arrays and dicts before sending them to the player due to performance issues in the go module. Byte arrays are excluded.
<!--Also any dictionary in dictionary, array in array, ect. endless depth types are supported, because they are resolved recursively.-->