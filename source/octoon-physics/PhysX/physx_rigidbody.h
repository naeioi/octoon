#ifndef OCTOON_PHYSX_RIGIDBODY_H_
#define OCTOON_PHYSX_RIGIDBODY_H_

#include <octoon/runtime/platform.h>
#include <octoon/runtime/rtti_macros.h>
#include <octoon/runtime/rtti_interface.h>
#include <octoon/math/math.h>

#include <octoon/physics/physics_rigidbody.h>

namespace octoon
{
    namespace physics
    {
        class OCTOON_EXPORT PhysxRigidbody : public PhysicsRigidbody
        {
            OctoonDeclareSubInterface(PhysxRigidbody, PhysicsRigidbody)
        public:
            PhysxRigidbody() noexcept;
            virtual ~PhysxRigidbody() noexcept;
        };
    }
}

#endif //OCTOON_PHYSX_RIGIDBODY_H_