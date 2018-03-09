#ifndef OCTOON_COLLIDER2D_COMPONENT_H_
#define OCTOON_COLLIDER2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/math/math.h>
#include <octoon/physics_material2d.h>


class b2Body;
class b2Fixture;

namespace octoon
{
    class OCTOON_EXPORT Collider2D : public GameComponent
	{
        OctoonDeclareSubInterface(Collider2D, GameComponent)
        public:
            Collider2D() noexcept;
            ~Collider2D();
            virtual GameComponentPtr clone() const noexcept;

            void set_bounciness(float b) noexcept;
            float get_bounciness() const noexcept;

            void set_density(float d) noexcept;
            float get_density() const noexcept;

            void set_friction(float f) noexcept;
            float get_friction() const noexcept;

        protected:
            virtual void on_collision_change() = 0;
            virtual void on_collision_enter() = 0;
            virtual void on_collision_exit() = 0;
            virtual void on_collision_stay() = 0;
        
        protected:
            b2Fixture *collider;

        private:
            float bounciness; // Get the bounciness used by the collider.
            float density; // The density of the collider used to calculate its mass (when auto mass is enabled).
            float friction; // Get the friction used by the collider.
            std::shared_ptr<PhysicsMaterial2D> shared_material; // The PhysicsMaterial2D that is applied to this collider.
            friend class Rigidbody2D;
    };
}


#endif // OCTOON_COLLIDER2D_COMPONENT_H_