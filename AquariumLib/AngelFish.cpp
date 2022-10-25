/**
 * @file AngelFish.cpp
 * @author Bryce Cooperkawa
 */

#include "pch.h"
#include "AngelFish.h"
#include "Aquarium.h"

using namespace std;

/// Angel Fish filename
const wstring FishAngelImageName = L"images/angelfish.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishAngel::FishAngel(Aquarium *aquarium) : Fish(aquarium, FishAngelImageName)
{
}


/**
 * Says what kind of item it is
 * @return string of the items name
 */
std::string FishAngel::Type()
{
    return "Angel Fish";
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishAngel::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"angel");
    itemNode->AddAttribute(L"xspeed", wxString::FromDouble(GetSpeedX()));
    itemNode->AddAttribute(L"yspeed", wxString::FromDouble(GetSpeedY()));

    return itemNode;
}

/**
 * Check value that activates the unique feature of each fish
 * @return check value that is unique to each fish
 */
int FishAngel::Custom()
{
    return 1;
}
