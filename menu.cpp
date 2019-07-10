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
#include <SFML/Audio.hpp>
#include <iostream>
using namespace::std;

#include "options.h"
#include "game.h"
#include "button.h"
#include "checkbox.h"

#include "menu.h"

const int SizeOfQuadrat = 150;
const sf::Color QuadratColor(146, 210, 125);

enum Side
{
    MainSide,
    PlaySide,
    HelpSide,
    OptionsSide
};

bool Menu::Run(sf::Font &Font, sf::Music &MyMusic)
{
    //for current side
    Side CurSide = MainSide;

    //for background and title
    sf::Image IMGBackground, IMGTitle;
    sf::Sprite Background, Title;

    //make background
    sf::Image IMGQuadrat(SizeOfQuadrat, SizeOfQuadrat, QuadratColor);
    IMGBackground.Create(1200, 1200, sf::Color(255, 255, 255));
    for(unsigned int i=0; i<1200; i+=SizeOfQuadrat)
    {
        for(unsigned int j=0; j<1200; j+=SizeOfQuadrat * 2)
            IMGBackground.Copy(IMGQuadrat, i, j);
        i+=SizeOfQuadrat;
        for(unsigned int j=SizeOfQuadrat; j<1200; j+=SizeOfQuadrat * 2)
            IMGBackground.Copy(IMGQuadrat, i, j);
    }
    Background.SetImage(IMGBackground);
    Background.SetCenter(600, 600);
    Background.SetPosition(800 / 2, 600 / 2);

    //load title
    IMGTitle.LoadFromFile("data/Title.png");
    Title.SetImage(IMGTitle);
    Title.SetPosition((800 - Title.GetSize().x) / 2, (600 - Title.GetSize().y) / 5);

    //make buttons
    CheckBox::Init();
    Button Play(App, 250, "data/play-de.png");
    Button Optionsb(App, 320, "data/options-de.png");
    Button Help(App, 390, "data/help-de.png");
    Button Exit(App, 460, "data/exit-de.png");
    Button Back(App, 500, "data/back-de.png");

    Button Go(App, sf::Vector2f(353, 400), "data/go-de.png");
    Button Plus(App, sf::Vector2f(461, 306), "data/plus.png");
    Plus.SetScale(sf::Vector2f(0.5f, 0.5f));
    Button Minus(App, sf::Vector2f(438, 309), "data/minus.png");
    Minus.SetScale(sf::Vector2f(0.5f, 0.5f));
    sf::String TextNumberOfPlayers("Anzahl Spieler:", Font, 15);
    TextNumberOfPlayers.SetPosition(330,300);
    TextNumberOfPlayers.SetColor(sf::Color::Black);
    int NumberOfPlayers = 2;
    sf::String ValueNumberOfPlayers("2", Font, 15);
    ValueNumberOfPlayers.SetPosition(450,300);
    ValueNumberOfPlayers.SetColor(sf::Color::Black);

    CheckBox Music(App, sf::Vector2f(430,350), true);
    sf::String TextMusic("Musik an/aus:", Font, 15);
    TextMusic.SetPosition(330,352);
    TextMusic.SetColor(sf::Color::Black);

    sf::String TextHelp1("Pfeiltatsten: Tank bewegen / Rohr drehen", Font, 15);
    TextHelp1.SetPosition(250,280);
    TextHelp1.SetColor(sf::Color::Black);
    sf::String TextHelp2("P und M: Schuss-stärke (P)lus / (M)inus", Font, 15);
    TextHelp2.SetPosition(250,300);
    TextHelp2.SetColor(sf::Color::Black);
    sf::String TextHelp3("Space: Schiessen", Font, 15);
    TextHelp3.SetPosition(250,320);
    TextHelp3.SetColor(sf::Color::Black);
    sf::String TextHelp4("Musik: The Hit - Goto80", Font, 15);
    TextHelp4.SetPosition(250,340);
    TextHelp4.SetColor(sf::Color::Black);
    sf::String TextHelp5("Version 0.1", Font, 15);
    TextHelp5.SetPosition(250,360);
    TextHelp5.SetColor(sf::Color::Black);


    sf::Event Event;

    //game loop
    while(true)
    {
        //event Handling
        while(App.GetEvent(Event))
        {
            if (Event.Type == sf::Event::Closed)
                return false;
            if (Event.Type == sf::Event::KeyPressed and Event.Key.Code == sf::Key::Escape)
            {
                //go back to a other Side
                switch(CurSide)
                {
                    case MainSide:
                        return false;
                    default:
                        CurSide = MainSide;
                }
            }
        }
        //rotate background
        Background.Rotate(5.f * App.GetFrameTime());

        //update current side
        switch(CurSide)
        {
            case MainSide:
                if(Play.Update())
                    CurSide = PlaySide;
                if(Optionsb.Update())
                    CurSide = OptionsSide;
                if(Help.Update())
                    CurSide = HelpSide;
                if(Exit.Update())
                    return false;
                break;

            case PlaySide:
                if(Plus.Update())
                {
                    if(NumberOfPlayers < 6)
                    {
                        ++NumberOfPlayers;
                        char Buffer[2];
                        sprintf(Buffer, "%i", NumberOfPlayers);
                        ValueNumberOfPlayers.SetText(Buffer);
                    }
                }
                if(Minus.Update())
                {
                    if(NumberOfPlayers > 2)
                    {
                        --NumberOfPlayers;
                        char Buffer[2];
                        sprintf(Buffer, "%i", NumberOfPlayers);
                        ValueNumberOfPlayers.SetText(Buffer);
                    }
                }
                if(Go.Update())
                {
                    MyGame.KillPlayers();
                    int h = 800 / (NumberOfPlayers + 1);
                    MyGame.AddPlayer("Player1", 0, 0, sf::Color::Green,  h);
                    MyGame.AddPlayer("Player2", 0, 0, sf::Color::Blue, 2*h);
                    if(NumberOfPlayers >= 3)
                        MyGame.AddPlayer("Player3", 0, 0, sf::Color::Yellow, 3*h);
                    if(NumberOfPlayers >= 4)
                        MyGame.AddPlayer("Player4", 0, 0, sf::Color::Red,    4*h);
                    if(NumberOfPlayers >= 5)
                        MyGame.AddPlayer("Player5", 0, 0, sf::Color::Black,  5*h);
                    if(NumberOfPlayers >= 6)
                        MyGame.AddPlayer("Player6", 0, 0, sf::Color::White,  6*h);
                    return true;
                }
                break;

            case HelpSide:
                if(Back.Update())
                    CurSide = MainSide;
                break;

            case OptionsSide:
                if(Music.Update())
                {
                    if(MyMusic.GetStatus() != sf::Music::Playing)
                        MyMusic.Play();
                }
                else
                {
                    if(MyMusic.GetStatus() == sf::Music::Playing)
                        MyMusic.Pause();
                }
                if(Back.Update())
                    CurSide = MainSide;
                break;
        }

        //render new frame
        App.Clear(sf::Color(255, 255, 255));

        App.Draw(Background);
        App.Draw(Title);

        //draw current side
        switch(CurSide)
        {
            case MainSide:
                Play.Draw();
                Optionsb.Draw();
                Help.Draw();
                Exit.Draw();
                break;
            case PlaySide:
                Go.Draw();
                Minus.Draw();
                Plus.Draw();
                App.Draw(TextNumberOfPlayers);
                App.Draw(ValueNumberOfPlayers);
                break;
            case HelpSide:
                App.Draw(TextHelp1);
                App.Draw(TextHelp2);
                App.Draw(TextHelp3);
                App.Draw(TextHelp4);
                App.Draw(TextHelp5);
                Back.Draw();
                break;
            case OptionsSide:
                Music.Draw();
                App.Draw(TextMusic);
                Back.Draw();
                break;
        }

        App.Display();
    }

}
