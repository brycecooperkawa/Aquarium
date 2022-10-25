/**
 * @file MainFrame.cpp
 * @author Bryce Cooperkawa
 */

#include "pch.h"

#include "MainFrame.h"
#include "AquariumView.h"
#include "ids.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Aquarium", wxDefaultPosition,  wxSize( 1000,800 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto aquariumView = new AquariumView();
    aquariumView->Initialize(this);

    // Add it to the sizer
    sizer->Add(aquariumView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    //adds a menu bar
    auto menuBar = new wxMenuBar( );

    //creates the three types of menus
    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto fishMenu = new wxMenu();

    //creates a decor menu
    auto decorMenu = new wxMenu();

    //adds the menus to the menu
    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(fishMenu, L"&Add Fish");
    menuBar->Append(helpMenu, L"&Help");

    //adds the decor menu to the menu
    menuBar->Append(decorMenu,"&Decor");

    //adds some info to the exit and help menus
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    fishMenu->Append(IDM_ADDFISHBETA, L"&Beta Fish", L"Add a Beta Fish");

    //adds the option to add an angel fish to the menu
    fishMenu->Append(IDM_ADDFISHANGEL, L"&Angel Fish", L"Add an Angel Fish");

    //adds the option to add magikarp to the menu
    fishMenu->Append(IDM_ADDMAGIKARP, L"&Magikarp", L"Add Magikarp");

    //adds the option to add the castle to the menu
    decorMenu->Append(IDM_ADDDECORCASTLE,L"&Castle",L"Add Castle");

    //binds the exit command to the exit button in the menu
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);

    //binds the about command to the about button in the menu
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);

    //adds the ability to save as to the file menu
    fileMenu->Append(wxID_SAVEAS, "Save &As...\tCtrl-S", L"Save aquarium as...");

    //adds the open command to the menu
    fileMenu->Append(wxID_OPEN, "Open &File...\tCtrl-F", L"Open aquarium file...");

    SetMenuBar( menuBar );

    //creates status bar
    CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * About menu option handlers
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Welcome to the Aquarium!",
            L"About Aquarium",
            wxOK,
            this);
}

