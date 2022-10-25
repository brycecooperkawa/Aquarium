/**
 * @file FishBeta.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef AQUARIUM_FISHBETA_H
#define AQUARIUM_FISHBETA_H

#include "Item.h"
#include "Fish.h"

/**
 * Class for a fish of type Beta
 */
class FishBeta : public Fish {
private:

public:
    /// Default constructor (disabled)
    FishBeta() = delete;

    /// Copy constructor (disabled)
    FishBeta(const FishBeta &) = delete;

    /// Assignment operator
    void operator=(const FishBeta &) = delete;

    FishBeta(Aquarium* aquarium);

    std::string Type() override;

    wxXmlNode* XmlSave(wxXmlNode* node) override;

    int Custom() override;
};

#endif //AQUARIUM_FISHBETA_H
