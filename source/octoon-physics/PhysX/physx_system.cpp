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
            dispatcher(nullptr)
        {

        }
        PhysxSystem::~PhysxSystem() noexcept
        {

        }
    }
}