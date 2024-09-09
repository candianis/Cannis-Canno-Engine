#include "ccpch.h"
#include "KeyboardEvent.h"

namespace Cannis {
	PressedKeyboardEvent::PressedKeyboardEvent(int p_key) : m_keyCode(p_key) {

	}

	ReleasedKeyboardEvent::ReleasedKeyboardEvent(int p_key) : m_keyCode(p_key)	{

	}
}