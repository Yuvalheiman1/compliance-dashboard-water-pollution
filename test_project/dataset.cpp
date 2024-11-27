#include "dataset.hpp"
#include "csv.hpp"
#include <stdexcept>
#include <sstream>

void WaterDataset::loadData(const std::string& filename) {
    csv::CSVReader reader(filename);

    data.clear();

    for (const auto& row : reader) {
        try {
            double level = 0.0;
            if (!row["result"].is_null()) {
                std::stringstream ss(row["result"].get<>());
                if (!(ss >> level)) {
                    throw std::runtime_error("Invalid numeric value in 'result'");
                }
            }

            WaterSample sample{
                row["sample.samplingPoint.label"].get<>(),
                row["determinand.label"].get<>(),
                level,
                row["determinand.unit.label"].get<>(),
                row["sample.isComplianceSample"].get<bool>() ? "Compliant" : "Non-Compliant"
            };
            data.push_back(sample);
        } catch (const std::exception& e) {
            // Log or skip invalid rows
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
