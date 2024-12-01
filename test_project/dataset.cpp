#include "dataset.hpp"
#include "WaterSample.hpp"
#include "csv.hpp"
#include <stdexcept>
#include <iostream>

void WaterDataset::loadData(const std::string& filename) {
    csv::CSVReader reader(filename);

    data.clear();

    for (const auto& row : reader) {
        try {
            double level = 0.0;
            if (!row["result"].is_null()) {
                level = row["result"].get<double>();
            }

            WaterSample sample(
            row["sample.samplingPoint.label"].get<>(),
            row["determinand.label"].get<>(),
            level,
            row["determinand.unit.label"].get<>(),
            row["sample.isComplianceSample"].get<bool>() ? "Compliant" : "Non-Compliant"
             );
            std::cout << "Created WaterSample: "
            << sample.getLocation() << ", "
            << sample.getPollutant() << ", "
            << sample.getLevel() << ", "
            << sample.getUnit() << ", "
            << sample.getComplianceStatus() << std::endl;

            data.push_back(sample);
        } catch (const std::exception& e) {
            std::cerr << "Error processing row: " << e.what() << std::endl;
            continue;
        }
    }
}

const std::vector<WaterSample>& WaterDataset::getData() const {
    checkDataExists();
    return data;
}

void WaterDataset::checkDataExists() const {
    if (data.empty()) {
        throw std::runtime_error("Dataset is empty or could not be loaded!");
    }
}
