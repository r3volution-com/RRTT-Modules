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
        NPC(float x, float y, int w, int h, float sp, std::string n);
        virtual ~NPC();
        
        void setTextParams(Font *f, int size, sf::Color fillColor, sf::Color outlineColor);
        void addSentence(std::string sentence, float x, float y);
        bool nextSentence();
        std::string getName() { return name; };
        std::string getCurrentSentenceText();
        Coordinate *getCurrentSentencePosition();
};

#endif /* NPC_H */