# altnet

> This package implements golang standard library `net` interfaces

## Usage
**Server**
```go
import (
    "net/rpc"

    "github.com/timo972/altv-go"
    altnet "github.com/timo972/altv-go/net"
)

func init() {
    // altnet.Listener implements net.Listener (accepts player connections on events.On.PlayerConnect)
    
    // simple net/rpc example
    // you can use any other net package that uses net.Listener
    rpc.Accept(altnet.Listener)
    rpc.Register(new(YourRPCService))

    // or you can use net.Conn directly
    // receive data using the client example below
    events.On.PlayerConnect(func (p altv.Player) {
        // new PlayerConn (implements net.Conn & io.ReadWriteCloser)
        conn := altnet.NewPlayerConn(p)
        conn.Write([]byte("Hello World"))
    })
}
```
**Client**
```ts
import * as alt from 'alt-client';
const GoNetEvent = "altv-go:net";

alt.onServer(GoNetEvent, (data: Uint8Array) => {
    const str = Buffer.from(data).toString();
    console.log(str) // Output: Hello World
})
```