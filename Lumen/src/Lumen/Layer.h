#pragma once

#include "Lumen/Core.h"
#include "Lumen/Core/Timestep.h"
#include "Lumen/Events/Event.h"

namespace Lumen
{
	class LUMEN_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		// When a layer is pushed on to the stack...
		virtual void OnAttach() {} // attach the layer
		virtual void OnDetach() {} // detach the layer
		virtual void OnUpdate(Timestep ts) {} // update layer
		virtual void OnEvent(Event& event) {} // event is sent to the layer

		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}