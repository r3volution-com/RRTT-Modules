#include <fstream>
#include <iostream>

#include "Save.h"

using namespace std;

Save::Save() {
    
    int value = 3;
    
    doc.LoadFile("resources/prueba.tmx");
    
    level = doc.FirstChildElement("level");

    level->QueryIntAttribute("level", &_numLevel);
    
    cout << "Numero del nivel: " << level->FirstAttribute()->Value() << endl;
   
    coords = doc.FirstChildElement("rath");
    
    level->QueryIntAttribute("x", &_rX);
    level->QueryIntAttribute("y", &_rY);
    
    cout << "Coordenada x de rath: " << _rX << endl;
    cout << "Coordenada y de rath: " << _rY << endl;
    
        
    XMLElement *nivel = doc.FirstChildElement("level")->ToElement();
    nivel->SetAttribute("level", 3);
    
    XMLElement *coordenadas = doc.FirstChildElement("rath")->ToElement();
    coordenadas->SetAttribute("x", 10);
    coordenadas->SetAttribute("y", 20);
 
    
    doc.SaveFile("resources/prueba2.tmx");
    
}

Save::~Save() {
}