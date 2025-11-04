#include <iostream>
#include "Player.h"

using namespace std;

void DisplayMenu() 
{
    cout << "\n╔════════════════════════════════╗\n";
    cout << "║      🎰 SLOT MACHINE 🎰        ║\n";
    cout << "╚════════════════════════════════╝\n";
    cout << "Make your choice:\n";
    cout << "1. Press '1' to insert credit\n";
    cout << "2. Press 'p' to play\n";
    cout << "3. Press 'i' for info\n";
    cout << "4. Press '3' to cashout and exit\n";
    cout << "────────────────────────────────\n\n";
    cout << "Your choice: ";
}

void ClearInputBuffer() 
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
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
            try {
                player.CashOut();
                running = false;
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
}
