#include "Game.h"

int clicked = -1;
bool matched = false;

int Game::generateKey()
{
    srand(time(0));
    int wordth = rand() % 851 + 1;
    std::ifstream wordlist("assets/wordlist.txt");
    while (wordth-- > 0) getline(wordlist, this->key);
    std::cout << this->key << std::endl;
    return this->key.size();
}

void Game::LoadString()
{
    SDL_Surface* tsurface = TTF_RenderText_Solid(this->font, ((this->ttl>0)?this->current:this->key).c_str(), { 0,0,0 });
    SDL_Surface* lsurface = TTF_RenderText_Solid(this->font, std::to_string(this->ttl).c_str(), { 0,0,0 });
    this->text = SDL_CreateTextureFromSurface(this->renderer, tsurface);
    this->life = SDL_CreateTextureFromSurface(this->renderer, lsurface);
    SDL_QueryTexture(this->text, nullptr, nullptr, &(this->desText.w), &(this->desText.h));
    SDL_QueryTexture(this->life, nullptr, nullptr, &(this->liveText.w), &(this->liveText.h));
    desText.x = 170; desText.y = 130;
    liveText.x = 670; liveText.y = 10;
    SDL_FreeSurface(tsurface);
    SDL_FreeSurface(lsurface);
}

Game::Game()
{
    InitSDL(this->window, this->renderer);
    this->isRunning = true;

    this->font = TTF_OpenFont("assets/right.ttf", 70);

    this->background = new GameObject(this->renderer, "assets/bg.png");
    this->background->updatePosition(0,0,0.5);
    this->surround = new GameObject(this->renderer, "assets/surround.png");
    this->board = new GameObject(this->renderer, "assets/board.png");
    this->board->updatePosition(30, 50, 1);
    this->again = new GameObject(this->renderer, "assets/again.png");
    this->again->updatePosition(280,400,1); // waiting to be changed
    this->okay = new GameObject(this->renderer, "assets/okay.png");
    this->okay->updatePosition(600, 500, 0.5);
    this->correct = new GameObject(this->renderer, "assets/correct.png");
    this->correct->updatePosition(110, 270, 1);
    this->lose = new GameObject(this->renderer, "assets/lose.png");
    this->lose->updatePosition(200, 270, 1);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (i == 2 && j == 8) break;
            this->letter[i][j].setTexture(this->renderer, 9*i + (j+1));
            this->letter[i][j].updatePosition(40 + 75 * j, 650 + 100 * i, 0.8);
        }
    }

    int len = generateKey();
    ttl = len + 8;
    this->current = "";
    for (int i = 0; i < len; ++i) current += "_";
    
    LoadString();

    std::cout << "Start game\n";
}

Game::~Game()
{
    QuitSDL(this->window, this->renderer);
    std::cout << "End game\n";
}

void Game::render()
{
    SDL_RenderClear(renderer);
    this->background->objRender(this->renderer);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (i == 2 && j == 8) break;
            this->letter[i][j].objRender(this->renderer);
        }
    }
    if (clicked >= 0) {
        this->surround->updatePosition(40 + 75 * ((clicked-1) % 9) - 5, 650 + 100 * static_cast<int>((clicked-1) / 9) + 5, 0.05);
        this->surround->objRender(this->renderer);
    }

    okay->objRender(this->renderer);
    board->objRender(this->renderer);
    if (this->key == this->current) this->correct->objRender(this->renderer);
    if (this->ttl == 0) this->lose->objRender(this->renderer);
    SDL_RenderCopy(this->renderer, text, nullptr, &desText);
    SDL_RenderCopy(this->renderer, life, nullptr, &liveText);
    SDL_RenderPresent(this->renderer);

    SDL_Delay(20);
}

void Game::input()
{
    while (SDL_WaitEvent(&(this->event)))
    {
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int xm = event.button.x, ym = event.button.y;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (i == 2 && j == 8) break;
                    if (this->letter[i][j].checkClick(xm, ym))
                    {
                        clicked = 9 * i + (j + 1);
                        goto NEXT;
                    }
                }
            }
            if (this->okay->checkClick(xm, ym)) {
                if (clicked >= 0) this->submit = true;
                goto NEXT;
            }
        }
        else if (event.type == SDL_QUIT)
        {
            this->isRunning = false;
            this->quit = true;
            break;
        }
        SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT);
    }
NEXT:
    {
    }
}

void Game::update()
{
    // game rule here
    if (this->submit)
    {
        char in = 'a' + clicked - 1;
        clicked = -1;        
        this->submit = false;
        
        matched = false;

        for (int i = 0; i < this->key.size(); ++i) {
            if (this->key[i] == in) {
                this->current[i] = in;
                matched = true;
            }
        }
        
        if (!matched) this->ttl--;
        if (this->ttl == 0 || this->current == this->key) {    
            LoadString();
            this->render();
            this->isRunning = false;
        }
    }

    LoadString();
    //
}

void Game::render(const char *random)
{
    SDL_RenderClear(renderer);
    this->background->objRender(this->renderer);
    this->again->objRender(this->renderer);

    SDL_RenderPresent(this->renderer);
    SDL_Delay(20);
}

void Game::input(const char *random)
{
    while(SDL_WaitEvent(&(this->event)))
    {
        int xm = event.button.x, ym = event.button.y;
        if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if (this->again->checkClick(xm, ym))
            {
                this->setReplay();
                this->isRunning = true;
                break;
            }
        }
        else if (event.type == SDL_QUIT)
        {
            this->quit = true;
            break;
        }
    }
}

void Game::update(const char *random)
{
    this->current = "";
    int len = generateKey();
    this->ttl = len + 8;
    for (int i = 0; i < len; ++i) this->current += "_";
    this->surround->updatePosition(0, 0, 0);
    LoadString();
    std::cout << "Replay" << std::endl;
}
