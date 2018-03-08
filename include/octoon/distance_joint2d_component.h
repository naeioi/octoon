#ifndef OCTOON_DISTANCE_JOINT2D_COMPONENT_H_
#define OCTOON_DISTANCE_JOINT2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/anchored_joint2d_component.h>
#include <octoon/joint2d_component.h>
#include <octoon/math/math.h>


class b2Body;
class b2Fixture;
class b2DistanceJoint;

namespace octoon
{
    class OCTOON_EXPORT DistanceJoint2D : public AnchoredJoint2D
	{
        OctoonDeclareSubInterface(DistanceJoint2D, AnchoredJoint2D)
        public:
            DistanceJoint2D() noexcept;
            ~DistanceJoint2D();
            virtual GameComponentPtr clone() const noexcept;
        
        protected:
            bool auto_configure_distance; //Should the distance be calculated automatically?
            float distance; // The distance separating the two ends of the joint.
            bool max_distance_only; //Whether to maintain a maximum distance only or not. If not then the absolute distance will be maintained instead.

        private:
            b2DistanceJoint *joint;

            friend class Rigidbody2D;
    };
}


#endif // OCTOON_DISTANCE_JOINT2D_COMPONENT_H_