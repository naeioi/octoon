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
        OctoonDeclareSubClass(BoxCollider2D, Collider2D)
        public:
            BoxCollider2D() noexcept;
            ~BoxCollider2D();
            virtual GameComponentPtr clone() const noexcept;

            void setAutoTiling(bool isAutoTilling) noexcept;
            bool getAutoTiling() const noexcept;

            void setEdgeRadius(float r) noexcept;
            float getEdgeRadius() const noexcept;

            void setSize(const math::Vector2& s) noexcept;
            math::Vector2 getSize() const noexcept;

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
            bool autoTiling; //Determines whether the BoxCollider2D's shape is automatically updated based on a SpriteRenderer's tiling properties.
            float edgeRadius; //Controls the radius of all edges created by the collider.
            math::Vector2 size; //The width and height of the rectangle.
    };
}


#endif // OCTOON_BOX_COLLIDER2D_COMPONENT_H_