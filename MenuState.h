#ifndef MENUSTATE_H
#define MENUSTATE_H

class MenuState {
    public:
        MenuState();
        void Render ();
        void Update();
        void Input();
        void Pause();
        void Resume();
        void CleanUp();
    
    private:

};

#endif /* MENUSTATE_H */

