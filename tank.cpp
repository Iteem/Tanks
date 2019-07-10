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
#include <cmath>

#include "tank.h"

const float Pi = 3.14159265;

Tank::Tank(sf::RenderWindow &Window, sf::Color Color, int PositionX) : App(Window)
{
    TankImage.LoadFromFile("data/tank.png");
    MuzzleImage.LoadFromFile("data/muzzle.png");
    for(int i = 0; i < static_cast<int>(TankImage.GetWidth()); ++i)
    {
        for(int j = 0; j < static_cast<int>(TankImage.GetHeight()); ++j)
        {
            if(TankImage.GetPixel(i,j) == sf::Color(0,0,0))
                TankImage.SetPixel(i,j,Color);
        }
    }

    TankSprite.SetImage(TankImage);
    TankSprite.SetCenter(34,40);
    TankSprite.SetPosition(PositionX, 300);
    TankSprite.SetScale(Size, Size);

    MuzzleSprite.SetImage(MuzzleImage);
    MuzzleSprite.SetCenter(5, 55);
    MuzzleSprite.SetScale(Size, Size);
    MuzzleSprite.SetPosition(TankSprite.GetPosition().x, TankSprite.GetPosition().y - 20.f * Size);
}
void Tank::Move(float ElapsedTime)
{
    TankSprite.Move(Speed * ElapsedTime, 0);
    if(TankSprite.GetPosition().x < 34.f * Size)
        TankSprite.SetX(34.f * Size);
    if((TankSprite.GetPosition().x + 34.f * Size) > 800)
        TankSprite.SetX(800 - 34.f * Size);

    MuzzleSprite.SetPosition(TankSprite.GetPosition().x, TankSprite.GetPosition().y - 20 * Size);
}
void Tank::RotateMuzzle(float ElapsedTime)
{
    MuzzleSprite.Rotate(ElapsedTime * RotationSpeed);
    if (90.f < MuzzleSprite.GetRotation() and MuzzleSprite.GetRotation() < 180.f)
        MuzzleSprite.SetRotation(90.f);
    if (180.f < MuzzleSprite.GetRotation() and MuzzleSprite.GetRotation() < 270.f)
        MuzzleSprite.SetRotation(270.f);

}
void Tank::Draw(void)
{
    App.Draw(TankSprite);
    App.Draw(MuzzleSprite);
}
float Tank::GetAngle(void) const
{
    return MuzzleSprite.GetRotation();
}
sf::Vector2f Tank::GetPosition(void) const
{
    return TankSprite.GetPosition();
}
sf::Vector2f Tank::GetMuzzlePosition(void) const
{
    sf::Vector2f h = MuzzleSprite.GetPosition();
    return sf::Vector2f(h.x - sin(MuzzleSprite.GetRotation()/180*Pi) * 55.f * Size, h.y - cos(MuzzleSprite.GetRotation()/180*Pi) * 55.f * Size);
}
bool Tank::PixelIsTank(sf::Vector2f Position) const
{
    sf::Vector2f a = TankSprite.TransformToLocal(Position);
    sf::Vector2i h(static_cast<int>(a.x), static_cast<int>(a.y));
    if(h.x >= 0 and h.y >= 0 and h.x < static_cast<int>(TankImage.GetWidth()) and h.y < static_cast<int>(TankImage.GetHeight()))
    {
        if(TankImage.GetPixel(h.x, h.y).a > 10)
            return true;
        else
            return false;
    }
    else
        return false;
}
void Tank::SetY(int PositionY)
{
    TankSprite.SetY(PositionY);
    MuzzleSprite.SetPosition(TankSprite.GetPosition().x, TankSprite.GetPosition().y - 20 * Size);
}
void Tank::SetX(int PositionX)
{
    TankSprite.SetX(PositionX);
    MuzzleSprite.SetPosition(TankSprite.GetPosition().x, TankSprite.GetPosition().y - 20 * Size);
}
void Tank::SetMuzzleRotation(float Angle)
{
    MuzzleSprite.SetRotation(Angle);
}
