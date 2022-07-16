#include "Game.h"
#include <cstdlib>
#include <iostream>


int main()
{
    bool repeat = true;

    while (repeat)
    {
        Game game;
        game.execute();

        std::cout << "Play again? (0=No, 1=Yes)" << std::endl;
        std::cin >> repeat;

        system("clear");
    }

    return 0;
}
