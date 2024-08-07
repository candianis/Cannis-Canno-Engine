#pragma once 

#include <cstdint>
#include <bitset>

using std::uint32_t;
using std::bitset;

const uint8_t maxComponents = 32;

class Signature {
public:
	void set(const uint32_t p_componentID);
	void set(const uint32_t p_componentID, bool p_leftUnchecked);
	void unset(const uint32_t p_componentID);
	bool hasComponent(const uint32_t p_componentID) const;

private:
	bitset<maxComponents> m_signature;
};