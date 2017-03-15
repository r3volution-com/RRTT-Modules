#ifndef NPC_H
#define NPC_H

#include "Entity.h"

class NPC : public Entity{
    private:
        
    public:
        NPC(float x, float y, int w, int h, float sp);
        virtual ~NPC();
};

#endif /* NPC_H */