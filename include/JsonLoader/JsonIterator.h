#ifndef JSONITERATOR_H
#define JSONITERATOR_H

class JsonNode;
class JsonContainer;
class JsonLeaf;

class JsonIterator {
protected:
    int m_idx;
    JsonNode* m_node;
public:
    JsonIterator(JsonNode* node, int i);
    virtual bool hasMore() = 0;
    // 最后一个元素后一个
    virtual bool atEnd() = 0;
    // 最后一个元素
    virtual bool atLast() = 0;
    virtual void getNext() = 0;
    virtual JsonNode* get() = 0;
    virtual ~JsonIterator() {}
};

class JsonLeafIterator :public JsonIterator {
public:
    JsonLeafIterator(JsonLeaf* leaf, int idx);
    virtual bool hasMore() override;
    virtual bool atEnd() override;
    virtual bool atLast() override;
    virtual void getNext() override;
    virtual JsonNode* get() override;
    virtual ~JsonLeafIterator();
};


class JsonContainerIterator :public JsonIterator {
public:
    JsonContainerIterator(JsonContainer* container, int idx);
    virtual bool hasMore() override;
    virtual bool atEnd() override;
    virtual bool atLast() override;
    virtual void getNext() override;
    virtual JsonNode* get() override;
    virtual ~JsonContainerIterator();
};

#endif