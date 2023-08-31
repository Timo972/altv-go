# Troubleshooting

## Installing Requirements

### mingw-w64 (Windows)

mingw-w64 is required to build your go project and the c-api on windows.<br />

#### Install mingw-w64 using msys2
Follow these instructions **until step 5** to install mingw-w64 using msys2: https://www.msys2.org/<br />
Inside the MSYS2 terminal run<br />
``pacman -S --needed base-devel mingw-w64-x86_64-toolchain``<br />
and <br />
``pacman -S mingw-w64-x86_64-dlfcn``<br />
Lastly close the MSYS2 terminal and add the mingw-w64 bin directory to your PATH environment variable.<br />
You are ready to build your go project as usual.

## Common Build Errors

### [...]\altv-go\base_object.go:3:11: fatal error: capi.h: No such file or directory

This error occurs when the c-api is not built or the header file is not in the correct location.
See the [Contribution Guide](/CONTRIBUTING.md#build-the-c-api) for instructions on how to build the c-api & copy the capi.h.

### [...]/x86_64-w64-mingw32/bin/ld.exe: cannot find -ldl: No such file or directory \ collect2.exe: error: ld returned 1 exit status

> This error only occurs on windows

You are missing the libdl.a library. This library is required to build the module on windows.<br />
If you are using mingw-w64 you can install the package `mingw-w64-dlfcn` which contains the libdl.a library.
Take a look at the [Installing Requirements](/TROUBLESHOOTING.md#installing-requirements) section for instructions on how to install mingw-w64.

### -buildmode=c-shared requires exactly one main package

You are probably running the `go build` command in the wrong directory. <br />
Make sure you are in the directory of your resource.

## Common Runtime Errors

### [Error] Failed to open main file

Make sure your `resource.toml` looks something like this:

```toml
type = 'go'
main = 'my-resource.dll'
```

**DO NOT** set `main` path to a **.go** file. It must be a shared library - a **.dll** or **.so** file.<br />
You should have built your resource with the `go build -o [resource-name].so -buildmode=c-shared` command previously.<br />
Set the path to that `[resource-name].so` output file as the `main` path in your `resource.toml` file.<br />

### [Error] Couldnt call OnStop

This error occurs when the module is unable to call the `OnStop` function of your resource.<br />
Make sure you have exported the `OnStop` function in your resource.<br />

```go
// import "C" is required at the top of your file to enable the //export directive
import "C"

//export OnStop
func OnStop() {
  // do something
}
```
