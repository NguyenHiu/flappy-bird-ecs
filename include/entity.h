#pragma once
#include <unordered_map>
#include "utils.h"

enum class EntityType {
    PLAYER,
    MENU
};

class Entity
{
private:
    static inline int m_nextId = 0;
    int m_id;
    std::unordered_map<std::string, void*> m_components;
public:
    Entity() : m_id(m_nextId++) {};
    ~Entity() {};

    int getId() const {
        return m_id;
    }

    template<typename T>
    void addComponent(T* component) {
        m_components[Utils::className<T>()] = component;
    }

    template<typename T>
    T* getComponent() {
        auto it = m_components.find(Utils::className<T>());
        // If the type T exists as a component, then cast it into T* before returning
        return it != m_components.end() ? static_cast<T*>(it->second) : nullptr;
    }

    template<typename T>
    bool hasComponent() {
        return m_components.find(Utils::className<T>()) != m_components.end();
    }
};