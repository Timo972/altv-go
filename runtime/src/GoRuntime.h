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

        static CBaseObject GetCBaseObject(alt::IEntity* entity);
        static CBaseObject GetCBaseObject(alt::IBaseObject* baseObject);
        static void GetCBaseObject(alt::IEntity* entity, CBaseObject* out);
        static void GetCBaseObject(alt::IBaseObject* baseObject, CBaseObject* out);
        static alt::IBaseObject *GetBaseObject(CBaseObject* baseObject);
        static alt::IEntity *GetEntity(CBaseObject* baseObject);

        static CConnectionInfo GetConnectionInfo(alt::IConnectionInfo* info);
        
        static CArray CreateBoneArray(std::vector<alt::BoneInfo> bones);

        // const char *SerializeConfig(alt::config::Node rootNode);

        static CArray CreateStringArray(std::vector<std::string> set) {
            CArray arr;
            arr.size = set.size();
            auto cset = new const char *[arr.size];

            for (uint64_t i = 0; i < set.size(); i++) {
                cset[i] = set[i].c_str();
            }

            arr.ptr = cset;

            return arr;
        }

        template<class ClassInstance>
        static CArray CreateCBaseObjectArray(std::vector<ClassInstance*> objects) {
            CArray arr;
            arr.size = objects.size();

            // TODO: test if this works
            auto entities = new CBaseObject*[arr.size];

            for (uint64_t i = 0; i < arr.size; i++) {
                GetCBaseObject(objects[i], entities[i]);
            }

            arr.ptr = entities;
            return arr;
        }

        /*template<typename Type, typename TargetType>
        static CArray CreateArray(alt::Array<Type> altArr) {
            CArray arr;
            arr.size = altArr.GetSize();
            auto cArray = new TargetType[arr.size];

            for (uint64_t i = 0; i < arr.size; i++) {
                cArray[i] = static_cast<TargetType>(altArr[i]);
            }

            arr.ptr = cArray;

            return arr;
        }*/

        template<typename Type, typename TargetType>
        static CArray CreateArray(std::unordered_set<Type> set) {
            CArray arr;
            arr.size = set.size();
            auto cset = new TargetType[arr.size];

            uint64_t i = 0;
            for (const auto &item: set) {
                cset[i] = item;
                i++;
            }

            arr.ptr = cset;

            return arr;
        }

        template<typename Type, typename TargetType>
        static CArray CreateArray(std::vector<Type> set) {
            CArray arr;
            arr.size = set.size();
            auto cset = new TargetType[arr.size];

            for (uint64_t i = 0; i < set.size(); i++) {
                cset[i] = static_cast<TargetType>(set[i]);
            }

            arr.ptr = cset;

            return arr;
        }

        static std::string PointerToString(void* p);

        // MValue to JSON and back
        static alt::MValue DecodeMValue(CArray data);
        static alt::MValue DecodeMValue(rapidjson::Value& value);

        static rapidjson::Document EncodeMValueToJSON(alt::MValueConst value);
        static CArray EncodeMValue(alt::MValueConst value);
        // static CArray EncodeMValue(alt::MValue value);

        static alt::MValueArgs DecodeMValueArgs(CArray args);
        static CArray EncodeMValueArgs(alt::MValueArgs args);

        static Go::Runtime *GetInstance();
    };
}