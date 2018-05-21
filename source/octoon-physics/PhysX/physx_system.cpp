#include <octoon/physics/Physx/physics_system.h>

namespace octoon
{
    namespace physics
    {
        OctoonImplementSubInterface(PhysxSystem, PhysicsSystem, "PhysxSystem")
        PhysxSystem::PhysxSystem() except
            :defaultErrorCallback(std::make_unique<physx::PxDefaultErrorCallback>()),
            defaultAllocatorCallback(std::make_unique<physx::PxDefaultAllocator>()),
            foundation(nullptr), pvd(nullptr),
            physics(nullptr), cooking(nullptr),
            dispatcher(nullptr), physicsScene(nullptr),
            accumulator(0.0f), stepSize(1.0f / 60.0f)
        {

        }
        PhysxSystem::~PhysxSystem() noexcept
        {

        }

        void PhysxSystem::setGravity(const math::Vector3& gravity) noexcept
        {

        }
        math::Vector3 PhysxSystem::getGravity() const noexcept
        {

        }

        void PhysxSystem::simulation(float delta) noexcept
        {
            
        }
    }
}