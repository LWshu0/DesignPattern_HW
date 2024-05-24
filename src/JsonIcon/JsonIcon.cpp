#include "JsonIcon/JsonIcon.h"

JsonIcon::JsonIcon(const std::string& file_path)
{
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        m_leafIcon = "";
        m_containerIcon = "";
    }
    std::getline(file, m_leafIcon);
    std::getline(file, m_containerIcon);
    file.close();
}

JsonIcon::JsonIcon(const std::string& leaf_icon, const std::string& container_icon) :
    m_leafIcon(leaf_icon), m_containerIcon(container_icon)
{}

std::string JsonIcon::getLeafIcon()
{
    return m_leafIcon;
}

std::string JsonIcon::getContainerIcon()
{
    return m_containerIcon;
}

JsonIcon::~JsonIcon()
{

}
