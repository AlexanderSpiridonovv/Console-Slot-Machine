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
            /*int normalWin = menu.Spin();
            int freeWin = 0;
            if(player.CanStartFreeGames())
            {
                freeWin = menu.PlayFreeGames();
            }
            //current win
            int totalWin = normalWin + freeWin;
            if(totalWin > 0)
            {
                int toDeposit = menu.Gamble(totalWin);
                menu.Deposit(toDeposit);
            }*/
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
            menu.PlayDemo();
        }
        else 
        {
            std::cout << "\n❌ Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}