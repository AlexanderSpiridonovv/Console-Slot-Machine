#include "Player.h"
#include <random>

Player::Player(unsigned balance, Slot& slot)
{
    m_balance = balance;
    m_slot = std::make_shared<Slot>(slot);
}

void Player::Deposit(unsigned deposit)
{
    m_balance += deposit;
}

auto Player::Play() -> int
{
    if(m_slot == nullptr)
    {
        throw std::logic_error("You already cashed out!");
    }
    if(m_balance < playCost)
    {
        throw std::logic_error("Not enough funds to play, please deposit more");
    }
    //variable
    int win = m_slot -> Play();
    m_balance -= playCost;
    DisplayInfo();
    //m_balance += win;   
    return win;
}

void Player::DisplayInfo()const
{
    std::cout << "Current credits: " << m_balance << std::endl;
}

void Player::CashOut()
{
    std::cout << "Total out: " << m_balance << std::endl; 
    m_slot = nullptr;
}

auto Player::CanStartFreeGames()const -> bool
{
    return m_slot -> GetScatterCount() >= scattersNeeded;
}

auto Player::GetPtr()const -> std::shared_ptr<Slot>
{
    return m_slot;
}
auto Player::_generateRedBlack()const -> char
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);
    int res = dist(rng);
    if(res == 0)
    {
        return 'R';
    }
    return 'B';
}
auto Player::Gamble(char input, int initialSum) -> int
{
    if(input == _generateRedBlack())
    {
        return initialSum * 2;
    }
    return 0;
}