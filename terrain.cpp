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

#include "terrain.h"

Terrain::Terrain(sf::RenderWindow &Window) : App(Window)
{
    IMGBackground.LoadFromFile("data/background-forest.png");
    sBackground.SetImage(IMGBackground);


    IMGTerrain.Create(800, 600, sf::Color(255,255,255,0));
    IMGTerrain.SetSmooth(false);

    Remake();

    sTerrain.SetImage(IMGTerrain);
}

void Terrain::Remake(void)
{
    IMGTerrain.Create(800, 600, sf::Color(255,255,255,0));

    for(int i = 0; i < 800; ++i)
    {
        for(int j = 0; j < 600; ++j)
            bTerrain[i][j] = false;
    }

    int NumberOfPoints = sf::Randomizer::Random(5, 7);
    int NumberOfPointsT = NumberOfPoints*2-1;
    int *PointsY = new int[NumberOfPointsT];
    int *PointsX = new int[NumberOfPointsT];

    for(int i = 0; i < NumberOfPoints; ++i)
        PointsY[2*i] = sf::Randomizer::Random(380, 480);
    for(int i = 1; i < NumberOfPointsT; i+=2)
        PointsY[i] = (PointsY[i-1] + PointsY[i+1]) / 2;
    for(int i = 0; i < NumberOfPointsT; ++i)
        PointsX[i] = static_cast<int>(800 / static_cast<float>(NumberOfPointsT - 1) * i);
    for(int i = 2; i < NumberOfPointsT - 2; i+=2)
        PointsX[i] += sf::Randomizer::Random(-10, 10);

    for(int i = 0; i < NumberOfPointsT - 1; ++i)
    {
        int Py,Px,Sy,Sx;
        if(i%2)
        {
            Sx = PointsX[i+1];
            Sy = PointsY[i+1];
            Px = PointsX[i];
            Py = PointsY[i];
        }
        else
        {
            Sx = PointsX[i];
            Sy = PointsY[i];
            Px = PointsX[i+1];
            Py = PointsY[i+1];
        }

        float a = static_cast<float>((Py-Sy))/static_cast<float>((Px-Sx)*(Px-Sx));

        for(int j = PointsX[i]; j < PointsX[i+1]; ++j)
            TerrainHighestPoint[j] = static_cast<int>(a*(pow(j-Sx,2))+Sy);

    }

    for(int i = 0; i < 800; ++i)
    {
        for(int j = TerrainHighestPoint[i]; j < 600; ++j)
        {
            IMGTerrain.SetPixel(i, j, sf::Color(119,171,0));
            bTerrain[i][j] = true;
        }
    }
}

void Terrain::Draw(void)
{
    App.Draw(sBackground);
    App.Draw(sTerrain);
}

bool Terrain::IsTerrain(int x, int y) const
{
    if(-1 < x and x < 800 and -1 < y and y < 600)
        return bTerrain[x][y];
    else
    {
        if(y < 0 and -1 < x and x < 800)
            return false;
        else
            return true;
    }
}

int Terrain::GetHighestPoint(int x) const
{
    return TerrainHighestPoint[x];
}

void Terrain::Explosion(sf::Vector2f Position, float Radius)
{

    float Rs = Radius * Radius;
    for(int i = static_cast<int>(-Radius); i <= static_cast<int>(Radius); ++i)
    {
        int x = i+static_cast<int>(Position.x);
        int is = i*i;
        for(int j = static_cast<int>(-Radius); j <= static_cast<int>(Radius); ++j)
        {
            if(is + j*j < Rs)
            {
                int y = j+static_cast<int>(Position.y);
                if(0 <= x and x < 800 and 0 <= y and y < 600)
                {
                    bTerrain[x][y] = false;
                    IMGTerrain.SetPixel(x, y, sf::Color(0,0,0,0));
                    //if(TerrainHighestPoint[x] < y)
                    //    TerrainHighestPoint[x] = y;
                }
            }
        }
    }

    for(int i = static_cast<int>(Position.x - Radius); i <= static_cast<int>(Position.x + Radius); ++i)
    {
        int h = 0;
        bool k = false;
        for(int j = TerrainHighestPoint[i]; j <= static_cast<int>(Position.y + Radius); ++j)
        {
            if(0 <= i and i < 800 and 0 <= j and j < 600)
            {
                if(!bTerrain[i][j] and k)
                    h++;
                else
                    k = true;
            }
        }

        for(int j = TerrainHighestPoint[i]; j < TerrainHighestPoint[i] + h; ++j)
        {
            if(0 <= i and i < 800 and 0 <= j and j < 600)
            {
                bTerrain[i][j] = false;
                IMGTerrain.SetPixel(i, j, sf::Color(0,0,0,0));
            }
        }

        TerrainHighestPoint[i] += h;

        for(int j = static_cast<int>(Position.y + Radius); j >= TerrainHighestPoint[i]; --j)
        {
            if(0 <= i and i < 800 and 0 <= j and j < 600)
            {
                bTerrain[i][j] = true;
                IMGTerrain.SetPixel(i, j, sf::Color(119,171,0));
            }
        }
    }
}
