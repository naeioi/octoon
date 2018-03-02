#ifndef OCTOON_POLYGON_COLLIDER2D_COMPONENT_H_
#define OCTOON_POLYGON_COLLIDER2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/collider2d_component.h>
#include <octoon/math/math.h>

class b2Body;

namespace octoon
{
    class OCTOON_EXPORT PolygonCollider2D : public Collider2D
	{
        OctoonDeclareSubInterface(PolygonCollider2D, runtime::RttiInterface)
        public:
            PolygonCollider2D() noexcept;
            ~PolygonCollider2D();
            virtual GameComponentPtr clone() const noexcept;

            void set_auto_tiling(bool is_auto_tilling) noexcept;
            bool get_auto_tiling() const noexcept;

            void set_path_count(int n) noexcept;
            int get_path_count() const noexcept;

            void set_points(const math::Vector2Array& pts) noexcept;
            math::Vector2Array get_points() const noexcept;

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
            bool auto_tiling; // Determines whether the PolygonCollider2D's shape is automatically updated based on a SpriteRenderer's tiling properties.
            int path_count; // The number of paths in the polygon.
            math::Vector2Array points; // Corner points that define the collider's shape in local space.
    };
}


#endif // OCTOON_POLYGON_COLLIDER2D_COMPONENT_H_