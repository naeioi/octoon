#ifndef OCTOON_PHYSICS_SYSTEM_H_
#define OCTOON_PHYSICS_SYSTEM_H_

#include <octoon/runtime/platform.h>
#include <octoon/runtime/rtti_macros.h>
#include <octoon/runtime/rtti_interface.h>
#include <octoon/math/math.h>

namespace octoon
{
    namespace physics
    {
        class OCTOON_EXPORT PhysicsSystem : public runtime::RttiInterface
        {
            OctoonDeclareSubInterface(PhysicsSystem, runtime::RttiInterface)
        public:
            PhysicsSystem() noexcept;
            virtual ~PhysicsSystem() noexcept;
        };
    }
}

#endif //OCTOON_PHYSICS_SYSTEM_H_