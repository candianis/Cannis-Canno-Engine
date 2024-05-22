#pragma once

// @brief Interface so that any data structure can contain Pools of different components
class IPool {
public:
	virtual ~IPool() = default;
	virtual void removeEntityFromPool(uint32_t p_entityId) = 0;
};