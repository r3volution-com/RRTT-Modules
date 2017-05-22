#include "NPC.h"

NPC::NPC(Coordinate position, Coordinate size, float sp, std::string npcName) : Entity(position, size, sp) {
    currentSentence=-1;
    name = npcName;
    inRange = false;
}

NPC::~NPC() {
    sentences.clear();
    for (int i=0; i<sentencePosition.size(); i++){
        delete sentencePosition.at(i);
        sentencePosition.at(i) = NULL;
    }
    sentencePosition.clear();
    
    delete runawayDirection;
    runawayDirection = NULL;
}
/*

*/
void NPC::addSentence(std::string sentence, Coordinate *pos){
    sentences.push_back(sentence);
    sentencePosition.push_back(pos);
}
bool NPC::nextSentence(){
    if (currentSentence+1 < sentences.size()) {
        currentSentence++;
        return true;
    } else {
        currentSentence = -1;
        return false;
    }
}
void NPC::setRunawayDirection(int x, int y){
    runawayDirection = new Coordinate(x, y);
}
std::string NPC::getCurrentSentenceText(){
    return sentences.at(currentSentence);
}
Coordinate *NPC::getCurrentSentencePosition(){
    return sentencePosition.at(currentSentence);
}