#include "dataset.hpp"
#include "csv.hpp"
#include <stdexcept>

void WaterDataset::loadData(const std::string& filename) {
    csv::CSVReader reader(filename);

    data.clear();

    for (const auto& row : reader) {
        WaterSample sample{
            row["sample.samplingPoint.label"].get<>(),
            row["determinand.label"].get<>(),
            row["result"].get<double>(),
            row["determinand.unit.label"].get<>(),
            row["sample.isComplianceSample"].get<bool>() ? "Compliant" : "Non-Compliant"
        };
        data.push_back(sample);
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
