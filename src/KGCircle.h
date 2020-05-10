#ifndef _KG_CIRCLE_H_
#define _KG_CIRCLE_H_
#include <interface/View.h>

class KGCircle
{
public:
    KGCircle(BPoint center, float radius);

    bool Contains(BPoint where) const;
    void DrawOn(BView* view) const;

private:
    BPoint fCenter;
    float fRadius;
};

#endif // _KG_CIRCLE_H_
