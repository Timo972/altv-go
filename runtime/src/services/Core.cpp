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