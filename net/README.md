# altnet

> This package implements golang standard library `net` interfaces

## Usage

```go
import (
    "net/rpc"

    "github.com/timo972/altv-go"
    altnet "github.com/timo972/altv-go/net"
)

func init() {
    rpc.Accept(altnet.Listener)

    rpc.Register(new(YourRPCService))
}
```
