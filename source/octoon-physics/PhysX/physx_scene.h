#ifndef OCTOON_PHYSX_SCENE_H_
#define OCTOON_PHYSX_SCENE_H_

#include <memory>

#include <octoon/runtime/platform.h>
#include <octoon/runtime/rtti_macros.h>
#include <octoon/runtime/rtti_interface.h>
#include <octoon/math/math.h>

#include <octoon/physics/physics_scene.h>

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
        class OCTOON_EXPORT PhysxScene : public PhysicsScene
        {
            OctoonDeclareSubClass(PhysxScene, PhysicsScene)
        public:
            PhysxScene() except;
            virtual ~PhysxScene() noexcept;

            virtual void setGravity(const math::Vector3& gravity) noexcept;
            virtual math::Vector3 getGravity() const noexcept;

            virtual void simulation(float delta) noexcept;

            virtual void addPhysicsRigidbody(PhysicsRigidbodyPtr rigidbody) noexcept;

            void setPhysicsScene(physx::PxScene* scene) noexcept;
            void setAccumulator(float a) noexcept;
            void setStepSize(float s) noexcept;
        protected:
            physx::PxScene* physicsScene;

            float accumulator;
            float stepSize;
        };
    }
}

#endif //OCTOON_PHYSX_SCENE_H_