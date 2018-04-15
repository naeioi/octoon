#ifndef OCTOON_PHYSICS_MATERIAL2D_COMPONENT_H_
#define OCTOON_PHYSICS_MATERIAL2D_COMPONENT_H_

#include <memory>
#include <octoon/gameComponent.h>
#include <octoon/math/math.h>


class b2Body;
class b2Fixture;

namespace octoon
{
    class OCTOON_EXPORT PhysicsMaterial2D : public runtime::RttiInterface
	{
        OctoonDeclareSubInterface(PhysicsMaterial2D, runtime::RttiInterface)
        public:
            PhysicsMaterial2D() noexcept;
            ~PhysicsMaterial2D();

            void setBounciness(float b) noexcept;
            float getBounciness() const noexcept;

            void setFriction(float f) noexcept;
            float getFriction() const noexcept;
        
        protected:
            float bounciness; // The degree of elasticity during collisions.
            float friction; // Coefficient of friction.
        private:
            friend class Rigidbody2D;
    };
}


#endif // OCTOON_PHYSICS_MATERIAL2D_COMPONENT_H_