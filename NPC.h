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
        Font *font;
    public:
        NPC(float x, float y, int w, int h, float sp, Font *f);
        virtual ~NPC();
        
        void addSentence(std::string sentence, float x, float y);
        bool nextSentence();
        Text *getCurrentSentence();
};

#endif /* NPC_H */