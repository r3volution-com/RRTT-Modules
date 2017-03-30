#include "NPC.h"

NPC::NPC(Coordinate position, Texture *t, Rect<float> newRect, float sp, std::string npcName) : Entity(position, t, newRect, sp) {
    currentSentence=-1;
    sentences = new std::vector<std::string>();
    sentencePosition = new std::vector<Coordinate *>();
    name = npcName;
}

NPC::~NPC() {
    delete sentences;
    delete sentencePosition;
    sentences = NULL;
    sentencePosition = NULL;
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