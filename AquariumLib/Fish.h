/**
 * @file Fish.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef AQUARIUM_FISH_H
#define AQUARIUM_FISH_H

#include "Item.h"
#include <wx/dc.h>

/**
 * Base class for a fish
 * This applies to all of the fish, but not the decor
 * items in the aquarium.
 */
class Fish : public Item {
private:
    /// Fish speed in the X direction
    /// in pixels per second
    double mSpeedX;

    /// Fish speed in the Y direction
    /// in pixels per second
    double mSpeedY;

protected:
    Fish(Aquarium *aquarium, const std::wstring &filename);

public:
    /// Default constructor (disabled)
    Fish() = delete;

    /// Copy constructor (disabled)
    Fish(const Fish &) = delete;

    /// Assignment operator
    void operator=(const Fish &) = delete;

    void Update(double elapsed);

    /// Gets the X speed
    double GetSpeedX() {return mSpeedX;}

    /// Gets the Y speed
    double GetSpeedY() {return mSpeedY;}

    virtual int Custom()=0;
};

#endif //AQUARIUM_FISH_H
