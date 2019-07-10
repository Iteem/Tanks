/*
   Copyright 2009 Patrick Winkler

   This file is part of Tank Battle

   Tank Battle software is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   Tank Battle software is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
#include <SFML/Graphics.hpp>

#include "options.h"
#include "menu.h"
#include "game.h"

const sf::Vector2i Screen(800, 600);

int main(void)
{
    sf::RenderWindow App(sf::VideoMode(Screen.x, Screen.y, 32), "Tanks");
    App.UseVerticalSync(true);

    Options MyOptions;
    Game MyGame(App, MyOptions);
    Menu MyMenu(App, MyOptions, MyGame);

    sf::Font Font;
    Font.LoadFromFile("data/din1451alt G.ttf", 15);

    //music
    sf::Music TheHit;
    TheHit.OpenFromFile("data/The Hit.ogg");
    TheHit.SetVolume(100.f);
    TheHit.SetLoop(true);
    TheHit.Play();

    while(true)
    {
        if(!MyMenu.Run(Font, TheHit))
            break;
        if(!MyGame.Run(Font))
            break;
    }

    return EXIT_SUCCESS;
}
