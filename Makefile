proto:
	protoc --go_out=.\ .\runtime\src\mvalue.proto

test:
	cd api/alt && go test -v

capi:
	c-for-go -out ./internal -ccdefs -ccincl c-api/altcapi.yml 