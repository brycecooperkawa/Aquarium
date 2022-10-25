/**
 * @file FishBetaTest.cpp
 * @author Bryce Cooperkawa
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <FishBeta.h>
#include <Aquarium.h>

TEST(FishBetaTest, Construct) {
    // Construct an item to test
    Aquarium aquarium;
    FishBeta fishBeta(&aquarium);
}


