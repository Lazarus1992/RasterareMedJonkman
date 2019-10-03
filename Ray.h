#pragma once

#include "MathLib4D.h"
#include "Plane.h"

class Ray
{
    //Project ray onto plane normal to get v'
public:
    Vector3 start;
    Vector3 end;

    // inline Vector3 GetIntersection(Plane& plane)
    // {
    //     //The ray we are shooting
    //     Vector3 ray = end - start;
    //     Vector3 startToPlane = plane.point - start;

        

    //     float k = startToPlane.Dot(plane.normal / ray.Dot(plane.normal));

    //     Vector3 intersection = start + ray * k;
    //     if (k >= 0 && k <= 1)
    //     {
    //         return intersection;
    //     }
    //     else
    //     {
    //         //Didnt hit the plane
    //         return Vector3(0.0f);
    //     }
    // }



};