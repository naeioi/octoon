#ifndef OCTOON_PHYSICS_SCENE_H_
#define OCTOON_PHYSICS_SCENE_H_

#include <octoon/runtime/platform.h>
#include <octoon/runtime/rtti_macros.h>
#include <octoon/runtime/rtti_interface.h>
#include <octoon/math/math.h>

namespace octoon
{
    namespace physics
    {
        class OCTOON_EXPORT PhysicsScene : public runtime::RttiInterface
        {
            OctoonDeclareSubInterface(PhysicsScene, runtime::RttiInterface)
        public:
            PhysicsScene() noexcept;
            virtual ~PhysicsScene() noexcept;

            virtual void setGravity(const math::Vector3& gravity) noexcept = 0;
            virtual math::Vector3 getGravity() const noexcept = 0;

            virtual void simulation(float delta) noexcept = 0;
        };
    }
}

#endif //OCTOON_PHYSICS_SCENE_H_