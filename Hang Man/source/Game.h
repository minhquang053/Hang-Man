#include "GameObject.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

#ifndef GAME_H
#define GAME_H

class Game
{
public:
    Game();
    ~Game();
    bool is_running() {
        return this->isRunning;
    }
    bool getReplay() {
        return this->replay;
    }
    void setReplay() {
        this->replay = true;
    }
    bool getQuit() {
        return this->quit;
    }
    int generateKey();
    void LoadString();
    void render();
    void render(const char *random);
    void update();
    void update(const char *random);
    void input();
    void input(const char *randon);
private:
    bool isRunning = false, replay = false, quit = false, submit = false;
    int ttl;
    std::string current, key;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    TTF_Font* font;
    SDL_Rect desText{ 0,0,0,0 }, liveText{ 0,0,0,0 };
    SDL_Texture* text;
    SDL_Texture* life;

    GameObject letter[3][9];
    GameObject* surround, * board, * again, * background, * okay, * correct, * lose;
};

#endif /* end of include guard: GAME_H */
