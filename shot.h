#ifndef SHOT_H_INCLUDED
#define SHOT_H_INCLUDED

const float EarthAcceleration = 250;
const float AirResistenc = 0;//1.f / 50000.f;

class Shot
{
    public:
        Shot(sf::Vector2f, sf::Vector2f);
        ~Shot(){};
        static void Init(void);
        void Update(float ElapsedTime);
        void Draw(sf::RenderWindow&);
        sf::Vector2f GetPosition(void) const{return sShot.GetPosition();};
        static float AirSpeed;
    private:
        sf::Vector2f Speed;
        sf::Vector2f PrevPosition;
        static sf::Image IMGShot;
        sf::Sprite sShot;
};

#endif // SHOT_H_INCLUDED
