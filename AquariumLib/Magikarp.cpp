/**
 * @file Magikarp.cpp
 * @author Bryce Cooperkawa
 */

#include "pch.h"
#include "Magikarp.h"
#include "Aquarium.h"

using namespace std;

/// Magikarp filename
const wstring MagikarpImageName = L"images/magikarp.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
Magikarp::Magikarp(Aquarium *aquarium) : Fish(aquarium, MagikarpImageName)
{
}


/**
 * Says what kind of item it is
 * @return string of the items name
 */
std::string Magikarp::Type()
{
    return "Magikarp";
}

/**
 * Save this fish to an XML node
 * @param node The parent node we are going to be a child of
 * @return
 */
wxXmlNode* Magikarp::XmlSave(wxXmlNode* node)
{
    auto itemNode = Item::XmlSave(node);
    itemNode->AddAttribute(L"type", L"magikarp");
    itemNode->AddAttribute(L"xspeed", wxString::FromDouble(GetSpeedX()));
    itemNode->AddAttribute(L"yspeed", wxString::FromDouble(GetSpeedY()));

    return itemNode;
}

/**
 * Check value that activates the unique feature of each fish
 * @return check value that is unique to each fish
 */
int Magikarp::Custom()
{
    return 2;
}