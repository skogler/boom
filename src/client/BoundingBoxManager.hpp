#ifndef BOUNDINGBOXMANAGER_HPP_ZJGDAKFV
#define BOUNDINGBOXMANAGER_HPP_ZJGDAKFV

#include "common.hpp"

class BoundingBoxManager
{
    DISABLECOPY(BoundingBoxManager);

public:
    BoundingBoxManager ();
    virtual ~BoundingBoxManager ();

private:
    std::map<Entity, BoundingBox> m_boundingBoxes;
    
};

#endif /* end of include guard: BOUNDINGBOXMANAGER_HPP_ZJGDAKFV */

