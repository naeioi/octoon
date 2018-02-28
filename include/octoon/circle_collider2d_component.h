#ifndef OCTOON_CIRCLE_COLLIDER2D_COMPONENT_H_
#define OCTOON_CIRCLE_COLLIDER2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/math/math.h>

class b2Body;

namespace octoon
{
    class OCTOON_EXPORT CircleCollider2D : public GameComponent
	{
        OctoonDeclareSubInterface(CircleCollider2D, runtime::RttiInterface)
        public:
            CircleCollider2D() noexcept;
            ~CircleCollider2D();
            virtual GameComponentPtr clone() const noexcept;

            void set_radius(float r) noexcept;
            float get_radius() const noexcept;

        private:
            float radius;
    };
}


#endif // OCTOON_CIRCLE_COLLIDER2D_COMPONENT_H_