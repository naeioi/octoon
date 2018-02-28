#include <octoon/rigidbody2d_component.h>
#include <Box2D/Box2D.h>


namespace octoon
{
    OctoonImplementSubClass(Rigidbody2DComponent, GameComponent, "Rigidbody2DComponent")

    Rigidbody2DComponent::Rigidbody2DComponent() noexcept
    {
        b2World *world = runtime::Singleton<b2World>::instance();

        b2BodyDef bodyDef;   //一个物体的定义  
        bodyDef.type = b2_staticBody; //物体的类型，不动的，坚硬的~ 可以把这样的物体当成地面  
        b2PolygonShape borderShape; // 一个方形的形状
        b2FixtureDef borderFixture; // 一个定制器
        
        //定义地板  
        bodyDef.position.Set(0, 0); // 地板在0，0位置  
        borderShape.SetAsBox(VisibleRect::right().x * PTM_RATIO, 0); //设置长度和高度，这里描述的地板就像是X轴，是一条线  
        borderFixture.shape = &borderShape;  
        b2Body * bottomBorder = mWorld->CreateBody(&bodyDef); //在世界中创建一个物体（地面）  
        bottomBorder->CreateFixture(&borderFixture);          //定制地面的形状  
    }

	Rigidbody2DComponent::~Rigidbody2DComponent()
    {

    }

	GameComponentPtr Rigidbody2DComponent::clone() const noexcept
    {

    }

    void Rigidbody2DComponent::set_body_type(RigidbodyType2D type)
    {
        body_type = type;
    }

    RigidbodyType2D Rigidbody2DComponent::get_body_type()
    {
        return body_type;
    }


    void Rigidbody2DComponent::on_activate() noexcept
    {

    }

    void Rigidbody2DComponent::on_deactivate() noexcept
    {

    }

    void Rigidbody2DComponent::on_attach_component(const GameComponentPtr& component) noexcept
    {

    }

    void Rigidbody2DComponent::on_detach_component(const GameComponentPtr& component) noexcept
    {

    }

    void Rigidbody2DComponent::on_collision_change() noexcept
    {

    }
    void Rigidbody2DComponent::on_collision_enter() noexcept
    {

    }
    void Rigidbody2DComponent::on_collision_exit() noexcept
    {

    }
    void Rigidbody2DComponent::on_collision_stay() noexcept
    {

    }

    void Rigidbody2DComponent::build_rigibody() noexcept
    {
    }
}