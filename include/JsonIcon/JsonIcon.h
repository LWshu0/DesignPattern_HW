#ifndef JSONICON_H
#define JSONICON_H

#include <string>
#include <fstream>
/**
 *@brief Json 图标的抽象接口
 *
 */
class JsonIcon {
private:
    std::string m_leafIcon;
    std::string m_containerIcon;
public:
    JsonIcon(const std::string& file_path);
    std::string getLeafIcon();
    std::string getContainerIcon();
    ~JsonIcon();
};

#endif