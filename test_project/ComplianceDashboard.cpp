#include "ComplianceDashboard.hpp"
#include "dataset.hpp"
#include "WaterSample.hpp"
#include "PollutantSample.hpp"
#include "csv.hpp"
#include <iostream>
#include <string>

ComplianceDashboard::ComplianceDashboard(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    populateTable("Y-2024-M.csv");
}

ComplianceDashboard::~ComplianceDashboard() {}

void ComplianceDashboard::setupUI() {
    // Central Widget
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout();

    // Header
    header = new QLabel("Compliance Dashboard");
    header->setAlignment(Qt::AlignCenter);
    header->setStyleSheet("font-size: 18px; font-weight: bold;");
    mainLayout->addWidget(header);

    // Summary Cards
    cardsLayout = new QHBoxLayout();

    WaterDataset dataset;
    std::vector<PollutantSample> pollutantSamples = dataset.loadPollutantSamples("pollutants.csv", 10);

    for (int i = 0; i < 4; ++i) { // Only first 4 rows
        summaryCards[i] = new QFrame();
        summaryCards[i]->setFrameShape(QFrame::StyledPanel);
        summaryCards[i]->setStyleSheet("background-color: #f2f2f2; border: 1px solid #d9d9d9; padding: 10px;");
        summaryCards[i]->setMinimumHeight(200);
        summaryCards[i]->setMinimumWidth(400);

        QVBoxLayout *cardLayout = new QVBoxLayout();

        QLabel *cardTitle = new QLabel();
        QLabel *cardDetails = new QLabel();

        if (i < pollutantSamples.size()) {
            const PollutantSample& sample = pollutantSamples[i];
            cardTitle->setText(QString::fromStdString(sample.getName()));
            QString details = QString("Unit: %1\nMin Threshold: %2\nMax Threshold: %3\nInfo: %4")
                                    .arg(QString::fromStdString(sample.getUnit()))
                                    .arg(QString::fromStdString(sample.getMinThreshold()))
                                    .arg(QString::fromStdString(sample.getMaxThreshold()))
                                    .arg(QString::fromStdString(sample.getInfo()));
            cardDetails->setText(details);
        } else {
            cardTitle->setText("No Data");
            cardDetails->setText("No additional information available.");
        }

        cardTitle->setAlignment(Qt::AlignCenter);
        cardDetails->setAlignment(Qt::AlignLeft);
        cardLayout->addWidget(cardTitle);
        cardLayout->addWidget(cardDetails);

        summaryCards[i]->setLayout(cardLayout);
        cardsLayout->addWidget(summaryCards[i]);
    }
    mainLayout->addLayout(cardsLayout);

    // Filters Section
    filtersLayout = new QHBoxLayout();

    yearFilter = new QComboBox();
    yearFilter->addItems({"All Years", "2020", "2021", "2022", "2023", "2024"});
     yearFilter->setCurrentIndex(5);

    csv::CSVReader reader1("Locations.csv");
    locationFilter = new QComboBox();
    locationFilter->addItems({"All Locations"});

    for (const auto& row : reader1) {
            locationFilter->addItems({QString::fromStdString(row["Location"].get<>())});
    }

    pollutantFilter = new QComboBox();


    pollutantFilter->addItem("All Pollutants");
    for (const auto& sample : pollutantSamples) {
        pollutantFilter->addItem(QString::fromStdString(sample.getName()));
    }

    statusFilter = new QComboBox();
    statusFilter->addItems({"All Statuses", "good", "medium", "bad"});

    filterButton = new QPushButton("Filter");

    filtersLayout->addWidget(yearFilter);
    filtersLayout->addWidget(locationFilter);
    filtersLayout->addWidget(pollutantFilter);
    filtersLayout->addWidget(statusFilter);
    filtersLayout->addWidget(filterButton);

    mainLayout->addLayout(filtersLayout);

    // Main Content Area
    contentLayout = new QHBoxLayout();

    // Detailed Table
    detailedTable = new QTableWidget(0, 6); // Start with 0 rows, 5 columns
    detailedTable->setHorizontalHeaderLabels({"Location", "Pollutant", "Level", "Unit", "Compliance", "Date"});
    detailedTable->setMinimumSize(600, 300); // Keep table smaller
    contentLayout->addWidget(detailedTable, 2);

    // Summary of Important Info
    importantInfo = new QTextEdit();
    importantInfo->setPlaceholderText("Summary of important information...");
    importantInfo->setReadOnly(true);
    importantInfo->setMinimumSize(200, 300);
    contentLayout->addWidget(importantInfo, 1);

    mainLayout->addLayout(contentLayout);

    // Footer
    footer = new QLabel("Data provided by UK Environmental Agency.");
    footer->setAlignment(Qt::AlignCenter);
    footer->setStyleSheet("font-size: 12px; color: gray;");
    mainLayout->addWidget(footer);

    // Set Layout
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    resize(1200, 800); // Adjust window size to fit larger cards

    // Connect filter button to applyFilters
    connect(filterButton, &QPushButton::clicked, this, &ComplianceDashboard::applyFilters);
}

void ComplianceDashboard::populateTable(const std::string& filename) {
    WaterDataset dataset;
    dataset.loadData(filename);

    std::vector<PollutantSample> pollutantSamples = dataset.loadPollutantSamples("pollutants.csv", 10);
    const auto& samples = dataset.getData();
    if (samples.empty()) {
        // Display a pop-up if the dataset is empty
        QMessageBox::warning(this, "No Data Found", "There is no data available in the file. Please download it from - <a href='https://environment.data.gov.uk/water-quality/view/download'>this link</a>");
        return;
    }

    detailedTable->setRowCount(samples.size());
    detailedTable->setColumnCount(6); // Number of columns
    detailedTable->setHorizontalHeaderLabels({"Location", "Pollutant", "Level", "Unit", "Date", "Compliance"});

    for (size_t i = 0; i < samples.size(); ++i) {
        const auto& sample = samples[i];
        detailedTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(sample.getLocation())));
        detailedTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(sample.getPollutant())));
        detailedTable->setItem(i, 2, new QTableWidgetItem(QString::number(sample.getLevel())));
        detailedTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(sample.getUnit())));
        detailedTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(sample.getSampleDate())));

        //Arab code-
for (int j = 0; j < 10; j++) {
    std::cout << "Created WaterSample---------------------------------------- " << j << std::endl;

    // Compare pollutant name with string comparison
    if (sample.getPollutant() == pollutantSamples[j].getName()) {

        std::cout << "Created WaterSample *********************" << j << std::endl;

        // Convert sample level and thresholds to double
        double sampleLevel = sample.getLevel();
        double minThreshold = std::stod(pollutantSamples[j].getMinThreshold());
        double maxThreshold = std::stod(pollutantSamples[j].getMaxThreshold());

        // Calculate the interval length (range between min and max threshold)
        double thresholdRange = maxThreshold - minThreshold;

        // First condition: Good level (within the threshold range)
        if (sampleLevel >= minThreshold && sampleLevel <= maxThreshold) {
            detailedTable->setItem(i, 5, new QTableWidgetItem(QString::fromStdString("good")));
        }
        // Second condition: Medium level (within 20% of the interval length)
        else if (sampleLevel >= minThreshold - 0.2 * thresholdRange && sampleLevel <= maxThreshold + 0.2 * thresholdRange) {
            detailedTable->setItem(i, 5, new QTableWidgetItem(QString::fromStdString("medium")));
        }
        // Else: Bad level (outside 20% of the interval range)
        else {
            detailedTable->setItem(i, 5, new QTableWidgetItem(QString::fromStdString("bad")));
        }
    }
}


// Set the compliance status as it is
detailedTable->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(sample.getComplianceStatus())));

    }
}

void ComplianceDashboard::applyFilters() {


    // Retrieve filter criteria
    QString selectedYear = yearFilter->currentText();
    QString selectedLocation = locationFilter->currentText();
    QString selectedPollutant = pollutantFilter->currentText();
    QString selectedStatus = statusFilter->currentText();

    // Load the dataset
    WaterDataset dataset;
    std::vector<PollutantSample> pollutantSamples = dataset.loadPollutantSamples("pollutants.csv", 10);
    if (selectedYear == "All Years") {
        for (int year = 2020; year <= 2024; ++year) {
            std::string yearFile = "Y-" + std::to_string(year) + "-M.csv";
            try {
                WaterDataset tempDataset;
                tempDataset.loadData(yearFile);
                dataset.appendData(tempDataset.getData());
            } catch (const std::exception& e) {
                continue;
            }
        }
    } else {
        std::string newDate = "Y-" + selectedYear.toStdString() + "-M.csv";
        try {
            dataset.loadData(newDate);
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Data Error", "There is no data available to read. Please download it from - <a href='https://environment.data.gov.uk/water-quality/view/download'>this link</a>");
            return;
        }
    }

    const auto& samples = dataset.getData();
    detailedTable->setRowCount(0);  // Clear the table for filtered results

    if (samples.empty()) {
        QMessageBox::information(this, "No Results", "No data matches the selected filters.");
        return;
    }

    // Iterate through samples and apply filters
    int row = 0;
    for (const auto& sample : samples) {
        if (selectedYear != "All Years" && sample.getYear() != std::stoi(selectedYear.toStdString())) continue;
        if (selectedLocation != "All Locations" && sample.getLocation() != selectedLocation.toStdString()) continue;
        if (selectedPollutant != "All Pollutants" && sample.getPollutant() != selectedPollutant.toStdString()) continue;
        if (selectedStatus != "All Status" && sample.getPollutant() != selectedPollutant.toStdString()) continue;

        detailedTable->insertRow(row);
        detailedTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(sample.getLocation())));
        detailedTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(sample.getPollutant())));
        detailedTable->setItem(row, 2, new QTableWidgetItem(QString::number(sample.getLevel())));
        detailedTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(sample.getUnit())));
        detailedTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(sample.getSampleDate())));

            for (int j = 0; j < 10; j++) {
                std::cout << "Created WaterSample---------------------------------------- " << j << std::endl;

                // Compare pollutant name with string comparison
                if (sample.getPollutant() == pollutantSamples[j].getName()) {

                    std::cout << "Created WaterSample *********************" << j << std::endl;

                    // Convert sample level and thresholds to double
                    double sampleLevel = sample.getLevel();
                    double minThreshold = std::stod(pollutantSamples[j].getMinThreshold());
                    double maxThreshold = std::stod(pollutantSamples[j].getMaxThreshold());

                    // Calculate the interval length (range between min and max threshold)
                    double thresholdRange = maxThreshold - minThreshold;

                    // First condition: Good level (within the threshold range)
                    if (sampleLevel >= minThreshold && sampleLevel <= maxThreshold) {
                        detailedTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString("good")));
                    }
                    // Second condition: Medium level (within 20% of the interval length)
                    else if (sampleLevel >= minThreshold - 0.2 * thresholdRange && sampleLevel <= maxThreshold + 0.2 * thresholdRange) {
                        detailedTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString("medium")));
                    }
                    // Else: Bad level (outside 20% of the interval range)
                    else {
                        detailedTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString("bad")));
                    }
                }
            }

        row++;
    }
}
