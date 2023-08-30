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
    go-module
]
```
Thats it!

## Building
**To build the module there are some prerequisites needed:**
- [Windows] Visual Studio 2019 or later
- [Linux] GCC >=8
- [CMake](https://cmake.org/download/)

### Clone the repository
Run ``git clone --recurse-submodules https://github.com/timo972/altv-go.git``

### Building the module
Run ``make runtime`` in the repo root folder.
In case you dont have make installed you can run ``./scripts/build-runtime.sh`` on linux and ``.\scripts\build-runtime.bat`` on windows.