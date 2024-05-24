#ifndef JSONNODE_H
#define JSONNODE_H

#include <string>
#include <vector>
#include <memory>

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
    virtual void draw(JsonRenderer* renderer, int level) = 0;
    virtual void clear() = 0;
    virtual ~JsonNode() {}
};

/**
 *@brief Json 树的中间容器节点, 可以有多个子节点, 子节点可以是另一个容器节点也可以是叶子节点.
 *       
 */
class JsonContainer :public JsonNode {
private:
    int m_level;
    std::vector<std::shared_ptr<JsonNode>> m_children;
public:
    /**
     *@brief Construct a new Json Container object
     * 
     * @param level 容器节点的层级, 最外层是第 0 层, 向内依次增加
     */
    JsonContainer(int level);

    // 访问方法
    /**
     *@brief 获取容器节点的子节点数量
     * 
     * @return int 容器节点的子节点数量
     */
    inline int size() { return m_children.size(); }
    /**
     *@brief 获取容器节点的子节点 vector 的起始迭代器
     * 
     * @return std::vector<std::shared_ptr<JsonNode>>::iterator
     */
    inline std::vector<std::shared_ptr<JsonNode>>::iterator begin() { return m_children.begin(); }
    /**
     *@brief 获取容器节点的子节点 vector 的结束迭代器
     * 
     * @return std::vector<std::shared_ptr<JsonNode>>::iterator 
     */
    inline std::vector<std::shared_ptr<JsonNode>>::iterator end() { return m_children.end(); }
    /**
     *@brief 获取一个指向子节点 vector 中位于下标 idx 处的子节点的指针引用
     * 
     * @param idx 子节点的下标
     * @return std::shared_ptr<JsonNode>& 指向子节点的指针引用
     */
    inline std::shared_ptr<JsonNode>& at(size_t idx) { return m_children[idx]; }

    // 修改方法
    /**
     *@brief 向容器节点添加一个子节点
     * 
     * @param node 待添加的子节点
     */
    void addChild(std::shared_ptr<JsonNode> node);
    /**
     *@brief 获取所有的子节点指针
     * 
     * @return std::vector<std::shared_ptr<JsonNode>>& 子节点指针数组
     */
    std::vector<std::shared_ptr<JsonNode>>& getChildren() { return m_children; }

    /**
     *@brief 使用指定的渲染器渲染该容器节点到字符串形式
     * 
     * @param renderer 渲染器
     * @param level 渲染的层级, 为该容器的层级
     */
    virtual void draw(JsonRenderer* renderer, int level) override;
    /**
     *@brief 清空子节点
     * 
     */
    virtual void clear() override;
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
    /**
     *@brief 设置叶子节点的值
     * 
     * @param value 值
     */
    void setValue(const std::string& value);
    /**
     *@brief 获取叶子节点的值
     * 
     * @return std::string 值
     */
    std::string getValue() { return m_value; }
    /**
     *@brief 使用指定的渲染器渲染叶子节点到字符串形式
     * 
     * @param renderer 渲染器
     * @param level 渲染层级, 上一层 container 的层级+1
     */
    virtual  void draw(JsonRenderer* renderer, int level) override;
    /**
     *@brief 将节点的内容置为 null
     * 
     */
    virtual void clear() override;
    virtual ~JsonLeaf();
};

#endif