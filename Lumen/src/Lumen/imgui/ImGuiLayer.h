#pragma once

#include "Lumen/Layer.h"
#include "Lumen/Core.h"

#include "Lumen/Events/ApplicationEvents.h"
#include "Lumen/Events/KeyEvent.h"
#include "Lumen/Events/MouseEvent.h"

namespace Lumen
{
	class LUMEN_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
		inline const std::string& GetName() const { return m_DebugName; }
		std::string ToString() const { return GetName(); }
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}