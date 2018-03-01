#ifndef OCTOON_CIRCLE_COLLIDER2D_COMPONENT_H_
#define OCTOON_CIRCLE_COLLIDER2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/math/math.h>

class b2Body;

namespace octoon
{
    class OCTOON_EXPORT CircleCollider2D : public Collider2D
	{
        OctoonDeclareSubInterface(CircleCollider2D, runtime::RttiInterface)
        public:
            CircleCollider2D() noexcept;
            ~CircleCollider2D();
            virtual GameComponentPtr clone() const noexcept;

            void set_radius(float r) noexcept;
            float get_radius() const noexcept;

        protected:
            virtual void on_collision_change() noexcept;
            virtual void on_collision_enter() noexcept;
            virtual void on_collision_exit() noexcept;
            virtual void on_collision_stay() noexcept;

        private:
            virtual void on_attach() except;
            virtual void on_detach() noexcept;

            virtual void on_attach_component(const GameComponentPtr& component) except;
            virtual void on_detach_component(const GameComponentPtr& component) noexcept;

        private:
            bool is_registered;
            float radius;
    };
}


#endif // OCTOON_CIRCLE_COLLIDER2D_COMPONENT_H_