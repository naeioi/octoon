#include <octoon/anchoredJoint2dComponent.h>
#include <octoon/rigidbody2dComponent.h>
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

    void AnchoredJoint2D::setAnchor(const math::Vector2& a) noexcept
    {
        anchor = a;
    }

    math::Vector2 AnchoredJoint2D::getAnchor() const noexcept
    {
        return anchor;
    }

    void AnchoredJoint2D::setAutoConfigureConnectedAnchor(bool isAutoConfigure) noexcept
    {
        autoConfigureConnectedAnchor = isAutoConfigure;
    }

    bool AnchoredJoint2D::getAutoConfigureConnectedAnchor() const noexcept
    {
        return autoConfigureConnectedAnchor;
    }

    void AnchoredJoint2D::setConnectedAnchor(const math::Vector2& a) noexcept
    {
        connectedAnchor = a;
    }

    math::Vector2 AnchoredJoint2D::getConnectedAnchor() const noexcept
    {
        return connectedAnchor;
    }
}