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
        OctoonDeclareSubClass(EdgeCollider2D, Collider2D)
        public:
            EdgeCollider2D() noexcept;
            ~EdgeCollider2D();
            virtual GameComponentPtr clone() const noexcept;

            void setEdgeCount(int n) noexcept;
            int getEdgeCount() const noexcept;

            void setPointCount(int n) noexcept;
            int getPointCount() const noexcept;

            void setEdgeRadius(float r) noexcept;
            float getEdgeRadius() const noexcept;

            void setPoints(const math::Vector2Array& pts) noexcept;
            math::Vector2Array getPoints() const noexcept;

        protected:
            virtual void onCollisionChange() noexcept;
            virtual void onCollisionEnter() noexcept;
            virtual void onCollisionExit() noexcept;
            virtual void onCollisionStay() noexcept;

        private:
            virtual void onAttach() except;
            virtual void onDetach() noexcept;

            virtual void onAttachComponent(const GameComponentPtr& component) except;
            virtual void onDetachComponent(const GameComponentPtr& component) noexcept;

        private:
            bool isRegistered;
            
            int edgeCount; // Gets the number of edges.
            float edgeRadius; // Controls the radius of all edges created by the collider.
            int pointCount; // Gets the number of points.
            math::Vector2Array points; // Get or set the points defining multiple continuous edges.
    };
}


#endif // OCTOON_EDGE_COLLIDER2D_COMPONENT_H_