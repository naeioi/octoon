#ifndef OCTOON_PHYSX_SYSTEM_H_
#define OCTOON_PHYSX_SYSTEM_H_

#include <memory>

#include <octoon/runtime/platform.h>
#include <octoon/runtime/rtti_macros.h>
#include <octoon/runtime/rtti_interface.h>
#include <octoon/math/math.h>

#include <octoon/physics/physics_system.h>

namespace physx
{
	class PxDefaultErrorCallback;
	class PxDefaultAllocator;
	class PxFoundation;
	class PxPvd;
	class PxPhysics;
	class PxCooking;
	class PxDefaultCpuDispatcher;
	class PxScene;
}


namespace octoon
{
    namespace physics
    {
        class OCTOON_EXPORT PhysxSystem : public PhysicsSystem
        {
            OctoonDeclareSubClass(PhysxSystem, PhysicsSystem)
        public:
            PhysxSystem() except;
            virtual PhysicsScenePtr createScene() except;
            virtual PhysicsRigidbodyPtr createRigidBody() except;
            virtual ~PhysxSystem() noexcept;
        protected:
            bool recordMemoryAllocations = true;

            std::unique_ptr<physx::PxDefaultErrorCallback> defaultErrorCallback;
            std::unique_ptr<physx::PxDefaultAllocator> defaultAllocatorCallback;
            physx::PxFoundation* foundation;
            physx::PxPvd* pvd;
            physx::PxPhysics* physics;
            physx::PxCooking* cooking;
            physx::PxDefaultCpuDispatcher* dispatcher;
        };
    }
}

#endif //OCTOON_PHYSX_SYSTEM_H_