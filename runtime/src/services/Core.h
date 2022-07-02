#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

#include "core.grpc.pb.h"

class CoreService final : public Core::Core::Service {
public:
	virtual ::grpc::Status CreateVehicle(::grpc::ServerContext* context, const ::Core::CreateVehicleRequest* req, ::Core::Pointer* res);
}