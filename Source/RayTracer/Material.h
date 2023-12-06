#pragma once
#include "Ray.h"
#include "Color.h"

class Material
{
public:
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, Color::color3_t& color, ray_t& scattered) const = 0;
	virtual Color::color3_t GetEmissive() const { return { 0, 0, 0 }; }
};

class Lambertian : public Material
{
public:
	Lambertian(const Color::color3_t& albedo) : m_albedo{ albedo } {}
	bool Scatter(const ray_t& ray, const raycastHit_t& raycast, Color::color3_t& color, ray_t& scattered) const override;

protected:
	Color::color3_t m_albedo;
};

class Metal : public Material
{
public:
	Metal(const glm::vec3& albedo, float fuzz) : m_albedo{ albedo }, m_fuzz{ fuzz } {}
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const override;

protected:
	glm::vec3 m_albedo{ 0 };
	float m_fuzz = 0;
};

class Dielectric : public Material
{
public:
	Dielectric(const glm::vec3& albedo, float index) : m_albedo{ albedo }, m_index{ index } {}
	virtual bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, glm::vec3& color, ray_t& scattered) const override;

protected:
	glm::vec3 m_albedo{ 1 };
	float m_index{ 1 }; // refraction index
};

class Emissive : public Material
{
public:
	Emissive(const Color::color3_t& albedo, float intensity = 1) : m_albedo{ albedo }, m_intensity{ intensity } {}
	bool Scatter(const ray_t& ray, const raycastHit_t& raycastHit, Color::color3_t& color, ray_t& scattered) const override { return false; }
	Color::color3_t GetEmissive() const override { return m_albedo * m_intensity; }

private:
	glm::vec3 m_albedo{ 1, 1, 1 };
	float m_intensity{ 1 };
};