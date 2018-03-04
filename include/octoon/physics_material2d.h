#ifndef OCTOON_PHYSICS_MATERIAL2D_COMPONENT_H_
#define OCTOON_PHYSICS_MATERIAL2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/math/math.h>


class b2Body;
class b2Fixture;

namespace octoon
{
    class OCTOON_EXPORT PhysicsMaterial2D : public runtime::RttiInterface
	{
        OctoonDeclareSubInterface(PhysicsMaterial2D, runtime::RttiInterface)
        public:
            PhysicsMaterial2D() noexcept;
            ~PhysicsMaterial2D();
        
        protected:

        private:
            friend class Rigidbody2D;
    };
}


#endif // OCTOON_PHYSICS_MATERIAL2D_COMPONENT_H_