#pragma once

#include "PayoutTable.h"
#include <vector>
#include <utility>

const int Reels = 5;
const int Rows = 3;
const int SymbolCount = 10;

class Slot
{
public:
    auto GetTotalWinnings() const -> int;
    void Play();
private:
    Symbol m_slot [Rows][Reels];
    int m_scatterCount = 0;
    
    auto _generateSymbol(int max) const -> Symbol;
    auto _generateSymbolNoScatter() const -> Symbol;
    auto _generateSymbolWithScatter() const -> Symbol;
    void _populateSlot();
    
    auto _loopHelper(int idx, const std::vector<int>& line, const Symbol& symbol)const -> int;
    auto _getNormalSymbolKeyByLine(const std::vector<int>& line) const -> std::pair<Symbol,int>;
    auto _getWildKeyByLine(const std::vector<int>& line) const -> std::pair<Symbol,int>;
    auto _getConsecutiveWildsByLine(const std::vector<int>& line) const -> int;
    auto _getWinnigsFromLine(const std::vector<int>& line) const -> int;
    auto _getWinnigsAmount(const std::pair<Symbol,int>& win) const -> int;
    auto _getScatterWinAmount() const -> int;
    
    void _printMatrix()const;
    void _printWinnigsHelper(const std::pair<Symbol,int>& win) const;
    void _printWinnigsHelperForLine(int N, const std::pair<Symbol,int>& win) const;
    void _printWinnigsFromLineN(int N, const std::vector<int>& line) const;
    void _printAllWinnings() const;
};