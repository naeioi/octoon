#ifndef OCTOON_PHYSICS_SYSTEM_H_
#define OCTOON_PHYSICS_SYSTEM_H_

#include <octoon/runtime/platform.h>
#include <octoon/runtime/rtti_macros.h>
#include <octoon/runtime/rtti_interface.h>
#include <octoon/math/math.h>

#include <octoon/physics/physics_scene.h>
#include <octoon/physics/physics_rigidbody.h>

namespace octoon
{
    namespace physics
    {
        class OCTOON_EXPORT PhysicsSystem : public runtime::RttiInterface
        {
            OctoonDeclareSubInterface(PhysicsSystem, runtime::RttiInterface)
        public:
            PhysicsSystem() noexcept;
            virtual PhysicsScene * createScene() except;
            virtual ~PhysicsSystem() noexcept;

            virtual PhysicsScene * createScene() except = 0;
            virtual void releaseScene(PhysicsScene * scene) except = 0;
            virtual PhysicsRigidbody * createRigidbody() except = 0;
            virtual void releaseRigidbody(PhysicsRigidbody * rigidbody) except = 0;
        };
    }
}

#endif //OCTOON_PHYSICS_SYSTEM_H_