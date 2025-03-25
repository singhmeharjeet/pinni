#include <gtest/gtest.h>

#include <iostream>

#include <Pinni.h>

class Mock : public Pinni::Application {};

Pinni::Application* CreateApplication() {
	return new Mock();
}

TEST(PinniTest, SmokeTest) {
	auto app = CreateApplication();
	EXPECT_TRUE(app->SmokeTest());
	delete app;
}
