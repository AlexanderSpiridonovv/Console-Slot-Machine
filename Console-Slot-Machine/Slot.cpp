#include "Slot.h"
#include "PayoutTable.h"
#include "VectorOfLines"
#include "Configurations"
#include <iostream>
#include <random>
#include <utility>

const int INVALID_KEY = -1;

static std::mt19937 rng(std::random_device{}());

auto Slot::_generateSymbol(int max)const -> Symbol
{
    std::uniform_int_distribution<int> dist(0, max);
    return static_cast<Symbol>(dist(rng));
}
auto Slot::_generateSymbolNoScatter() const -> Symbol
{
    return _generateSymbol(SymbolCount - 2); //Scatter is last
}
auto Slot::_generateSymbolWithScatter() const -> Symbol
{
    return _generateSymbol(SymbolCount - 1); //All symbols
}
void Slot::_populateSlot()
{
    if(m_demoMode)
    {
        unsigned configurationIndex;
        std::cin >> configurationIndex;
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            configurationIndex = -1;
        }
        //predefined operator=
        *this = configurations.at(configurationIndex);
        return;
    }
    m_scatterCount = 0;

    for(int col = 0; col < Reels; col++)
    {
        if(col % 2 == 0) //only on selected reels
        {
            bool scatterUsed = false;
            for(int row = 0; row < Rows; row++)
            {
                Symbol symbol; 
                do
                {
                symbol = _generateSymbolWithScatter();
                } while(scatterUsed && symbol == Symbol::SCATTER);

                if(symbol == Symbol::SCATTER)
                {
                    scatterUsed = true;
                    m_scatterCount++;
                }

                m_slot[row][col] = symbol;
            }
        }
        else
        {
           for(int row = 0; row < Rows; row++)
           {
                Symbol symbol = _generateSymbolNoScatter();
                m_slot[row][col] = symbol;
           }
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
Slot& Slot::operator=(const std::vector<std::vector<Symbol>>& slot)
{
    for(int i = 0; i < Rows; i++)
    {
        for(int j = 0; j < Reels; j++)
        {
            m_slot[i][j] = slot[i][j];
        }
        
    }
    m_scatterCount = _calculateScatterCount(slot);

    return *this;
}
void Slot::SetDemoMode(bool mode)
{
    m_demoMode = mode;
}
auto Slot::GetScatterCount() -> int
{
    return m_scatterCount;
}

auto Slot::_forwardLoopHelper(int idx, const std::vector<int>& line, const Symbol& symbol) const -> int
{
    while(idx < Reels && 
         (m_slot[line[idx]][idx] == symbol || 
          m_slot[line[idx]][idx] == Symbol::WILD))
    {
        idx++;
    }
    return idx;
}
auto Slot::_backwardLoopHelper(int idx, const std::vector<int>& line, const Symbol& symbol) const -> int
{
    while(idx >= 0 && 
         (m_slot[line[idx]][idx] == symbol || 
          m_slot[line[idx]][idx] == Symbol::WILD))
    {
        idx--;
    }
    return idx;
}
auto Slot::_getNormalSymbolKeyByLineForward(const std::vector<int>& line)const -> std::pair<Symbol,int>
{
    Symbol initialSymbol = m_slot[line[0]][0];
    //scatter win logic is handled separately
    if(initialSymbol == Symbol::SCATTER)
    {
        return {Symbol::SCATTER, INVALID_KEY};
    }
    //for non pure wild wins starting with wild
    int wildCount = _getConsecutiveWildsByLineForward(line);

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

    int count = _forwardLoopHelper(index,line,normalSymbol);

    if(count >= 3)
    {
        return {normalSymbol,count};
    }
    return {normalSymbol, INVALID_KEY};
}
auto Slot::_getNormalSymbolKeyByLineBackward(const std::vector<int>& line)const -> std::pair<Symbol,int>
{
    Symbol initialSymbol = m_slot[line[Reels -1]][Reels -1];
    //scatter win logic is handled separately
    if(initialSymbol == Symbol::SCATTER)
    {
        return {Symbol::SCATTER, INVALID_KEY};
    }
    //for non pure wild wins starting with wild
    int afterWildIndex = _getConsecutiveWildsByLineBackward(line);

    //All Wilds
    if(afterWildIndex <= 0)
    {
        return {initialSymbol, INVALID_KEY};
    }

    int index = afterWildIndex;
    Symbol normalSymbol = m_slot[line[index]][index];

    if(normalSymbol == Symbol::SCATTER)
    {
        return {Symbol::SCATTER, INVALID_KEY};
    }

    int count = Reels - _backwardLoopHelper(index,line,normalSymbol) - 1;
    
    //5 in a row handled in forward pass
    if(count >= 3 && count < 5)
    {
        return {normalSymbol,count};
    }
    return {normalSymbol, INVALID_KEY};
}

auto Slot::_getConsecutiveWildsByLineForward(const std::vector<int>& line)const -> int
{
    return _forwardLoopHelper(0, line, Symbol::WILD);
}

auto Slot::_getConsecutiveWildsByLineBackward(const std::vector<int>& line)const -> int
{
    return _backwardLoopHelper(Reels - 1, line, Symbol::WILD);
}

auto Slot::_getWildKeyByLineForward(const std::vector<int>& line)const -> std::pair<Symbol,int>
{
    int count = _getConsecutiveWildsByLineForward(line);
    return {Symbol::WILD, count};
}

auto Slot::_getWildKeyByLineBackward(const std::vector<int>& line)const -> std::pair<Symbol,int>
{
    int count = Reels - _getConsecutiveWildsByLineBackward(line) - 1;
    //5 wilds handled in forward pass
    if(count >= Reels)
    {
        return {Symbol::WILD, INVALID_KEY};
    }
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
//ask
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
    const auto& normalPairF =  _getNormalSymbolKeyByLineForward(line);
    const auto& wildPairF = _getWildKeyByLineForward(line);

    const auto& normalPairB =  _getNormalSymbolKeyByLineBackward(line);
    const auto& wildPairB = _getWildKeyByLineBackward(line);
    
    int normalWinF = _getWinnigsAmount(normalPairF);
    int wildWinF = _getWinnigsAmount(wildPairF);

    int normalWinB = _getWinnigsAmount(normalPairB);
    int wildWinB = _getWinnigsAmount(wildPairB);
    
    return normalWinF + wildWinF + normalWinB + wildWinB;
}

void Slot::_printWinnigsFromLineN(int N, const std::vector<int>& line)const
{
    const auto& normalPairF =  _getNormalSymbolKeyByLineForward(line);
    const auto& wildPairF = _getWildKeyByLineForward(line);

    const auto& normalPairB =  _getNormalSymbolKeyByLineBackward(line);
    const auto& wildPairB = _getWildKeyByLineBackward(line);
 
    _printWinnigsHelperForLine(N, normalPairF);
    _printWinnigsHelperForLine(N, wildPairF);
    _printWinnigsHelperForLine(N, normalPairB);
    _printWinnigsHelperForLine(N, wildPairB);
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

void Slot::_printAllWinnings(int totalWin)const
{
    if(totalWin == 0)
    {
       return;
    }

    int N = 1;
    for(const auto& line : lines)
    {
        _printWinnigsFromLineN(N, line);
        N++;
    }

    if(m_scatterCount >= 3)
    {
        _printWinnigsHelper({Symbol::SCATTER, m_scatterCount});
    }
    std::cout << "\nTotal win: " << totalWin << '\n';
}

auto Slot::Play() -> int
{
    _populateSlot();
    _printMatrix();
    std::cout << "\n----------------------------------------------------------------\n\n";
    int total = GetTotalWinnings();
    _printAllWinnings(total);
    std::cout << "\n----------------------------------------------------------------\n\n";
    return total;
}

//can be slightly optimized
auto Slot::_calculateScatterCount(const std::vector<std::vector<Symbol>> slot)const -> int
{
    int count = 0;
    for(int i = 0; i < Rows; i++)
    {
        for(int j = 0; j < Reels; j++)
        {
            if(slot[i][j] == Symbol::SCATTER)
            {
                count++;
            }
        }
    }
    return count;
}

auto Slot::_generateRedBlack()const -> char
{
    std::uniform_int_distribution<int> dist(0, 1);
    int res = dist(rng);
    if(res == 0)
    {
        return 'R';
    }
    return 'B';
}
auto Slot::SimpleGamble(char input, int initialSum) -> int
{
    if(input == _generateRedBlack())
    {
        return initialSum * 2;
    }
    return 0;
}