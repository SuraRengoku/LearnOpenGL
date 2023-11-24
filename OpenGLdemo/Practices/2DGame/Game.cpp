//
//  Game.cpp
//  OpenGLdemo
//
//  Created by SHERLOCK on 22.11.23.
//

#include "Game.h"

Game::Game(GLuint width,GLuint height):State(GAME_ACTIVE),Keys(),Width(width),Height(height){
    
}

Game::~Game(){
    
}

void Game::Init(){
    ResourceManager::LoadShader("Practices/2DGame/sprite.vs", "Practices/2DGame/sprite.fs", nullptr, "sprite");
    glm::mat4 projection=glm::ortho(0.0f,static_cast<GLfloat>(this->Width),static_cast<GLfloat>(this->Height),0.0f,-1.0f,1.0f);
    ResourceManager::GetShader("sprite").use().setInt("image", 0);
    ResourceManager::GetShader("sprite").setMat4("projection", projection);
    
    Sprite=new SpriteRender(ResourceManager::GetShader("name"));
    ResourceManager::LoadTexture("resource/awesomeface.png", GL_TRUE, "face");
}

void Game::Update(GLfloat dt){
    
}

void Game::ProcessInput(GLfloat dt){
    
}

void Game::Render(){
    Sprite->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200,200),glm::vec2(300,400),45.0f,glm::vec3(1.0f,1.0f,1.0f));
}

//void SpriteRender::initRenderData(){
//
//}
