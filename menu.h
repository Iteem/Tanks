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

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "options.h"
#include "game.h"

class Menu
{
    public:
        Menu(sf::RenderWindow &inApp, Options &inOptions, Game &inGame) : MyOptions(inOptions),  App(inApp), MyGame(inGame){};
        bool Run(sf::Font &Font, sf::Music &MyMusic);
    private:
        Options MyOptions;
        sf::RenderWindow &App;
        Game &MyGame;
};

#endif // MENU_H_INCLUDED
