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

#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include <list>

#include "terrain.h"
#include "tank.h"
#include "shot.h"

class Player
{
    private:
        std::string MyName;
        int MyMoney;
        int MyScore;
        float ShotStrength;
        float Fuel;
        int MaxFuel;
        float Live;
        int MaxLive;
        sf::Color MyColor;
        int *MyWeapons;
    protected:
        sf::RenderWindow &App;
        static Terrain *MyTerrain;
        Tank MyTank;
    public:
        Player(sf::RenderWindow &Window, std::string Name, int Money, int Score, sf::Color Color, int PositionX);
        virtual ~Player();
        static void Init(Terrain *InTerrain);
        virtual bool UpdateTank(float ElapsedTime, std::list<Shot *> &InShots) = 0;
        void SmallUpdateTank(void);
        void DrawTank(void);
        bool PixelIsTank(sf::Vector2f Position){return MyTank.PixelIsTank(Position);};
        int Explosion(float Damage, sf::Vector2f Position, float MaxRadius);
        void SetName(std::string Name){MyName = Name;};
        void SetMoney(int Money){MyMoney = Money;};
        void SetScore(int Score){MyScore = Score;};
        void SetColor(sf::Color Color){MyColor = Color;};
        void SetX(int PositionX){MyTank.SetX(PositionX);};
        void ResetLive(void){Live = MaxLive;};
        void ResetFuel(void){Fuel = MaxFuel;};
        void ResetMuzzle(void){MyTank.SetMuzzleRotation(0);};
        void ResetShotStrength(void){ShotStrength = 50;};
        sf::Vector2f GetPosition(void){return MyTank.GetPosition();};
        std::string GetName(void) const{return MyName;};
        int GetMoney(void) const{return MyMoney;};
        int GetScore(void) const{return MyScore;};
        sf::Color GetColor(void) const{return MyColor;};
        int GetAngle(void) const{return static_cast<int>(MyTank.GetAngle());};
        int GetFuel(void) const{return static_cast<int>(Fuel);};
        int GetMaxFuel(void) const{return MaxFuel;};
        int GetLive(void) const{return static_cast<int>(Live);};
        int GetMaxLive(void) const{return MaxLive;};
        int GetShotStrength(void) const{return static_cast<int>(ShotStrength);};
        void AddMoney(int Add){MyMoney += Add;};
        void AddScore(int Add){MyScore += Add;};
        void AddFuel(float Add){Fuel += Add;};
        void AddMaxFuel(int Add){MaxFuel += Add;};
        void AddLive(float Add){Live += Add;};
        void AddMaxLive(int Add){MaxLive += Add;};
        void AddShotStrength(float Add);
        void SetNumberOfWeapons(int NumberOfWeapons);
};

class HumanPlayer : public Player
{
    public:
        HumanPlayer(sf::RenderWindow &Window, std::string Name, int Money, int Score, sf::Color Color, int PositionX);
        virtual ~HumanPlayer(){};
        virtual bool UpdateTank(float ElapsedTime, std::list<Shot *> &InShots);
};

class KIPlayer : public Player
{
    public:
        KIPlayer(sf::RenderWindow &Window, std::string Name, int Money, int Score, sf::Color Color, int PositionX);
        virtual ~KIPlayer(){};
        virtual bool UpdateTank(float ElapsedTime, std::list<Shot *> &InShots);
};

#endif // PLAYER_H_INCLUDED
