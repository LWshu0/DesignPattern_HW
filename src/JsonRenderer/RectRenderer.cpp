#include "JsonRenderer/RectRenderer.h"
#include "JsonIcon/JsonIcon.h"
#include "JsonLoader/JsonNode.h"
#include "JsonLoader/JsonIterator.h"

RectRenderer::RectRenderer(JsonIcon* icon) :JsonRenderer(), m_icon(icon), m_length(0)
{}

void RectRenderer::render(JsonLeaf* leaf, int level)
{
    size_t ll = level * 3 + 3;

    if (m_icon != nullptr)
    {
        m_outputBuffer.back() += (m_icon->getLeafIcon() + " ");
        ll += 2;
    }
    m_outputBuffer.back() += leaf->getName();
    ll += leaf->getName().length();
    if (!leaf->empty())
    {
        m_outputBuffer.back() += (": " + leaf->getValue());
        ll += 2 + leaf->getValue().length();
    }
    m_outputBuffer.push_back("");

    m_length = m_length > ll ? m_length : ll;
}

void RectRenderer::render(JsonContainer* container, int level)
{
    size_t ll = level * 3 + 3;

    if (container->getName() != "")
    {
        if (m_icon != nullptr)
        {
            m_outputBuffer.back() += (m_icon->getContainerIcon() + " ");
            ll += 2;
        }
        m_outputBuffer.back() += container->getName();
        ll += container->getName().length();
        m_length = m_length > ll ? m_length : ll;
        m_outputBuffer.push_back("");
    }

    int child_num = container->size();
    
    for (int i = 0;i < child_num;i++)
    {

        if (i == 0)
        {
            shrinkPrefix(level);
            if (level == 0)
            {
                m_prefix.push_back("┌─ ");
            }
            else
            {
                m_prefix.back() = "│  ";
                // m_prefix.push_back("│  ");
                m_prefix.push_back("├─ ");
            }
        }
        // else if (i == child_num - 1)
        // {
        //     // m_prefix = m_prefix.substr(0, (level - 1) * 3) + "│  ";
        //     shrinkPrefix(level);
        //     if (level != 0) m_prefix.back() = "│  ";
        //     m_prefix.push_back("└─ ");
        // }
        else
        {
            // m_prefix = m_prefix.substr(0, (level - 1) * 3) + "│  "; ├─
            shrinkPrefix(level);
            if (level != 0) m_prefix.back() = "│  ";
            m_prefix.push_back("├─ ");
        }

        if (!m_outputBuffer.empty()) m_outputBuffer.back() += getPrefix();
        else m_outputBuffer.push_back(getPrefix());
        container->at(i)->draw(this, level + 1);
    }
    if (level == 0)
    {
        m_prefix[0] = "└──";

        for (int i = 1;i < m_prefix.size();i++)
        {
            m_prefix[i] = "┴──";
        }
        m_outputBuffer.back() += getPrefix();

        for (int i = 0; i < m_outputBuffer.size();i++)
        {
            size_t pre_part = count_u8(m_outputBuffer[i]);
            if (i != m_outputBuffer.size() - 1) m_outputBuffer[i] += ' ';
            else m_outputBuffer[i] += "─";
            for (int j = m_length - pre_part - 2;j >= 0;j--)
            {
                m_outputBuffer[i] += "─";
            }
            if (i == 0) m_outputBuffer[i] += "┐";
            else if (i == m_outputBuffer.size() - 1) m_outputBuffer[i] += "┘";
            else m_outputBuffer[i] += "┤";
        }
    }
}

void RectRenderer::shrinkPrefix(int num)
{
    while (m_prefix.size() > num && m_prefix.size() > 0)
    {
        m_prefix.pop_back();
    }
}
std::string RectRenderer::getPrefix()
{
    std::string str = "";
    for (auto& s : m_prefix)
    {
        str += s;
    }
    return str;
}

RectRenderer::~RectRenderer()
{}

size_t RectRenderer::count_u8(const std::string& str)
{
    size_t count = 0;
    for (int i = 0; i < str.length();)
    {
        if ((str[i] & 0x80) == 0x00)
        { // ASCII
            ++i;
            ++count;
        }
        else if ((str[i] & 0xe0) == 0xc0)
        { // 2字节字符
            i += 2;
            ++count;
        }
        else if ((str[i] & 0xf0) == 0xe0)
        { // 3字节字符
            i += 3;
            ++count;
        }
        else if ((str[i] & 0xf8) == 0xf0)
        { // 四字节字符
            i += 4;
            ++count;
        }
    }
    return count;
}