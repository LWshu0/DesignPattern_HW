#include "JsonLoader/JsonLoader.h"

JsonLoader::JsonLoader() :m_root(nullptr)
{}

int JsonLoader::load(const std::string& path)
{
    clear();
    // read
    std::ifstream file(path);
    if (!file.is_open()) return -1;
    std::string line = "";
    std::string content = "";
    while (std::getline(file, line))
    {
        content += line;
        content += '\n';
    }
    // parse
    size_t now_pos = 0;
    try
    {
        m_root = parseContainer(content, now_pos, 0);
    }
    catch(const std::exception& e)
    {
        m_root = nullptr;
        std::cerr << e.what() << '\n';
    }
    return 0;
}

std::string JsonLoader::draw(RendererFactory* factory)
{
    if (factory == nullptr || m_root == nullptr) return "";
    JsonRenderer* renderer = factory->create();
    renderer->renderContainer(m_root.get(), 0);
    std::string result = renderer->getResult();
    delete renderer;
    return result;
}

void JsonLoader::clear()
{
    if (m_root == nullptr)
    {
        return;
    }
    m_root->clear();
    m_root = nullptr;
}

JsonLoader::~JsonLoader()
{}

bool JsonLoader::skipSpace(std::string& input_file, size_t& now_pos)
{
    now_pos = input_file.find_first_not_of(" \n\r\t", now_pos);
    return now_pos == std::string::npos;
}

std::string JsonLoader::getIdentifier(std::string& input_file, size_t& now_pos)
{
    if (input_file[now_pos] == '\"')
    {
        now_pos += 1;
        size_t end_pos = input_file.find_first_of('\"', now_pos);
        if (end_pos == std::string::npos)
        {
            throw JsonLoaderException("error: JsonLoader::getIdentifier missing right \"\n");
        }
        std::string identifier = input_file.substr(now_pos, end_pos - now_pos);
        now_pos = end_pos + 1;
        return identifier;
    }
    else
    {
        size_t end_pos = input_file.find_first_of(",: \n\r\t", now_pos);
        if (end_pos == std::string::npos)
        {
            throw JsonLoaderException("error: JsonLoader::getIdentifier has no end marker\n");
        }
        std::string identifier = input_file.substr(now_pos, end_pos - now_pos);
        now_pos = end_pos;
        return identifier;
    }
}

std::shared_ptr<JsonContainer> JsonLoader::parseContainer(std::string& input_file, size_t& now_pos, int level)
{
    std::shared_ptr<JsonContainer> container = std::make_shared<JsonContainer>(level);
    if (skipSpace(input_file, now_pos) || input_file[now_pos] != '{')
    {
        throw JsonLoaderException("error: JsonLoader::parseContainer missing left \'{\'\n");
    }
    now_pos += 1;
    while (true)
    {
        // parse key
        if (skipSpace(input_file, now_pos))
        {
            throw JsonLoaderException("error: JsonLoader::parseContainer missing right \'}\'\n");
        }
        std::string key = getIdentifier(input_file, now_pos);
        // 检查 key 后的 :
        if (skipSpace(input_file, now_pos) || input_file[now_pos] != ':')
        {
            throw JsonLoaderException("error: JsonLoader::parseContainer missing \':\' after key\n");
        }
        now_pos += 1;
        // parse value
        if (skipSpace(input_file, now_pos))
        {
            throw JsonLoaderException("error: JsonLoader::parseContainer missing value\n");
        }
        // container
        if (input_file[now_pos] == '{')
        {
            std::shared_ptr<JsonContainer> child = parseContainer(input_file, now_pos, level + 1);
            child->setName(key);
            container->addChild(child);
        }
        // leaf
        else
        {
            std::shared_ptr<JsonLeaf> child = parseLeaf(input_file, now_pos);
            child->setName(key);
            container->addChild(child);
        }
        if (skipSpace(input_file, now_pos))
        {
            throw JsonLoaderException("error: JsonLoader::parseContainer missing right \'}\'\n");
        }
        if (input_file[now_pos] != ',') break;
        now_pos += 1;
    }
    // return if accept
    if (input_file[now_pos] == '}')
    {
        now_pos += 1;
        return container;
    }
    else
    {
        throw JsonLoaderException("error: JsonLoader::parseContainer missing right \'}\'\n");
    }
}

std::shared_ptr<JsonLeaf> JsonLoader::parseLeaf(std::string& input_file, size_t& now_pos)
{
    std::shared_ptr<JsonLeaf> leaf = std::make_shared<JsonLeaf>();
    std::string value = getIdentifier(input_file, now_pos);
    leaf->setValue(value);
    return leaf;
}