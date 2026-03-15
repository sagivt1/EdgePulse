#pragma once
#include <string>

namespace edge::domain{
/**
 * @struct TelemetryRecord
 * @brief Represents a single data point captured from a sensor.
 * 
 * This struct is the core data model for telemetry information as it moves
 * through the system, from initial capture to persistence and synchronization.
 */
struct TelemetryRecord {

    /**
     * @brief The unique identifier for the record in the local database.
     * This is typically auto-incremented.
     */
    int id=0;
    
    /// @brief The timestamp when the record was captured, preferably in ISO 8601 format.
    std::string timestamp;

    /// @brief The unique identifier of the sensor that generated this data.
    std::string sensor_id;

    /// @brief The numerical value of the sensor reading.
    double value;

    /// @brief A flag indicating whether this record has been identified as an anomaly.
    bool is_anomaly = false;

    /// @brief A flag indicating if this record has been successfully synced with the cloud. This is the core of the store-and-forward mechanism.
    bool is_synced = false;
};

} // namespace edge::domain