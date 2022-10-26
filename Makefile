
ifeq ($(OS), Windows_NT)
capi:
	"$(CURDIR)/scripts/build-capi.bat"
runtime:
	"$(CURDIR)/scripts/build-runtime.bat"
else
capi:
	"$(CURDIR)/scripts/build-capi.sh"
runtime:
	"$(CURDIR)/scripts/build-runtime.sh"
endif

.PHONY: capi runtime