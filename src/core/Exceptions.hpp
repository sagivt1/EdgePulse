#pragma once
#include <stdexcept>
#include <string>

namespace edge {

/**
 * @class EdgePulseException
 * @brief Base exception class for the EdgePulse application.
 * 
 * Inherits from std::runtime_error to provide a standard way to handle
 * runtime errors specific to this application.
 */
class EdgePulseException : public std::runtime_error {
    
public:
    /**
     * @brief Construct a new Edge Pulse Exception object.
     * 
     * @param message The error message describing the exception.
     */
    explicit EdgePulseException(const std::string& message) : 
        std::runtime_error(message) {}
};

/**
 * @class HardwareException
 * @brief Exception thrown when a hardware-related error occurs.
 * 
 * Automatically prefixes the error message with "Hardware Error: ".
 */
class HardwareException : public EdgePulseException {
public:
    /**
     * @brief Construct a new Hardware Exception object.
     * 
     * @param message The specific hardware error details.
     */
    explicit HardwareException(const std::string& message) : 
        EdgePulseException("Hardware Error: " + message) {}
};

/**
 * @class NetworkException
 * @brief Exception thrown when a network-related error occurs.
 * 
 * Automatically prefixes the error message with "Network Error: ".
 */
class NetworkException : public EdgePulseException {
public:
    /**
     * @brief Construct a new Network Exception object.
     * 
     * @param message The specific network error details.
     */
    explicit NetworkException(const std::string& message) : 
        EdgePulseException("Network Error: " + message) {}
};

} // namespace edge
