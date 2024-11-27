#include "WaterSample.hpp"

// Constructor
WaterSample::WaterSample(const std::string& location, const std::string& pollutant, double level, 
                         const std::string& unit, const std::string& complianceStatus)
    : location(location), pollutant(pollutant), level(level), unit(unit), complianceStatus(complianceStatus) {}

// Getters
const std::string& WaterSample::getLocation() const {
    return location;
}

const std::string& WaterSample::getPollutant() const {
    return pollutant;
}

double WaterSample::getLevel() const {
    return level;
}

const std::string& WaterSample::getUnit() const {
    return unit;
}

const std::string& WaterSample::getComplianceStatus() const {
    return complianceStatus;
}

// Setters (optional)
void WaterSample::setLocation(const std::string& location) {
    this->location = location;
}

void WaterSample::setPollutant(const std::string& pollutant) {
    this->pollutant = pollutant;
}

void WaterSample::setLevel(double level) {
    this->level = level;
}

void WaterSample::setUnit(const std::string& unit) {
    this->unit = unit;
}

void WaterSample::setComplianceStatus(const std::string& complianceStatus) {
    this->complianceStatus = complianceStatus;
}
