#include "Animation.h"

LinearAnimation createLinearAnimation(
    Entity* object, Vec2f start_point, Vec2f movement,
    float speed, void* origin_segment
)
{
    LinearAnimation anim;
    anim.object = object;
    anim.type   = LINEAR;
    anim.origin_segment = origin_segment;

    anim.start_point    = start_point;
    anim.movement       = movement;
    anim.speed          = speed;

    return anim;
}

RotationAnimation createRotationAnimation(
    Entity* object, float start_angle, float rotation_speed,
    void* origin_segment
)
{
    RotationAnimation anim;
    anim.object = object;
    anim.type   = ROTATION;
    anim.origin_segment = origin_segment;

    anim.start_angle    = start_angle;
    anim.rotation_speed = rotation_speed;

    return anim;
}

BouncyAnimation createBouncyAnimation(
    Entity* object, float rebound_height, float rebound_width,
    int max_bounces, void* origin_segment
)
{
    BouncyAnimation anim;
    anim.object = object;
    anim.type   = BOUNCY;
    anim.origin_segment = origin_segment;

    anim.height         = rebound_height;
    anim.width          = rebound_width;
    anim.max_bounces    = max_bounces;
    anim.bounces = 0;

    return anim;
}

PhysicAnimation createPhysicAnimation(
    Entity* object, Vec2f acceleration, float bounciness,
    void* origin_segment
)
{
    PhysicAnimation anim;
    anim.object = object;
    anim.type   = PHYSIC;
    anim.origin_segment = origin_segment;

    anim.acc        = acceleration;
    anim.bounciness = bounciness;

    return anim;
}

void testRegressionAnimations()
{
    //TODO Implémenter le test régression pour les fonctions génératrices d'animations
}