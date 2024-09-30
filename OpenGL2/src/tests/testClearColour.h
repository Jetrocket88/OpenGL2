#pragma once

#include "Test.h"

namespace test
{
	class TestClearColour : public Test
	{
	public:
		TestClearColour();
		~TestClearColour();

		void onUpdate(float deltaTime) override;
		void onRender() override;
		void onImGuiRender() override;
	private:
		float m_ClearColour[4];
	};
}