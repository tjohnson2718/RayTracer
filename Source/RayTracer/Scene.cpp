#include "Scene.h"
#include "Canvas.h"
#include "MathUtils.h"
#include "Ray.h"
#include "Object.h"
#include "Random.h"

void Scene::Render(class Canvas& canvas, int numSamples)
{
	for (int y = 0; y < canvas.GetSize().y; y++)
	{
		for (int x = 0; x < canvas.GetSize().x; x++)
		{
			glm::vec2 pixel = glm::vec2{ x, y };

			Color::color3_t color{ 0 };

			for (int sample = 0; sample < numSamples; sample++)
			{
				glm::vec2 point = (pixel + glm::vec2{ Random::random01(), Random::random01() }) / canvas.GetSize();
				
				//flip y
				point.y = 1.0f - point.y;

				//Create ray from camera
				ray_t ray = m_camera->GetRay(point);

				//Cast ray into scene
				//set color value from trace
				raycastHit_t raycastHit;
				color += Trace(ray, 0, 100, raycastHit, m_depth);
			}

			//draw color to canvas point (pixel)
			// Get average color
			color /= numSamples;
			canvas.DrawPoint(pixel, Color::color4_t(color, 1));
		}
	}
}

Color::color3_t Scene::Trace(const ray_t& ray)
{
	glm::vec3 direction = glm::normalize(ray.direction);

	// set scene sky color
	float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
	Color::color3_t color = MathUtils::lerp(m_bottomColor, m_topColor, t);

	return color;
}

Color::color3_t Scene::Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth)
{
	bool rayHit = false;
	float closestDistance = maxDistance;

	// check if scene objects are hit by the ray
	for (const auto& object : m_objects)
	{
		if (!object)
		{
			break;
		}
		// when checking objects don't include objects farther than closest hit (starts at max distance)
		if (object->Hit(ray, minDistance, closestDistance, raycastHit))
		{
			rayHit = true;
			// set closest distance to the raycast hit distance (only hit objects closer than closest distance)
			closestDistance = raycastHit.distance;
		}
	}

	if (rayHit)
	{
		ray_t scattered;
		Color::color3_t color;

		// check if maximum depth (number of bounces) is reached, get color from material and scattered ray
		if (depth > 0 && raycastHit.material->Scatter(ray, raycastHit, color, scattered))
		{
			// recursive function, call self and modulate colors of depth bounces
			return color * Trace(scattered, minDistance, maxDistance, raycastHit, depth - 1);
		}
		else
		{
			// reached maximum depth of bounces (get emissive color, will be black except for Emissive materials)
			return raycastHit.material->GetEmissive();
		}
	}

	// if ray hit object, scatter (bounce) ray and check for next hit
	/*if (rayHit)
	{
		ray_t scattered;
		Color::color3_t color;

		if (raycastHit.material->Scatter(ray, raycastHit, color, scattered))
		{
			return raycastHit.normal;
		}
		// check if maximum depth (number of bounces) is reached, get color from material and scattered ray
		if (depth > 0 && raycastHit.material->Scatter(ray, raycastHit, color, scattered))
		{
			// recursive function, call self and modulate (multiply) colors of depth bounces
			return color * Trace(scattered, minDistance, maxDistance, raycastHit, depth - 1);
		}
		else
		{
			// reached maximum depth of bounces (color is black)
			return Color::color3_t{ 0, 0, 0 };
		}
	}
	*/

	// if ray not hit, return scene sky color
	glm::vec3 direction = glm::normalize(ray.direction);
	float t = (direction.y + 1) * 0.5f; // direction.y (-1 <-> 1) => (0 <-> 1)
	Color::color3_t color = MathUtils::lerp(m_bottomColor, m_topColor, t);

	return color;
}