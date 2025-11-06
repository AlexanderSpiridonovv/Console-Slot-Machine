#include <iostream>
#include "Player.h"
#include "Menu.h"
using namespace std;


int main()
{
    Slot slot;
    Player player(0, slot);
    Menu menu(player);

    menu.WelcomeMenu();
    
    string choice;
    bool running = true;
    
    while (running) 
    {
        menu.DisplayMenu();

        cin >> choice;
        
        if (choice == "1") 
        {
            menu.InsertCredit();
        }
        else if (choice == "p" || choice == "P") 
        {
            int normalWin = menu.Spin();
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
            }
            
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
        else 
        {
            cout << "\n❌ Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}
/*int main()
{
    Slot slot;
    Player player(0, slot);
    
    cout << "╔════════════════════════════════╗\n";
    cout << "║   Welcome to Slot Machine!     ║\n";
    cout << "╚════════════════════════════════╝\n";
    
    string choice;
    bool running = true;
    
    while (running) 
    {
        DisplayMenu();

        cin >> choice;
        
        if (choice == "1") 
        {
            cout << "\nEnter credit amount: ";
            int deposit;
            cin >> deposit;
            
            if (cin.fail() || deposit <= 0) {
                ClearInputBuffer();
                cout << "\n❌ Invalid credit amount! Returning to menu...\n";
            } else {
                player.Deposit(deposit);
                cout << "\n✅ Successfully deposited " << deposit << " credits.\n";
            }
        }
        else if (choice == "p" || choice == "P") 
        {
            try {
                cout << "\n";
                cout << "\n";
                player.Play();
                if(slot.GetScatterCount() >= 3)
                {
                    slot.Countdown(3);
                    for(int i = 0; i < FreeSpins; i++)
                    {
                        
                    }
                }
            }
            
            catch (const logic_error& e) {
                cout << "\n❌ " << e.what() << "\n";
            }
        }
        else if (choice == "i" || choice == "I") 
        {
            player.DisplayInfo();
        }
        else if (choice == "3") 
        {
            running = false;
            try {
                player.CashOut();
                cout << "\nThank you for playing! 🎰\n";
            }
            catch (const logic_error& e) {
                cout << "\n❌ " << e.what() << "\n";
            }
        }
        else 
        {
            cout << "\n❌ Invalid choice! Please try again.\n";
        }
    }
    
    return 0;
}*/