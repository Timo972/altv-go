#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>
#include "google/protobuf/empty.pb.h"

#include "core.grpc.pb.h"

using Core::CoreAPI;
using grpc::Status;
using grpc::ServerContext;

class CoreService final : public CoreAPI::Service {
public:
	virtual Status CreateVehicle(ServerContext* context, const Core::CreateVehicleRequest* req, Core::Pointer* res);
	//virtual Status LogInfo(ServerContext* context, const google::protobuf::StringValue* req, google::protobuf::Empty* res);
	//virtual Status LogWarning(ServerContext* context, const google::protobuf::StringValue* req, google::protobuf::Empty* res);
	//virtual Status LogError(ServerContext* context, const google::protobuf::StringValue* req, google::protobuf::Empty* res);
	//virtual Status LogColored(ServerContext* context, const google::protobuf::StringValue* req, google::protobuf::Empty* res);
	//virtual Status LogDebug(ServerContext* context, const google::protobuf::StringValue* req, google::protobuf::Empty* res);
	virtual Status CreateVoiceChannel(ServerContext* context, const Core::CreateVoiceChannelRequest* req, Core::Pointer* res);
	virtual Status GetVersion(ServerContext* context, const google::protobuf::Empty* req, google::protobuf::StringValue* res);
	virtual Status GetBranch(ServerContext* context, const google::protobuf::Empty* req, google::protobuf::StringValue* res);
	virtual Status IsDebug(ServerContext* context, const google::protobuf::Empty* req, google::protobuf::BoolValue* res);
	virtual Status Hash(ServerContext* context, const google::protobuf::StringValue* req, google::protobuf::UInt32Value* res);
	virtual Status FileExists(ServerContext* context, const google::protobuf::StringValue* req, google::protobuf::BoolValue* res);
	virtual Status FileRead(ServerContext* context, const google::protobuf::StringValue* req, google::protobuf::StringValue* res);
};