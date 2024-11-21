#pragma once

namespace Cannis {
	class Timestep {
	public:
		Timestep(float p_time = 0.0f);

		inline operator float() const { return m_time; }

		inline float GetSeconds() const { return m_time; }
		inline float GetMilliseconds() const { return m_time * 1000.0f; }

	private:
		float m_time;

	};
}