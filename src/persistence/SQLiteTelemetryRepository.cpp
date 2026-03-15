#include "SQLiteTelemetryRepository.hpp"
#include "../core/Logger.hpp"
#include "../core/Exceptions.hpp"

namespace edge::persistence {

// Constructor: Initializes the SQLite database connection.
// Opens the database in read/write mode and creates it if it doesn't exist.
SQLiteTelemetryRepository::SQLiteTelemetryRepository(const std::string& db_path) 
    : m_db(db_path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) 
{

    EDGE_INFO("Database connected at: {}", db_path);
    InitializeSchema(); // Ensure the required tables exist upon connection
}

// Creates the 'telemetry' table if it doesn't already exist in the database.
void SQLiteTelemetryRepository::InitializeSchema() {
    try {
        // SQL statement to create the telemetry table with appropriate data types.
        const char* create_table_sql = R"(
        CREATE TABLE IF NOT EXISTS telemetry (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            timestamp TEXT NOT NULL,
            sensor_id TEXT NOT NULL,
            value REAL NOT NULL,
            is_anomaly INTEGER DEFAULT 0,
            is_synced INTEGER DEFAULT 0
            );
        )";
        m_db.exec(create_table_sql);
        EDGE_TRACE("Database schema initialized.");
    } catch (const std::exception& e) {
        // Log the error and rethrow as a domain-specific exception
        EDGE_CRITICAL("Failed to initialize database schema: {}", e.what());
        throw HardwareException("Database Initialization Failure");
    }
}

// Inserts a new telemetry record into the database.
void SQLiteTelemetryRepository::SaveRecord(const domain::TelemetryRecord& record) {

    try {
        // Use a parameterized query to prevent SQL injection attacks.
        SQLite::Statement query(m_db, 
            R"(INSERT INTO telemetry
                (timestamp, sensor_id, value, is_anomaly, is_synced)
                VALUES (?, ?, ?, ?, ?))"
        );
        
        // Bind the record's properties to the query parameters.
        query.bind(1, record.timestamp);
        query.bind(2, record.sensor_id);
        query.bind(3, record.value);
        query.bind(4, record.is_anomaly ? 1 : 0); // Convert bool to integer for SQLite
        query.bind(5, record.is_synced ? 1 : 0);  // Convert bool to integer for SQLite

        query.exec(); // Execute the insertion
    } catch (const std::exception& e) {
        EDGE_ERROR("Failed to save record: {}", e.what());
        throw HardwareException("Database Write Failure");
    }
}

// Retrieves records that have not yet been synchronized.
// Currently a stub pending implementation.
std::vector<domain::TelemetryRecord> SQLiteTelemetryRepository::GetUnsyncedRecords() {
    // TODO : implement sending data
    return {};
}

// Updates a specific record to indicate it has been successfully synchronized.
// Currently a stub pending implementation.
void SQLiteTelemetryRepository::MarkAsSynced(int id) {
    // TODO: implement mark as sync
}

}