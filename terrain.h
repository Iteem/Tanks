/*
   Copyright 2009 Patrick Winkler

   This file is part of Tanks

   Tanks software is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   Tanks software is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

class Terrain
{
    public:
        Terrain(sf::RenderWindow &Window);
        ~Terrain(){};
        void Remake(void);
        void Draw(void);
        bool IsTerrain(int x, int y) const;
        int GetHighestPoint(int) const;
        void Explosion(sf::Vector2f Position, float Radius);
    private:
        sf::Image IMGTerrain, IMGBackground;
        sf::Sprite sTerrain, sBackground;
        bool bTerrain[800][600];
        int TerrainHighestPoint[800];
        sf::RenderWindow &App;
};

#endif // TERRAIN_H_INCLUDED
