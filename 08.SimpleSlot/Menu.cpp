#include "Menu.h"
//#include "Configurations"
#include <iostream>
#include <thread>
#include <chrono>

Menu::Menu(Player& p)
{
    m_player = std::make_shared<Player>(p);
}

void Menu::WelcomeMenu()const
{
    std::cout << "╔════════════════════════════════╗\n";
    std::cout << "║   Welcome to Slot Machine!     ║\n";
    std::cout << "╚════════════════════════════════╝\n";
}

void Menu::DisplayMenu()const
{
    std::cout << "\n╔════════════════════════════════╗\n";
    std::cout << "║      🎰 SLOT MACHINE 🎰        ║\n";
    std::cout << "╚════════════════════════════════╝\n";
    std::cout << "Make your choice:\n";
    std::cout << "1. Press '1' to insert credit\n";
    std::cout << "2. Press 'p' to play\n";
    std::cout << "3. Press 'i' for info\n";
    std::cout << "4. Press '3' to cashout and exit\n";
    std::cout << "5. Press 'd' to enter demo mode\n";
    std::cout << "────────────────────────────────\n\n";
    std::cout << "Your choice: ";
}

void Menu::ClearInputBuffer()const
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void Menu::DisplayInfo()const
{
    m_player -> DisplayInfo();
}
void Menu::InsertCredit()
{
    std::cout << "\nEnter credit amount: ";
    int deposit;
    std::cin >> deposit;
        
    if (std::cin.fail() || deposit <= 0) {
        ClearInputBuffer();
        std::cout << "\n❌ Invalid credit amount! Returning to menu...\n";
    } else {
        m_player -> Deposit(deposit);
        std::cout << "\n✅ Successfully deposited " << deposit << " credits.\n";
    }
}
auto Menu::Spin() -> int
{
    try 
    {
        std::cout << "\n";
        std::cout << "\n";
        int win = m_player -> Play();
        
        return win;
    }
            
    catch (const std::logic_error& e) 
    {
        std::cout << "\n❌ " << e.what() << "\n";
    }
    return 0;
}

void Menu::CashOut()
{
    try 
    {      
        m_player -> CashOut();
        std::cout << "\nThank you for playing! 🎰\n";
    }
            
    catch (const std::logic_error& e) 
    {       
        std::cout << "\n❌ " << e.what() << "\n";    
    }
}

void Menu::Countdown(int seconds)const
{
    /*std::cin.clear();
    //saw it on internet, tries to clear input during countdown
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');*/
    for (int i = seconds; i > 0; i--) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "\nGo!\n\n";
}

auto Menu::_playFreeSpin(int &spinsRemaining)const -> int 
{
    std::cin.clear();
    //saw it on internet, tries to clear input during countdown
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Spins remaining: " << spinsRemaining << "\n\n";
    std::cout << "Press p to spin\n\n";


    std::string choice;
    std::cin >>choice;

    if(choice != "p")
    {
        throw std::invalid_argument("You can only enter p in free spins");
    }
    
    int totalWon = m_player-> GetPtr() -> Play();

    if(m_player -> CanStartFreeGames())
    {
        std::cout << "\nCongrats, you get 10 more spins\n";
        spinsRemaining += FreeSpins;
    }

    return totalWon;
}

auto Menu::PlayFreeGames() -> int
{
    
    m_player -> GetPtr() -> SetDemoMode(false);
    if(!m_player-> CanStartFreeGames())
    {
        return 0;
    }
    //Congratulations 3s
    std::cout << "\nCONGRATS, YOU WON 10 FREE SPINS!\n";
    Countdown(3);
    int totalWon = 0;

    for(int i = FreeSpins; i > 0; i--)
    {
        try
        {
            totalWon += _playFreeSpin(i);
        }
        catch(const std::invalid_argument& e)
        {
            //i gets decremented if an exception is thrown
            i++;
           std::cout << "\n❌ " << e.what() << "\n";
        }
    }
    std::cout << "Your total winnings are : " << totalWon << '\n';
    return totalWon;
}

void Menu::Deposit(int sum)
{
    m_player -> Deposit(sum);
}

auto Menu::Gamble(int initialSum) const -> int
{
    std::cout << "Press 'g' to gamble or any other key to quit.\n";
    std::string input;
    std::cin >> input;

    if (input != "g") 
    {
        std::cout << "\nTotal out: "<< initialSum << '\n';
        return initialSum;
    }

    if (initialSum == 0) 
    {
        return 0;
    }

    std::cout << "Press 'R' for RED or 'B' for BLACK:\n";
    std::string inputColor;
    std::cin >> inputColor;

    if (inputColor == "R" || inputColor == "B") 
    {
        //can return 0
        int win = m_player -> SimpleGamble(inputColor[0], initialSum);

        if (win != 0) 
        {
            std::cout << "WIN: " << win << "\n\n";

            return Gamble(win);
        } 
        else 
        {
            std::cout << "You lost!\n";
            return 0;
        }
    } 
    else 
    {
        std::cout << "Invalid color choice!\n";
        std::cout << "Total out: "<< initialSum << '\n';
        return initialSum;
    }
}
void Menu::PlayFeature()
{
    int normalWin = Spin();
    int freeWin = 0;
    if(m_player -> CanStartFreeGames())
    {
        freeWin = PlayFreeGames();
    }
    //current win
    int totalWin = normalWin + freeWin;
    if(totalWin > 0)
    {
        int toDeposit = Gamble(totalWin);
        Deposit(toDeposit);
    }
}
void Menu::PlayDemo()
{
    std::cout << "\nYOU ENTERED DEMO MODE ! \n\n";
    bool running = true;
    m_player -> GetPtr() -> SetDemoMode(true);
    while(running)
    {
        std::cout << "Enter 0 for 3 SCATTERS\n";
        std::cout << "Enter 1 for 5 WILDS";
        PlayFeature();//the cin is in _populateSlot
        std::cout << "\nIf you still want to be in demo mode, press 'y', else press 'n'.\n";
        std::string choice;
        std::cin >> choice;
        if(choice == "n")
        {
            running = false;
            m_player -> GetPtr() -> SetDemoMode(false);
            break;
        }
        else if(choice == "y")
        {
            m_player -> GetPtr() -> SetDemoMode(true);
        }
        else
        {
            std::cout << "Invalid choice, exiting...\n";
            running = false;
            m_player -> GetPtr() -> SetDemoMode(false);
            break;
        }
    }
    m_player -> GetPtr() -> SetDemoMode(false);
}