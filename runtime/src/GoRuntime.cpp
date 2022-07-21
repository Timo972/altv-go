#include "GoRuntime.h"
#include "GoResource.h"
#include <google/protobuf/text_format.h>
// #include <cstdio>
#include <cstdint>
#include <sstream>

// #include "services/Core.h"

// #include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

Go::Runtime::Runtime() {
    alt::ICore::Instance().LogInfo("Creating Go::Runtime");
    grpc::ServerBuilder builder;
    builder.AddListeningPort("127.0.0.1:50051", grpc::InsecureServerCredentials());

    // CoreService core_service;
    // builder.RegisterService(&core_service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    alt::ICore::Instance().LogInfo("GRPC started");
}

Go::Runtime *Go::Runtime::Instance = nullptr;

Go::Runtime *Go::Runtime::GetInstance() {
    if (Instance == nullptr) {
        Instance = new Go::Runtime();
    }

    return Instance;
}

alt::IResource::Impl *Go::Runtime::CreateImpl(alt::IResource *impl) {
    auto resource = new Go::Resource(this, impl);
    _resources.push_back({{impl->GetName().c_str(), resource}});

    return resource;
}

void Go::Runtime::DestroyImpl(alt::IResource::Impl *impl) {
    auto resource = dynamic_cast<Go::Resource *>(impl);

    if (resource != nullptr)
        delete resource;
}

void Go::Runtime::OnDispose() {
    // Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();
}

alt::IResource::Impl *Go::Runtime::GetResource(const std::string &name) {
    for (auto &resource: _resources) {
        if (resource.find(name) != resource.end()) {
            return resource[name];
        }
    }

    return nullptr;
}

Entity Go::Runtime::GetEntity(alt::Ref <alt::IEntity> entity) {
    Entity e;

    if (!entity.IsEmpty()) {
        auto entityType = entity->GetType();
        e.Type = static_cast<unsigned char>(entityType);

        switch (entityType) {
            case alt::IEntity::Type::PLAYER:
                e.Ptr = entity.As<alt::IPlayer>().Get();
                break;
            case alt::IEntity::Type::VEHICLE:
                e.Ptr = entity.As<alt::IVehicle>().Get();
                break;
        }
    } else {
        e.Ptr = nullptr;
    }

    return e;
}

ConnectionInfo Go::Runtime::GetConnectionInfo(alt::Ref <alt::IConnectionInfo> info) {
    connectionInfo conn;
    conn.authToken = info->GetAuthToken().c_str();
    conn.branch = info->GetBranch().c_str();
    conn.build = info->GetBuild();
    conn.cdnUrl = info->GetCdnUrl().c_str();
    conn.discordUserID = info->GetDiscordUserID().c_str();
    conn.hwidExHash = info->GetHwIdExHash();
    conn.hwidHash = info->GetHwIdHash();
    conn.ip = info->GetIp().c_str();
    conn.isDebug = info->GetIsDebug();
    conn.name = info->GetName().c_str();
    conn.passwordHash = info->GetPasswordHash();
    conn.socialID = info->GetSocialId();

    return conn;
}

Array Go::Runtime::ConfigNodeToProtoBytes(alt::config::Node node) 
{
    auto value = new MValue::MValue();
    ConfigNodeToProto(node, value);

    Array arr;
    arr.size = value->ByteSizeLong();

    unsigned char* byteArray = new unsigned char[arr.size];
    value->SerializeToArray(byteArray, arr.size);
    arr.array = byteArray;

    return arr;
}

void Go::Runtime::ConfigNodeToProto(alt::config::Node node, MValue::MValue *out)
{
    alt::config::Node::Type type = node.GetType();

    if (type == alt::config::Node::Type::DICT) {
        auto dict = node.ToDict();

        for (auto it = dict.begin(); it != dict.end(); ++it) {
            auto key = it->first;
            out->add_dict(key);

            auto value = out->add_list();
            ConfigNodeToProto(it->second, value);
        }
    } else if (type == alt::config::Node::Type::LIST) {
        auto list = node.ToList();

        for (auto it = list.begin(); it != list.end(); ++it) {
            auto value = out->add_list();
            ConfigNodeToProto(*it, value);
        }
    } else if (type == alt::config::Node::Type::SCALAR) {
        for (uint8_t i = 0; i < 3; i++) {
            try {
                if (i == 0) {
                    out->set_boolvalue(node.ToBool());
                }
                else if (i == 1) {
                    out->set_doublevalue(node.ToNumber());
                }
                else if (i == 2) {
                    out->set_stringvalue(node.ToString());
                }
            }
            catch (...) {
                continue;
            }
        }
    } else {
        out->set_nilvalue(true);
    }
}

alt::IEntity *Go::Runtime::GetEntityRef(Entity entity) {
    auto type = static_cast<alt::IEntity::Type>(entity.Type);

    switch (type) {
        case alt::IEntity::Type::PLAYER:
            return reinterpret_cast<alt::IPlayer *>(entity.Ptr);

        case alt::IEntity::Type::VEHICLE:
            return reinterpret_cast<alt::IVehicle *>(entity.Ptr);

        default:
            return nullptr;
    }
}

alt::IBaseObject* Go::Runtime::GetBaseObjectRef(Entity baseObject) {
    auto type = static_cast<alt::IBaseObject::Type>(baseObject.Type);

    switch (type) {
    case alt::IBaseObject::Type::BLIP:
        return reinterpret_cast<alt::IBlip*>(baseObject.Ptr);
    case alt::IBaseObject::Type::CHECKPOINT:
        return reinterpret_cast<alt::ICheckpoint*>(baseObject.Ptr);
    case alt::IBaseObject::Type::COLSHAPE:
        return reinterpret_cast<alt::IColShape*>(baseObject.Ptr);
    case alt::IBaseObject::Type::PLAYER:
        return reinterpret_cast<alt::IPlayer*>(baseObject.Ptr);
    case alt::IBaseObject::Type::VEHICLE:
        return reinterpret_cast<alt::IVehicle*>(baseObject.Ptr);
    case alt::IBaseObject::Type::VOICE_CHANNEL:
        return reinterpret_cast<alt::IVoiceChannel*>(baseObject.Ptr);
    }

    return nullptr;
}

std::string Go::Runtime::PointerToString(void* p) {
    auto i = reinterpret_cast<std::uintptr_t>(p);
    std::stringstream ss;
    ss << i;
    return ss.str();
}

alt::MValue Go::Runtime::ProtoToMValue(unsigned char *data, unsigned long long size) {
    if (size == 0) {
        return alt::ICore::Instance().CreateMValueNone();
    }

    MValue::MValue mValue;
    mValue.ParseFromArray(data, size);
    return ProtoToMValue(mValue);
}

alt::MValue Go::Runtime::ProtoToMValue(MValue::MValue mValue) {
    if (mValue.has_boolvalue()) {
        return alt::ICore::Instance().CreateMValueBool(mValue.boolvalue());
    } else if (mValue.has_uintvalue()) {
        return alt::ICore::Instance().CreateMValueUInt(mValue.uintvalue());
    } else if (mValue.has_intvalue()) {
        return alt::ICore::Instance().CreateMValueInt(mValue.intvalue());
    } else if (mValue.has_doublevalue()) {
        return alt::ICore::Instance().CreateMValueDouble(mValue.doublevalue());
    } else if (mValue.has_stringvalue()) {
        return alt::ICore::Instance().CreateMValueString(mValue.stringvalue());
    } else if (mValue.has_baseobjectvalue()) {
        const auto &baseObject = mValue.baseobjectvalue();
        Entity e;
        e.Type = baseObject.type();
        sscanf(baseObject.ptr().c_str(), "%p", &e.Ptr);

        auto altBaseObject = GetBaseObjectRef(e);
        return alt::ICore::Instance().CreateMValueBaseObject(altBaseObject);
    } else if (mValue.has_bytesvalue()) {
        auto bytes = mValue.bytesvalue();
        return alt::ICore::Instance().CreateMValueByteArray(reinterpret_cast<const uint8_t *>(bytes.data()), bytes.size());
    } else if (mValue.has_rgbavalue()) {
        const auto &rgba = mValue.rgbavalue();
        return alt::ICore::Instance().CreateMValueRGBA(alt::RGBA(rgba.r(), rgba.g(), rgba.b(), rgba.a()));
    } else if (mValue.has_vector2value()) {
        const auto &vector2 = mValue.vector2value();
        auto v2 = alt::Vector2f();
        v2[0] = vector2.x();
        v2[1] = vector2.y();
        return alt::ICore::Instance().CreateMValueVector2(v2);
    } else if (mValue.has_vector3value()) {
        const auto &vector3 = mValue.vector3value();
        auto v3 = alt::Vector3f();
        v3[0] = vector3.x();
        v3[1] = vector3.y();
        v3[2] = vector3.z();
        return alt::ICore::Instance().CreateMValueVector3(v3);
    } else if (mValue.has_internfunctionvalue()) {
        const auto &func = mValue.internfunctionvalue();
        auto resource = dynamic_cast<Go::Resource *>(Go::Runtime::GetInstance()->GetResource(func.resourcename()));
        if (resource == nullptr) {
            return alt::ICore::Instance().CreateMValueNil();
        }

        auto goFunc = new Go::Function(resource->Module, func.id());
        return alt::ICore::Instance().CreateMValueFunction(goFunc);
    } else if (mValue.dict_size() > 0) {
        auto dictSize = mValue.dict_size();
        auto dict = alt::ICore::Instance().CreateMValueDict();

        for (auto i = 0; i < dictSize; i++) {
            const auto &key = mValue.dict(i);
            const auto &value = mValue.list(i);

            auto val = ProtoToMValue(value);

            dict->Set(key, val);
        }

        return dict;
    } else if (mValue.list_size() > 0) {
        auto listSize = mValue.list_size();
        auto list = alt::ICore::Instance().CreateMValueList(listSize);

        for (auto i = 0; i < listSize; i++) {
            const auto &value = mValue.list(i);

            auto val = ProtoToMValue(value);

            list->Set(i, val);
        }

        return list;
    } else if (mValue.has_nonevalue()) {
        return alt::ICore::Instance().CreateMValueNone();
    } else {
        return alt::ICore::Instance().CreateMValueNil();
    }
}

void Go::Runtime::MValueToProto(alt::MValue mValue, MValue::MValue *value) {
    switch (mValue->GetType()) {
    case alt::IMValue::Type::BOOL: {
        auto b = mValue.As<alt::IMValueBool>();
        value->set_boolvalue(b->Value());
        break;
    }
    case alt::IMValue::Type::UINT: {
        auto mValueUint = mValue.As<alt::IMValueUInt>();
        value->set_uintvalue(mValueUint->Value());
        break;
    }
    case alt::IMValue::Type::INT: {
        auto mValueInt = mValue.As<alt::IMValueInt>();
        value->set_intvalue(mValueInt->Value());
        break;
    }
    case alt::IMValue::Type::DOUBLE: {
        auto mValueDouble = mValue.As<alt::IMValueDouble>();
        value->set_doublevalue(mValueDouble->Value());
        break;
    }
    case alt::IMValue::Type::STRING: {
        auto mValueString = mValue.As<alt::IMValueString>();
        value->set_stringvalue(mValueString->Value());
        break;
    }
    case alt::IMValue::Type::BASE_OBJECT: {
        auto mValueBaseObject = mValue.As<alt::IMValueBaseObject>();
        auto object = mValueBaseObject->Value();
        auto base = value->mutable_baseobjectvalue();
        base->set_ptr(PointerToString(object.Get()));
        base->set_type(static_cast<uint32_t>(object->GetType()));
        break;
    }
    case alt::IMValue::Type::BYTE_ARRAY: {
        auto mValueByteArray = mValue.As<alt::IMValueByteArray>();
        const auto bytes = mValueByteArray->GetData();
        const auto size = mValueByteArray->GetSize();

        value->set_bytesvalue(bytes, size);
        break;
    }
    case alt::IMValue::Type::RGBA: {
        auto mValueRGBA = mValue.As<alt::IMValueRGBA>();
        auto rgba = mValueRGBA->Value();
        auto color = value->mutable_rgbavalue();

        color->set_r(rgba.r);
        color->set_g(rgba.g);
        color->set_b(rgba.b);
        color->set_a(rgba.a);

        break;
    }
    case alt::IMValue::Type::VECTOR2: {
        auto mValueV2 = mValue.As<alt::IMValueVector2>();
        auto v2 = mValueV2->Value();
        auto vec = value->mutable_vector2value();

        vec->set_x(v2[0]);
        vec->set_y(v2[1]);

        break;
    }
    case alt::IMValue::Type::VECTOR3: {
        auto mValueV3 = mValue.As<alt::IMValueVector3>();
        auto v3 = mValueV3->Value();
        auto vec = value->mutable_vector3value();
        
        vec->set_x(v3[0]);
        vec->set_y(v3[1]);
        vec->set_z(v3[2]);

        break;
    }
    case alt::IMValue::Type::FUNCTION: {
        auto mValueFunc = mValue.As<alt::IMValueFunction>();
        
        auto func = value->mutable_externfunctionvalue();
        func->set_ptr(PointerToString(mValueFunc.Get()));

        break;
    }
    case alt::IMValue::Type::DICT: {
        auto mValueDict = mValue.As<alt::IMValueDict>();

        for (auto it = mValueDict->Begin(); it; it = mValueDict->Next()) {
            auto k = it->GetKey();
            value->add_dict(k.c_str());
            
            auto v = it->GetValue();
            auto lv = value->add_list();
            MValueToProto(v, lv);
        }

        break;
    }
    case alt::IMValue::Type::LIST: {
        auto mValueList = mValue.As<alt::IMValueList>();

        alt::Size size = mValueList->GetSize();
        for (alt::Size i = 0; i < size; i++) {
            auto mValue = mValueList->Get(i);
            auto lv = value->add_list();

            MValueToProto(mValue, lv);
        }

        break;
    }
    case alt::IMValue::Type::NIL: {
        value->set_nilvalue(true);
        break;
    }
    default:
        value->set_nonevalue(true);
        break;
    }
}

void Go::Runtime::MValueToProto(alt::MValueConst mValue, MValue::MValue *value) {
    switch (mValue->GetType()) {
    case alt::IMValue::Type::BOOL: {
        auto b = mValue.As<const alt::IMValueBool>();
        value->set_boolvalue(b->Value());
        break;
    }
    case alt::IMValue::Type::UINT: {
        auto mValueUint = mValue.As<const alt::IMValueUInt>();
        value->set_uintvalue(mValueUint->Value());
        break;
    }
    case alt::IMValue::Type::INT: {
        auto mValueInt = mValue.As<const alt::IMValueInt>();
        value->set_intvalue(mValueInt->Value());
        break;
    }
    case alt::IMValue::Type::DOUBLE: {
        auto mValueDouble = mValue.As<const alt::IMValueDouble>();
        value->set_doublevalue(mValueDouble->Value());
        break;
    }
    case alt::IMValue::Type::STRING: {
        auto mValueString = mValue.As<const alt::IMValueString>();
        value->set_stringvalue(mValueString->Value());
        break;
    }
    case alt::IMValue::Type::BASE_OBJECT: {
        auto mValueBaseObject = mValue.As<const alt::IMValueBaseObject>();
        auto object = mValueBaseObject->Value();
        auto base = value->mutable_baseobjectvalue();

        base->set_ptr(PointerToString(object.Get()));
        base->set_type(static_cast<uint32_t>(object->GetType()));

        break;
    }
    case alt::IMValue::Type::BYTE_ARRAY: {
        auto mValueByteArray = mValue.As<const alt::IMValueByteArray>();
        const auto bytes = mValueByteArray->GetData();
        const auto size = mValueByteArray->GetSize();

        value->set_bytesvalue(bytes, size);
        break;
    }
    case alt::IMValue::Type::RGBA: {
        auto mValueRGBA = mValue.As<const alt::IMValueRGBA>();
        auto rgba = mValueRGBA->Value();
        auto color = value->mutable_rgbavalue();
        
        color->set_r(rgba.r);
        color->set_g(rgba.g);
        color->set_b(rgba.b);
        color->set_a(rgba.a);

        break;
    }
    case alt::IMValue::Type::VECTOR2: {
        auto mValueV2 = mValue.As<const alt::IMValueVector2>();
        auto v2 = mValueV2->Value();
        auto vec = value->mutable_vector2value();
        
        vec->set_x(v2[0]);
        vec->set_y(v2[1]);

        break;
    }
    case alt::IMValue::Type::VECTOR3: {
        auto mValueV3 = mValue.As<const alt::IMValueVector3>();
        auto v3 = mValueV3->Value();
        auto vec = value->mutable_vector3value();

        vec->set_x(v3[0]);
        vec->set_y(v3[1]);
        vec->set_z(v3[2]);

        break;
    }
    case alt::IMValue::Type::FUNCTION: {
        auto mValueFunc = mValue.As<const alt::IMValueFunction>();
        auto func = value->mutable_externfunctionvalue();

        func->set_ptr(PointerToString(const_cast<alt::IMValueFunction*>(mValueFunc.Get())));

        break;
    }
    case alt::IMValue::Type::DICT: {
        auto mValueDict = mValue.As<const alt::IMValueDict>();

        for (auto it = mValueDict->Begin(); it; it = mValueDict->Next()) {
            auto k = it->GetKey();
            value->add_dict(k.c_str());

            alt::MValueConst v = it->GetValue();
            MValue::MValue* lv = value->add_list();
            MValueToProto(v, lv);
        }

        break;
    }
    case alt::IMValue::Type::LIST: {
        auto mValueList = mValue.As<const alt::IMValueList>();

        alt::Size size = mValueList->GetSize();
        for (alt::Size i = 0; i < size; i++) {
            auto mValue = mValueList->Get(i);
            MValue::MValue* lv = value->add_list();
            MValueToProto(mValue, lv);
        }
        break;
    }
    case alt::IMValue::Type::NIL: {
        value->set_nilvalue(true);
        break;
    }
    default:
        value->set_nonevalue(true);
        break;
    }
}

Array Go::Runtime::MValueToProtoBytes(alt::MValue mValue) {
    auto value = new MValue::MValue();
    MValueToProto(mValue, value);

    Array arr;
    arr.size = value->ByteSizeLong();

    unsigned char *byteArray = new unsigned char[arr.size];
    value->SerializeToArray(byteArray, arr.size);
    arr.array = byteArray;

    return arr;
}

Array Go::Runtime::MValueToProtoBytes(alt::MValueConst mValue) {
    auto value = new MValue::MValue();
    MValueToProto(mValue, value);

    Array arr;
    arr.size = value->ByteSizeLong();

    unsigned char* byteArray = new unsigned char[arr.size];
    value->SerializeToArray(byteArray, arr.size);
    arr.array = byteArray;

    return arr;
}

Array Go::Runtime::MValueArgsToProtoBytes(alt::MValueArgs args) {
    Array all;
    all.size = args.GetSize();

#ifdef _WIN32
    auto constArgs = new Array[all.size];
#else
    Array constArgs[all.size];
#endif

    for (auto i = 0; i < all.size; i++) {
        alt::MValueConst mValue = args[i];
        auto bytes = MValueToProtoBytes(mValue);
        constArgs[i] = bytes;
    }

    all.array = constArgs;

    return all;
}

alt::MValueArgs Go::Runtime::ProtoToMValueArgs(Array data) {
    alt::MValueArgs args;

    if (!data.size || data.array == nullptr) {
        return args;
    }

    auto byteArrays = reinterpret_cast<Array*>(data.array);

    for (auto i = 0; i < data.size; i++) {
        Array arr = byteArrays[i];
        auto data = reinterpret_cast<unsigned char*>(arr.array);

        alt::MValue arg = ProtoToMValue(data, arr.size);

        args.Push(arg);
    }

// crashes
//#ifdef _WIN32
//    delete[] data.array;
//#endif

    return args;
}