//
//  Game.hpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 22.11.23.
//

#ifndef Game_hpp
#define Game_hpp

#include "ResourManager.hpp"
#include "render.h"

static SpriteRender *Sprite;

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

//class SpriteRender{
//public:
//    SpriteRender(Shader &shader);
//    ~SpriteRender();
//    
//    void DrawSprite(Texture2D &texture,glm::vec2 position,glm::vec2 size=glm::vec2(10,10),GLfloat rotate=0.0f,glm::vec3 color=glm::vec3(1.0f));
//private:
//    Shader shader;
//    GLuint quadVAO;
//    void initRenderData();
//};

#endif /* Game_hpp */
