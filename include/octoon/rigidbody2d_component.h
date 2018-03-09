#ifndef OCTOON_RIGIDBODY2D_COMPONENT_H_
#define OCTOON_RIGIDBODY2D_COMPONENT_H_

#include <memory>
#include <vector>
#include <octoon/game_component.h>
#include <octoon/collider2d_component.h>
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

            void set_angular_velocity(float v) noexcept;
            float get_angular_velocity() const noexcept;

            void set_gravity_scale(float scale) noexcept;
            float get_gravity_scale() const noexcept;

            void set_mass(float m) noexcept;
            float get_mass() const noexcept;

            void set_sleep_mode(RigidbodySleepMode2D mode) noexcept;
            RigidbodySleepMode2D get_sleep_mode() const noexcept;

            void set_body_type(RigidbodyType2D type) noexcept;
            RigidbodyType2D get_body_type() const noexcept;

            void set_position(math::Vector2 pos) noexcept;
            math::Vector2 get_position() const noexcept;

            void set_rotation(float delta) noexcept;
            float get_rotation() const noexcept;

        private:
        	virtual void on_attach() except;
            virtual void on_detach() noexcept;

            virtual void on_attach_component(const GameComponentPtr& component) noexcept;
            virtual void on_detach_component(const GameComponentPtr& component) noexcept;

            void rigidbody_enter() noexcept;
            void rigidbody_exit() noexcept;
            void rigidbody_change() noexcept;

        private:
            b2Body* body;

            float angular_velocity;
            float gravity_scale; // The degree to which this object is affected by gravity.
            float mass; // Mass of the rigidbody.
            RigidbodySleepMode2D sleep_mode;
            math::Vector2 velocity;
            RigidbodyType2D body_type;
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