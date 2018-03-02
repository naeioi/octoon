#ifndef OCTOON_BOX_COLLIDER2D_COMPONENT_H_
#define OCTOON_BOX_COLLIDER2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/collider2d_component.h>
#include <octoon/math/math.h>

class b2Body;

namespace octoon
{
    class OCTOON_EXPORT BoxCollider2D : public Collider2D
	{
        OctoonDeclareSubInterface(BoxCollider2D, runtime::RttiInterface)
        public:
            BoxCollider2D() noexcept;
            ~BoxCollider2D();
            virtual GameComponentPtr clone() const noexcept;

            void set_auto_tiling(bool is_auyo_tilling) noexcept;
            bool get_auto_tiling() const noexcept;

            void set_edge_radius(float r) noexcept;
            float get_edge_radius() const noexcept;

            void set_size(const math::Vector2& s) noexcept;
            math::Vector2 get_size() const noexcept;

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
            bool auto_tiling; //Determines whether the BoxCollider2D's shape is automatically updated based on a SpriteRenderer's tiling properties.
            float edge_radius; //Controls the radius of all edges created by the collider.
            math::Vector2 size; //The width and height of the rectangle.
    };
}


#endif // OCTOON_BOX_COLLIDER2D_COMPONENT_H_