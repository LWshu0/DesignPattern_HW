#ifndef JSONNODE_H
#define JSONNODE_H

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

class JsonIcon;
class JsonRenderer;

/**
 *@brief Json 节点的抽象基类, 提供一个绘制接口
 *
 */
class JsonNode {
protected:
    std::string m_name;

public:
    JsonNode() :m_name("") {}

    inline void setName(const std::string& name)
    {
        m_name = name;
    }
    inline std::string getName()
    {
        return m_name;
    }

    /* 使用 renderer 渲染器, 把内容渲染到字符流 */
    virtual void draw(JsonRenderer* renderer, int level) = 0;

    virtual void clear() = 0;
    virtual void output(std::ofstream& os, int level) = 0;
    virtual ~JsonNode() {}
};

/**
 *@brief Json 树的中间容器节点, 可以有多个子节点, 子节点可以是另一个容器节点也可以是叶子节点.
 *       可以设置该容器节点中子节点的图标
 */
class JsonContainer :public JsonNode {
private:
    int m_level;
    std::vector<std::shared_ptr<JsonNode>> m_children;
public:
    JsonContainer(int level);

    // 访问方法
    inline int size() { return m_children.size(); }
    inline std::vector<std::shared_ptr<JsonNode>>::iterator begin() { return m_children.begin(); }
    inline std::vector<std::shared_ptr<JsonNode>>::iterator end() { return m_children.end(); }
    inline std::shared_ptr<JsonNode>& at(size_t idx) { return m_children[idx]; }

    // 修改方法
    void addChild(std::shared_ptr<JsonNode> node);
    std::vector<std::shared_ptr<JsonNode>>& getChildren() { return m_children; }
    
    virtual void draw(JsonRenderer* renderer, int level) override;
    virtual void clear() override;
    virtual void output(std::ofstream& os, int level) override;
    virtual ~JsonContainer();
};

/**
 *@brief Json 树的叶子节点
 *
 */
class JsonLeaf :public JsonNode {
private:
    std::string m_value;
public:
    JsonLeaf();
    void setValue(const std::string& value);
    std::string getValue() { return m_value; }
    virtual  void draw(JsonRenderer* renderer, int level) override;
    virtual void clear() override;
    virtual void output(std::ofstream& os, int level) override;
    virtual ~JsonLeaf();
};

#endif