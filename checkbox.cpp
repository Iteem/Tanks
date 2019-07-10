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

#include "checkbox.h"
#include <SFML/Graphics.hpp>

sf::Image CheckBox::BoxImage;
sf::Image CheckBox::CheckImage;

bool CheckBox::Init(void)
{
    return BoxImage.LoadFromFile("data/checkbox-box.png") and CheckImage.LoadFromFile("data/checkbox-check.png");
}

CheckBox::CheckBox(sf::RenderWindow &Window, sf::Vector2f Position, bool Status, float Scale) : App(Window)
{
    BoxSprite.SetImage(BoxImage);
    CheckSprite.SetImage(CheckImage);
    BoxSprite.SetPosition(Position);
    CheckSprite.SetPosition(Position);
    BoxSprite.SetScale(Scale, Scale);
    CheckSprite.SetScale(Scale, Scale);
    MyPosition = Position;
    MyStatus = Status;
    MyScale = Scale;
}

void CheckBox::SetPosition(sf::Vector2f Position)
{
    BoxSprite.SetPosition(Position);
    CheckSprite.SetPosition(Position);
    MyPosition = Position;
}

void CheckBox::SetScale(float Scale)
{
    BoxSprite.SetScale(Scale, Scale);
    CheckSprite.SetScale(Scale, Scale);
    MyScale = Scale;
}

void CheckBox::Resize(float Size)
{
    BoxSprite.Resize(Size, Size);
    CheckSprite.Resize(Size, Size);
    MyScale = BoxSprite.GetScale().x;
}

bool CheckBox::Update(void) //true when pressed, else false
{
    const sf::Input &Input = App.GetInput();
    bool LeftMouseButton = Input.IsMouseButtonDown(sf::Mouse::Left);

    sf::Vector2f MousePos = App.ConvertCoords(App.GetInput().GetMouseX(), App.GetInput().GetMouseY());

    if(BoxSprite.GetPosition().x  < MousePos.x and MousePos.x < (BoxSprite.GetPosition().x + BoxSprite.GetSize().x) and BoxSprite.GetPosition().y < MousePos.y and MousePos.y < (BoxSprite.GetPosition().y + BoxSprite.GetSize().y)){
        if (!LeftMouseButton and Down)
                MyStatus = !MyStatus;
        BoxSprite.SetScale(1.5f * MyScale, 1.5f * MyScale);
        BoxSprite.SetPosition(MyPosition.x - BoxSprite.GetSize().x / 6, MyPosition.y - BoxSprite.GetSize().y / 6);
        CheckSprite.SetScale(1.5f * MyScale, 1.5f * MyScale);
        CheckSprite.SetPosition(MyPosition.x - CheckSprite.GetSize().x / 6, MyPosition.y - CheckSprite.GetSize().y / 6);
    }
    else
    {
        BoxSprite.SetScale(1.0f * MyScale, 1.0f * MyScale);
        BoxSprite.SetPosition(MyPosition);
        CheckSprite.SetScale(1.0f * MyScale, 1.0f * MyScale);
        CheckSprite.SetPosition(MyPosition);
    }

    Down = LeftMouseButton;
    return MyStatus;
}

void CheckBox::Draw(void)
{
    App.Draw(BoxSprite);
    if(MyStatus)
        App.Draw(CheckSprite);
}

