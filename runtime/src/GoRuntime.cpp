#include "GoRuntime.h"
#include "GoResource.h"
// #include <cstdio>
#include <cstdint>
#include <sstream>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/memorybuffer.h"

Go::Runtime *Go::Runtime::Instance = nullptr;

Go::Runtime *Go::Runtime::GetInstance()
{
    if (Instance == nullptr)
        Instance = new Runtime();

    return Instance;
}

alt::IResource::Impl *Go::Runtime::CreateImpl(alt::IResource *impl)
{
    auto resource = new Go::Resource(this, impl);
    _resources.push_back({{impl->GetName().c_str(), resource}});

    return resource;
}

void Go::Runtime::DestroyImpl(alt::IResource::Impl *impl)
{
    auto resource = dynamic_cast<Go::Resource *>(impl);

    if (resource != nullptr)
        delete resource;
}

void Go::Runtime::OnDispose()
{
}

alt::IResource::Impl *Go::Runtime::GetResource(const std::string &name)
{
    for (auto &resource : _resources)
    {
        if (resource.find(name) != resource.end())
        {
            return resource[name];
        }
    }

    return nullptr;
}

Entity Go::Runtime::GetEntity(alt::IEntity *entity)
{
    Entity e;

    if (entity != nullptr)
    {
        auto entityType = entity->GetType();
        e.typ = static_cast<unsigned char>(entityType);
        e.id = entity->GetID();

        switch (entityType)
        {
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
    }
    else
    {
        e.ptr = nullptr;
    }

    return e;
}

Entity Go::Runtime::GetBaseObject(alt::IBaseObject *baseObject)
{
    Entity e;

    if (baseObject != nullptr)
    {
        auto entityType = baseObject->GetType();
        e.typ = static_cast<unsigned char>(entityType);

        switch (entityType)
        {
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
    }
    else
    {
        e.ptr = nullptr;
    }

    return e;
}

ConnectionInfo Go::Runtime::GetConnectionInfo(alt::IConnectionInfo *info)
{
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

Array Go::Runtime::CreateBoneArray(std::vector<alt::BoneInfo> bones)
{
    Array arr;
    arr.size = bones.size();

    auto cArr = new BoneInfo[arr.size];

    for (uint64_t i = 0; i < arr.size; i++)
    {
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

alt::IEntity *Go::Runtime::GetEntityRef(Entity entity)
{
    auto type = static_cast<alt::IEntity::Type>(entity.typ);

    switch (type)
    {
    case alt::IEntity::Type::PLAYER:
        return reinterpret_cast<alt::IPlayer *>(entity.ptr);

    case alt::IEntity::Type::VEHICLE:
        return reinterpret_cast<alt::IVehicle *>(entity.ptr);

    default:
        return nullptr;
    }
}

alt::IBaseObject *Go::Runtime::GetBaseObjectRef(Entity baseObject)
{
    auto type = static_cast<alt::IBaseObject::Type>(baseObject.typ);

    switch (type)
    {
    case alt::IBaseObject::Type::BLIP:
        return reinterpret_cast<alt::IBlip *>(baseObject.ptr);
    case alt::IBaseObject::Type::CHECKPOINT:
        return reinterpret_cast<alt::ICheckpoint *>(baseObject.ptr);
    case alt::IBaseObject::Type::COLSHAPE:
        return reinterpret_cast<alt::IColShape *>(baseObject.ptr);
    case alt::IBaseObject::Type::PLAYER:
        return reinterpret_cast<alt::IPlayer *>(baseObject.ptr);
    case alt::IBaseObject::Type::VEHICLE:
        return reinterpret_cast<alt::IVehicle *>(baseObject.ptr);
    case alt::IBaseObject::Type::VOICE_CHANNEL:
        return reinterpret_cast<alt::IVoiceChannel *>(baseObject.ptr);
    default:
        return nullptr;
    }
}

std::string Go::Runtime::PointerToString(void *p)
{
    auto i = reinterpret_cast<std::uintptr_t>(p);
    std::stringstream ss;
    ss << i;
    return ss.str();
}

alt::MValue Go::Runtime::DecodeMValue(rapidjson::Value &d)
{
    alt::ICore &core = alt::ICore::Instance();

    if (d.IsNull())
    {
        return core.CreateMValueNil();
    }

    if (d.IsBool())
    {
        return core.CreateMValueBool(d.GetBool());
    }

    if (d.IsUint64())
    {
        return core.CreateMValueUInt(d.GetUint64());
    }

    if (d.IsInt64())
    {
        return core.CreateMValueInt(d.GetInt64());
    }

    if (d.IsDouble())
    {
        return core.CreateMValueDouble(d.GetDouble());
    }

    if (d.IsString())
    {
        return core.CreateMValueString(std::string(d.GetString(), d.GetStringLength()));
    }

    if (d.IsObject())
    {
        std::cout << "is object" << std::endl;
        rapidjson::Value &$type = d["$type"];

        if ($type.IsInt())
        {
            std::cout << "is special mvalue" << std::endl;
            auto typ = static_cast<alt::IMValue::Type>($type.GetInt());

            if (typ == alt::IMValue::Type::BASE_OBJECT)
            {
                rapidjson::Value &id = d["id"];
                rapidjson::Value &type = d["type"];

                if (!id.IsUint() || !type.IsInt())
                {
                    core.LogError("Invalid BaseObject MValue");
                    return core.CreateMValueNone();
                }

                return core.CreateMValueBaseObject(core.GetBaseObjectByID(static_cast<alt::IBaseObject::Type>(type.GetInt()), id.GetUint()));
            }
            else if (typ == alt::IMValue::Type::BYTE_ARRAY)
            {
                rapidjson::Value &data = d["data"];

                // data.Empty() || 
                if (!data.IsString())
                {
                    core.LogError("Invalid ByteArray MValue");
                    return core.CreateMValueNone();
                }

                return core.CreateMValueByteArray(reinterpret_cast<const uint8_t *>(data.GetString()), static_cast<alt::Size>(data.GetStringLength()));
            }
            else if (typ == alt::IMValue::Type::RGBA)
            {
                rapidjson::Value &r = d["r"];
                rapidjson::Value &g = d["g"];
                rapidjson::Value &b = d["b"];
                rapidjson::Value &a = d["a"];

                if (!r.IsUint() || !g.IsUint() || !b.IsUint() || !a.IsUint())
                {
                    core.LogError("Invalid RGBA MValue");
                    return core.CreateMValueNone();
                }

                return core.CreateMValueRGBA(alt::RGBA(r.GetUint(), g.GetUint(), b.GetUint(), a.GetUint()));
            }
            else if (typ == alt::IMValue::Type::VECTOR2)
            {
                rapidjson::Value &x = d["x"];
                rapidjson::Value &y = d["y"];

                if (!x.IsFloat() || !y.IsFloat())
                {
                    core.LogError("Invalid Vector2 MValue");
                    return core.CreateMValueNone();
                }

                auto v2 = alt::Vector2f();
                v2[0] = x.GetFloat();
                v2[1] = y.GetFloat();
                return core.CreateMValueVector2(v2);
            }
            else if (typ == alt::IMValue::Type::VECTOR3)
            {
                rapidjson::Value &x = d["x"];
                rapidjson::Value &y = d["y"];
                rapidjson::Value &z = d["z"];

                if (!x.IsFloat() || !y.IsFloat() || z.IsFloat())
                {
                    core.LogError("Invalid Vector3 MValue");
                    return core.CreateMValueNone();
                }

                auto v3 = alt::Vector3f();
                v3[0] = x.GetFloat();
                v3[1] = y.GetFloat();
                v3[2] = z.GetFloat();
                return core.CreateMValueVector3(v3);
            }
            else if (typ == alt::IMValue::Type::FUNCTION)
            {
                rapidjson::Value &id = d["id"];
                rapidjson::Value &resourceName = d["resourceName"];

                if (!id.IsInt() || !resourceName.IsString())
                {
                    core.LogError("Invalid (exported) Function MValue");
                    return core.CreateMValueNone();
                }

                auto resource = dynamic_cast<Go::Resource *>(Go::Runtime::GetInstance()->GetResource(resourceName.GetString()));
                if (resource == nullptr)
                {
                    core.LogError("Unable to get resource; Failed to export Function MValue");
                    return core.CreateMValueNone();
                }

                auto goFunc = new Go::Function(resource->Module, id.GetInt());
                return core.CreateMValueFunction(goFunc);
            }
        }
        else
        {
            auto dict = core.CreateMValueDict();

            auto obj = d.GetObject();

            for (auto it = obj.begin(); it != obj.end(); it++)
            {
                dict->Set(it->name.GetString(), DecodeMValue(it->value));
            }

            return dict;
        }
    }

    if (d.IsArray())
    {
        auto arr = d.GetArray();
        auto list = alt::ICore::Instance().CreateMValueList();

        for (auto it = arr.begin(); it != arr.end(); it++)
        {
            list->Push(DecodeMValue(*it));
        }

        return list;
    }

    core.LogWarning("Unknown MValue type");

    return core.CreateMValueNone();
}

alt::MValue Go::Runtime::DecodeMValue(Array value)
{
    alt::ICore &core = alt::ICore::Instance();
    auto data = reinterpret_cast<const char *>(value.array);

    std::cout << "-------------------" << std::endl;
    std::cout << "decoding mvalue" << std::endl;
    std::cout << data << std::endl;

    rapidjson::Document d;
    d.Parse(data, value.size);
    // call GetType for IsObject check to work. dont ask why
    d.GetType();

    return DecodeMValue(d);
}

rapidjson::Document Go::Runtime::EncodeMValueToJSON(alt::MValueConst mValue)
{
    rapidjson::Document d;

    auto type = mValue->GetType();

    if (type == alt::IMValue::Type::NONE)
    {
        d.SetNull();
    }
    else if (type == alt::IMValue::Type::NIL)
    {
        d.SetNull();
    }
    if (type == alt::IMValue::Type::BOOL)
    {
        bool value = std::dynamic_pointer_cast<const alt::IMValueBool>(mValue)->Value();
        d.SetBool(value);
    }
    else if (type == alt::IMValue::Type::UINT)
    {
        uint64_t value = std::dynamic_pointer_cast<const alt::IMValueUInt>(mValue)->Value();
        d.SetUint64(value);
    }
    else if (type == alt::IMValue::Type::INT)
    {
        int64_t value = std::dynamic_pointer_cast<const alt::IMValueInt>(mValue)->Value();
        d.SetInt64(value);
    }
    else if (type == alt::IMValue::Type::DOUBLE)
    {
        double value = std::dynamic_pointer_cast<const alt::IMValueDouble>(mValue)->Value();
        d.SetDouble(value);
    }
    else if (type == alt::IMValue::Type::STRING)
    {
        std::string value = std::dynamic_pointer_cast<const alt::IMValueString>(mValue)->Value();
        d.SetString(value.c_str(), value.size());
    }
    else if (type == alt::IMValue::Type::BASE_OBJECT)
    {
        auto baseObject = std::dynamic_pointer_cast<const alt::IMValueBaseObject>(mValue)->Value();
        Entity data = GetBaseObject(baseObject.get());
        auto ptr = PointerToString(data.ptr);
        d.SetObject();
        d.AddMember(rapidjson::Value("$type"), rapidjson::Value(static_cast<int>(alt::IMValue::Type::BASE_OBJECT)), d.GetAllocator());
        d.AddMember(rapidjson::Value("id"), rapidjson::Value(data.id), d.GetAllocator());
        d.AddMember(rapidjson::Value("type"), rapidjson::Value(data.typ), d.GetAllocator());
        d.AddMember(rapidjson::Value("ptr"), rapidjson::Value(ptr.c_str(), ptr.size()), d.GetAllocator());
        d.AddMember(rapidjson::Value("model"), rapidjson::Value(data.model), d.GetAllocator());
    }
    else if (type == alt::IMValue::Type::RGBA)
    {
        alt::RGBA value = std::dynamic_pointer_cast<const alt::IMValueRGBA>(mValue)->Value();
        d.SetObject();
        d.AddMember(rapidjson::Value("$type"), rapidjson::Value(static_cast<int>(alt::IMValue::Type::RGBA)), d.GetAllocator());
        d.AddMember(rapidjson::Value("r"), rapidjson::Value(value.r), d.GetAllocator());
        d.AddMember(rapidjson::Value("g"), rapidjson::Value(value.g), d.GetAllocator());
        d.AddMember(rapidjson::Value("b"), rapidjson::Value(value.b), d.GetAllocator());
        d.AddMember(rapidjson::Value("a"), rapidjson::Value(value.a), d.GetAllocator());
    } else if (type == alt::IMValue::Type::FUNCTION) {
        auto value = std::dynamic_pointer_cast<const alt::IMValueFunction>(mValue);
        std::string ptr = PointerToString(const_cast<alt::IMValueFunction *>(value.get()));
        d.SetObject();
        auto alloc = d.GetAllocator();
        d.AddMember(rapidjson::Value("$type"), rapidjson::Value(static_cast<int>(alt::IMValue::Type::FUNCTION)), alloc);
        d.AddMember(rapidjson::Value("ptr"), rapidjson::Value(ptr.c_str(), ptr.size()), alloc);
    } else if (type == alt::IMValue::Type::VECTOR2) {
        auto value = std::dynamic_pointer_cast<const alt::IMValueVector2>(mValue)->Value();
        d.SetObject();
        auto alloc = d.GetAllocator();
        d.AddMember(rapidjson::Value("$type"), rapidjson::Value(static_cast<int>(alt::IMValue::Type::VECTOR2)), alloc);
        d.AddMember(rapidjson::Value("x"), rapidjson::Value(value[0]), alloc);
        d.AddMember(rapidjson::Value("y"), rapidjson::Value(value[1]), alloc);
    } else if (type == alt::IMValue::Type::VECTOR3) {
        auto value = std::dynamic_pointer_cast<const alt::IMValueVector3>(mValue)->Value();
        d.SetObject();
        auto alloc = d.GetAllocator();
        d.AddMember(rapidjson::Value("$type"), rapidjson::Value(static_cast<int>(alt::IMValue::Type::VECTOR3)), alloc);
        d.AddMember(rapidjson::Value("x"), rapidjson::Value(value[0]), alloc);
        d.AddMember(rapidjson::Value("y"), rapidjson::Value(value[1]), alloc);
        d.AddMember(rapidjson::Value("z"), rapidjson::Value(value[2]), alloc);
    } else if (type == alt::IMValue::Type::BYTE_ARRAY) {
        auto value = std::dynamic_pointer_cast<const alt::IMValueByteArray>(mValue);
        d.SetObject();
        auto alloc = d.GetAllocator();
        d.AddMember(rapidjson::Value("$type"), rapidjson::Value(static_cast<int>(alt::IMValue::Type::BYTE_ARRAY)), alloc);
        d.AddMember(rapidjson::Value("data"), rapidjson::Value(reinterpret_cast<const char *>(value->GetData()), value->GetSize()), alloc);
    } else if (type == alt::IMValue::Type::DICT) {
        auto dict = std::dynamic_pointer_cast<const alt::IMValueDict>(mValue);
        auto alloc = d.GetAllocator();
        d.SetObject();

        for (auto it = dict->Begin(); it != nullptr; it = dict->Next()) {
            std::string key = it->GetKey();
            d.AddMember(rapidjson::Value(key.c_str(), key.size()), EncodeMValueToJSON(it->GetValue()), alloc);
        }
    } else if (type == alt::IMValue::Type::LIST) {
        auto list = std::dynamic_pointer_cast<const alt::IMValueList>(mValue);
        auto alloc = d.GetAllocator();
        d.SetArray();

        for (alt::Size i = 0; i < list->GetSize(); i++) {
            d.PushBack(EncodeMValueToJSON(list->Get(i)), alloc);
        }
    }

    return d;
}

Array Go::Runtime::EncodeMValue(alt::MValueConst mValue)
{
    rapidjson::Document d = EncodeMValueToJSON(mValue);

    rapidjson::MemoryBuffer buf;
    rapidjson::Writer<rapidjson::MemoryBuffer> writer(buf);

    rapidjson::StringBuffer strBuf;
    rapidjson::Writer<rapidjson::StringBuffer> strWriter(strBuf);

    d.Accept(writer);
    d.Accept(strWriter);

    std::cout << "-------------------" << std::endl;
    std::cout << "encoded mvalue" << std::endl;
    std::cout << "membuf: " << buf.GetBuffer() << std::endl;
    std::cout << "strbuf: " << strBuf.GetString() << std::endl;
    std::cout << "-------------------" << std::endl;

    auto size = strBuf.GetSize();
    auto data = new char[size];

    Array arr;
    memcpy(data, strBuf.GetString(), size);
    arr.array = data;
    arr.size = size;

    std::cout << "copied" << std::endl;

    return arr;
}

Array Go::Runtime::EncodeMValueArgs(alt::MValueArgs args) {
    Array cbufs;
    cbufs.size = args.size();
    auto bufs = new Array[cbufs.size];
    for (auto i = 0; i < cbufs.size; i++) {
        bufs[i] = EncodeMValue(args[i]);
    }
    cbufs.array = bufs;
    return cbufs;
}

alt::MValueArgs Go::Runtime::DecodeMValueArgs(Array cbufs) {
    auto bufs = reinterpret_cast<Array *>(cbufs.array);
    alt::MValueArgs args;
    
    for (auto i = 0; i < cbufs.size; i++) {
        args.push_back(DecodeMValue(bufs[i]));
    }

    return args;
}

/*Array Go::Runtime::EncodeMValue(alt::MValue mValue)
{
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
    }
}*/

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