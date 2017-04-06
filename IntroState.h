#ifndef INTROSTATE_H
#define INTROSTATE_H

class IntroState {
    public:
        IntroState();
        void Render ();
        void Update();
        void Input();
        void Pause();
        void Resume();
        void CleanUp();

    private:

};

#endif /* INTROSTATE_H */

