#ifndef OCTOON_JOINT2D_COMPONENT_H_
#define OCTOON_JOINT2D_COMPONENT_H_

#include <memory>
#include <octoon/game_component.h>
#include <octoon/math/math.h>


class b2Body;
class b2Fixture;

namespace octoon
{
    class OCTOON_EXPORT Joint2D : public GameComponent
	{
        OctoonDeclareSubInterface(Joint2D, runtime::RttiInterface)
        public:
            Joint2D() noexcept;
            ~Joint2D();
            virtual GameComponentPtr clone() const noexcept;
        
        protected:
            virtual void on_joint_change() = 0;
            virtual void on_joint_enter() = 0;
            virtual void on_joint_exit() = 0;
        private:

            friend class Rigidbody2D;
    };
}


#endif // OCTOON_JOINT2D_COMPONENT_H_