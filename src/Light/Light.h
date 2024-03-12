#pragma once

#include <glm/glm.hpp>

#include "../Shaders/Shader.h"

using glm::vec3;

namespace Cannis {

	class Light {
		public:
			Light(const vec3& p_position, const vec3& p_color);
			~Light() = default;

			void AssignToShader(const string& lightName, Shader* p_shader);

			/* @brief Apply this light or not */
			bool isEnabled;

			/* @brief Should be true for a spotlight or a point light, but false for a positional light */
			bool isLocal;

			/* @brief Contribution to ambient light or the light that is always in the scene */
			vec3 ambient;

			/* @brief Light that comes direclty from this */
			vec3 diffuse;

			/* @brief light that will be reflected producing a shiny way from this light by an object*/
			vec3 specular;

			/* @brief Color of the light @note This values should be between 0 and 1 */
			vec3 color;

			/* @brief */
			vec3 position;


		private:
			/* @brief */
			vec3 m_halfVector;

			/* @brief */
			float m_shininess;

			/* @brief */
			float m_constantAttenuation;

			/* @brief */
			float m_linearAttenuation;

			/* @brief */
			float m_quadraticAttenuation;
	};
}