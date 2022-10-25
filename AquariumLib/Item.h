/**
 * @file Item.h
 * @author Bryce Cooperkawa
 *
 *
 */

#ifndef AQUARIUM_ITEM_H
#define AQUARIUM_ITEM_H

class Aquarium;

/**
 * Base class for any item in our aquarium.
 */
class Item {
private:
    /// The aquarium this item is contained in
    Aquarium   *mAquarium;

    // Item location in the aquarium
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

    /// The underlying fish image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mItemBitmap;

    bool mMirror = false;   ///< True mirrors the item image

protected:
    Item(Aquarium *aquarium, const std::wstring &filename);

public:
    virtual ~Item();

    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * The width of the item
     * @return width in pixels
     */
    double GetItemWidth() const { return mItemBitmap->GetWidth(); }

    /**
     * The height of the item
     * @return height in pixels
     */
    double GetItemHeight() const { return mItemBitmap->GetHeight(); }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y) { mX = x; mY = y; }

    void Draw(wxDC *dc);

    bool HitTest(int x, int y);

    double DistanceTo(std::shared_ptr<Item> item);

    /**
     * Tests the item to see what kind of fish it is
     * @return returns the string of the name of the item
     */
     virtual std::string Type()=0;

     virtual wxXmlNode* XmlSave(wxXmlNode *node);

     virtual void XmlLoad(wxXmlNode* node);

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    /**
     * Get the pointer to the Aquarium object
     * @return Pointer to Aquarium object
     */
    Aquarium *GetAquarium() { return mAquarium;  }

    void SetMirror(bool m);

    /**
     * Get the mirror status
     * @param m New mirror flag
     */
    bool GetMirror() {return mMirror;}

    void SetBitmap(bool m);

    void Evolve();
};



#endif //AQUARIUM_ITEM_H
