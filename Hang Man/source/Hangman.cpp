#include "Game.h"

int main(int argc, char** argv)
{
    Game* hangman = new Game();

    if (hangman->is_running()) std::cout << "Running\n";

    do
    {
        while (hangman->is_running())
        {
            hangman->render();
            hangman->input();
            hangman->update();
        }
        if (hangman->getQuit()) break;
        SDL_Delay(1500);
        hangman->render("replay");
        hangman->input("replay");
        hangman->update("replay");
    } while (hangman->getReplay());

    delete hangman;

    return 0;
}
