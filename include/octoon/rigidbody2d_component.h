#ifndef OCTOON_RIGIDBODY2D_COMPONENT_H_
#define OCTOON_RIGIDBODY2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/math/math.h>

class b2Body;

namespace octoon
{
    enum class RigidbodyType2D: int
    {
        Static = 0,
        Dynamic = 1,
        Kinematic = 2
    };

    class OCTOON_EXPORT Rigidbody2DComponent final : public GameComponent
	{
        public:
            Rigidbody2DComponent() noexcept;
            ~Rigidbody2DComponent();
            virtual GameComponentPtr clone() const noexcept;

            void set_body_type(RigidbodyType2D type);
            RigidbodyType2D get_body_type();

        private:
        	virtual void on_activate() noexcept;
            virtual void on_deactivate() noexcept;

            virtual void on_attach_component(const GameComponentPtr& component) noexcept;
            virtual void on_detach_component(const GameComponentPtr& component) noexcept;

            virtual void on_collision_change() noexcept;
            virtual void on_collision_enter() noexcept;
            virtual void on_collision_exit() noexcept;
            virtual void on_collision_stay() noexcept;

            void build_rigibody() noexcept;

        private:
            std::unique_ptr<b2Body> body;
            RigidbodyType2D body_type;
    };
}


#endif // OCTOON_RIGIDBODY2D_COMPONENT_H_