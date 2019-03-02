#ifndef H_9C7EBBAB_91A4_47FA_9597_C69775689E3F
#define H_9C7EBBAB_91A4_47FA_9597_C69775689E3F

#include <memory>
#include <unordered_map>

template<typename Key, typename Data = void*>
class Tree
{
public:
    using Self = Tree<Key, Data>;
    explicit Tree(Self* m_parent = nullptr, Data data = Data{});
    Self* addChild(const Key& key, Data data = Data{});
    Self* getChild(const Key& key);
    const Self* getChild(const Key& key) const;
    void setData(Data data);
    Data getData() const;
    const Self* getParent() const;

private:
    Tree<Key, Data>* m_parent{nullptr};
    Data m_data{};
    using NestedTree = std::unique_ptr<Tree<Key, Data>>;
    std::unordered_map<Key, NestedTree> m_childs;
};

template<typename Key, typename Data>
Tree<Key, Data>::Tree(Self* parent, Data data)
    : m_parent(parent)
    , m_data(data)
{}

template<typename Key, typename Data>
Tree<Key, Data>* Tree<Key, Data>::addChild(const Key& key, Data data)
{
    m_childs[key] = std::make_unique<Self>(this, data);
    return m_childs[key].get();
}

template<typename Key, typename Data>
Tree<Key, Data>* Tree<Key, Data>::getChild(const Key &key)
{
    auto it = m_childs.find(key);
    if (it == m_childs.end()) {
        return nullptr;
    }
    return it->second.get();
}

template<typename Key, typename Data>
const Tree<Key, Data>* Tree<Key, Data>::getChild(const Key &key) const
{
    auto it = m_childs.find(key);
    if (it == m_childs.end()) {
        return nullptr;
    }
    return it->second.get();
}

template<typename Key, typename Data>
void Tree<Key, Data>::setData(Data data)
{
    m_data = data;
}

template<typename Key, typename Data>
Data Tree<Key, Data>::getData() const
{
    return m_data;
}

template<typename Key, typename Data>
const Tree<Key, Data>* Tree<Key, Data>::getParent() const
{
    return m_parent;
}

#endif /* #ifndef H_9C7EBBAB_91A4_47FA_9597_C69775689E3F */
