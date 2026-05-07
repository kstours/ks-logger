#include "window_menu.h"

namespace window_menu {

void initWindowMenu(){

    // File
    window_menu::MenuItem fileMenu{"File"};
    fileMenu.addOption("Save","CTRL + S" ,{})
    .addOption("Find", "CTL + F", {})
     .addOption("Exit", "CTL + X", {});
    window_menu::menu.push_back(fileMenu);

    // Edit
    window_menu::MenuItem editMenu{"Edit"};
    editMenu.addOption("Copy", "CTRL + C", {})
    .addOption("Select All", "CTRL + A" , {});
    window_menu::menu.push_back(editMenu);

    // View
    window_menu::MenuItem viewMenu{"View"};
    viewMenu.addOption("Find", "CTRL + F",{});
    window_menu::menu.push_back(viewMenu);
  

    // Preferences 
    window_menu::MenuItem preferencesMenu{"Preferences"};
    preferencesMenu.addOption("Theme","",{});
    window_menu::menu.push_back(preferencesMenu);

    // Help
    window_menu::MenuItem helpMenu{"Help"};
    helpMenu.addOption("About" ,"",{});
    window_menu::menu.push_back(helpMenu);

}

}