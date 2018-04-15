#include <octoon/polygonCollider2dComponent.h>
#include <octoon/rigidbody2dComponent.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(PolygonCollider2D, GameComponent, "PolygonCollider2D")

    PolygonCollider2D::PolygonCollider2D() noexcept
        :isRegistered(false)
    {

    }

    PolygonCollider2D::~PolygonCollider2D()
    {

    }

    GameComponentPtr PolygonCollider2D::clone() const noexcept
    {
        return std::makeShared<PolygonCollider2D>();
    }

    void PolygonCollider2D::setAutoTiling(bool isAutoTilling) noexcept
    {
        autoTiling = isAutoTilling;
        onCollisionChange();
    }

    bool PolygonCollider2D::getAutoTiling() const noexcept
    {
        return autoTiling;
    }

    void PolygonCollider2D::setPathCount(int n) noexcept
    {
        pathCount = n;
        onCollisionChange();
    }

    int PolygonCollider2D::getPathCount() const noexcept
    {
        return pathCount;
    }

    void PolygonCollider2D::setPoints(const math::Vector2Array& pts) noexcept
    {
        points = pts;
        onCollisionChange();
    }

    math::Vector2Array PolygonCollider2D::getPoints() const noexcept
    {
        return points;
    }

    void PolygonCollider2D::onCollisionChange() noexcept
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;

        if(!isRegistered)
            return;

        std::vector<b2Vec2> vertices(points.size());
        for (int i = 0; i != points.size(); ++i)
        {
            vertices[i].Set(points[i].x, points[i].y);
        }
        b2PolygonShape shapeDef;
        shapeDef.Set(vertices.data(), vertices.size());

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shapeDef;
        
        rigidBody->body->DestroyFixture(collider);
        collider = rigidBody->body->CreateFixture(&fixtureDef);
    }

    void PolygonCollider2D::onCollisionEnter() noexcept
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;
        
        std::vector<b2Vec2> vertices(points.size());
        for (int i = 0; i != points.size(); ++i)
        {
            vertices[i].Set(points[i].x, points[i].y);
        }
        b2PolygonShape shapeDef;
        shapeDef.Set(vertices.data(), vertices.size());

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shapeDef;
        
        collider = rigidBody->body->CreateFixture(&fixtureDef);

        isRegistered = true;
    }

    void PolygonCollider2D::onCollisionExit() noexcept
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;

        if(!isRegistered)
            return;

        rigidBody->body->DestroyFixture(collider);
    }

    void PolygonCollider2D::onCollisionStay() noexcept
    {

    }

    void PolygonCollider2D::onAttach() except
    {
        auto rigidBody = getComponent<Rigidbody2D>();
        if (!rigidBody)
            return;

        onCollisionEnter();
    }

    void PolygonCollider2D::onDetach() noexcept
    {
        onCollisionExit();
    }

    void PolygonCollider2D::onAttachComponent(const GameComponentPtr& component) except
    {
        if (component->isA<Rigidbody2D>())
        {
            onCollisionEnter();
        }
    }

    void PolygonCollider2D::onDetachComponent(const GameComponentPtr& component) noexcept
    {
    }
}