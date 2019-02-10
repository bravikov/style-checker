#ifndef H_9C7EBBAB_91A4_47FA_9597_C69775689E3F
#define H_9C7EBBAB_91A4_47FA_9597_C69775689E3F

#include <memory>
#include <unordered_map>

template<typename Key>
class Tree
{
public:
    Tree<Key>() = default;
    Tree<Key>* addChild(const Key& key);
    Tree<Key>* getChild(const Key& key);
    const Tree<Key>* getChild(const Key& key) const;

private:
    Tree<Key>* parent{nullptr};
    std::unordered_map<Key, std::unique_ptr<Tree<Key>>> childs;
};


template<typename Key>
Tree<Key>* Tree<Key>::addChild(const Key& key)
{
    childs[key]->parent = this;
    return childs[key].get();
}

template<typename Key>
Tree<Key>* Tree<Key>::getChild(const Key &key)
{
    auto it = childs.find(key);
    if (it == childs.end()) {
        return nullptr;
    }
    return it->second.get();
}

template<typename Key>
const Tree<Key>* Tree<Key>::getChild(const Key &key) const
{
    auto it = childs.find(key);
    if (it == childs.end()) {
        return nullptr;
    }
    return it->second.get();
}

#endif /* #ifndef H_9C7EBBAB_91A4_47FA_9597_C69775689E3F */
