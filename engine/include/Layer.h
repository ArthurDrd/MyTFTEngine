#pragma once
#include <string>
#include "Timestep.h"

namespace MyTFTEngine {

	class Layer {
	public:
		Layer(const std::string& name = "Layer"): m_DebugName(name) {}
		virtual ~Layer() = default;
		
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	
		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}