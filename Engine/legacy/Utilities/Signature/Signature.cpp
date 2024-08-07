#include "Signature.h"

void Signature::set(const uint32_t p_componentID) {
	m_signature.set(p_componentID);
}

void Signature::set(const uint32_t p_componentID, bool p_leftUnchecked) {
	m_signature.set(p_componentID, p_leftUnchecked);
}

void Signature::unset(const uint32_t p_componentID) {
	m_signature.reset(p_componentID);
}

bool Signature::hasComponent(const uint32_t p_componentID) const {
	return m_signature.test(p_componentID);
}
