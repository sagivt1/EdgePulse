#include <gtest/gtest.h>
#include "../src/persistence/SQLiteTelemetryRepository.hpp"
#include "../src/domain/TelemetryRecord.hpp"
#include "../src/core/Logger.hpp"

/**
 * @class PersistenceTest
 * @brief Test fixture for persistence layer testing.
 *
 * Ensures that the required environment (like the core Logger) is initialized
 * before running the database tests to prevent runtime crashes.
 */
class PersistenceTest : public ::testing::Test {
protected:
    /**
     * @brief Prepares the test environment.
     */
    void SetUp() override {
        // Initialize Logger for the tests so EDGE_INFO doesn't crash
        edge::Logger::Init();
    }
};

/**
 * @brief Verifies schema initialization and basic insertion capabilities.
 *
 * Uses an in-memory database to avoid touching the filesystem and ensures
 * that the SaveRecord method executes without throwing any exceptions.
 */
TEST_F(PersistenceTest, InitializesSchemaAndSavesRecord) {
    // 1. Arrange: Instantiate the repository using a temporary IN-MEMORY database
    edge::persistence::SQLiteTelemetryRepository repo(":memory:");

    edge::domain::TelemetryRecord record;
    record.timestamp = "2026-03-15T11:34:00Z";
    record.sensor_id = "sensor_vibration_1";
    record.value = 42.5;
    record.is_anomaly = false;
    record.is_synced = false;

    // 2 & 3. Act & Assert: Verify that saving the record does not throw an exception
    EXPECT_NO_THROW(repo.SaveRecord(record));
}
