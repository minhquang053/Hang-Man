#include "GameObject.h"

void GameObject::setTexture(SDL_Renderer*& renderer, const char* filepath)
{
    SDL_Surface* surface = IMG_Load(filepath);
    this->objTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (this->objTexture == nullptr) std::cout << "setTexture ! error : " << filepath << std::endl;
    SDL_FreeSurface(surface);

    SDL_QueryTexture(this->objTexture, nullptr, nullptr, &(this->srcRect.w), &(this->srcRect.h));
}

void GameObject::setTexture(SDL_Renderer*& renderer, int letter)
{
    switch(letter) {
    case 1:
        this->setTexture(renderer, "./assets/a.png");
        break;
    case 2:
        this->setTexture(renderer, "./assets/b.png");
        break;
    case 3:
        this->setTexture(renderer, "./assets/c.png");
        break;
    case 4:
        this->setTexture(renderer, "./assets/d.png");
        break;
    case 5:
        this->setTexture(renderer, "./assets/e.png");
        break;
    case 6:
        this->setTexture(renderer, "./assets/f.png");
        break;
    case 7:
        this->setTexture(renderer, "./assets/g.png");
        break;
    case 8:
        this->setTexture(renderer, "./assets/h.png");
        break;
    case 9:
        this->setTexture(renderer, "./assets/i.png");
        break;
    case 10:
        this->setTexture(renderer, "./assets/j.png");
        break;
    case 11:
        this->setTexture(renderer, "./assets/k.png");
        break;
    case 12:
        this->setTexture(renderer, "./assets/l.png");
        break;
    case 13:
        this->setTexture(renderer, "./assets/m.png");
        break;
    case 14:
        this->setTexture(renderer, "./assets/n.png");
        break;
    case 15:
        this->setTexture(renderer, "./assets/o.png");
        break;
    case 16:
        this->setTexture(renderer, "./assets/p.png");
        break;
    case 17:
        this->setTexture(renderer, "./assets/q.png");
        break;
    case 18:
        this->setTexture(renderer, "./assets/r.png");
        break;  
    case 19:
        this->setTexture(renderer, "./assets/s.png");
        break;
    case 20:
        this->setTexture(renderer, "./assets/t.png");
        break;
    case 21:
        this->setTexture(renderer, "./assets/u.png");
        break;
    case 22:
        this->setTexture(renderer, "./assets/v.png");
        break;
    case 23:
        this->setTexture(renderer, "./assets/w.png");
        break;
    case 24:
        this->setTexture(renderer, "./assets/x.png");
        break;
    case 25:
        this->setTexture(renderer, "./assets/y.png");
        break;
    case 26:
        this->setTexture(renderer, "./assets/z.png");
        break;
    default:
        break;
    }
}

GameObject::GameObject(SDL_Renderer*& renderer, const char* filepath)
{
    this->setTexture(renderer, filepath);
}

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
    SDL_DestroyTexture(objTexture);
}

void GameObject::objRender(SDL_Renderer*& renderer)
{
    SDL_RenderCopy(renderer, this->objTexture, nullptr, &(this->desRect));
}

void GameObject::updatePosition(int xpos, int ypos, double scale)
{
    this->desRect.x = xpos;
    this->desRect.y = ypos;
    this->desRect.w = this->srcRect.w * scale;
    this->desRect.h = this->srcRect.h * scale;
}

bool GameObject::checkClick(int xmouse, int ymouse)
{
    if (xmouse > this->desRect.x
        && xmouse < this->desRect.w+this->desRect.x
        && ymouse > this->desRect.y
        && ymouse < this->desRect.h + this->desRect.y)
        return true;
    else return false;
}
