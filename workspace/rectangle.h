#ifndef __RECTANGLE_H_
#define __RECTANGLE_H_
#include "point.h"

class rectangle
{
private:
    point upLeft;
    point lowRight;
public:
    bool InitMembers(const point &ul, const point &lr);
    void ShowRecInfo() const;
};
#endif
