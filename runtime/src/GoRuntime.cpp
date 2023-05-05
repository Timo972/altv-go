#include "GoRuntime.h"
#include "GoResource.h"
// #include <cstdio>
#include <cstdint>
#include <sstream>
#include "rapidjson/document.h"

Go::Runtime *Go::Runtime::Instance = nullptr;

Go::Runtime *Go::Runtime::GetInstance() {
    if (Instance == nullptr)
        Instance = new Runtime();

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

}

alt::IResource::Impl *Go::Runtime::GetResource(const std::string &name) {
    for (auto &resource: _resources) {
        if (resource.find(name) != resource.end()) {
            return resource[name];
        }
    }

    return nullptr;
}

Entity Go::Runtime::GetEntity(alt::IEntity* entity) {
    Entity e;

    if (entity != nullptr) {
        auto entityType = entity->GetType();
        e.typ = static_cast<unsigned char>(entityType);
        e.id = entity->GetID();

        switch (entityType) {
            case alt::IEntity::Type::PLAYER:
                e.ptr = entity->As<alt::IPlayer>();
                break;
            case alt::IEntity::Type::VEHICLE:
                e.ptr = entity->As<alt::IVehicle>();
                e.model = entity->As<alt::IVehicle>()->GetModel();
                break;
            case alt::IEntity::Type::BLIP:
                e.ptr = entity->As<alt::IBlip>();
                break;
            case alt::IEntity::Type::CHECKPOINT:
                e.ptr = entity->As<alt::ICheckpoint>();
                break;
            case alt::IEntity::Type::COLSHAPE:
                e.ptr = entity->As<alt::IColShape>();
                break;
            case alt::IEntity::Type::VOICE_CHANNEL:
                e.ptr = entity->As<alt::IVoiceChannel>();
                break;
            case alt::IEntity::Type::PED:
                e.ptr = entity->As<alt::IPed>();
                break;
            case alt::IEntity::Type::MARKER:
                e.ptr = entity->As<alt::IMarker>();
                break;
            case alt::IEntity::Type::VIRTUAL_ENTITY:
                e.ptr = entity->As<alt::IVirtualEntity>();
                break;
            case alt::IEntity::Type::VIRTUAL_ENTITY_GROUP:
                e.ptr = entity->As<alt::IVirtualEntityGroup>();
                break;
            case alt::IEntity::Type::NETWORK_OBJECT:
                e.ptr = entity->As<alt::INetworkObject>();
                break;
            case alt::IEntity::Type::OBJECT:
                e.ptr = entity->As<alt::IObject>();
                break;
            case alt::IEntity::Type::TEXT_LABEL:
                e.ptr = entity->As<alt::ITextLabel>();
                break;
            default:
                e.ptr = nullptr;
                break;
        }
    } else {
        e.ptr = nullptr;
    }

    return e;
}

Entity Go::Runtime::GetBaseObject(alt::IBaseObject* baseObject)  {
    Entity e;

    if (baseObject != nullptr) {
        auto entityType = baseObject->GetType();
        e.typ = static_cast<unsigned char>(entityType);

        switch (entityType) {
            case alt::IBaseObject::Type::PLAYER:
                e.ptr = baseObject->As<alt::IPlayer>();
                e.id = baseObject->As<alt::IPlayer>()->GetID();
                break;
            case alt::IBaseObject::Type::VEHICLE:
                e.ptr = baseObject->As<alt::IVehicle>();
                e.id = baseObject->As<alt::IVehicle>()->GetID();
                e.model = baseObject->As<alt::IVehicle>()->GetModel();
                break;
            case alt::IBaseObject::Type::BLIP:
                e.ptr = baseObject->As<alt::IBlip>();
                e.id = baseObject->As<alt::IBlip>()->GetID();
                break;
            case alt::IBaseObject::Type::CHECKPOINT:
                e.ptr = baseObject->As<alt::ICheckpoint>();
                e.id = baseObject->As<alt::ICheckpoint>()->GetID();
                break;
            case alt::IBaseObject::Type::COLSHAPE:
                e.ptr = baseObject->As<alt::IColShape>();
                e.id = baseObject->As<alt::IColShape>()->GetID();
                break;
            case alt::IBaseObject::Type::VOICE_CHANNEL:
                e.ptr = baseObject->As<alt::IVoiceChannel>();
                e.id = baseObject->As<alt::IVoiceChannel>()->GetID();
                break;
            case alt::IBaseObject::Type::MARKER:
                e.ptr = baseObject->As<alt::IMarker>();
                e.id = baseObject->As<alt::IMarker>()->GetID();
                break;
            case alt::IBaseObject::Type::PED:
                e.ptr = baseObject->As<alt::IPed>();
                e.id = baseObject->As<alt::IPed>()->GetID();
                break;
            case alt::IBaseObject::Type::VIRTUAL_ENTITY:
                e.ptr = baseObject->As<alt::IVirtualEntity>();
                e.id = baseObject->As<alt::IVirtualEntity>()->GetID();
                break;
            case alt::IBaseObject::Type::VIRTUAL_ENTITY_GROUP:
                e.ptr = baseObject->As<alt::IVirtualEntityGroup>();
                e.id = baseObject->As<alt::IVirtualEntityGroup>()->GetID();
                break;
            case alt::IBaseObject::Type::NETWORK_OBJECT:
                e.ptr = baseObject->As<alt::INetworkObject>();
                e.id = baseObject->As<alt::INetworkObject>()->GetID();
                break;
            case alt::IBaseObject::Type::TEXT_LABEL:
                e.ptr = baseObject->As<alt::ITextLabel>();
                e.id = baseObject->As<alt::ITextLabel>()->GetID();
                break;
            default:
                e.ptr = nullptr;
                break;
        }
    } else {
        e.ptr = nullptr;
    }

    return e;
}

ConnectionInfo Go::Runtime::GetConnectionInfo(alt::IConnectionInfo* info) {
    connectionInfo conn{};
    conn.authToken = info->GetAuthToken().c_str();
    conn.branch = info->GetBranch().c_str();
    conn.build = info->GetBuild();
    conn.cdnUrl = info->GetCdnUrl().c_str();
    conn.discordUserID = info->GetDiscordUserID();
    conn.hwidExHash = info->GetHwIdExHash();
    conn.hwidHash = info->GetHwIdHash();
    conn.ip = info->GetIp().c_str();
    conn.isDebug = info->GetIsDebug();
    conn.name = info->GetName().c_str();
    conn.passwordHash = info->GetPasswordHash();
    conn.socialID = info->GetSocialId();
    conn.id = info->GetID();
    conn.socialName = info->GetSocialName().c_str();
    conn.cloudAuthHash = info->GetCloudAuthHash().c_str();

    return conn;
}

Array Go::Runtime::CreateBoneArray(std::vector<alt::BoneInfo> bones) {
    Array arr;
    arr.size = bones.size();

#ifdef _WIN32
    auto cArr = new BoneInfo[arr.size];
#else
    BoneInfo cArr[arr.size];
#endif
    

    for (uint64_t i = 0; i < arr.size; i++) {
        auto b = bones[i];
        BoneInfo bone;
        bone.id = b.id;
        bone.index = b.index;
        bone.name = b.name.c_str();
        cArr[i] = bone;
    }

    arr.array = cArr;

    return arr;
}

alt::IEntity *Go::Runtime::GetEntityRef(Entity entity) {
    auto type = static_cast<alt::IEntity::Type>(entity.typ);

    switch (type) {
        case alt::IEntity::Type::PLAYER:
            return reinterpret_cast<alt::IPlayer *>(entity.ptr);

        case alt::IEntity::Type::VEHICLE:
            return reinterpret_cast<alt::IVehicle *>(entity.ptr);

        default:
            return nullptr;
    }
}

alt::IBaseObject* Go::Runtime::GetBaseObjectRef(Entity baseObject) {
    auto type = static_cast<alt::IBaseObject::Type>(baseObject.typ);

    switch (type) {
    case alt::IBaseObject::Type::BLIP:
        return reinterpret_cast<alt::IBlip*>(baseObject.ptr);
    case alt::IBaseObject::Type::CHECKPOINT:
        return reinterpret_cast<alt::ICheckpoint*>(baseObject.ptr);
    case alt::IBaseObject::Type::COLSHAPE:
        return reinterpret_cast<alt::IColShape*>(baseObject.ptr);
    case alt::IBaseObject::Type::PLAYER:
        return reinterpret_cast<alt::IPlayer*>(baseObject.ptr);
    case alt::IBaseObject::Type::VEHICLE:
        return reinterpret_cast<alt::IVehicle*>(baseObject.ptr);
    case alt::IBaseObject::Type::VOICE_CHANNEL:
        return reinterpret_cast<alt::IVoiceChannel*>(baseObject.ptr);
    default:
        return nullptr;
    }
}

std::string Go::Runtime::PointerToString(void* p) {
    auto i = reinterpret_cast<std::uintptr_t>(p);
    std::stringstream ss;
    ss << i;
    return ss.str();
}

alt::MValue Go::Runtime::DecodeMValue(Array value) {
    auto data = reinterpret_cast<const char *>(value.array);

    rapidjson::Document d;
    d.Parse(data);

    rapidjson::Value& $type = d["$type"];

    if (d.IsBool()) {
        return alt::ICore::Instance().CreateMValueBool(d.GetBool());
    } else if (d.IsUint64()) {
        return alt::ICore::Instance().CreateMValueUInt(d.GetUint64());
    } else if (d.IsInt64()) {
        return alt::ICore::Instance().CreateMValueInt(d.GetInt64());
    } else if (d.IsDouble()) {
        return alt::ICore::Instance().CreateMValueDouble(d.GetDouble());
    } else if (d.IsString()) {
        return alt::ICore::Instance().CreateMValueString(std::string(d.GetString(), d.GetStringLength()));
    } else if (d.IsObject() && !$type.Empty() && $type.IsInt()) {
        auto typ = static_cast<alt::IMValue::Type>($type.GetInt());

        if (typ == alt::IMValue::Type::BASE_OBJECT) {
            rapidjson::Value& id = d["id"];
            rapidjson::Value& type = d["type"];

            if (id.Empty() || type.Empty()) {
                alt::ICore::Instance().LogError("Invalid BaseObject MValue");
                return alt::ICore::Instance().CreateMValueNone();
            }

            return alt::ICore::Instance().CreateMValueBaseObject(alt::ICore::Instance().GetBaseObjectByID(static_cast<alt::IBaseObject::Type>(type.GetInt()), id.GetUint()));
        } else if (typ == alt::IMValue::Type::BYTE_ARRAY) {
            rapidjson::Value& data = d["data"];

            if (data.Empty() || !data.IsString()) {
                alt::ICore::Instance().LogError("Invalid ByteArray MValue");
                return alt::ICore::Instance().CreateMValueNone();
            }

            return alt::ICore::Instance().CreateMValueByteArray(reinterpret_cast<const uint8_t*>(data.GetString()), static_cast<alt::Size>(data.GetStringLength()));
        } else if (typ == alt::IMValue::Type::RGBA) {
            rapidjson::Value& r = d["r"];
            rapidjson::Value& g = d["g"];
            rapidjson::Value& b = d["b"];
            rapidjson::Value& a = d["a"];

            if (r.Empty() || !r.IsUint() || g.Empty() || !g.IsUint() || b.Empty() || !b.IsUint() || a.Empty() || !a.IsUint()) {
                alt::ICore::Instance().LogError("Invalid RGBA MValue");
                return alt::ICore::Instance().CreateMValueNone();
            }

            return alt::ICore::Instance().CreateMValueRGBA(alt::RGBA(r.GetUint(), g.GetUint(), b.GetUint(), a.GetUint()));
        } else if (typ == alt::IMValue::Type::VECTOR2) {
            rapidjson::Value& x = d["x"];
            rapidjson::Value& y = d["y"];

            if (x.Empty() || !x.IsFloat() || y.Empty() || !y.IsFloat()) {
                alt::ICore::Instance().LogError("Invalid Vector2 MValue");
                return alt::ICore::Instance().CreateMValueNone();
            }

            auto v2 = alt::Vector2f();
            v2[0] = x.GetFloat();
            v2[1] = y.GetFloat();
            return alt::ICore::Instance().CreateMValueVector2(v2);
        } else if (typ == alt::IMValue::Type::VECTOR3) {
            rapidjson::Value& x = d["x"];
            rapidjson::Value& y = d["y"];
            rapidjson::Value& z = d["z"];

            if (x.Empty() || !x.IsFloat() || y.Empty() || !y.IsFloat() || z.Empty() || z.IsFloat()) {
                alt::ICore::Instance().LogError("Invalid Vector3 MValue");
                return alt::ICore::Instance().CreateMValueNone();
            }


            auto v3 = alt::Vector3f();
            v3[0] = x.GetFloat();
            v3[1] = y.GetFloat();
            v3[2] = z.GetFloat();
            return alt::ICore::Instance().CreateMValueVector3(v3);
        } else if (typ == alt::IMValue::Type::FUNCTION) {
            rapidjson::Value& id = d["id"];
            rapidjson::Value& resourceName = d["resourceName"];

            if (id.Empty() || !id.IsInt() || resourceName.Empty() || resourceName.IsString()) {
                alt::ICore::Instance().LogError("Invalid (exported) Function MValue");
                return alt::ICore::Instance().CreateMValueNone();
            }

            auto resource = dynamic_cast<Go::Resource *>(Go::Runtime::GetInstance()->GetResource(resourceName.GetString()));
            if (resource == nullptr) {
                alt::ICore::Instance().LogError("Unable to get resource; Failed to export Function MValue");
                return alt::ICore::Instance().CreateMValueNone();
            }

            auto goFunc = new Go::Function(resource->Module, id.GetInt());
            return alt::ICore::Instance().CreateMValueFunction(goFunc);
        }
    } else if (d.IsObject()) {
        auto dict = alt::ICore::Instance().CreateMValueDict();

        auto obj = d.GetObject();

        for (auto it = obj.begin(); it != obj.end(); it++) {
      
        }

        return dict;
    } else if (d.IsArray()) {
        auto list = alt::ICore::Instance().CreateMValueList(value.size);

        auto arr = d.GetArray();

        for (auto it = arr.begin(); it != arr.end(); it++) {

        }

        return list;
    } else if (d.IsNull()) {
        return alt::ICore::Instance().CreateMValueNil();
    }

    return alt::ICore::Instance().CreateMValueNone();
}

Array Go::Runtime::EncodeMValue(alt::MValueConst mValue) {
    return Array{};
}

Array Go::Runtime::EncodeMValue(alt::MValue mValue) {
    return Array{};
    /*auto t = mValue->GetType();
    value->typ = static_cast<unsigned char>(t);
    switch (t) {
    case alt::IMValue::Type::BOOL: {
        value->boolValue = mValue.As<alt::IMValueBool>()->Value();
        break;
    }
    case alt::IMValue::Type::UINT: {
        value->uintValue = mValue.As<alt::IMValueUInt>()->Value();
        break;
    }
    case alt::IMValue::Type::INT: {
        value->intValue = mValue.As<alt::IMValueInt>()->Value();
        break;
    }
    case alt::IMValue::Type::DOUBLE: {
        value->doubleValue = mValue.As<alt::IMValueDouble>()->Value();
        break;
    }
    case alt::IMValue::Type::STRING: {
        auto str = mValue.As<alt::IMValueString>()->Value();
        value->size = str.size();
        // does this work? idk i am bad at c / c++
        memcpy(value->stringValue, str.c_str(), str.size());
        break;
    }
    case alt::IMValue::Type::BASE_OBJECT: {
        // TODO:
        // auto object = mValue->As<alt::IMValueBaseObject>()->Value();
        // value->entityValue = GetBaseObject(object);
        break;
    }
    case alt::IMValue::Type::BYTE_ARRAY: {
        auto mValueByteArray = mValue.As<alt::IMValueByteArray>();
        value->bytes = mValueByteArray->GetData();
        value->size = mValueByteArray->GetSize();
        break;
    }
    case alt::IMValue::Type::RGBA: {
        auto rgba = mValue.As<alt::IMValueRGBA>()->Value();

        RGBA color{};
        color.r = rgba.r;
        color.g = rgba.g;
        color.b = rgba.b;
        color.a = rgba.a;

        value->rgbaValue = color;
        break;
    }
    case alt::IMValue::Type::VECTOR2: {
        auto v2 = mValue.As<alt::IMValueVector2>()->Value();

        Position vector{};
        vector.x = v2[0];
        vector.y = v2[1];

        value->vectorValue = vector;
        break;
    }
    case alt::IMValue::Type::VECTOR3: {
        auto v3 = mValue.As<alt::IMValueVector3>()->Value();

        Position vector{};
        vector.x = v3[0];
        vector.y = v3[1];
        vector.z = v3[2];

        value->vectorValue = vector;
        break;
    }
    case alt::IMValue::Type::FUNCTION: {
        value->externFunc = mValue.As<alt::IMValueFunction>().Get();
        break;
    }
    case alt::IMValue::Type::DICT: {
        auto mValueDict = mValue.As<alt::IMValueDict>();
        value->size = mValueDict->GetSize();
#ifdef _WIN32
        value->list = new GoValue[value->size];
#else
        GoValue list[value->size];
        value->list = list;
#endif
        uint64_t i = 0;
        for (auto it = mValueDict->Begin(); it; it = mValueDict->Next()) {
            auto key = it->GetKey();
            memcpy(value->keys[i], key.c_str(), key.size());
            // TODO: check if this works
            MValueToGo(it->GetValue(), &value->list[i]);
            i++;
        }

        break;
    }
    case alt::IMValue::Type::LIST: {
        auto mValueList = mValue.As<alt::IMValueList>();

        alt::Size size = mValueList->GetSize();
        value->size = size;
#ifdef _WIN32
        value->list = new GoValue[size];
#else
        GoValue list[size];
        value->list = list;
#endif
        for (alt::Size i = 0; i < size; i++) {
            value->list[i] = GoValue{};
            MValueToGo(mValueList->Get(i), &value->list[i]);
        }

        break;
    }
    case alt::IMValue::Type::NIL: {
        break;
    }
    default:
        break;
    }*/
}

/*
void Go::Runtime::EncodeMValue(alt::MValueConst mValue, GoValue *value) {
    auto t = mValue->GetType();
    value->typ = static_cast<unsigned char>(t);

    switch (t) {
    case alt::IMValue::Type::BOOL: {
        value->boolValue = mValue.As<const alt::IMValueBool>()->Value();
        break;
    }
    case alt::IMValue::Type::UINT: {
        value->uintValue = mValue.As<const alt::IMValueUInt>()->Value();
        break;
    }
    case alt::IMValue::Type::INT: {
        value->intValue = mValue.As<const alt::IMValueInt>()->Value();
        break;
    }
    case alt::IMValue::Type::DOUBLE: {
        value->doubleValue = mValue.As<const alt::IMValueDouble>()->Value();
        break;
    }
    case alt::IMValue::Type::STRING: {
        auto str = mValue.As<const alt::IMValueString>()->Value();
        value->size = str.size();
        memcpy(value->stringValue, str.c_str(), str.size());
        break;
    }
    case alt::IMValue::Type::BASE_OBJECT: {
        // TODO:
        //auto object = mValue.As<const alt::IMValueBaseObject>()->Value();
        // value->entityValue = GetBaseObject(object);
        break;
    }
    case alt::IMValue::Type::BYTE_ARRAY: {
        auto mValueByteArray = mValue.As<const alt::IMValueByteArray>();
        value->bytes = const_cast<unsigned char*>(mValueByteArray->GetData());
        value->size = mValueByteArray->GetSize();
        break;
    }
    case alt::IMValue::Type::RGBA: {
        auto rgba = mValue.As<const alt::IMValueRGBA>()->Value();

        RGBA color{};
        color.r = rgba.r;
        color.g = rgba.g;
        color.b = rgba.b;
        color.a = rgba.a;

        value->rgbaValue = color;

        break;
    }
    case alt::IMValue::Type::VECTOR2: {
        auto v2 = mValue.As<const alt::IMValueVector2>()->Value();

        Position vector{};
        vector.x = v2[0];
        vector.y = v2[1];

        value->vectorValue = vector;
        break;
    }
    case alt::IMValue::Type::VECTOR3: {
        auto v3 = mValue.As<const alt::IMValueVector3>()->Value();

        Position vector{};
        vector.x = v3[0];
        vector.y = v3[1];
        vector.z = v3[2];

        value->vectorValue = vector;
        break;
    }
    case alt::IMValue::Type::FUNCTION: {
        value->externFunc = const_cast<alt::IMValueFunction*>(mValue.As<const alt::IMValueFunction>().Get());
        break;
    }
    case alt::IMValue::Type::DICT: {
        auto mValueDict = mValue.As<const alt::IMValueDict>();
        value->size = mValueDict->GetSize();
#ifdef _WIN32
        value->list = new GoValue[value->size];
#else
        GoValue list[value->size];
        value->list = list;
#endif
        uint64_t i = 0;
        for (auto it = mValueDict->Begin(); it; it = mValueDict->Next()) {
            auto key = it->GetKey();
            memcpy(value->keys[i], key.c_str(), key.size());
            // TODO: check if this works
            MValueToGo(it->GetValue(), &value->list[i]);
            i++;
        }

        break;
    }
    case alt::IMValue::Type::LIST: {
        auto mValueList = mValue.As<const alt::IMValueList>();
        alt::Size size = mValueList->GetSize();
        value->size = size;
#ifdef _WIN32
        value->list = new GoValue[size];
#else
        GoValue list[size];
        value->list = list;
#endif
        for (alt::Size i = 0; i < size; i++) {
            value->list[i] = GoValue{};
            MValueToGo(mValueList->Get(i), &value->list[i]);
        }
        break;
    }
    case alt::IMValue::Type::NIL: {
        break;
    }
    default:
        break;
    }
}

GoValueArgs Go::Runtime::EncodeMValueArgs(alt::MValueArgs args) {
    GoValueArgs all;
    all.size = args.size();

#ifdef _WIN32
    auto constArgs = new GoValue[all.size];
#else
    GoValue constArgs[all.size];
#endif

    for (auto i = 0; i < all.size; i++) {
        alt::MValueConst mValue = args[i];

        GoValue value{};
        MValueToGo(mValue, &value);
        constArgs[i] = value;
    }

    all.args = constArgs;

    return all;
}

alt::MValueArgs Go::Runtime::DecodeMValueArgs(GoValueArgs data) {
    alt::MValueArgs args;

    if (!data.size || data.args == nullptr) {
        return args;
    }

    for (auto i = 0; i < data.size; i++) {
        args.push_back(GoToMValue( data.args[i]));
    }

// crashes
//#ifdef _WIN32
//    delete[] data.args;
//#endif

    return args;
}
*/