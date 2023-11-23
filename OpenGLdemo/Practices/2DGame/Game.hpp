//
//  Game.hpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 22.11.23.
//

#ifndef Game_hpp
#define Game_hpp

#include "general.h"

enum GameState{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game{
public:
    GameState State;
    GLboolean Keys[1024];
    GLuint Width,Height;
    //contructor
    Game(GLuint width,GLuint height);
    //destructor
    ~Game();
    
    void Init();
    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();
};


#endif /* Game_hpp */
