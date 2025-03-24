#include <Engine.h>
#include <gtest/gtest.h>

#include <iostream>

// Basic test to check if the engine can be initialized
TEST(EngineTest, Initialization) {
	Pinni::Engine gameEngine;
	// Just testing if initialization doesn't crash
	ASSERT_NO_THROW({
		gameEngine.print();
	});
}
