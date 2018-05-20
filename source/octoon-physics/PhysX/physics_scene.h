#ifndef OCTOON_PHYSX_SCENE_H_
#define OCTOON_PHYSX_SCENE_H_

#include <octoon/runtime/platform.h>
#include <octoon/runtime/rtti_macros.h>
#include <octoon/runtime/rtti_interface.h>
#include <octoon/math/math.h>

#include <octoon/physics/physics_scene.h>

namespace octoon
{
    namespace physics
    {
        class OCTOON_EXPORT PhysxScene : public PhysicsScene
        {
            OctoonDeclareSubClass(PhysxScene, PhysicsScene)
        public:
            PhysxScene() noexcept;
            virtual ~PhysxScene() noexcept;

            virtual void setGravity(const math::Vector3& gravity) noexcept;
            virtual math::Vector3 getGravity() const noexcept;

            virtual void simulation(float delta) noexcept;
        protected:
            
        };
    }
}

#endif //OCTOON_PHYSX_SCENE_H_