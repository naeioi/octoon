#ifndef OCTOON_RIGIDBODY2D_COMPONENT_H_
#define OCTOON_RIGIDBODY2D_COMPONENT_H_

#include <memory>
#include <vector>
#include <octoon/gameComponent.h>
#include <octoon/collider2dComponent.h>
#include <octoon/math/math.h>
#include <octoon/runtime/singleton.h>

class b2Body;

namespace octoon
{
    enum class RigidbodyType2D: int
    {
        Static = 0,
        Dynamic = 1,
        Kinematic = 2
    };

    enum class RigidbodySleepMode2D:int
    {
        NeverSleep, //Rigidbody2D never automatically sleeps.
        StartAwake, //Rigidbody2D is initially awake.
        StartAsleep, //Rigidbody2D is initially asleep.
    };

    class OCTOON_EXPORT Rigidbody2D final : public GameComponent
	{
        OctoonDeclareSubInterface(Rigidbody2D, runtime::RttiInterface)
        public:
            Rigidbody2D() noexcept;
            ~Rigidbody2D();
            virtual GameComponentPtr clone() const noexcept;

            void setAngularVelocity(float v) noexcept;
            float getAngularVelocity() const noexcept;

            void setGravityScale(float scale) noexcept;
            float getGravityScale() const noexcept;

            void setMass(float m) noexcept;
            float getMass() const noexcept;

            void setSleepMode(RigidbodySleepMode2D mode) noexcept;
            RigidbodySleepMode2D getSleepMode() const noexcept;

            void setBodyType(RigidbodyType2D type) noexcept;
            RigidbodyType2D getBodyType() const noexcept;

            void setPosition(math::Vector2 pos) noexcept;
            math::Vector2 getPosition() const noexcept;

            void setRotation(float delta) noexcept;
            float getRotation() const noexcept;

        private:
        	virtual void onAttach() except;
            virtual void onDetach() noexcept;

            virtual void onAttachComponent(const GameComponentPtr& component) noexcept;
            virtual void onDetachComponent(const GameComponentPtr& component) noexcept;

            void rigidbodyEnter() noexcept;
            void rigidbodyExit() noexcept;
            void rigidbodyChange() noexcept;

        private:
            b2Body* body;

            float angularVelocity;
            float gravityScale; // The degree to which this object is affected by gravity.
            float mass; // Mass of the rigidbody.
            RigidbodySleepMode2D sleepMode;
            math::Vector2 velocity;
            RigidbodyType2D bodyType;
            math::Vector2 position;
            float rotation;
        
            friend class Collider2D;
            friend class CircleCollider2D;
            friend class BoxCollider2D;
            friend class PolygonCollider2D;
            friend class EdgeCollider2D;
    };
}


#endif // OCTOON_RIGIDBODY2D_COMPONENT_H_