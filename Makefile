proto:
	protoc --go_out=.\ .\runtime\src\mvalue.proto

test:
	cd api/alt && go test -v