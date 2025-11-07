#include <iostream>
#include "Player.h"
#include "Menu.h"
//#include "Configurations"

int main()
{
    Slot slot;
    Player player(0, slot);
    Menu menu(player);

    menu.WelcomeMenu();
    
    std::string choice;
    bool running = true;
    
    while (running) 
    {
        menu.DisplayMenu();

        std::cin >> choice;
        
        if (choice == "1") 
        {
            menu.InsertCredit();
        }
        else if (choice == "p" || choice == "P") 
        {
            menu.PlayFeature();
        }
        else if (choice == "i" || choice == "I") 
        {
            menu.DisplayInfo();
        }
        else if (choice == "3") 
        {
            running = false;
            menu.CashOut();
        }
        else if (choice == "d") 
        {
            menu.PlayDemoSafe();
        }
        else 
        {
            std::cout << "\n❌ Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}