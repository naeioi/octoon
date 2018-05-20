#include <octoon/physics/Physx/physics_scene.h>

namespace octoon
{
    namespace physics
    {
        OctoonImplementSubInterface(PhysxScene, PhysicsScene, "PhysxScene")
        PhysxScene::PhysxScene() except
            :defaultErrorCallback(std::make_unique<physx::PxDefaultErrorCallback>()),
            defaultAllocatorCallback(std::make_unique<physx::PxDefaultAllocator>()),
            foundation(nullptr), pvd(nullptr),
            physics(nullptr), cooking(nullptr),
            dispatcher(nullptr), physicsScene(nullptr),
            accumulator(0.0f), stepSize(1.0f / 60.0f)
        {

        }
        PhysxScene::~PhysxScene() noexcept
        {

        }

        void PhysxScene::setGravity(const math::Vector3& gravity) noexcept
        {

        }
        math::Vector3 PhysxScene::getGravity() const noexcept
        {

        }

        void PhysxScene::simulation(float delta) noexcept
        {
            
        }
    }
}