#include "NPC.h"

NPC::NPC(float x, float y, int w, int h, float sp, std::string n) : Entity(x, y, w, h, sp) {
    currentSentence=-1;
    sentences = new std::vector<std::string>();
    sentencePosition = new std::vector<Coordinate *>();
    name = n;
}

NPC::~NPC() {
}
/*

*/
void NPC::addSentence(std::string sentence, float x, float y){
    sentences->push_back(sentence);
    sentencePosition->push_back(new Coordinate(x, y));
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