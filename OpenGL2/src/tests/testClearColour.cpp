#include "testClearColour.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test
{
	TestClearColour::TestClearColour()
		:m_ClearColour {0.2f, 0.3f, 0.8f, 1.0f}
	{

	}
	TestClearColour::~TestClearColour()
	{

	}
	void TestClearColour::onUpdate(float deltaTime)
	{

	}
	void TestClearColour::onRender()
	{
		GLCall(glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	void TestClearColour::onImGuiRender()
	{
		ImGui::ColorEdit4("Clear Colour", m_ClearColour);
	}
}