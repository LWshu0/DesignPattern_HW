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
    JsonIcon(const std::string& leaf_icon, const std::string& container_icon);
    /**
     *@brief 获取叶子节点的图标
     * 
     * @return std::string 叶子节点的图标
     */
    std::string getLeafIcon();
    /**
     *@brief 获取容器节点的图标
     * 
     * @return std::string 容器节点的图标
     */
    std::string getContainerIcon();
    ~JsonIcon();
};

#endif