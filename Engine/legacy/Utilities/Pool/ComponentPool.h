#pragma once

#include <vector>
#include <unordered_map>
#include <cstdint>

#include "../Interface/IPool.h"

using std::vector;
using std::unordered_map;

// @brief Wrapper 
template <typename T>
class ComponentPool : public IPool {
public:
	ComponentPool(int p_size = 100);

	~ComponentPool() = default;

	bool isEmpty() const;

	int getSize() const;

	void resize(uint32_t p_newSize);

	void clear();

	void add(T p_object);

	// @brief
	// @param p_ID ID of the entity that a component 
	void set(uint32_t p_entityID, T p_component);

	void remove(uint32_t p_entityID);

	void removeEntityFromPool(uint32_t p_entityID) override {
		if (m_IDToIndex.find(p_entityID) != m_IDToIndex.end()) {
			remove(p_entityID);
		}
	}

	T& get(const uint32_t p_entityID);

	T& operator[](size_t index);

private:
	// @brief List of all 
	std::vector<T> m_data;

	// @brief We give data a capacity of 100 but the size of the object T inside is 0 at construction: we can have 5 objects but our capacity is 100
	uint32_t m_size;

	// @brief Helper maps to keep the vector always packed
	unordered_map<uint32_t, uint32_t> m_IDToIndex;

	// @brief Helper maps to keep the vector always packed
	unordered_map<uint32_t, uint32_t> m_indexToID;
};

template<typename T>
inline ComponentPool<T>::ComponentPool(int p_size) {
	m_size = 0;
	m_data.resize(p_size);
}

template<typename T>
inline bool ComponentPool<T>::isEmpty() const {
	return m_size == 0;
}

template<typename T>
inline int ComponentPool<T>::getSize() const {
	return m_size;
}

template<typename T>
inline void ComponentPool<T>::resize(uint32_t p_newSize) {
	m_data.resize(p_newSize);
}

template<typename T>
inline void ComponentPool<T>::clear() {
	m_data.clear();
	m_size = 0;
}

template<typename T>
inline void ComponentPool<T>::add(T p_object) {
	m_data.push_back(T);
}

template<typename T>
void ComponentPool<T>::set(uint32_t p_entityID, T p_component) {
	if (m_IDToIndex.find(p_entityID) != m_IDToIndex.end()) {
		//If we found the object then we do not need to add a new object, we simply replace those values
		int index = m_IDToIndex[p_entityID];
		m_data[index] = p_component;
		return;
	}

	int index = m_size;
	m_IDToIndex.emplace(p_entityID, index);
	m_indexToID.emplace(index, p_entityID);
	if (index >= m_data.capacity()) {
		m_data.resize(m_size * 2);
	}
	m_data[index] = p_component;
	m_size++;
}

template<typename T>
void ComponentPool<T>::remove(uint32_t p_entityID) {
	//Copy the last object to the deleted position in order to keep the array packed
	int indexOfRemoved = m_IDToIndex[p_entityID];
	int indexOfLast = m_size - 1;
	m_data[indexOfRemoved] = m_data[indexOfLast];

	//Update the index-entity maps to point to the correct elements
	int entityIdOfLast = m_indexToID[indexOfLast];
	m_IDToIndex[entityIdOfLast] = indexOfRemoved;
	m_indexToID[indexOfRemoved] = entityIdOfLast;

	m_IDToIndex.erase(p_entityID);
	m_indexToID.erase(indexOfLast);

	--m_size;
}

template<typename T>
T& ComponentPool<T>::get(const uint32_t p_entityID) {
	int index = m_IDToIndex[p_entityID];
	return static_cast<T&>(m_data[index]);
}

template<typename T>
T& ComponentPool<T>::operator[](size_t index) {
	return m_data[index];
}

