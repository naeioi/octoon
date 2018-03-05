#ifndef OCTOON_EDGE_COLLIDER2D_COMPONENT_H_
#define OCTOON_EDGE_COLLIDER2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/collider2d_component.h>
#include <octoon/math/math.h>

class b2Body;

namespace octoon
{
    class OCTOON_EXPORT EdgeCollider2D : public Collider2D
	{
        OctoonDeclareSubInterface(EdgeCollider2D, Collider2D)
        public:
            EdgeCollider2D() noexcept;
            ~EdgeCollider2D();
            virtual GameComponentPtr clone() const noexcept;

            void set_edge_count(int n) noexcept;
            int get_edge_count() const noexcept;

            void set_point_count(int n) noexcept;
            int get_point_count() const noexcept;

            void set_edge_radius(float r) noexcept;
            float get_edge_radius() const noexcept;

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
            
            int edge_count; // Gets the number of edges.
            float edge_radius; // Controls the radius of all edges created by the collider.
            int point_count; // Gets the number of points.
            math::Vector2Array points; // Get or set the points defining multiple continuous edges.
    };
}


#endif // OCTOON_EDGE_COLLIDER2D_COMPONENT_H_