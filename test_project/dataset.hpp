#ifndef WATERDATASET_HPP
#define WATERDATASET_HPP

#include <vector>
#include <string>
#include "WaterSample.hpp"

class WaterDataset {
public:
    void loadData(const std::string& filename);
    const std::vector<WaterSample>& getData() const;
    void appendData(const std::vector<WaterSample>& newSamples);


private:
    std::vector<WaterSample> data;
    void checkDataExists() const;
};

#endif // WATERDATASET_HPP
