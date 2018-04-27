#include <octoon/box_collider2d_component.h>
#include <octoon/rigidbody2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(BoxCollider2D, Collider2D, "BoxCollider2D")

    BoxCollider2D::BoxCollider2D() noexcept
        :isRegistered(false)
    {

    }

    BoxCollider2D::~BoxCollider2D()
    {

    }

    GameComponentPtr BoxCollider2D::clone() const noexcept
    {
        return std::make_shared<BoxCollider2D>();
    }

    void BoxCollider2D::setAutoTiling(bool isAutoTilling) noexcept
    {
        autoTiling = isAutoTilling;
        onCollisionChange();
    }

    bool BoxCollider2D::getAutoTiling() const noexcept
    {
        return autoTiling;
    }

    void BoxCollider2D::setEdgeRadius(float r) noexcept
    {
        edgeRadius = r;
        onCollisionChange();
    }

    float BoxCollider2D::getEdgeRadius() const noexcept
    {
        return edgeRadius;
    }

    void BoxCollider2D::setSize(const math::Vector2& s) noexcept
    {
        size = s;
        onCollisionChange();
    }

    math::Vector2 BoxCollider2D::getSize() const noexcept
    {
        return size;
    }

    void BoxCollider2D::onCollisionChange() noexcept
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;

        if(!isRegistered)
            return;
        
        b2PolygonShape shapeDef;
        shapeDef.SetAsBox(size.x, size.y);
        shapeDef.m_radius = edgeRadius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shapeDef;
        
        rigidBody->body->DestroyFixture(collider);
        collider = rigidBody->body->CreateFixture(&fixtureDef);
    }

    void BoxCollider2D::onCollisionEnter() noexcept
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;
        
        b2PolygonShape shapeDef;
        shapeDef.SetAsBox(size.x, size.y);
        shapeDef.m_radius = edgeRadius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shapeDef;
        
        collider = rigidBody->body->CreateFixture(&fixtureDef);

        isRegistered = true;
    }

    void BoxCollider2D::onCollisionExit() noexcept
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;

        if(!isRegistered)
            return;

        rigidBody->body->DestroyFixture(collider);
    }

    void BoxCollider2D::onCollisionStay() noexcept
    {

    }

    void BoxCollider2D::onAttach() except
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;

        onCollisionEnter();
    }

    void BoxCollider2D::onDetach() noexcept
    {
        onCollisionExit();
    }

    void BoxCollider2D::onAttachComponent(const GameComponentPtr& component) except
    {
        if (component->isA<Rigidbody2D>())
        {
            onCollisionEnter();
        }
    }

    void BoxCollider2D::onDetachComponent(const GameComponentPtr& component) noexcept
    {
    }
}