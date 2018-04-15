#include <octoon/distanceJoint2dComponent.h>
#include <octoon/rigidbody2dComponent.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(DistanceJoint2D, AnchoredJoint2D, "DistanceJoint2D")

    DistanceJoint2D::DistanceJoint2D() noexcept
    {
    }

    DistanceJoint2D::~DistanceJoint2D()
    {

    }

    void DistanceJoint2D::setAutoConfigureDistance(bool b) noexcept
    {
        autoConfigureDistance = b;
    }

    bool DistanceJoint2D::getAutoConfigureDistance() const noexcept
    {
        return autoConfigureDistance;
    }

    void DistanceJoint2D::setDistance(float d) noexcept
    {
        distance = d;
        b2DistanceJointDef jointDef;
        jointDef.Initialize(myBodyA, myBodyB, worldAnchorOnBodyA, worldAnchorOnBodyB);
        jointDef.collideConnected = true;
    }

    float DistanceJoint2D::getDistance() const noexcept
    {
        return distance;
    }

    void DistanceJoint2D::setMaxDistanceOnly(bool b) noexcept
    {
        maxDistanceOnly = b;
    }
    bool DistanceJoint2D::getMaxDistanceOnly() const noexcept
    {
        return maxDistanceOnly;
    }

    void DistanceJoint2D::onJointChange()
    {

    }

    void DistanceJoint2D::onJointEnter()
    {

    }

    void DistanceJoint2D::onJointExit()
    {

    }
}