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

            void setAutoTiling(bool isAutoTilling) noexcept;
            bool getAutoTiling() const noexcept;

            void setPathCount(int n) noexcept;
            int getPathCount() const noexcept;

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
            bool autoTiling; // Determines whether the PolygonCollider2D's shape is automatically updated based on a SpriteRenderer's tiling properties.
            int pathCount; // The number of paths in the polygon.
            math::Vector2Array points; // Corner points that define the collider's shape in local space.
    };
}


#endif // OCTOON_POLYGON_COLLIDER2D_COMPONENT_H_