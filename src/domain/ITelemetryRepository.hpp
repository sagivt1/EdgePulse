#pragma once
#include "TelemetryRecord.hpp"
#include <vector>

namespace edge::domain {
/**
 * @class ITelemetryRepository
 * @brief Defines the interface for telemetry data persistence.
 *
 * This class follows the Repository Pattern, abstracting the data storage
 * mechanism (e.g., SQLite, in-memory) from the domain logic. It provides
 * a contract for saving and retrieving telemetry records, which is crucial
 * for the store-and-forward mechanism.
 */
class ITelemetryRepository {
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived classes.
     */
    virtual ~ITelemetryRepository() = default;

    /**
     * @brief Persists a new telemetry record to the data store.
     * @param record The TelemetryRecord object to save.
     */
    virtual void SaveRecord(const TelemetryRecord& record) = 0;

    /**
     * @brief Fetches all records that have not yet been synchronized.
     * @return A vector of TelemetryRecord objects that are marked as unsynced.
     */
    virtual std::vector<TelemetryRecord> GetUnsyncedRecords() = 0;

    /**
     * @brief Marks a specific record as synchronized after it has been successfully forwarded.
     * @param id The unique identifier of the record to update.
     */
    virtual void MarkAsSynced(int id) = 0;

};    
} // namespace edge::domain
