#include "Trigonometry.h"
#include "Coordinate.h"
#include "../Game.h"
#include <cmath>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>


Trigonometry::Trigonometry() {
    PI = 3.14159265f;
    ang = 0.0f;
}

Trigonometry::~Trigonometry() {
}

float Trigonometry::angle(Coordinate initial, Coordinate end){
    
    posI[0]=initial.x;
    posI[1]=initial.y;
    
    posF[0]=end.x-posI[0];
    posF[1]=(end.y-posI[1])*-1;
    
    if(posF[0]>=0 && posF[1]>=0){
        ang=std::atan(posF[0]/posF[1])*180/PI+180;    
        //derecha arriba
    }else{
        if(posF[0]<=0 && posF[1]>=0){
        posF[0]=0-posF[0];
        ang=std::atan(posF[1]/posF[0])*180/PI+90;
        //izquierda arriba
        }else{
            if(posF[0]<0 && posF[1]<0){
            posF[0]=0-posF[0];
            posF[1]=0-posF[1];
            ang=std::atan(posF[0]/posF[1])*180/PI;
            //izquierda abajo
            }else{
                if(posF[0]>0 && posF[1]<0){
                posF[1]=0-posF[1];
                ang=std::atan(posF[1]/posF[0])*180/PI+270;
                //derecha abajo
                }
            }
        }
    }
    return ang;
}

float Trigonometry::angleWindow(Coordinate end){
    
    posI[0]=Game::Instance()->window->getSize().x/2;
    posI[1]=Game::Instance()->window->getSize().y/2;
    
    posF[0]=end.x-posI[0];
    posF[1]=(end.y-posI[1])*-1;
    
    if(posF[0]>=0 && posF[1]>=0){
        ang=std::atan(posF[0]/posF[1])*180/PI+180;    
        //derecha arriba
    }else{
        if(posF[0]<=0 && posF[1]>=0){
        posF[0]=0-posF[0];
        ang=std::atan(posF[1]/posF[0])*180/PI+90;
        //izquierda arriba
        }else{
            if(posF[0]<0 && posF[1]<0){
            posF[0]=0-posF[0];
            posF[1]=0-posF[1];
            ang=std::atan(posF[0]/posF[1])*180/PI;
            //izquierda abajo
            }else{
                if(posF[0]>0 && posF[1]<0){
                posF[1]=0-posF[1];
                ang=std::atan(posF[1]/posF[0])*180/PI+270;
                //derecha abajo
                }
            }
        }
    }
    return ang;
}

float Trigonometry::distance(Coordinate initial, Coordinate end){
    int x = initial.x - end.x;
    int y = initial.y - end.y;
    
    float dis = std::sqrt(x*x+y*y);
    return dis;
}

std::vector<float> Trigonometry::distance(std::vector<Coordinate> initial, Coordinate end){
    std::vector<int> x = std::vector<int>();
    std::vector<int> y = std::vector<int>();
    
    std::vector<float> dis = std::vector<float>();
    
    for(int i = 0; i < initial.size(); i++){
        x[i] = initial.at(i).x - end.x;
        y[i] = initial.at(i).y - end.y;
        
        dis[i] = std::sqrt(x[i]*x[i]+y[i]*y[i]);
    }
    
    return dis;
}

Coordinate Trigonometry::direction(Coordinate initial, Coordinate end){
    
    int x = initial.x - end.x;
    int y = initial.y - end.y;
    
    if(x == 0){
        if(y == 0){
            return  Coordinate(0, 0);
        }else if(y < 0){
            return  Coordinate(0, -1);
        }else if(y > 0){
            return  Coordinate(0, 1);
        }
    }else if(x < 0){
        if(y == 0){
            return  Coordinate(-1, 0);
        }else if(y < 0){
            return  Coordinate(-1, -1);
        }else if(y > 0){
            return  Coordinate(-1, 1);
        }
    }else if(x > 0){
        if(y == 0){
            return  Coordinate(1, 0);
        }else if(y < 0){
            return  Coordinate(1, -1);
        }else if(y > 0){
            return  Coordinate(1, +1);
        }
    }
    return Coordinate(0,0);
}