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

JsonLeaf::~JsonLeaf()
{

}