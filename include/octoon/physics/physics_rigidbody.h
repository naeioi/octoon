#ifndef OCTOON_PHYSICS_RIGIDBODY_H_
#define OCTOON_PHYSICS_RIGIDBODY_H_

#include <octoon/runtime/platform.h>
#include <octoon/runtime/rtti_macros.h>
#include <octoon/runtime/rtti_interface.h>
#include <octoon/math/math.h>

namespace octoon
{
    namespace physics
    {
        class OCTOON_EXPORT PhysicsRigidbody : public runtime::RttiInterface
        {
            OctoonDeclareSubInterface(PhysicsRigidbody, runtime::RttiInterface)
        public:
            PhysicsRigidbody() noexcept;
            virtual ~PhysicsRigidbody() noexcept;
        };
    }
}

#endif //OCTOON_PHYSICS_RIGIDBODY_H_