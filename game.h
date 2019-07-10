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

#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>

#include "options.h"
#include "player.h"

class Game
{
    public:
        Game(sf::RenderWindow &inApp, Options &inOptions) : MyOptions(inOptions), App(inApp){};
        ~Game();
        bool Run(sf::Font &Font);
        void AddPlayer(std::string Name, int Money, int Score, sf::Color Color, int PositionX);
        void KillPlayers(void);
    private:
        Options MyOptions;
        sf::RenderWindow &App;
        std::list<Player *> Players;
};

#endif // GAME_H_INCLUDED
