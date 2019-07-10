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
#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>

class Button{
    public:
        Button(sf::RenderWindow &Window, sf::Vector2f Position, std::string IMGName);
        Button::Button(sf::RenderWindow &Window, float PositionY, std::string IMGName);
        ~Button(){};
        void SetPosition(sf::Vector2f SetPosition);
        void SetImage(std::string IMGName);
        void SetScale(sf::Vector2f Scale);
        void Resize(sf::Vector2f Size);
        sf::Vector2i ImageSize(void) const;
        bool Update(void); //true when pressed, else false
        void Draw(void);
    private:
        sf::Image ButtonImage;
        sf::Sprite ButtonSprite;
        sf::Vector2f MyPosition;
        sf::Vector2f MyScale;
        bool Down;
        sf::RenderWindow &App;
};

#endif // BUTTON_H_INCLUDED
