#pragma once

#include <iostream>
#include <map>
#include <vector>

#include "rapidjson/document.h"
#include "Main.h"

namespace Go {
    class Runtime : public alt::IScriptRuntime {
    private:
        static Runtime *Instance;
        std::vector<std::map<std::string, alt::IResource::Impl *>> _resources;
    public:
        Runtime() = default;

        alt::IResource::Impl *CreateImpl(alt::IResource *resource) override;

        void DestroyImpl(alt::IResource::Impl *impl) override;

        void OnDispose() override;

        alt::IResource::Impl *GetResource(const std::string &name);

        static Entity GetEntity(alt::IEntity* entity);
        static Entity GetBaseObject(alt::IBaseObject* baseObject);

        static alt::IEntity *GetEntityRef(Entity entity);
        static alt::IBaseObject *GetBaseObjectRef(Entity baseObject);

        static ConnectionInfo GetConnectionInfo(alt::IConnectionInfo* info);
        
        static Array CreateBoneArray(std::vector<alt::BoneInfo> bones);

        // const char *SerializeConfig(alt::config::Node rootNode);

        static Array CreateStringArray(std::vector<std::string> set) {
            Array arr;
            arr.size = set.size();
            auto cset = new const char *[arr.size];

            for (uint64_t i = 0; i < set.size(); i++) {
                cset[i] = set[i].c_str();
            }

            arr.array = cset;

            return arr;
        }

        template<class ClassInstance>
        static Array CreateEntityArray(std::vector<ClassInstance*> objects) {
            Array arr;
            arr.size = objects.size();

            auto entities = new Entity[arr.size];

            for (uint64_t i = 0; i < arr.size; i++) {
                entities[i] = GetBaseObject(objects[i]);
            }

            arr.array = entities;
            return arr;
        }

        template<typename Type, typename TargetType>
        static Array CreateArray(alt::Array<Type> altArr) {
            Array arr;
            arr.size = altArr.GetSize();
            auto cArray = new TargetType[arr.size];

            for (uint64_t i = 0; i < arr.size; i++) {
                cArray[i] = static_cast<TargetType>(altArr[i]);
            }

            arr.array = cArray;

            return arr;
        }

        template<typename Type, typename TargetType>
        static Array CreateArray(std::unordered_set<Type> set) {
            Array arr;
            arr.size = set.size();
            auto cset = new TargetType[arr.size];

            uint64_t i = 0;
            for (const auto &item: set) {
                cset[i] = item;
                i++;
            }

            arr.array = cset;

            return arr;
        }

        template<typename Type, typename TargetType>
        static Array CreateArray(std::vector<Type> set) {
            Array arr;
            arr.size = set.size();
            auto cset = new TargetType[arr.size];

            for (uint64_t i = 0; i < set.size(); i++) {
                cset[i] = static_cast<TargetType>(set[i]);
            }

            arr.array = cset;

            return arr;
        }

        static std::string PointerToString(void* p);

        // MValue to JSON and back
        static alt::MValue DecodeMValue(Array data);
        static alt::MValue DecodeMValue(rapidjson::Value& value);

        static rapidjson::Document EncodeMValueToJSON(alt::MValueConst value);
        static Array EncodeMValue(alt::MValueConst value);
        // static Array EncodeMValue(alt::MValue value);

        static alt::MValueArgs DecodeMValueArgs(Array args);
        static Array EncodeMValueArgs(alt::MValueArgs args);

        static Go::Runtime *GetInstance();
    };
}