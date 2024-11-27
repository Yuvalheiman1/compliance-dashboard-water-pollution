#ifndef WATERSAMPLE_HPP
#define WATERSAMPLE_HPP

#include <string>

class WaterSample {
public:
    // Constructor
    WaterSample(const std::string& location, const std::string& pollutant, double level, 
                const std::string& unit, const std::string& complianceStatus);

    // Getters
    const std::string& getLocation() const;
    const std::string& getPollutant() const;
    double getLevel() const;
    const std::string& getUnit() const;
    const std::string& getComplianceStatus() const;

    // Setters (optional, if modification is needed)
    void setLocation(const std::string& location);
    void setPollutant(const std::string& pollutant);
    void setLevel(double level);
    void setUnit(const std::string& unit);
    void setComplianceStatus(const std::string& complianceStatus);

private:
    // Member variables
    std::string location;
    std::string pollutant;
    double level;
    std::string unit;
    std::string complianceStatus;
};

#endif // WATERSAMPLE_HPP
