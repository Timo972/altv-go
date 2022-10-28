
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
test: runtime
	"$(CURDIR)/scripts/test.sh"
endif

.PHONY: capi runtime test