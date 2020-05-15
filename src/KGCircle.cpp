#include "KGCircle.h"

KGCircle::KGCircle(BPoint center, float radius)
    : fCenter(center), fRadius(radius)
{
}


bool
KGCircle::Contains(BPoint where) const
{
    float distance;

    distance = sqrt(pow(where.x - fCenter.x, 2) +
		    pow(where.y - fCenter.y, 2));    
    return distance <= fRadius;
}


void
KGCircle::DrawOn(BView* view) const
{
    view->FillEllipse(fCenter, fRadius, fRadius);
}

