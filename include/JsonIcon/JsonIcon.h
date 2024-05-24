#ifndef JSONICON_H
#define JSONICON_H

#include <string>

/**
 *@brief Json 图标的抽象接口
 * 
 */
class JsonIcon {
public:
    JsonIcon() = default;
    virtual std::string getLeafIcon() = 0;
    virtual std::string getContainerIcon() = 0;
    virtual ~JsonIcon() {}
};

#endif