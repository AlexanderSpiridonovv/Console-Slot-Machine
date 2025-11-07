#pragma once
#include "Slot.h"
#include <memory>

const int playCost = 5;
const int scattersNeeded = 3;
class Player
{
public:


    Player(unsigned balance, Slot& slot);
    auto Play() -> int;
    void Deposit(unsigned deposit);
    void DisplayInfo()const;
    void CashOut();
    auto SimpleGamble(char input, int initialSum) -> int;
    auto CanStartFreeGames()const -> bool;
    auto GetBalance()const -> int;
    auto GetPtr()const -> std::shared_ptr<Slot>;
    
private:
    unsigned m_balance;
    std::shared_ptr<Slot> m_slot = nullptr;
    auto _generateRedBlack()const -> char;
};