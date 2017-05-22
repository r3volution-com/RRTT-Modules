#ifndef NPC_H
#define NPC_H

#include "libs/Text.h"
#include "Entity.h"

class NPC : public Entity {
    private:
        std::string name;
        std::vector<std::string> sentences;
        std::vector<Coordinate*> sentencePosition;
        Coordinate *runawayDirection;
        int currentSentence;
        
        bool inRange;
    public:
        /**
         * Crea el objeto npc
         * @param position: Posicion del npc (tipo coordenadas)
         * @param size: tamano del npc
         * @param sp: Velocidad de la animacion del npc
         * @param name: Nombre del npc
         */
        NPC(Coordinate position, Coordinate size, float sp, std::string name);
        virtual ~NPC();
        
        /**
         * Actualiza los parametros del texto del npc
         * @param f: Fuente del texto
         * @param size: Tamano del texto
         * @param fillColor: Color del texto del npc
         * @param outlineColor: Color del borde del texto del npc
         */
        void setTextParams(Font *f, int size, sf::Color fillColor, sf::Color outlineColor);
        
        /**
         * Anadir una frase
         * @param sentence: Frase a anadir
         * @param position: Posicion de la frase (tipo coord)
         */
        void addSentence(std::string sentence, Coordinate *position);
        
        /**
         * Comprueba la siguiente frase
         * @return 
         */
        bool nextSentence();
        
        /**
         * Actualiza la direccion en la que corre el npc
         * @param x: Coordenada x
         * @param y: Coordenada y
         */
        void setRunawayDirection(int x, int y);
        
        /**
         * Actualiza si esta en el rango
         * @param b: Mira si esta en rango
         */
        void setInRange(bool b){ inRange = b; }
        
        bool getRange(){ return inRange; }
        std::string getName() { return name; };
        Coordinate *getRunawayDirection() { return runawayDirection; }
        std::string getCurrentSentenceText();
        Coordinate *getCurrentSentencePosition();
};

#endif /* NPC_H */
