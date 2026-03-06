#include "core/Exceptions.hpp"
#include "core/Logger.hpp"

int main() {
    
    // init observability core
    edge::Logger::Init();
    EDGE_INFO("EdgePulse Gateway: Observability Initialized.");

    try {
        // Simulate a routine operation
        EDGE_TRACE("Attempting to connect to sensor network...");

        throw edge::HardwareException("I2C Bus timeout on Sensor A4");
    } catch (const edge::EdgePulseException& e) {
        // Cathc domain specific exception and log them as error
        EDGE_CRITICAL("Gateway caught a fatal standard exception: {}", e.what());
    } catch (const std::exception& e) {
        // Catch-all for standard library exceptions
        EDGE_CRITICAL("Gateway caught a fatal standard exception: {}", e.what());
        return 1;
    }

    EDGE_INFO("EdgePulse Gateway shutting down gracefully.");
    return 0;
}