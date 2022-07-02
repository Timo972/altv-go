# altv-go-module
Go module for alt:V Multiplayer.
Go package for creating custom game-modes can be found [here](https://github.com/Timo972/altv-go).

Module is still under heavy development, and it's not suitable for production usage.  
Right now the module should cover most of the alt:V API but its untested.

If you find a bug or missing function please open an issue for it.

## Installation
Installing the module is very simple:
1. Download ``go-module.dll`` for windows or ``libgo-module.so`` for linux from [Releases](https://github.com/Timo972/altv-go/releases)
2. Put the downloaded file into the your servers module folder
3. Edit the server.cfg and add the module:
```
modules: [
    go
]
```
Thats it!

## Building
**To build the module you need some prerequisites:**
- [Windows] Visual Studio 2019 or later
- [Linux] GCC 8
- [CMake >=3.15](https://cmake.org/download/)
- [ProtoC 3.19.4](https://github.com/protocolbuffers/protobuf/releases/tag/v3.19.4)
- [Protobuf](https://github.com/protocolbuffers/protobuf)
- [gRPC](https://github.com/grpc/grpc)

Then just run ``build.bat`` or ``build.sh`` in the root folder (depending on os).