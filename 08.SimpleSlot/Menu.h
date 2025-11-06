#pragma once
#include "Player.h"
class Menu
{
public:
    Menu(Player& p);
    void WelcomeMenu()const;
    void DisplayMenu()const;
    void ClearInputBuffer()const;
    void InsertCredit();
    auto Spin() -> int;
    void CashOut();
    void DisplayInfo()const;
    void Countdown(int seconds)const;
    void Deposit(int sum);
    auto PlayFreeGames() -> int;

    auto StartFreeGames()const -> bool;
    auto Gamble(int initialSum)const -> int;
private:
    auto _playFreeSpin(int &spinsRemaining) const -> int;
    std::shared_ptr<Player> m_player = nullptr;
};