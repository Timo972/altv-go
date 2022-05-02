# Setup
You need the following requirements to use the go module.

* [Go 1.16 or higher](https://golang.org/dl/).
* [GCC compiler (mingw-w64 for windows)](https://www.mingw-w64.org/).
* [GCC compiler (gcc for linux)](https://gcc.gnu.org/).

## Step 1

Download server from https://altv.mp/#/downloads and check data files. Also make sure to select the operating system where you want to run the server

Your server should now look like this:

```
modules/
resources/
server.cfg
altv-server.exe (altv-server on linux)
```

## Step 2

Download go-module from https://github.com/shockdev04/altv-go-module/releases

Your server should now look like this:

```
modules/
└── go-module.dll (libgo-module.so on linux)
resources/
server.cfg
altv-server.exe (altv-server on linux)
```

Now you are ready for creating your [first go resource](create-resource.md).