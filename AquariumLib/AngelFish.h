/**
 * @file AngelFish.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef AQUARIUM_ANGELFISH_H
#define AQUARIUM_ANGELFISH_H

#include <wx/dc.h>
#include "Item.h"
#include "Fish.h"


/**
 * Class for a fish of type Angel
 */
class FishAngel : public Fish {
private:

public:
    /// Default constructor (disabled)
    FishAngel() = delete;

    /// Copy constructor (disabled)
    FishAngel(const FishAngel &) = delete;

    /// Assignment operator
    void operator=(const FishAngel &) = delete;

    FishAngel(Aquarium* aquarium);

    std::string Type() override;

    wxXmlNode* XmlSave(wxXmlNode* node);

    int Custom();
};


#endif //AQUARIUM_ANGELFISH_H
