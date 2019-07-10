#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED

#include <SFML/Graphics.hpp>

const float Size = 0.25f;
const int Speed = 50; //pixels per secound
const int RotationSpeed = 50; //degrees per secound

class Tank
{
    public:
        Tank(sf::RenderWindow &Window, sf::Color Color, int PositionX);
        ~Tank(){};
        void Move(float ElapsedTime);
        void RotateMuzzle(float ElapsedTime);
        void Draw(void);
        float GetAngle(void) const;
        sf::Vector2f GetPosition(void) const;
        sf::Vector2f GetMuzzlePosition(void) const;
        void SetY(int PositionY);
        void SetX(int PositionX);
        void SetMuzzleRotation(float Angle);
        bool PixelIsTank(sf::Vector2f Position) const;
    private:
        sf::RenderWindow &App;
        sf::Image MuzzleImage, TankImage;
        sf::Sprite MuzzleSprite, TankSprite;
};

#endif // TANK_H_INCLUDED
