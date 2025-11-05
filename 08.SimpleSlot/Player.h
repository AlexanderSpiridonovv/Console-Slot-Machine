#pragma once
#include "Slot.h"
#include <memory>

const int playCost = 5;

class Menu;
class Player
{
public:


    Player(unsigned balance, Slot& slot);
    void Play();
    void Deposit(unsigned deposit);
    void DisplayInfo()const;
    void CashOut();
    void Gamble();
    auto StartFreeGames()const -> bool;
    auto GetPtr()const -> std::shared_ptr<Slot>;
    
private:
    unsigned m_balance;
    std::shared_ptr<Slot> m_slot = nullptr;
    //std::weak_ptr<Menu> m_menu;
};