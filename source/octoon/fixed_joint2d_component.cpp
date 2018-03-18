#include <octoon/fixed_joint2d_component.h>
#include <octoon/rigidbody2d_component.h>
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

    void FixedJoint2D::on_joint_change()
    {

    }

    void FixedJoint2D::on_joint_enter()
    {

    }

    void FixedJoint2D::on_joint_exit()
    {

    }
}