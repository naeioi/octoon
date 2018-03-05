#ifndef OCTOON_COLLIDER2D_COMPONENT_H_
#define OCTOON_COLLIDER2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/math/math.h>


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

        protected:
            virtual void on_collision_change() = 0;
            virtual void on_collision_enter() = 0;
            virtual void on_collision_exit() = 0;
            virtual void on_collision_stay() = 0;
        
        protected:
            b2Fixture *collider;

        private:

            friend class Rigidbody2D;
    };
}


#endif // OCTOON_COLLIDER2D_COMPONENT_H_