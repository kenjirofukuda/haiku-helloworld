#ifndef KG_CIRCLE_H
#define KG_CIRCLE_H
#include <View.h>

class KGCircle {
public:
	KGCircle(BPoint center, float radius);

	bool Contains(BPoint where) const;
	void DrawOn(BView* view) const;

private:
	BPoint fCenter;
	float fRadius;
};

#endif // KG_CIRCLE_H
