#ifndef SAVE_H
#define SAVE_H

#include <vector>
#include <string>
#include <tinyxml2.h>

using namespace tinyxml2;

class Save {
public:
    Save();
    virtual ~Save();
    
    XMLDocument doc;
    XMLElement* level;
    XMLElement* coords;
    
    int _numLevel, _rX, _rY;
    
private:

};

#endif /* SAVE_H */

