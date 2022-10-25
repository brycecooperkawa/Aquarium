/**
 * @file Fish.cpp
 * @author Bryce Cooperkawa
 */

#include "pch.h"
#include "Fish.h"
#include "Aquarium.h"

/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 20;

///makes sure the custom features only work once per fish
int betacheck=1;
int angelcheck=1;
int magicheck=1;

/**
 * Constructor
 * @param aquarium The aquarium we are in
 * @param filename Filename for the image we use
 */
Fish::Fish(Aquarium *aquarium, const std::wstring &filename) :
        Item(aquarium, filename)
{
    std::uniform_real_distribution<> distribution(MinSpeedX, MaxSpeedX);
    mSpeedX = distribution(aquarium->GetRandom());
    mSpeedY = distribution(aquarium->GetRandom());
}

/**
 * Handle updates in time of our fish
 *
 * This is called before we draw and allows us to
 * move our fish. We add our speed times the amount
 * of time that has elapsed.
 * @param elapsed Time elapsed since the class call
 */
void Fish::Update(double elapsed)
{
    //implements the unique feature of each fish
    int c=Custom();

    //makes the beta fish go fast
    if(c==0 && betacheck==1)
    {
        mSpeedX=mSpeedX*5;
        mSpeedY=mSpeedY*2;
        betacheck=0;
    }

    //makes the angel fish go backwards at the start
    if(c==1 && angelcheck==1)
    {
        mSpeedX=mSpeedX*-1;
        mSpeedY=mSpeedY*-1;
        angelcheck=0;
    }

    //makes the magikarp evolve when it hits the right wall for the first time
    //magikarp becomes a gyarados!!!
    if(c==2 && magicheck==1 && mSpeedX<0)
    {
        Evolve();
    }

    SetLocation(GetX() + mSpeedX * elapsed,
            GetY() + mSpeedY * elapsed);

    //calculates when to flip on the right side
    double right=GetAquarium()->GetWidth()-10-(GetItemWidth()/2);

    //calculates when to flip on the left side
    double left=10+(GetItemWidth()/2);

    //calculates when to make the fish go up
    double bottom=GetAquarium()->GetHeight()-10-(GetItemHeight()/2);

    //calculates when to make the fish go down
    double top=10+(GetItemHeight()/2);

    //flips fish when it gets close to the right side of the tank
    if (mSpeedX > 0 && GetX() >= right)
    {
        mSpeedX = -mSpeedX;
        SetMirror(true);
    }

    //flips the fish when it gets close to the left side of the tank
    if (mSpeedX < 0 && GetX() <= left)
    {
        mSpeedX = -mSpeedX;
        SetMirror(false);
    }

    //flips fish direction when it gets close to the bottom of the tank
    if (mSpeedY > 0 && GetY() >= bottom)
    {
        mSpeedY = -mSpeedY;
    }

    //flips the fish when it gets close to the left side of the tank
    if (mSpeedY < 0 && GetY() <= top)
    {
        mSpeedY = -mSpeedY;
    }

    //if the mirror is true it flips the fish
    if(GetMirror()==true)
    {
        SetBitmap(true);
    }

    //if the mirror is false it unflips the fish
    if(GetMirror()==false)
    {
        SetBitmap(false);
    }

}