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
#include <iostream>

#include "button.h"

Button::Button(sf::RenderWindow &Window, sf::Vector2f Position, std::string IMGName) : App(Window)
{
    ButtonImage.LoadFromFile(IMGName);
    ButtonSprite.SetImage(ButtonImage);
    ButtonSprite.SetPosition(Position);
    MyPosition = Position;
    MyScale = sf::Vector2f(1.f, 1.f);
    Down = false;
}

Button::Button(sf::RenderWindow &Window, float PositionY, std::string IMGName) : App(Window)
{
    ButtonImage.LoadFromFile(IMGName);
    ButtonSprite.SetImage(ButtonImage);

    float PositionX = App.GetWidth() / 2 - ButtonImage.GetWidth() / 2;

    ButtonSprite.SetPosition(PositionX, PositionY);
    MyPosition = sf::Vector2f(PositionX, PositionY);
    MyScale = sf::Vector2f(1.f, 1.f);
    Down = false;
}


void Button::SetPosition(sf::Vector2f Position)
{
    ButtonSprite.SetPosition(Position);
    MyPosition = Position;
}

void Button::SetImage(std::string IMGName)
{
    ButtonImage.LoadFromFile(IMGName);
    ButtonSprite.SetImage(ButtonImage);
}

void Button::SetScale(sf::Vector2f Scale)
{
    ButtonSprite.SetScale(Scale);
    MyScale = Scale;
}

void Button::Resize(sf::Vector2f Size)
{
    ButtonSprite.Resize(Size);
    MyScale = ButtonSprite.GetScale();
}

sf::Vector2i Button::ImageSize(void) const
{
    return sf::Vector2i(static_cast<int>(ButtonImage.GetWidth()), static_cast<int>(ButtonImage.GetHeight()));
}

bool Button::Update(void) //true when pressed, else false
{
    const sf::Input &Input = App.GetInput();
    bool LeftMouseButton = Input.IsMouseButtonDown(sf::Mouse::Left);

    sf::Vector2f MousePos = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());

    if(ButtonSprite.GetPosition().x < MousePos.x and MousePos.x < (ButtonSprite.GetPosition().x + ButtonSprite.GetSize().x) and ButtonSprite.GetPosition().y < MousePos.y and MousePos.y < (ButtonSprite.GetPosition().y + ButtonSprite.GetSize().y)){
        if (!LeftMouseButton and Down)
        {
            Down = false;
            ButtonSprite.SetScale(1.0f * MyScale);
            ButtonSprite.SetPosition(MyPosition);
            return true;
        }
        ButtonSprite.SetScale(1.5f * MyScale);
        ButtonSprite.SetPosition(MyPosition.x - ButtonSprite.GetSize().x / 6, MyPosition.y - ButtonSprite.GetSize().y / 6);
    }
    else
    {
        ButtonSprite.SetScale(1.0f * MyScale);
        ButtonSprite.SetPosition(MyPosition);
    }

    Down = LeftMouseButton;
    return false;
}

void Button::Draw(void)
{
    App.Draw(ButtonSprite);
}
