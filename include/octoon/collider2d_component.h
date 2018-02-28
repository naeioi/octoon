#ifndef OCTOON_COLLIDER2D_COMPONENT_H_
#define OCTOON_COLLIDER2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/math/math.h>

class b2Body;

namespace octoon
{
    class OCTOON_EXPORT Collider2DComponent final : public GameComponent
	{
        public:
            Collider2DComponent() noexcept;
            ~Collider2DComponent();
            virtual GameComponentPtr clone() const noexcept;

        private:
    };
}


#endif // OCTOON_COLLIDER2D_COMPONENT_H_