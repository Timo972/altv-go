#include "GoRuntime.h"
#include "GoResource.h"
// #include <cstdio>
#include <cstdint>
#include <sstream>

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

Entity Go::Runtime::GetEntity(alt::Ref <alt::IEntity> entity) {
    Entity e;

    if (!entity.IsEmpty()) {
        auto entityType = entity->GetType();
        e.typ = static_cast<unsigned char>(entityType);

        switch (entityType) {
            case alt::IEntity::Type::PLAYER:
                e.ptr = entity.As<alt::IPlayer>().Get();
                e.id = entity->GetID();
                break;
            case alt::IEntity::Type::VEHICLE:
                e.ptr = entity.As<alt::IVehicle>().Get();
                e.id = entity->GetID();
                e.model = entity.As<alt::IVehicle>()->GetModel();
                break;
            case alt::IEntity::Type::BLIP:
                e.ptr = entity.As<alt::IBlip>().Get();
                break;
            case alt::IEntity::Type::CHECKPOINT:
                e.ptr = entity.As<alt::ICheckpoint>().Get();
                break;
            case alt::IEntity::Type::COLSHAPE:
                e.ptr = entity.As<alt::IColShape>().Get();
                break;
            case alt::IEntity::Type::VOICE_CHANNEL:
                e.ptr = entity.As<alt::IVoiceChannel>().Get();
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

Entity Go::Runtime::GetBaseObject(alt::Ref<alt::IBaseObject> baseObject)  {
    Entity e;

    if (!baseObject.IsEmpty()) {
        auto entityType = baseObject->GetType();
        e.typ = static_cast<unsigned char>(entityType);

        switch (entityType) {
            case alt::IBaseObject::Type::PLAYER:
                e.ptr = baseObject.As<alt::IPlayer>().Get();
                e.id = baseObject.As<alt::IPlayer>()->GetID();
                break;
            case alt::IBaseObject::Type::VEHICLE:
                e.ptr = baseObject.As<alt::IVehicle>().Get();
                e.id = baseObject.As<alt::IVehicle>()->GetID();
                e.model = baseObject.As<alt::IVehicle>()->GetModel();
                break;
            case alt::IBaseObject::Type::BLIP:
                e.ptr = baseObject.As<alt::IBlip>().Get();
                break;
            case alt::IBaseObject::Type::CHECKPOINT:
                e.ptr = baseObject.As<alt::ICheckpoint>().Get();
                break;
            case alt::IBaseObject::Type::COLSHAPE:
                e.ptr = baseObject.As<alt::IColShape>().Get();
                break;
            case alt::IBaseObject::Type::VOICE_CHANNEL:
                e.ptr = baseObject.As<alt::IVoiceChannel>().Get();
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

ConnectionInfo Go::Runtime::GetConnectionInfo(alt::Ref <alt::IConnectionInfo> info) {
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

/*Array Go::Runtime::ConfigNodeToProtoBytes(alt::config::Node node)
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
}*/

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

alt::MValue Go::Runtime::GoToMValue(GoValue value) {
    auto typ = static_cast<alt::IMValue::Type>(value.typ);

    if (typ == alt::IMValue::Type::BOOL) {
        return alt::ICore::Instance().CreateMValueBool(value.boolValue == 1);
    } else if (typ == alt::IMValue::Type::UINT) {
        return alt::ICore::Instance().CreateMValueUInt(value.uintValue);
    } else if (typ == alt::IMValue::Type::INT) {
        return alt::ICore::Instance().CreateMValueInt(value.intValue);
    } else if (typ == alt::IMValue::Type::DOUBLE) {
        return alt::ICore::Instance().CreateMValueDouble(value.doubleValue);
    } else if (typ == alt::IMValue::Type::STRING) {
        return alt::ICore::Instance().CreateMValueString(std::string(value.stringValue, value.size));
    } else if (typ == alt::IMValue::Type::BASE_OBJECT) {
        return alt::ICore::Instance().CreateMValueBaseObject(GetBaseObjectRef(value.entityValue));
    } else if (typ == alt::IMValue::Type::BYTE_ARRAY) {
        return alt::ICore::Instance().CreateMValueByteArray(value.bytes, value.size);
    } else if (typ == alt::IMValue::Type::RGBA) {
        return alt::ICore::Instance().CreateMValueRGBA(alt::RGBA(value.rgbaValue.r, value.rgbaValue.g, value.rgbaValue.b, value.rgbaValue.a));
    } else if (typ == alt::IMValue::Type::VECTOR2) {
        auto v2 = alt::Vector2f();
        v2[0] = value.vectorValue.x;
        v2[1] = value.vectorValue.y;
        return alt::ICore::Instance().CreateMValueVector2(v2);
    } else if (typ == alt::IMValue::Type::VECTOR3) {
        auto v3 = alt::Vector3f();
        v3[0] = value.vectorValue.x;
        v3[1] = value.vectorValue.y;
        v3[2] = value.vectorValue.z;
        return alt::ICore::Instance().CreateMValueVector3(v3);
    } else if (typ == alt::IMValue::Type::FUNCTION) {
        auto resource = dynamic_cast<Go::Resource *>(Go::Runtime::GetInstance()->GetResource(value.internFunc.resourceName));
        if (resource == nullptr) {
            return alt::ICore::Instance().CreateMValueNil();
        }

        auto goFunc = new Go::Function(resource->Module, value.internFunc.id);
        return alt::ICore::Instance().CreateMValueFunction(goFunc);
    } else if (typ == alt::IMValue::Type::DICT) {
        auto dict = alt::ICore::Instance().CreateMValueDict();

        for (auto i = 0; i < value.size; i++)
            dict->Set(value.keys[i], GoToMValue(value.list[i]));

        return dict;
    } else if (typ == alt::IMValue::Type::LIST) {
        auto list = alt::ICore::Instance().CreateMValueList(value.size);

        for (auto i = 0; i < value.size; i++)
            list->Set(i, GoToMValue(value.list[i]));

        return list;
    } else if (typ == alt::IMValue::Type::NIL) {
        return alt::ICore::Instance().CreateMValueNil();
    } else {
        return alt::ICore::Instance().CreateMValueNone();
    }
}

void Go::Runtime::MValueToGo(alt::MValue mValue, GoValue *value) {
    auto t = mValue->GetType();
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
        auto object = mValue.As<alt::IMValueBaseObject>()->Value();
        value->entityValue = GetBaseObject(object);
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
    }
}

void Go::Runtime::MValueToGo(alt::MValueConst mValue, GoValue *value) {
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
        auto object = mValue.As<const alt::IMValueBaseObject>()->Value();
        value->entityValue = GetBaseObject(object);
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

GoValueArgs Go::Runtime::MValueArgsToGo(alt::MValueArgs args) {
    GoValueArgs all;
    all.size = args.GetSize();

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

alt::MValueArgs Go::Runtime::GoToMValueArgs(GoValueArgs data) {
    alt::MValueArgs args;

    if (!data.size || data.args == nullptr) {
        return args;
    }

    for (auto i = 0; i < data.size; i++) {
        args.Push(GoToMValue( data.args[i]));
    }

// crashes
//#ifdef _WIN32
//    delete[] data.args;
//#endif

    return args;
}