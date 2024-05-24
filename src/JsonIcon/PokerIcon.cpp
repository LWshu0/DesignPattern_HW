#include "JsonIcon/PokerIcon.h"

PokerIcon::PokerIcon() :JsonIcon()
{}

std::string PokerIcon::getLeafIcon()
{
    return "\u2664";
}
std::string PokerIcon::getContainerIcon()
{
    return "\u2662";
}

PokerIcon::~PokerIcon()
{}
