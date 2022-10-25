/**
 * @file DecorCastle.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef AQUARIUM_DECORCASTLE_H
#define AQUARIUM_DECORCASTLE_H

#include "Item.h"

/**
 * Class for a fish of type Beta
 */
class DecorCastle : public Item {
private:

public:
    /// Default constructor (disabled)
    DecorCastle() = delete;

    /// Copy constructor (disabled)
    DecorCastle(const DecorCastle &) = delete;

    /// Assignment operator
    void operator=(const DecorCastle &) = delete;

    DecorCastle(Aquarium* aquarium);

    std::string Type() override;

    wxXmlNode* XmlSave(wxXmlNode* node);
};

#endif //AQUARIUM_DECORCASTLE_H