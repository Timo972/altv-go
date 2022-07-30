#include "Core.h"
#include "Main.h"
#include "GoRuntime.h"


Status CoreService::CreateVehicle(ServerContext* context, const Core::CreateVehicleRequest* req, Core::Pointer* res)
{
	auto pos = req->pos();
	auto rot = req->rot();
	alt::Position position(pos.x(), pos.y(), pos.z());
	alt::Rotation rotation(rot.x(), rot.y(), rot.z());

	auto vehicle = alt::ICore::Instance().CreateVehicle(req->model(), position, rotation);
	auto ptr = vehicle.Get();
	res->set_ptr(Go::Runtime::PointerToString(ptr));

	return Status::OK;
}

Status CoreService::CreateVoiceChannel(ServerContext* context, const Core::CreateVoiceChannelRequest* req, Core::Pointer* res)
{
	auto vc = alt::ICore::Instance().CreateVoiceChannel(req->spatial(), req->maxdistance());
	auto ptr = vc.Get();
	res->set_ptr(Go::Runtime::PointerToString(ptr));

	return Status::OK;
}

Status CoreService::GetVersion(ServerContext* context, const google::protobuf::Empty* req, google::protobuf::StringValue* res)
{
	res->set_value(alt::ICore::Instance().GetVersion());
	return Status::OK;
}

Status CoreService::GetBranch(ServerContext* context, const google::protobuf::Empty* req, google::protobuf::StringValue* res)
{
	res->set_value(alt::ICore::Instance().GetBranch());
	return Status::OK;
}

Status CoreService::IsDebug(ServerContext* context, const google::protobuf::Empty* req, google::protobuf::BoolValue* res)
{
	res->set_value(alt::ICore::Instance().IsDebug());
	return Status::OK;
}

Status CoreService::Hash(ServerContext* context, const google::protobuf::StringValue* req, google::protobuf::UInt32Value* res)
{
	auto hash = alt::ICore::Instance().Hash(req->value());
	res->set_value(hash);
	return Status::OK;
}

Status CoreService::FileExists(ServerContext* context, const google::protobuf::StringValue* req, google::protobuf::BoolValue* res)
{
	std::cout << "CoreService::FileExists" << std::endl;
	auto exists = alt::ICore::Instance().FileExists(req->value());
	res->set_value(exists);
	return Status::OK;
}

Status CoreService::FileRead(ServerContext* context, const google::protobuf::StringValue* req, google::protobuf::StringValue* res)
{
	auto content = alt::ICore::Instance().FileRead(req->value());
	res->set_value(content);
	return Status::OK;
}