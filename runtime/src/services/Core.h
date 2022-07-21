#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

#include "core.grpc.pb.h"

using Core::CoreAPI;
using grpc::Status;
using grpc::ServerContext;

class CoreService final : public CoreAPI::Service {
public:
	virtual Status CreateVehicle(ServerContext* context, const Core::CreateVehicleRequest* req, Core::Pointer* res);
};