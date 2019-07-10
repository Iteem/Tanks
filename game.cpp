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
#include <list>
#include <cstdio>
#include <iostream>
using namespace::std;

#include "terrain.h"
#include "player.h"
#include "shot.h"
#include "explosion.h"
#include "button.h"

#include "game.h"

Game::~Game()
{
    KillPlayers();
}

void Game::AddPlayer(std::string Name, int Money, int Score, sf::Color Color, int PositionX)
{
    Players.push_back(new HumanPlayer(App, Name, Money, Score, Color, PositionX));
}

void Game::KillPlayers(void)
{
    for(std::list<Player *>::iterator i = Players.begin();i != Players.end();)
    {
        delete *i;
        i = Players.erase(i);
    }
}
bool Game::Run(sf::Font &Font)
{
    //text to display
    sf::String TextName("Name", Font, 15);
    TextName.SetColor(sf::Color::Blue);
    TextName.SetPosition(10, 10);
    sf::String TextShotStrenght("Schussstärke:", Font, 15);
    TextShotStrenght.SetPosition(10, 30);
    TextShotStrenght.SetColor(sf::Color::Black);
    sf::String TextAngle("Winkel:", Font, 15);
    TextAngle.SetPosition(10, 50);
    TextAngle.SetColor(sf::Color::Black);
    sf::String TextFuel("Treibstoff:", Font, 15);
    TextFuel.SetPosition(10, 70);
    TextFuel.SetColor(sf::Color::Black);
    sf::String TextLive("Leben:", Font, 15);
    TextLive.SetPosition(10, 90);
    TextLive.SetColor(sf::Color::Black);
    sf::String TextScore("Score", Font, 15);
    TextScore.SetPosition(10, 110);
    TextScore.SetColor(sf::Color::Black);
    sf::String TextRound("Runde:", Font, 15);
    TextRound.SetPosition(710, 10);
    TextRound.SetColor(sf::Color::Blue);

    sf::String ValueShotStrenght("50", Font, 15);
    ValueShotStrenght.SetPosition(110, 30);
    ValueShotStrenght.SetColor(sf::Color::Red);
    sf::String ValueAngle("0", Font, 15);
    ValueAngle.SetPosition(110, 50);
    ValueAngle.SetColor(sf::Color::Red);
    sf::String ValueFuel("10", Font, 15);
    ValueFuel.SetPosition(110, 70);
    ValueFuel.SetColor(sf::Color::Red);
    sf::String ValueLive("100", Font, 15);
    ValueLive.SetPosition(110, 90);
    ValueLive.SetColor(sf::Color::Red);
    sf::String ValueScore("100", Font, 15);
    ValueScore.SetPosition(110, 110);
    ValueScore.SetColor(sf::Color::Red);
    sf::String ValueRound("1", Font, 15);
    ValueRound.SetPosition(760, 10);
    ValueRound.SetColor(sf::Color::Blue);


    //init players, shots and explosions
    Shot::Init();
    std::list<Shot *> Shots;
    Explosion::Init();
    std::list<Explosion *> Explosions;
    Terrain MyTerrain(App);
    Player::Init(&MyTerrain);

    std::list<Player *> RoundPlayers = Players;
    std::list<Player *>::iterator CurPlayer = RoundPlayers.begin();

    bool GameIsRunning = true;
    bool NextPlayer = false;
    int Round = 1;

    sf::Event Event;

    while(true)
    {
        while(GameIsRunning)
        {
            while(App.GetEvent(Event))
            {
                if(Event.Type == sf::Event::Closed)
                {
                    for(std::list<Shot*>::iterator pos = Shots.begin(); pos != Shots.end();)
                    {
                        delete *pos;
                        pos = Shots.erase(pos);
                    }
                    for(std::list<Explosion *>::iterator pos = Explosions.begin(); pos != Explosions.end();)
                    {
                        delete *pos;
                        pos = Explosions.erase(pos);
                    }
                    return false;
                }
                if(Event.Type == sf::Event::KeyPressed and Event.Key.Code == sf::Key::Escape)
                {
                    for(std::list<Shot*>::iterator pos = Shots.begin(); pos != Shots.end();)
                    {
                        delete *pos;
                        pos = Shots.erase(pos);
                    }
                    for(std::list<Explosion *>::iterator pos = Explosions.begin(); pos != Explosions.end();)
                    {
                        delete *pos;
                        pos = Explosions.erase(pos);
                    }
                    return true;
                }
            }

            float ElapsedTime = App.GetFrameTime();

            App.Clear(sf::Color::White);


            for(std::list<Player *>::iterator i = RoundPlayers.begin(); i != RoundPlayers.end(); ++i)
            {
                if(i != CurPlayer or NextPlayer)
                    (*i)->SmallUpdateTank();
            }
            if(!NextPlayer)
                NextPlayer = (*CurPlayer)->UpdateTank(ElapsedTime, Shots);

            MyTerrain.Draw();

            for(std::list<Shot*>::iterator pos = Shots.begin(); pos != Shots.end();)
            {
                (*pos)->Update(ElapsedTime);
                bool h = false;
                for(std::list<Player *>::iterator i = RoundPlayers.begin(); i != RoundPlayers.end(); ++i)
                {
                    if((*i)->PixelIsTank((*pos)->GetPosition()))
                        h = true;
                }
                if(!MyTerrain.IsTerrain(static_cast<int>((*pos)->GetPosition().x),static_cast<int>((*pos)->GetPosition().y)) and !h)
                {
                    (*pos)->Draw(App);
                    ++pos;
                }
                else
                {
                    if(!((*pos)->GetPosition().x < 0.f or (*pos)->GetPosition().x > 800))
                        Explosions.push_back(new Explosion((*pos)->GetPosition(), 15));
                    delete *pos;
                    pos = Shots.erase(pos);
                }
            }

            for(std::list<Explosion*>::iterator pos = Explosions.begin(); pos != Explosions.end();)
            {
                (*pos)->Update(ElapsedTime);
                if(!((*pos)->End))
                {
                    (*pos)->Draw(App);
                    ++pos;
                }
                else
                {
                    MyTerrain.Explosion((*pos)->GetPosition(), (*pos)->GetMaxRadius());
                    for(std::list<Player *>::iterator i = RoundPlayers.begin(); i != RoundPlayers.end(); ++i)
                    {
                        int h;
                        if((*i)->PixelIsTank((*pos)->GetPosition()))
                            h = (*i)->Explosion(25, (*i)->GetPosition(), 1);
                        else
                            h = (*i)->Explosion(25, (*pos)->GetPosition(), (*pos)->GetMaxRadius());
                        if(i == CurPlayer)
                            h *= -1;
                        (*CurPlayer)->AddMoney(h);
                        (*CurPlayer)->AddScore(h);
                    }
                    delete *pos;
                    pos = Explosions.erase(pos);
                }
            }

            if(Explosions.empty() and Shots.empty() and NextPlayer)
            {
                NextPlayer = false;
                CurPlayer++;
                if(CurPlayer == RoundPlayers.end())
                    CurPlayer = RoundPlayers.begin();
                for(std::list<Player *>::iterator i = RoundPlayers.begin(); i != RoundPlayers.end();)
                {
                    if((*i)->GetLive() < 1)
                    {
                        if(i == CurPlayer)
                        {
                            CurPlayer++;
                            if(CurPlayer == RoundPlayers.end())
                                CurPlayer = RoundPlayers.begin();
                        }
                        i = RoundPlayers.erase(i);
                    }
                    else
                        ++i;
                }
                if(RoundPlayers.size() == 1)
                {
                    GameIsRunning = false;
                }
            }

            char Buffer[20];
            sprintf(Buffer, ((*CurPlayer)->GetName()).c_str());
            TextName.SetText(Buffer);
            sprintf(Buffer, "%i", (*CurPlayer)->GetShotStrength());
            ValueShotStrenght.SetText(Buffer);
            sprintf(Buffer, "%i", ((*CurPlayer)->GetAngle()+90)%360);
            ValueAngle.SetText(Buffer);
            sprintf(Buffer, "%i", (*CurPlayer)->GetFuel());
            ValueFuel.SetText(Buffer);
            sprintf(Buffer, "%i", (*CurPlayer)->GetLive());
            ValueLive.SetText(Buffer);
            sprintf(Buffer, "%i", (*CurPlayer)->GetScore());
            ValueScore.SetText(Buffer);
            sprintf(Buffer, "%i", Round);
            ValueRound.SetText(Buffer);

            for(std::list<Player *>::iterator i = RoundPlayers.begin(); i != RoundPlayers.end(); ++i)
                (*i)->DrawTank();

            App.Draw(TextName);
            App.Draw(TextShotStrenght);
            App.Draw(TextAngle);
            App.Draw(TextFuel);
            App.Draw(TextLive);
            App.Draw(TextScore);
            App.Draw(TextRound);
            App.Draw(ValueShotStrenght);
            App.Draw(ValueAngle);
            App.Draw(ValueFuel);
            App.Draw(ValueLive);
            App.Draw(ValueScore);
            App.Draw(ValueRound);

            App.Display();
        }

        Button Go(App, sf::Vector2f(353, 400), "data/go-de.png");

        while(!GameIsRunning)
        {
            while(App.GetEvent(Event))
            {
                if(Event.Type == sf::Event::Closed)
                    return false;
                if(Event.Type == sf::Event::KeyPressed and Event.Key.Code == sf::Key::Escape)
                    return true;
            }
            if(Go.Update())
                break;

            App.Clear(sf::Color::Black);
            Go.Draw();
            App.Display();
        }

        (*CurPlayer)->AddScore(100);
        RoundPlayers = Players;
        CurPlayer = RoundPlayers.begin();

        int h = 800 / (RoundPlayers.size() + 1);
        int a = 1;
        for(std::list<Player *>::iterator i = RoundPlayers.begin(); i != RoundPlayers.end(); i++)
        {
            (*i)->ResetLive();
            (*i)->ResetFuel();
            (*i)->ResetShotStrength();
            (*i)->ResetMuzzle();
            (*i)->SetX(h*a);
            a++;
        }


        MyTerrain.Remake();
        Round++;
        GameIsRunning = true;
    }
}
