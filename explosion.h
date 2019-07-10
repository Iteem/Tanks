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

#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include <SFML/Graphics.hpp>

const float DurationOfExplosion = 0.2f;

class Explosion
{
    public:
        Explosion(sf::Vector2f InPosition, float Radius);
        ~Explosion(void){};
        static void Init(void);
        void Update(float ElapsedTime);
        void Draw(sf::RenderWindow &App);
        float GetMaxRadius(void) const{return MaxRadius;};
        sf::Vector2f GetPosition(void) const{return sExplosion.GetPosition();};
        bool End;
    private:
        float MaxRadius, CurRadius;
        static sf::Image IMGExplosion;
        sf::Sprite sExplosion;
};

#endif // EXPLOSION_H_INCLUDED
