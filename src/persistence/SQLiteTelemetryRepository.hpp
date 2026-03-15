#pragma once
#include "../domain/ITelemetryRepository.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <string>

namespace edge::persistence {

/**
 * @class SQLiteTelemetryRepository
 * @brief A concrete implementation of the ITelemetryRepository interface using SQLite.
 *
 * This class handles all database operations for telemetry records, including
 * creating the database schema, saving new records, and retrieving unsynced records.
 * It uses the SQLiteCpp library to interact with the SQLite database file.
 */
class SQLiteTelemetryRepository : public domain::ITelemetryRepository {

public:
    /**
     * @brief Constructs a new SQLiteTelemetryRepository object.
     *
     * Opens a connection to the SQLite database at the given path and ensures
     * the necessary table schema is created.
     * @param db_path The file path to the SQLite database.
     */
    explicit SQLiteTelemetryRepository(const std::string& db_path);

    /// @brief Saves a telemetry record to the database.
    /// @param record The record to persist.
    void SaveRecord(const domain::TelemetryRecord& record) override;

    /// @brief Retrieves all records from the database that have not been synced.
    /// @return A vector of unsynced TelemetryRecord objects.
    std::vector<domain::TelemetryRecord> GetUnsyncedRecords() override;

    /// @brief Marks a record in the database as synced.
    /// @param id The primary key ID of the record to update.
    void MarkAsSynced(int id) override;

private:
    /**
     * @brief The database connection object.
     *
     * The SQLiteCpp library uses RAII to manage the connection lifecycle,
     * ensuring the database is properly opened and closed.
     */
    SQLite::Database m_db;
    
    /// @brief Ensures the 'telemetry' table exists in the database with the correct schema.
    void InitializeSchema();

};

}