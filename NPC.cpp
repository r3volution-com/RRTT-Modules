#include "NPC.h"

NPC::NPC(Rect<float> *npcData, float sp, std::string npcName) : Entity(npcData, sp) {
    currentSentence=-1;
    sentences = new std::vector<std::string>();
    sentencePosition = new std::vector<Coordinate *>();
    name = npcName;
}

NPC::~NPC() {
}
/*

*/
void NPC::addSentence(std::string sentence, Coordinate *pos){
    sentences->push_back(sentence);
    sentencePosition->push_back(pos);
}
bool NPC::nextSentence(){
    if (currentSentence+1 < sentences->size()) {
        currentSentence++;
        return true;
    } else {
        currentSentence = -1;
        return false;
    }
}
std::string NPC::getCurrentSentenceText(){
    return sentences->at(currentSentence);
}
Coordinate *NPC::getCurrentSentencePosition(){
    return sentencePosition->at(currentSentence);
}