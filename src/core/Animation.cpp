#include "Animation.h"

LinearAnimation create_linear_animation(Entity* object, Vec2f start_point, Vec2f movement, float speed)
{
    LinearAnimation anim;
    anim.object = object;
    anim.type   = LINEAR;

    anim.start_point    = start_point;
    anim.movement       = movement;
    anim.speed          = speed;

    return anim;
}

RotationAnimation create_rotation_animation(Entity* object, float start_angle, float rotation_speed)
{
    RotationAnimation anim;
    anim.object = object;
    anim.type   = ROTATION;

    anim.start_angle    = start_angle;
    anim.rotation_speed = rotation_speed;

    return anim;
}

BouncyAnimation create_bouncy_animation(Entity* object, float rebound_height, float rebound_width, int max_bounces)
{
    BouncyAnimation anim;
    anim.object = object;
    anim.type   = BOUNCY;

    anim.height         = rebound_height;
    anim.width          = rebound_width;
    anim.max_bounces    = max_bounces;
    anim.bounces = 0;

    return anim;
}

PhysicAnimation create_physic_animation(Entity* object, Vec2f acceleration, float bounciness)
{
    PhysicAnimation anim;
    anim.object = object;
    anim.type   = PHYSIC;

    anim.acc        = acceleration;
    anim.bounciness = bounciness;

    return anim;
}

void testRegressionAnimations()
{
    //TODO Implémenter le test régression pour les fonctions génératrices d'animations
}