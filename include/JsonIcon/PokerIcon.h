#ifndef POKERICON_H
#define POKERICON_H

#include "JsonIcon.h"

class PokerIcon :public JsonIcon {
public:
    PokerIcon();
    virtual std::string getLeafIcon() override;
    virtual std::string getContainerIcon() override;
    virtual ~PokerIcon();
};

#endif