#include "../../include/JackdawBezier.h"

namespace jdw 
{
    Vec2f Bezier::get(double t) const
    {
        if (t > 1) t = 1;
        else if (t < 0) t = 0;
        double ttt = t*t*t, tt = t*t;
        return {
            a1 * (  -ttt +3*tt -3*t +1) +
            c1 * ( 3*ttt -6*tt +3*t   ) +
            c2 * (-3*ttt +3*tt        ) +
            a2 * (   ttt              )
        };
    }

    Vec2f Bezier::getDerivative(double t) const
    {
        if (t > 1) t = 1;
        else if (t < 0) t = 0;
        double tt = t*t;
        return {
            a1 * (-3*tt  +6*t -3) +
            c1 * ( 9*tt -12*t +3) +
            c2 * (-9*tt  +6*t   ) +
            a2 * ( 3*tt         )
        };
    }
}