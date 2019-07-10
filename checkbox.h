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

#ifndef CHECKBOX_H_INCLUDED
#define CHECKBOX_H_INCLUDED

#include <SFML/Graphics.hpp>

class CheckBox{
    public:
        CheckBox(sf::RenderWindow &Window, sf::Vector2f Position, bool Status = true, float Scale = .8f);
        ~CheckBox(){};
        static bool Init(void);
        void SetPosition(sf::Vector2f SetPosition);
        void SetScale(float Scale);
        void Resize(float Size);
        bool Update(void); //return current status of the box
        void Draw(void);
    private:
        static sf::Image BoxImage, CheckImage;
        sf::Sprite BoxSprite, CheckSprite;
        sf::Vector2f MyPosition;
        sf::RenderWindow &App;
        float MyScale;
        bool Down;
        bool MyStatus;
};

#endif // CHECKBOX_H_INCLUDED
