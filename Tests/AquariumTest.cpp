/**
 * @file AquariumTest.cpp
 * @author Bryce Cooperkawa
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Aquarium.h>
#include <FishBeta.h>
#include <Magikarp.h>
#include <AngelFish.h>
#include <DecorCastle.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>

using namespace std;

//sets the random seed
const unsigned int RandomSeed = 1238197374;

class AquariumTest : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/aquarium";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
    * Read a file into a wstring and return it.
    * @param filename Name of the file to read
    * @return File contents
    */
    wstring ReadFile(const wxString &filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());

        return str;
    }

    /**
     * Test to ensure an aquarium .aqua file is empty
     */
    void TestEmpty(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua/>")));
    }

    /**
     *  Populate an aquarium with three Beta fish
     */
    void PopulateThreeBetas(Aquarium *aquarium)
    {
        aquarium->GetRandom().seed(RandomSeed);

        auto fish1 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish1);
        fish1->SetLocation(100, 200);

        auto fish2 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish2);
        fish2->SetLocation(400, 400);

        auto fish3 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish3);
        fish3->SetLocation(600, 100);
    }

    /**
     * Tests for three beta fish
     * @param filename the file of the saved aquarium
     */
    void TestThreeBetas(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure three items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));

        // Ensure the speeds are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* xspeed=\"34.6892\" yspeed=\"40.6032\"/>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* xspeed=\"40.6797\" yspeed=\"42.1756\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* xspeed=\"48.756\" yspeed=\"49.6308\"")));

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"beta\".*/><item.* type=\"beta\".*/><item.* type=\"beta\".*/></aqua>")));
    }

    /**
     *  Populate an aquarium with all types
     */
    void PopulateAllTypes(Aquarium *aquarium)
    {
        aquarium->GetRandom().seed(RandomSeed);

        auto fish1 = make_shared<FishBeta>(aquarium);
        aquarium->Add(fish1);
        fish1->SetLocation(100, 200);

        auto fish2 = make_shared<FishAngel>(aquarium);
        aquarium->Add(fish2);
        fish2->SetLocation(400, 400);

        auto fish3 = make_shared<Magikarp>(aquarium);
        aquarium->Add(fish3);
        fish3->SetLocation(600, 100);

        auto decor1 = make_shared<DecorCastle>(aquarium);
        aquarium->Add(decor1);
        decor1->SetLocation(900, 300);
    }

    /**
     * Tests for all types
     * @param filename the file of the saved aquarium
 `   */
    void TestAllTypes(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure four items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*</aqua>")));

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"900\" y=\"300\"")));

        // Ensure the speeds are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* xspeed=\"34.6892\" yspeed=\"40.6032\"/>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* xspeed=\"40.6797\" yspeed=\"42.1756\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* xspeed=\"48.756\" yspeed=\"49.6308\"")));

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"beta\".*/><item.* type=\"angel\".*/><item.* type=\"magikarp\".*/><item.* type=\"castle\"/></aqua>")));
    }

    /**
     * Tests for all types
     * @param filename the file of the saved aquarium
`    */
    void LoadTestAllTypes(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure four items
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*</aqua>")));

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"900\" y=\"300\"")));

        // Ensure the speeds are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* xspeed=\"23.7721\" yspeed=\"45.1928\"/>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* xspeed=\"21.8432\" yspeed=\"30.6497\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.* xspeed=\"20.0011\" yspeed=\"47.2232\"")));

        // Ensure the types are correct
        ASSERT_TRUE(regex_search(xml,
                wregex(L"<aqua><item.* type=\"beta\".*/><item.* type=\"angel\".*/><item.* type=\"magikarp\".*/><item.* type=\"castle\"/></aqua>")));
    }

};

TEST_F(AquariumTest, Construct){
    Aquarium aquarium;
}

TEST_F(AquariumTest, HitTest) {
    Aquarium aquarium;

    ASSERT_EQ(aquarium.HitTest(100, 200), nullptr) <<
                                                   L"Testing empty aquarium";

    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish1);
    fish1->SetLocation(100, 200);

    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish1) <<
                                                     L"Testing fish at 100, 200";

    //adds a second fish on top of fish1
    shared_ptr<FishBeta> fish2 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish2);
    fish2->SetLocation(100, 200);
    //tests that the fish clicked is fish2 not fish1
    ASSERT_EQ(aquarium.HitTest(100, 200), fish2);

    //tests that the aquarium with fish in it will
    //return nullptr if tested for where there is no image
    ASSERT_EQ(aquarium.HitTest(1000, 200), nullptr);
}

TEST_F(AquariumTest, Save) {

    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    //
    // Now populate the aquarium
    //

    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);

    TestEmpty(file1);

    //
    // Test all types
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);

    TestAllTypes(file3);
}

TEST_F(AquariumTest, Clear){
    Aquarium aquarium;

    // Create a path to temporary files
    auto path = TempPath();

    //puts items in the aquarium
    PopulateAllTypes(&aquarium);

    //tests that those items were added
    auto file = path + L"/test.aqua";
    aquarium.Save(file);
    TestAllTypes(file);

    //clears the items and saves
    aquarium.Clear();
    aquarium.Save(file);

    //tests that they were cleared
    TestEmpty(file);
}

TEST_F(AquariumTest, Load) {
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;
    Aquarium aquarium2;
    aquarium2.GetRandom().seed(RandomSeed);

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    aquarium2.Load(file1);
    aquarium2.Save(file1);
    TestEmpty(file1);

    //
    // Now populate the aquarium
    //
    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);
    TestThreeBetas(file2);

    //
    // Test all types
    //
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);

    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);
    TestAllTypes(file3);

    aquarium2.Load(file2);
    aquarium2.Save(file2);
    TestThreeBetas(file2);

    aquarium3.Load(file3);
    aquarium3.Save(file3);
    LoadTestAllTypes(file3);
}