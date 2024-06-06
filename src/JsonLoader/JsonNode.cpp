#include "JsonLoader/JsonNode.h"
#include "JsonIcon/JsonIcon.h"
#include "JsonRenderer/JsonRenderer.h"
#include "JsonLoader/JsonIterator.h"

JsonContainer::JsonContainer(int level) :JsonNode(), m_level(level)
{
    m_children.clear();
}

size_t JsonContainer::size()
{
    return m_children.size();
}
bool JsonContainer::empty()
{
    return m_children.empty();
}
JsonNode* JsonContainer::at(size_t idx)
{
    if (idx < 0 || idx >= size()) return nullptr;
    return m_children[idx].get();
}
JsonNode* JsonContainer::at(const std::string& name)
{
    for (auto& child : m_children)
    {
        if (child->getName() == name)
        {
            return child.get();
        }
    }
    std::string msg = "JsonContainer::at(const std::string& name) -- name: \"" + name + "\" doesn't exist\n";
    throw std::out_of_range(msg.c_str());
}

void JsonContainer::setValue(const std::string& value)
{
    return;
}
std::string JsonContainer::getValue()
{
    return "";
}
int JsonContainer::getInt()
{
    return 0;
}
float JsonContainer::getFloat()
{
    return 0.0f;
}
bool JsonContainer::getBool()
{
    return false;
}

std::shared_ptr<JsonIterator> JsonContainer::begin()
{
    return std::make_shared<JsonContainerIterator>(this, 0);
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
    renderer->render(this, level);
}

JsonContainer::~JsonContainer()
{

}

JsonLeaf::JsonLeaf() :JsonNode()
{

}

size_t JsonLeaf::size()
{
    return m_value == "" ? 0 : 1;
}
bool JsonLeaf::empty()
{
    return m_value == "";
}
JsonNode* JsonLeaf::at(size_t idx)
{
    return this;
}
JsonNode* JsonLeaf::at(const std::string& name)
{
    return this;
}

void JsonLeaf::setValue(const std::string& value)
{
    m_value = value;
}
std::string JsonLeaf::getValue()
{
    return m_value;
}
int JsonLeaf::getInt()
{
    return std::stoi(m_value);
}
float JsonLeaf::getFloat()
{
    return std::stof(m_value);
}
bool JsonLeaf::getBool()
{
    std::string v = m_value;
    for (auto& ch : v) ch = std::tolower(ch);
    if ("true" == v) return true;
    else if ("false" == v) return false;
    else
    {
        throw std::invalid_argument("JsonLeaf::getBool() -- invalid argument, must be \"true\" ot \"false\"\n");
    }
}
std::shared_ptr<JsonIterator> JsonLeaf::begin()
{
    return std::make_shared<JsonLeafIterator>(this, 0);
}

void JsonLeaf::draw(JsonRenderer* renderer, int level)
{
    renderer->render(this, level);
}
void JsonLeaf::clear()
{
    m_value = "";
    return;
}

JsonLeaf::~JsonLeaf()
{

}