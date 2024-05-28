#include "JsonLoader/JsonNode.h"
#include "JsonIcon/JsonIcon.h"
#include "JsonRenderer/JsonRenderer.h"

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
JsonNode& JsonContainer::at(size_t idx)
{
    return *m_children[idx];
}
JsonNode& JsonContainer::at(const std::string& name)
{
    for (auto& child : m_children)
    {
        if (child->getName() == name)
        {
            return *child;
        }
    }
    std::string msg = "JsonContainer::at(const std::string& name) -- name: \"" + name + "\" doesn't exist\n";
    throw std::out_of_range(msg.c_str());
}
JsonNode& JsonContainer::operator[](size_t idx)
{
    return this->at(idx);
}
JsonNode& JsonContainer::operator[](const std::string& name)
{
    return this->at(name);
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
    renderer->renderContainer(this, level);
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
JsonNode& JsonLeaf::at(size_t idx)
{
    return *this;
}
JsonNode& JsonLeaf::at(const std::string& name)
{
    return *this;
}
JsonNode& JsonLeaf::operator[](size_t idx)
{
    return this->at(idx);
}
JsonNode& JsonLeaf::operator[](const std::string& name)
{
    return this->at(name);
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
    for (auto& ch : v) std::tolower(ch);
    if ("true" == v) return true;
    else if ("false" == v) return false;
    else
    {
        throw std::invalid_argument("JsonLeaf::getBool() -- invalid argument, must be \"true\" ot \"false\"\n");
    }
}

void JsonLeaf::draw(JsonRenderer* renderer, int level)
{
    renderer->renderLeaf(this, level);
}
void JsonLeaf::clear()
{
    m_value = "";
    return;
}

JsonLeaf::~JsonLeaf()
{

}