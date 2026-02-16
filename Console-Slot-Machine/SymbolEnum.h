#include <iostream>
#include <string>

enum class Symbol 
{
    J,
    Q,
    K,
    A,
    CHERRY,
    BANANA,
    PLUM,
    WATERMELON,
    WILD,
    SCATTER
};

inline std::string symbolToString(Symbol s)
{
    switch (s)
    {
        case Symbol::J:           return "J";
        case Symbol::Q:           return "Q";
        case Symbol::K:           return "K";
        case Symbol::A:           return "A";
        case Symbol::CHERRY:      return "CHERRY";
        case Symbol::BANANA:      return "BANANA";
        case Symbol::PLUM:        return "PLUM";
        case Symbol::WATERMELON:  return "WATERMELON";
        case Symbol::WILD:        return "WILD";
        case Symbol::SCATTER:     return "SCATTER";
        default:                  return "UNKNOWN";
    }
}

inline std::string symbolToStringForSlot(Symbol s)
{
    switch (s)
    {
        case Symbol::J:           return "      J     ";
        case Symbol::Q:           return "      Q     ";
        case Symbol::K:           return "      K     ";
        case Symbol::A:           return "      A     ";
        case Symbol::CHERRY:      return "   CHERRY   ";
        case Symbol::BANANA:      return "   BANANA   ";
        case Symbol::PLUM:        return "    PLUM    ";
        case Symbol::WATERMELON:  return " WATERMELON ";
        case Symbol::WILD:        return "    WILD    ";
        case Symbol::SCATTER:     return "   SCATTER  ";
        default:                  return "   UNKNOWN  ";
    }
}

inline std::ostream& operator<<(std::ostream& os, Symbol s)
{
    return os << symbolToString(s);
}