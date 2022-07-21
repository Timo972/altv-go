proto:
	protoc --go_out=.\ --go-grpc_out=.\ .\runtime\src\mvalue.proto --proto_path=.\runtime
	protoc --go_out=.\ --go-grpc_out=.\ .\runtime\src\core.proto --proto_path=.\runtime

test:
	cd api/alt && go test -v