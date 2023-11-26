/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include "OvRendering/Core/CompositeRenderer.h"
#include "OvRendering/Features/ARenderFeature.h"
#include "OvRendering/Data/FrameInfo.h"
#include "OvRendering/Entities/Light.h"
#include "OvRendering/Buffers/ShaderStorageBuffer.h"
#include "OvRendering/Data/Frustum.h"

namespace OvRendering::Features
{
	class LightingRenderFeature : public ARenderFeature
	{
	public:
		using LightSet = std::vector<std::reference_wrapper<const OvRendering::Entities::Light>>;

		/**
		* Constructor
		* @param p_renderer
		* @param p_bufferBindingPoint
		*/
		LightingRenderFeature(OvRendering::Core::CompositeRenderer& p_renderer, uint32_t p_bufferBindingPoint = 0);

		/**
		* Fill up the light buffer with light matrices generated from the given light set, and filtered
		* using the given optional frustum instance
		* @param p_lights
		* @param p_frustum
		*/
		void UploadLightingData(const LightSet& p_lights, std::optional<OvRendering::Data::Frustum> p_frustum);

		/**
		* Invoked when the frame begins, bind the light buffer
		* @param p_outputDesc
		*/
		virtual void OnBeginFrame(std::optional<Data::RenderOutputDesc>& p_outputDesc) override;

		/**
		* Invoked when the frame ends, unbind the light buffer
		*/
		virtual void OnEndFrame() override;

	private:
		uint32_t m_bufferBindingPoint;
		std::unique_ptr<OvRendering::Buffers::ShaderStorageBuffer> m_lightBuffer;
	};
}
