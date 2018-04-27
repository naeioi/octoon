#ifndef OCTOON_CIRCLE_COLLIDER2D_COMPONENT_H_
#define OCTOON_CIRCLE_COLLIDER2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/collider2d_component.h>
#include <octoon/math/math.h>

class b2Body;

namespace octoon
{
    class OCTOON_EXPORT CircleCollider2D : public Collider2D
	{
        OctoonDeclareSubClass(CircleCollider2D, Collider2D)
        public:
            CircleCollider2D() noexcept;
            ~CircleCollider2D();
            virtual GameComponentPtr clone() const noexcept;

            void setRadius(float r) noexcept;
            float getRadius() const noexcept;

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
            float radius;
    };
}


#endif // OCTOON_CIRCLE_COLLIDER2D_COMPONENT_H_