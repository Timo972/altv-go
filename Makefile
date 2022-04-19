proto:
	protoc --go_out=.\ .\mvalue.proto

test:
	cd alt && go test -v