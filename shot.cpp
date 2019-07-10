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

#include "shot.h"

sf::Image Shot::IMGShot;
float Shot::AirSpeed;

void Shot::Init(void)
{
    IMGShot.LoadFromFile("data/shot.png");
}

Shot::Shot(sf::Vector2f InPosition, sf::Vector2f InSpeed)
{
    Speed = InSpeed;

    AirSpeed = 0.f;

    PrevPosition = InPosition;

    sShot.SetImage(IMGShot);
    sShot.SetPosition(InPosition);
    sShot.SetCenter(8, 8);
    sShot.SetScale(.2f, .2f);
}

void Shot::Update(float ElapsedTime)
{
    PrevPosition = sShot.GetPosition();
    sShot.Move(Speed * ElapsedTime);
    Speed.y += EarthAcceleration * ElapsedTime;
    Speed.x += AirSpeed * ElapsedTime;
    Speed.y *= 1 - (Speed.y * Speed.y * AirResistenc * ElapsedTime);
    Speed.x *= 1 - (Speed.x * Speed.x * AirResistenc * ElapsedTime);
}

void Shot::Draw(sf::RenderWindow &App)
{
    App.Draw(sShot);
}
