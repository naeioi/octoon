#include <octoon/anchored_joint2d_component.h>
#include <octoon/rigidbody2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(AnchoredJoint2D, Joint2D, "AnchoredJoint2D")

    AnchoredJoint2D::AnchoredJoint2D() noexcept
    {
    }

    AnchoredJoint2D::~AnchoredJoint2D()
    {

    }
}