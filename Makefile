proto:
	protoc --go_out=.\ .\runtime\src\mvalue.proto --proto_path=.\runtime

test:
	cd api/alt && go test -v