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
#include <string>
#include <list>
#include <cmath>

#include "terrain.h"
#include "tank.h"
#include "shot.h"

#include "player.h"

const float Pi = 3.14159265;

Terrain *Player::MyTerrain;

Player::Player(sf::RenderWindow &Window, std::string Name, int Money, int Score, sf::Color Color, int PositionX) : App(Window) , MyTank(App, Color, PositionX)
{
    MyName = Name;
    MyMoney = Money;
    MyScore = Score;
    MyColor = Color;
    ShotStrength = 50;
    MaxFuel = 10;
    Fuel = MaxFuel;
    MaxLive = 100;
    Live = MaxLive;
    MyWeapons = NULL;
}
Player::~Player()
{
    if(MyWeapons != NULL)
        delete[] MyWeapons;
}
void Player::Init(Terrain *InTerrain)
{
    MyTerrain = InTerrain;
}
void Player::DrawTank(void)
{
    MyTank.Draw();
}
void Player::SmallUpdateTank(void)
{
    MyTank.SetY(MyTerrain->GetHighestPoint(static_cast<int>(MyTank.GetPosition().x)));
}
void Player::AddShotStrength(float Add)
{
    ShotStrength += Add;
    if(ShotStrength > 100)
        ShotStrength = 100;
    else if(ShotStrength < 0)
        ShotStrength = 0;
}
int Player::Explosion(float Damage, sf::Vector2f Position, float MaxRadius)
{
    float h = sqrt(pow(Position.x - MyTank.GetPosition().x,2) + pow(Position.y - MyTank.GetPosition().y,2));
    if(h<MaxRadius)
    {
        float re = Damage * (1 - h / MaxRadius);
        Live -= re;
        return static_cast<int>(re);
    }
    else
        return 0;
}
void Player::SetNumberOfWeapons(int NumberOfWeapons)
{
    if(MyWeapons == NULL)
        MyWeapons = new int[NumberOfWeapons];
}
HumanPlayer::HumanPlayer(sf::RenderWindow &Window, std::string Name, int Money, int Score, sf::Color Color, int PositionX)
: Player(Window, Name, Money, Score, Color, PositionX)
{
}

bool HumanPlayer::UpdateTank(float ElapsedTime, std::list<Shot *> &InShots)
{
    const sf::Input &Input = App.GetInput();

    if(Input.IsKeyDown(sf::Key::P))
        AddShotStrength(ElapsedTime * 10.f);
    if(Input.IsKeyDown(sf::Key::M))
        AddShotStrength(-ElapsedTime * 10.f);

    if(Player::GetFuel() > 0.f)//move tank
    {
        if(Input.IsKeyDown(sf::Key::Left) xor Input.IsKeyDown(sf::Key::Right))
        {
            if (Input.IsKeyDown(sf::Key::Left))
            {
                MyTank.Move(-ElapsedTime);
                AddFuel(-ElapsedTime);
            }
            if (Input.IsKeyDown(sf::Key::Right))
            {
                MyTank.Move(ElapsedTime);
                AddFuel(-ElapsedTime);
            }
        }
    }

    //Rohr drehen
    if (Input.IsKeyDown(sf::Key::Down))
        MyTank.RotateMuzzle(ElapsedTime);
    if (Input.IsKeyDown(sf::Key::Up))
        MyTank.RotateMuzzle(-ElapsedTime);

    MyTank.SetY(MyTerrain->GetHighestPoint(static_cast<int>(MyTank.GetPosition().x)));

    if(InShots.empty())
    {
        if(Input.IsKeyDown(sf::Key::Space))
        {
            InShots.push_back(new Shot(MyTank.GetMuzzlePosition(), sf::Vector2f(cos((-GetAngle() + 270)* Pi / 180.f) * 6.f * GetShotStrength(), sin((-GetAngle() + 270)* Pi / 180.f) * 6.f * GetShotStrength())));
            return true;
        }
    }
    return false;
}

KIPlayer::KIPlayer(sf::RenderWindow &Window, std::string Name, int Money, int Score, sf::Color Color, int PositionX)
: Player(Window, Name, Money, Score, Color, PositionX)
{
}

bool KIPlayer::UpdateTank(float ElapsedTime, std::list<Shot *> &InShots)
{
    static int direction = 1;

    if(sf::Randomizer::Random(1, 500) == 1)
        direction *= -1;

    MyTank.Move(ElapsedTime * direction);
    MyTank.SetY(MyTerrain->GetHighestPoint(static_cast<int>(MyTank.GetPosition().x)));

    if(sf::Randomizer::Random(1,500) == 1)
    {
        InShots.push_back(new Shot(MyTank.GetMuzzlePosition(), sf::Vector2f(cos((-MyTank.GetAngle() + 270)* Pi / 180.f) * 6.f * GetShotStrength(), sin((-MyTank.GetAngle() + 270)* Pi / 180.f) * 6.f * GetShotStrength())));
        return true;
    }
    return false;
}
