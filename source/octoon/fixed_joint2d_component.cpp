#include <octoon/fixedJoint2dComponent.h>
#include <octoon/rigidbody2dComponent.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(FixedJoint2D, AnchoredJoint2D, "FixedJoint2D")

    FixedJoint2D::FixedJoint2D() noexcept
    {
    }

    FixedJoint2D::~FixedJoint2D()
    {

    }

    void FixedJoint2D::onJointChange()
    {

    }

    void FixedJoint2D::onJointEnter()
    {

    }

    void FixedJoint2D::onJointExit()
    {

    }
}