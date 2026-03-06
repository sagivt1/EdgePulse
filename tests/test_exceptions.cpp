#include <gtest/gtest.h>
#include "../src/core/Exceptions.hpp"
#include "../src/core/Logger.hpp"


// Test that our exceptions format messages correctly
TEST(ExceptionTest, HardwareExceptionFormatting) {
    try {
        throw edge::HardwareException("I2C Bus timeout on Sensor A4");
    } catch (const edge::HardwareException& e) {
        EXPECT_STREQ(e.what(), "Hardware Error: I2C Bus timeout on Sensor A4");
    }
}

TEST(ExceptionTest, NetworkExceptionFormatting) {
    try {
        throw edge::NetworkException("MQTT Broker disconnected");
    } catch (const edge::NetworkException& e) {
        EXPECT_STREQ(e.what(), "Network Error: MQTT Broker disconnected");
    }
}

// Test Logger initialization (smoke test)
TEST(LoggerTest, InitializationDoesNotCrash) {
    EXPECT_NO_THROW(edge::Logger::Init());
    EXPECT_NE(edge::Logger::GetCoreLogger(), nullptr);
}
