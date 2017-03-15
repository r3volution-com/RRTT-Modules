#include "NPC.h"

NPC::NPC(float x, float y, int w, int h, float sp) : Entity(x, y, w, h, sp) {
    currentSentence=0;
    sentences = new std::vector<std::string>();
    sentencePosition = new std::vector<Coordinate *>();
    currentText = new Text(std::string(), 0, 0, sf::Color::White);
}

NPC::~NPC() {
}

void NPC::addSentence(std::string sentence, float x, float y){
    sentences->push_back(sentence);
    sentencePosition->push_back(new Coordinate(x, y));
}
bool NPC::nextSentence(){
    if (currentSentence < sentences->size()) {
        currentSentence++;
        currentText->setText(sentences->at(currentSentence));
        currentText->setPosition(sentencePosition->at(currentSentence)->x, sentencePosition->at(currentSentence)->y);
        return true;
    } else return false;
}
Text *NPC::getCurrentSentence(){
    return currentText;
}