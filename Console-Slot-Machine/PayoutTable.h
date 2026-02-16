#pragma once
#include <unordered_map>
#include <utility>
#include "SymbolEnum.h"

// Custom hash so we can use std::pair<Symbol, int> as a key
struct SymbolCountHash {
    std::size_t operator()(const std::pair<Symbol, int>& p) const noexcept {
        return std::hash<int>()(static_cast<int>(p.first)) ^ (std::hash<int>()(p.second) << 1);
    }
};

// Payout table: key = (Symbol, count), value = payout
const std::unordered_map<std::pair<Symbol, int>, int, SymbolCountHash> PayoutTable = {
    {{Symbol::J, 3}, 5},   {{Symbol::J, 4}, 20},   {{Symbol::J, 5}, 60},
    {{Symbol::Q, 3}, 5},   {{Symbol::Q, 4}, 25},   {{Symbol::Q, 5}, 70},
    {{Symbol::K, 3}, 8},   {{Symbol::K, 4}, 35},   {{Symbol::K, 5}, 90},
    {{Symbol::A, 3}, 8},   {{Symbol::A, 4}, 40},   {{Symbol::A, 5}, 100},
    {{Symbol::CHERRY, 3}, 10},  {{Symbol::CHERRY, 4}, 50},  {{Symbol::CHERRY, 5}, 100},
    {{Symbol::BANANA, 3}, 20},  {{Symbol::BANANA, 4}, 60},  {{Symbol::BANANA, 5}, 120},
    {{Symbol::PLUM, 3}, 40},    {{Symbol::PLUM, 4}, 80},    {{Symbol::PLUM, 5}, 160},
    {{Symbol::WATERMELON, 3}, 50}, {{Symbol::WATERMELON, 4}, 100}, {{Symbol::WATERMELON, 5}, 150},
    {{Symbol::WILD, 3}, 80},   {{Symbol::WILD, 4}, 200},   {{Symbol::WILD, 5}, 700},
    {{Symbol::SCATTER, 3}, 100}
};
