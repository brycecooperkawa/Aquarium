/**
 * @file Magikarp.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef AQUARIUM_MAGIKARP_H
#define AQUARIUM_MAGIKARP_H

#include <wx/dc.h>
#include "Item.h"
#include "Fish.h"


/**
 * Class for a fish of type Magikarp
 */
class Magikarp : public Fish {
private:

public:
    /// Default constructor (disabled)
    Magikarp() = delete;

    /// Copy constructor (disabled)
    Magikarp(const Magikarp &) = delete;

    /// Assignment operator
    void operator=(const Magikarp &) = delete;

    Magikarp(Aquarium* aquarium);

    std::string Type() override;

    wxXmlNode* XmlSave(wxXmlNode* node);

    int Custom();
};

#endif //AQUARIUM_MAGIKARP_H
