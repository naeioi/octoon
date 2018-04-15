#ifndef OCTOON_PHYSICS2D_H_
#define OCTOON_PHYSICS2D_H_

#include <octoon/math/math.h>

namespace octoon
{
    class Physics2D
    {
        public:
        static void setGravity(const math::Vector2& g){gravity=g;}
        static math::Vector2 getGravity(){return gravity;}



        private:
        static math::Vector2 gravity;
    };
}



#endif // OCTOON_PHYSICS2D_H_