/**
 * @file Aquarium.cpp
 * @author Bryce Cooperkawa
 */

#include "pch.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "AngelFish.h"
#include "Magikarp.h"
#include "DecorCastle.h"
#include <algorithm>

using namespace std;

/**
 * Aquarium Constructor
 */
Aquarium::Aquarium()
{
    mBackground = make_unique<wxBitmap>(
            L"images/background1.png", wxBITMAP_TYPE_ANY);

    // Seed the random number generator
    std::random_device rd;
    mRandom.seed(rd());

}

/**
 * Draw the aquarium
 * @param dc The device context to draw on
 */
void Aquarium::OnDraw(wxDC *dc)
{
    dc->DrawBitmap(*mBackground, 0, 0);

    wxFont font(wxSize(0, 20),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(wxColour(0, 64, 0));
    dc->DrawText(L"Under the Sea!", 10, 10);

    for (auto item : mItems)
    {
        item->Draw(dc);
    }
}

/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;

/**
 * Add an item to the aquarium
 * @param item New item to add
 */
void Aquarium::Add(std::shared_ptr<Item> item)
{
    //this value will check to make sure its not the first item added
    int i=1;
    //if its the first item added it will be place in the inital spot and added to the vector
    if(mItems.size()==0)
    {
        item->SetLocation(InitialX, InitialY);
        //adds the new item to the item vector
        mItems.push_back(item);
        //changes the check so that the loop won't run
        i=0;
    }

    //checks if the loop should run (its not the first item)
    if(i==1)
    {
        //loops through all items and calculates the distance
        for (auto element: mItems) {
            //if within a pixel of another fish it moves 10 pixels right and 10 pixels down
            if (item->DistanceTo(element)<=1) {
                //sets the new x and y values for the new item
                int NewX = (element->GetX())+10;
                int NewY = (element->GetY())+10;

                //places the item in the new location
                item->SetLocation(NewX, NewY);
            }
            else {
                //item is placed in the initial spot
                //item is not within a pixel of another
                item->SetLocation(InitialX, InitialY);

            }
        }

        //adds the new item to the item vector
        mItems.push_back(item);
    }
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the aquarium.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Aquarium::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}

/**
 * Moves an item that was clicked on to the end of the list
 * @param item item that will be moved to the back of the list
 */
void Aquarium::MoveToBack(std::shared_ptr<Item> item)
{
    //finds the location of the item that was clicked
    auto loc = find(begin(mItems), end(mItems), item);

    //if the item is found in the vector
    if(loc != end(mItems))
    {
        //erases the item from the vector
        mItems.erase(loc);

        //adds the item back in at the end of the vector
        mItems.push_back(item);
    }
}

/**
 * Save the aquarium as a .aqua XML file.
 *
 * Open an XML file and stream the aquarium data to it.
 *
 * @param filename The filename of the file to save the aquarium to
 */
void Aquarium::Save(const wxString &filename)
{
    wxXmlDocument xmlDoc;

    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"aqua");
    xmlDoc.SetRoot(root);

    // Iterate over all items and save them
    for (auto item : mItems)
    {
        item->XmlSave(root);
    }


    if(!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
    {
        wxMessageBox(L"Write to XML failed");
        return;
    }
}

/**
 * Load the aquarium from a .aqua XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the aquarium from.
 */
void Aquarium::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Aquarium file");
        return;
    }

    Clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"item")
        {
            XmlItem(child);
        }
    }
}

/**
 * Clear the aquarium data.
 *
 * Deletes all known items in the aquarium.
 */
void Aquarium::Clear()
{
    mItems.clear();
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Aquarium::XmlItem(wxXmlNode *node)
{
    // A pointer for the item we are loading
    shared_ptr<Item> item;

    // We have an item. What type?
    auto type = node->GetAttribute(L"type");
    if (type == L"beta")
    {
        item = make_shared<FishBeta>(this);
    }

    //checks for angel fish type
    if (type == L"angel")
    {
        item = make_shared<FishAngel>(this);
    }

    //checks for magikarp type
    if (type == L"magikarp")
    {
        item = make_shared<Magikarp>(this);
    }

    //checks for castle type
    if (type == L"castle")
    {
        item = make_shared<DecorCastle>(this);
    }

    if (item != nullptr)
    {
        Add(item);
        item->XmlLoad(node);
    }
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Aquarium::Update(double elapsed)
{
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
}

