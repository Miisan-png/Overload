/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <cmath>

#include "OvRendering/Entities/Camera.h"
#include "OvMaths/FMatrix4.h"

OvRendering::Entities::Camera::Camera() :
    m_projectionMode(Settings::EProjectionMode::PERSPECTIVE),
	m_fov(45.0f),
    m_size(5.0f),
	m_near(0.1f),
	m_far(100.f),
	m_clearColor(0.f, 0.f, 0.f),
	m_frustumGeometryCulling(false),
	m_frustumLightCulling(false)
{
}

void OvRendering::Entities::Camera::CacheMatrices(uint16_t p_windowWidth, uint16_t p_windowHeight, const OvMaths::FVector3& p_position, const OvMaths::FQuaternion& p_rotation)
{
	CacheProjectionMatrix(p_windowWidth, p_windowHeight);
	CacheViewMatrix(p_position, p_rotation);
	CacheFrustum(m_viewMatrix, m_projectionMatrix);
}

void OvRendering::Entities::Camera::CacheProjectionMatrix(uint16_t p_windowWidth, uint16_t p_windowHeight)
{
	m_projectionMatrix = CalculateProjectionMatrix(p_windowWidth, p_windowHeight);
}

void OvRendering::Entities::Camera::CacheViewMatrix(const OvMaths::FVector3& p_position, const OvMaths::FQuaternion& p_rotation)
{
	m_viewMatrix = CalculateViewMatrix(p_position, p_rotation);
}

void OvRendering::Entities::Camera::CacheFrustum(const OvMaths::FMatrix4& p_view, const OvMaths::FMatrix4& p_projection)
{
	m_frustum.CalculateFrustum(p_projection * p_view);
}

float OvRendering::Entities::Camera::GetFov() const
{
	return m_fov;
}

float OvRendering::Entities::Camera::GetSize() const
{
    return m_size;
}

float OvRendering::Entities::Camera::GetNear() const
{
	return m_near;
}

float OvRendering::Entities::Camera::GetFar() const
{
	return m_far;
}

const OvMaths::FVector3 & OvRendering::Entities::Camera::GetClearColor() const
{
	return m_clearColor;
}

const OvMaths::FMatrix4& OvRendering::Entities::Camera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

const OvMaths::FMatrix4& OvRendering::Entities::Camera::GetViewMatrix() const
{
	return m_viewMatrix;
}

const OvRendering::Data::Frustum& OvRendering::Entities::Camera::GetFrustum() const
{
	return m_frustum;
}

bool OvRendering::Entities::Camera::HasFrustumGeometryCulling() const
{
	return m_frustumGeometryCulling;
}

bool OvRendering::Entities::Camera::HasFrustumLightCulling() const
{
	return m_frustumLightCulling;
}

OvRendering::Settings::EProjectionMode OvRendering::Entities::Camera::GetProjectionMode() const
{
    return m_projectionMode;
}

void OvRendering::Entities::Camera::SetFov(float p_value)
{
	m_fov = p_value;
}

void OvRendering::Entities::Camera::SetSize(float p_value)
{
    m_size = p_value;
}

void OvRendering::Entities::Camera::SetNear(float p_value)
{
	m_near = p_value;
}

void OvRendering::Entities::Camera::SetFar(float p_value)
{
	m_far = p_value;
}

void OvRendering::Entities::Camera::SetClearColor(const OvMaths::FVector3 & p_clearColor)
{
	m_clearColor = p_clearColor;
}

void OvRendering::Entities::Camera::SetFrustumGeometryCulling(bool p_enable)
{
	m_frustumGeometryCulling = p_enable;
}

void OvRendering::Entities::Camera::SetFrustumLightCulling(bool p_enable)
{
	m_frustumLightCulling = p_enable;
}

void OvRendering::Entities::Camera::SetProjectionMode(OvRendering::Settings::EProjectionMode p_projectionMode)
{
    m_projectionMode = p_projectionMode;
}

OvMaths::FMatrix4 OvRendering::Entities::Camera::CalculateProjectionMatrix(uint16_t p_windowWidth, uint16_t p_windowHeight) const
{
    using namespace OvMaths;
    using namespace OvRendering::Settings;

    const auto ratio = p_windowWidth / static_cast<float>(p_windowHeight);

    switch (m_projectionMode)
    {
    case EProjectionMode::ORTHOGRAPHIC:
        return FMatrix4::CreateOrthographic(m_size, ratio, m_near, m_far);

    case EProjectionMode::PERSPECTIVE: 
        return FMatrix4::CreatePerspective(m_fov, ratio, m_near, m_far);

    default:
        return FMatrix4::Identity;
    }
}

OvMaths::FMatrix4 OvRendering::Entities::Camera::CalculateViewMatrix(const OvMaths::FVector3& p_position, const OvMaths::FQuaternion& p_rotation) const
{
	const auto& up = p_rotation * OvMaths::FVector3::Up;
	const auto& forward = p_rotation * OvMaths::FVector3::Forward;

	return OvMaths::FMatrix4::CreateView
	(
		p_position.x, p_position.y, p_position.z,												// Position
		p_position.x + forward.x, p_position.y + forward.y, p_position.z + forward.z,			// LookAt (Position + Forward)
		up.x, up.y, up.z																		// Up Vector
	);
}