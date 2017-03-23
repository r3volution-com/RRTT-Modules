#ifndef NPC_H
#define NPC_H

#include "Coordinate.h"
#include "Text.h"
#include "Entity.h"

class NPC : public Entity {
    private:
        std::string name;
        std::vector<std::string> *sentences;
        std::vector<Coordinate*> *sentencePosition;
        int currentSentence;
    public:
        NPC(Rect *npcData, float sp, std::string n);
        virtual ~NPC();
        
        void setTextParams(Font *f, int size, sf::Color fillColor, sf::Color outlineColor);
        void addSentence(std::string sentence, Coordinate *position);
        bool nextSentence();
        std::string getName() { return name; };
        std::string getCurrentSentenceText();
        Coordinate *getCurrentSentencePosition();
};

#endif /* NPC_H */