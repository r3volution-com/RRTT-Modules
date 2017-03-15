#ifndef NPC_H
#define NPC_H

#include "Coordinate.h"
#include "Text.h"
#include "Entity.h"

class NPC : public Entity{
    private:
        std::vector<std::string> *sentences;
        std::vector<Coordinate*> *sentencePosition;
        int currentSentence;
        Text *currentText;
    public:
        NPC(float x, float y, int w, int h, float sp);
        virtual ~NPC();
        
        void addSentence();
        bool nextSentence();
        void getCurrentSentence();
};

#endif /* NPC_H */