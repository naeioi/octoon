#ifndef OCTOON_DISTANCE_JOINT2D_COMPONENT_H_
#define OCTOON_DISTANCE_JOINT2D_COMPONENT_H_

#include <memory>
#include <octoon/gameComponent.h>
#include <octoon/anchoredJoint2dComponent.h>
#include <octoon/joint2dComponent.h>
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
        
            void setAutoConfigureDistance(bool b) noexcept;
            bool getAutoConfigureDistance() const noexcept;

            void setDistance(float d) noexcept;
            float getDistance() const noexcept;

            void setMaxDistanceOnly(bool b) noexcept;
            bool getMaxDistanceOnly() const noexcept;

        protected:
            virtual void onJointChange() override;
            virtual void onJointEnter() override;
            virtual void onJointExit() override;
        
        protected:
            bool autoConfigureDistance; //Should the distance be calculated automatically?
            float distance; // The distance separating the two ends of the joint.
            bool maxDistanceOnly; //Whether to maintain a maximum distance only or not. If not then the absolute distance will be maintained instead.

        private:
            b2DistanceJoint *joint;

            friend class Rigidbody2D;
    };
}


#endif // OCTOON_DISTANCE_JOINT2D_COMPONENT_H_