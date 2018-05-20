#include <octoon/physics/physics_system.h>

namespace octoon
{
    namespace physics
    {
        OctoonImplementSubInterface(PhysicsSystem, runtime::RttiInterface, "PhysicsSystem")
        PhysicsSystem::PhysicsSystem() noexcept
        {

        }
        PhysicsSystem::~PhysicsSystem() noexcept
        {

        }
    }
}