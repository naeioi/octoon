#ifndef OCTOON_COLLIDER2D_COMPONENT_H_
#define OCTOON_COLLIDER2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/math/math.h>

class b2Body;

namespace octoon
{
    class OCTOON_EXPORT Collider2D : public GameComponent
	{
        OctoonDeclareSubInterface(Collider2D, runtime::RttiInterface)
        public:
            Collider2D() noexcept;
            ~Collider2D();
            virtual GameComponentPtr clone() const noexcept;

        private:
    };
}


#endif // OCTOON_COLLIDER2D_COMPONENT_H_