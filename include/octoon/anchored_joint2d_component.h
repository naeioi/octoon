#ifndef OCTOON_ANCHORED_JOINT2D_COMPONENT_H_
#define OCTOON_ANCHORED_JOINT2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/math/math.h>


class b2Body;
class b2Fixture;

namespace octoon
{
    class OCTOON_EXPORT AnchoredJoint2D : public GameComponent
	{
        OctoonDeclareSubInterface(AnchoredJoint2D, runtime::RttiInterface)
        public:
            AnchoredJoint2D() noexcept;
            ~AnchoredJoint2D();
            virtual GameComponentPtr clone() const noexcept;
        
        protected:

        private:

            friend class Rigidbody2D;
    };
}


#endif // OCTOON_ANCHORED_JOINT2D_COMPONENT_H_