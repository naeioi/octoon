#ifndef OCTOON_CONSTANT_FORCE2D_COMPONENT_H_
#define OCTOON_CONSTANT_FORCE2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/math/math.h>


class b2Body;
class b2Fixture;

namespace octoon
{
    class OCTOON_EXPORT ConstantForce2D : public GameComponent
	{
        OctoonDeclareSubInterface(ConstantForce2D, GameComponent)
        public:
            ConstantForce2D() noexcept;
            ~ConstantForce2D();
            virtual GameComponentPtr clone() const noexcept;
        
        protected:
    
        private:

            friend class Rigidbody2D;
    };
}


#endif // OCTOON_CONSTANT_FORCE2D_COMPONENT_H_