#include "Player.h"

Player::Player(unsigned balance, Slot& slot)
{
    m_balance = balance;
    m_slot = std::make_unique<Slot>(slot);
}

void Player::Deposit(unsigned deposit)
{
    m_balance += deposit;
}

void Player::Play()
{
    if(m_slot == nullptr)
    {
        throw std::logic_error("You already cashed out!");
    }
    if(m_balance < playCost)
    {
        throw std::logic_error("Not enough funds to play, please deposit more");
    }
    
    m_balance -= playCost;
    m_balance += m_slot -> Play();
    m_balance += m_slot -> PlayFreeGames();
   
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