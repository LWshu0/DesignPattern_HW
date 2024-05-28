#include "JsonRenderer/TreeRenderer.h"
#include "JsonIcon/JsonIcon.h"
#include "JsonLoader/JsonNode.h"

TreeRenderer::TreeRenderer(JsonIcon* icon) :m_icon(icon)
{
    m_prefix.clear();
}

void TreeRenderer::renderLeaf(JsonLeaf* leaf, int level)
{
    if (m_icon != nullptr) m_outputBuffer.back() += (m_icon->getLeafIcon() + " ");
    m_outputBuffer.back() += leaf->getName();
    if (!leaf->empty()) m_outputBuffer.back() += (": " + leaf->getValue());
    m_outputBuffer.push_back("");
}

void TreeRenderer::renderContainer(JsonContainer* container, int level)
{
    if (container->getName() != "")
    {
        if (m_icon != nullptr) m_outputBuffer.back() += (m_icon->getContainerIcon() + " ");
        m_outputBuffer.back() += container->getName();
        m_outputBuffer.push_back("");
    }

    int child_num = container->size();
    if (m_childEnd)
    {
        shrinkPrefix(level - 1);
        m_prefix.push_back("   ");
        m_childEnd = false;
    }
    else
    {
        shrinkPrefix(level - 1);
        m_prefix.push_back("│  ");
    }
    for (int i = 0;i < child_num;i++)
    {
        if (i == child_num - 1)
        {
            // m_prefix = m_prefix.substr(0, (level - 1) * 3) + "|  ";
            shrinkPrefix(level);
            m_prefix.push_back("└─ ");
            m_childEnd = true;
        }
        else
        {
            // m_prefix = m_prefix.substr(0, (level - 1) * 3) + "|  ";
            shrinkPrefix(level);
            m_prefix.push_back("├─ ");
        }
        if (!m_outputBuffer.empty()) m_outputBuffer.back() += getPrefix();
        else m_outputBuffer.push_back(getPrefix());
        container->at(i).draw(this, level + 1);
    }
}
void TreeRenderer::shrinkPrefix(int num)
{
    while (m_prefix.size() > num && m_prefix.size() > 0)
    {
        m_prefix.pop_back();
    }
}
std::string TreeRenderer::getPrefix()
{
    std::string str = "";
    for (auto& s : m_prefix)
    {
        str += s;
    }
    return str;
}

TreeRenderer::~TreeRenderer()
{}