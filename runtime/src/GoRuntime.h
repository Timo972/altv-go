#pragma once

#include <iostream>
#include <map>
#include <vector>

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

        template<class ClassInstance>
        static Array CreateEntityArray(std::vector<ClassInstance*> objects) {
            Array arr;
            arr.size = objects.size();

#ifdef _WIN32
            auto playerRefs = new Entity[arr.size];
#else
            Entity playerRefs[arr.size];
#endif
            for (uint64_t i = 0; i < arr.size; i++) {
                playerRefs[i] = GetBaseObject(objects[i]);
            }

            arr.array = playerRefs;

            return arr;
        }

        template<typename Type, typename TargetType>
        static Array CreateArray(alt::Array<Type> altArr) {
            Array arr;
            arr.size = altArr.GetSize();

#ifdef _WIN32
            auto cArray = new TargetType[arr.size];
#else
            TargetType cArray[arr.size];
#endif
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
#ifdef _WIN32
            auto cset = new TargetType[arr.size];
#else
            TargetType cset[arr.size];
#endif
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
#ifdef _WIN32
            auto cset = new TargetType[arr.size];
#else
            TargetType cset[arr.size];
#endif
            for (uint64_t i = 0; i < set.size(); i++) {
                cset[i] = static_cast<TargetType>(set[i]);
            }

            arr.array = cset;

            return arr;
        }

        static std::string PointerToString(void* p);

        static alt::MValue GoToMValue(GoValue value);
        static void MValueToGo(alt::MValue value, GoValue * out);
        static void MValueToGo(alt::MValueConst value, GoValue * out);

        static alt::MValueArgs GoToMValueArgs(GoValueArgs args);
        static GoValueArgs MValueArgsToGo(alt::MValueArgs args);

        static Go::Runtime *GetInstance();
    };
}