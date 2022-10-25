/**
 * @file FishBeta.cpp
 * @author Bryce Cooperkawa
 */

#include "pch.h"
#include "FishBeta.h"
#include "Aquarium.h"

using namespace std;

/// Fish filename
const wstring FishBetaImageName = L"images/beta.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
FishBeta::FishBeta(Aquarium *aquarium) : Fish(aquarium, FishBetaImageName)
{
}

/**
 * Says what kind of item it is
 * @return string of the items name
 */
std::string FishBeta::Type()
{
    return "Beta Fish";
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* FishBeta::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"beta");
    itemNode->AddAttribute(L"xspeed", wxString::FromDouble(GetSpeedX()));
    itemNode->AddAttribute(L"yspeed", wxString::FromDouble(GetSpeedY()));

    return itemNode;
}

/**
 * Check value that activates the unique feature of each fish
 * @return check value that is unique to each fish
 */
int FishBeta::Custom()
{
    return 0;
}