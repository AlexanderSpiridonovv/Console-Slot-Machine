#include "Slot.h"
#include "PayoutTable.h"
#include "VectorOfLines"
#include <iostream>
#include <random>
#include <utility>

const int INVALID_KEY = -1;

auto Slot::_generateSymbol()const -> Symbol
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, SymbolCount - 1); // 10 symbols total
    return static_cast<Symbol>(dist(rng));
}

void Slot::_populateSlot()
{
    m_scatterCount = 0;

    for(int col = 0; col < Reels; col++)
    {
        bool scatterUsed = false;
        for(int row = 0; row < Rows; row++)
        {
            Symbol symbol; 
            do
            {
               symbol = _generateSymbol();
            } while(scatterUsed && symbol == Symbol::SCATTER);

            if(symbol == Symbol::SCATTER)
            {
                scatterUsed = true;
                m_scatterCount++;
            }

            m_slot[row][col] = symbol;
        }
    }
}

void Slot::_printMatrix()const
{
    for(int i = 0; i < Rows; i++)
    {
        for(int j = 0; j < Reels; j++)
        {
            std::cout << symbolToStringForSlot(m_slot[i][j]) << ' ';
        }
        std::cout << "\n\n";
    }
}

auto Slot::_loopHelper(int idx, const std::vector<int>& line, const Symbol& symbol) const -> int
{
    while(idx < Reels && 
         (m_slot[line[idx]][idx] == symbol || 
          m_slot[line[idx]][idx] == Symbol::WILD))
    {
        idx++;
    }
    return idx;
}

auto Slot::_getNormalSymbolKeyByLine(const std::vector<int>& line)const -> std::pair<Symbol,int>
{
    Symbol initialSymbol = m_slot[line[0]][0];
    //scatter win logic is handled separately
    if(initialSymbol == Symbol::SCATTER)
    {
        return {Symbol::SCATTER, INVALID_KEY};
    }
    //for non pure wild wins starting with wild
    int wildCount = _getConsecutiveWildsByLine(line);

    //All Wilds
    if(wildCount >= Reels)
    {
        return {initialSymbol, INVALID_KEY};
    }

    int index = wildCount;
    Symbol normalSymbol = m_slot[line[index]][index];

    if(normalSymbol == Symbol::SCATTER)
    {
        return {Symbol::SCATTER, INVALID_KEY};
    }

    int count = _loopHelper(index,line,normalSymbol);

    if(count >= 3)
    {
        return {normalSymbol,count};
    }
    return {normalSymbol, INVALID_KEY};
}

auto Slot::_getConsecutiveWildsByLine(const std::vector<int>& line)const -> int
{
    return _loopHelper(0, line, Symbol::WILD);
}

auto Slot::_getWildKeyByLine(const std::vector<int>& line)const -> std::pair<Symbol,int>
{
    int count = _getConsecutiveWildsByLine(line);
    return {Symbol::WILD, count};
}

auto Slot::_getWinnigsAmount(const std::pair<Symbol,int>& win)const -> int
{
    auto it = PayoutTable.find(win);
    if(it == PayoutTable.end())
    {
        return 0;
    }
    int winningAmount = it -> second;
    return winningAmount;
}
//ask about that
void Slot::_printWinnigsHelper(const std::pair<Symbol,int>& win)const
{
    int currentWin = _getWinnigsAmount(win);

    if(currentWin == 0)
    {
        return;
    }
    for(int i = 0; i < win.second; i++)
    {
        //predefined operator <<
        std::cout << win.first << ' ';
    }
    std::cout << "= " << currentWin << '\n';
}

void Slot::_printWinnigsHelperForLine(int N, const std::pair<Symbol,int>& win)const
{
    int currentWin = _getWinnigsAmount(win);

    if(currentWin == 0)
    {
        return;
    }

    std::cout << "L" << N << "  -->  ";
    for(int i = 0; i < win.second; i++)
    {
        //predefined operator <<
        std::cout << win.first << ' ';
    }
    std::cout << "= " << currentWin << '\n';
}

auto Slot::_getWinnigsFromLine(const std::vector<int>& line)const -> int
{
    const auto& normalPair =  _getNormalSymbolKeyByLine(line);
    const auto& wildPair = _getWildKeyByLine(line);
    
    int normalWin = _getWinnigsAmount(normalPair);
    int wildWin = _getWinnigsAmount(wildPair);
    
    return normalWin + wildWin;
}

void Slot::_printWinnigsFromLineN(int N, const std::vector<int>& line)const
{
    const auto& normalPair =  _getNormalSymbolKeyByLine(line);
    const auto& wildPair = _getWildKeyByLine(line);
 
    _printWinnigsHelperForLine(N, normalPair);
    _printWinnigsHelperForLine(N, wildPair);
}

auto Slot::_getScatterWinAmount()const -> int
{
    return _getWinnigsAmount({Symbol::SCATTER, m_scatterCount});
}

auto Slot::GetTotalWinnings()const -> int
{
    int totalWin = 0;
    for(const auto& line : lines)
    {
        totalWin += _getWinnigsFromLine(line);
    }

    totalWin += _getScatterWinAmount();

    return totalWin;
}

void Slot::_printAllWinnings()const
{
    int totalWin = GetTotalWinnings();
    if(totalWin == 0)
    {
       return;
    }

    int i = 1;
    for(const auto& line : lines)
    {
        _printWinnigsFromLineN(i, line);
        i++;
    }

    if(m_scatterCount >= 3)
    {
        _printWinnigsHelper({Symbol::SCATTER, m_scatterCount});
    }
    std::cout << "\nTotal win: " << totalWin << '\n';
}

void Slot::Play()
{
    _populateSlot();
    _printMatrix();
    std::cout << "\n----------------------------------------------------------------\n\n";
    _printAllWinnings();
    std::cout << "\n----------------------------------------------------------------\n\n";
}
