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

#include "explosion.h"

sf::Image Explosion::IMGExplosion;

Explosion::Explosion(sf::Vector2f InPosition, float Radius)
{
    sExplosion.SetImage(IMGExplosion);
    sExplosion.SetCenter(136, 136);
    sExplosion.SetPosition(InPosition);
    sExplosion.SetScale(0, 0);
    MaxRadius = Radius;
    CurRadius = 0;
    End = false;
}

void Explosion::Init(void)
{
    IMGExplosion.LoadFromFile("data/Explosion.png");
}

void Explosion::Update(float ElapsedTime)
{
    CurRadius += MaxRadius * ElapsedTime / DurationOfExplosion;
    sExplosion.SetScale(CurRadius * 2.f / 271.f, CurRadius * 2.f / 271.f);
    if(CurRadius > MaxRadius)
        End = true;
}

void Explosion::Draw(sf::RenderWindow &App)
{
    if(!End)
        App.Draw(sExplosion);
}
