#pragma once

#include "Logger.h"
#include "Event.h"
#include "GLFW/glfw3.h"

namespace Demo
{	
	class Window
	{
	private:
		using OnEventFn = std::function<void(Event&)>;

		struct WindowData
		{
			std::string Title;
			int Width;
			int Height;
			OnEventFn OnEvent;
		};

		WindowData windowData;
		std::unique_ptr<Logger> logger;
		GLFWwindow* glfwWindow;

	public:
		Window(const std::string& title, int width, int height);
		~Window();

		void SetEventListener(const std::function<void(Event&)>& onEvent);
		void OnUpdate();

	private:
		void InitGlfw();
		void TerminateGlfw();
		GLFWwindow* GetGlfwWindow();
		GLFWwindow* CreateGlfwWindow();
		void SetGlfwCallbacks();
	};
}