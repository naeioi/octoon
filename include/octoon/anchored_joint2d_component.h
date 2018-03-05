#ifndef OCTOON_ANCHORED_JOINT2D_COMPONENT_H_
#define OCTOON_ANCHORED_JOINT2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/joint2d_component.h>
#include <octoon/math/math.h>


class b2Body;
class b2Fixture;

namespace octoon
{
    class OCTOON_EXPORT AnchoredJoint2D : public Joint2D
	{
        OctoonDeclareSubInterface(AnchoredJoint2D, runtime::RttiInterface)
        public:
            AnchoredJoint2D() noexcept;
            ~AnchoredJoint2D();
            virtual GameComponentPtr clone() const noexcept;
        
        protected:
            math::Vector2 anchor; // The joint's anchor point on the object that has the joint component.
            bool auto_configure_connected_anchor; // Should the connectedAnchor be calculated automatically?
            math::Vector2 connected_anchor; // The joint's anchor point on the second object (ie, the one which doesn't have the joint component).

        private:
            friend class Rigidbody2D;
    };
}


#endif // OCTOON_ANCHORED_JOINT2D_COMPONENT_H_