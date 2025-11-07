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
    void CashOut();
    void DisplayInfo()const;
    void Countdown(int seconds)const;
    void Deposit(int sum);
    void PlayFeature();

    auto Spin() -> int;
    auto PlayFreeGames() -> int;
    auto StartFreeGames()const -> bool;
    auto Gamble(int initialSum)const -> int;

    void PlayDemo();
private:
    auto _playFreeSpin(int &spinsRemaining) const -> int;
    std::shared_ptr<Player> m_player = nullptr;
};