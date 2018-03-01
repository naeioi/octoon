#ifndef OCTOON_RIGIDBODY2D_COMPONENT_H_
#define OCTOON_RIGIDBODY2D_COMPONENT_H_

#include <memory>
#include <vector>
#include <octoon/game_component.h>
#include <octoon/collider2d_component.h>
#include <octoon/circle_collider2d_component.h>
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

    class OCTOON_EXPORT Rigidbody2D final : public GameComponent
	{
        OctoonDeclareSubInterface(Rigidbody2D, runtime::RttiInterface)
        public:
            Rigidbody2D() noexcept;
            ~Rigidbody2D();
            virtual GameComponentPtr clone() const noexcept;

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

            void build_rigibody() noexcept;

        private:
            b2Body* body;
            RigidbodyType2D body_type;
            math::Vector2 position;
            float rotation;
        
            friend class Collider2D;
            friend class CircleCollider2D;
    };
}


#endif // OCTOON_RIGIDBODY2D_COMPONENT_H_