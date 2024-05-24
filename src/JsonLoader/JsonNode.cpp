#include "JsonLoader/JsonNode.h"
#include "JsonIcon/JsonIcon.h"
#include "JsonRenderer/JsonRenderer.h"

JsonContainer::JsonContainer(int level) :JsonNode(), m_level(level)
{
    m_children.clear();
}

void JsonContainer::addChild(std::shared_ptr<JsonNode> node)
{
    m_children.push_back(node);
}

void JsonContainer::clear()
{
    for (auto& child : m_children)
    {
        child->clear();
    }
    m_children.clear();
}

void JsonContainer::draw(JsonRenderer* renderer, int level)
{
    // 渲染容器名称
    renderer->renderContainer(this, level);
}

void JsonContainer::output(std::ofstream& os, int level)
{
    std::string spaces(level * 4, ' ');
    if (m_name != "") os << spaces << '\"' << m_name << "\":";
    os << "{\n";
    for (int i = 0;i < m_children.size();i++)
    {
        m_children[i]->output(os, level + 1);
        if (i != m_children.size() - 1) os << ',';
        os << '\n';
    }
    os << spaces << "}";
}

JsonContainer::~JsonContainer()
{

}

JsonLeaf::JsonLeaf() :JsonNode()
{

}

void JsonLeaf::setValue(const std::string& value)
{
    m_value = value;
}

void JsonLeaf::draw(JsonRenderer* renderer, int level)
{
    renderer->renderLeaf(this, level);
}
void JsonLeaf::clear()
{
    return;
}

void JsonLeaf::output(std::ofstream& os, int level)
{
    std::string spaces(level * 4, ' ');
    os << spaces << '\"' << m_name << "\": ";
    if (m_value == "null")
    {
        os << m_value;
    }
    else
    {
        os << '\"' << m_value << '\"';
    }
}

JsonLeaf::~JsonLeaf()
{

}