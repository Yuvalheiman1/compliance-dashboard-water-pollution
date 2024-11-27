#include "ComplianceDashboard.hpp"
#include "dataset.hpp"
#include "WaterSample.hpp"

ComplianceDashboard::ComplianceDashboard(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    populateTable("Y-2024.csv");
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
    for (int i = 0; i < 4; ++i) {
        summaryCards[i] = new QFrame();
        summaryCards[i]->setFrameShape(QFrame::StyledPanel);
        summaryCards[i]->setStyleSheet("background-color: #f2f2f2; border: 1px solid #d9d9d9; padding: 10px;");
        QVBoxLayout *cardLayout = new QVBoxLayout();
        QLabel *cardTitle = new QLabel(QString("Summary Card %1").arg(i + 1));
        cardTitle->setAlignment(Qt::AlignCenter);
        cardLayout->addWidget(cardTitle);
        summaryCards[i]->setLayout(cardLayout);
        cardsLayout->addWidget(summaryCards[i]);
    }
    mainLayout->addLayout(cardsLayout);

    // Filters Section
    filtersLayout = new QHBoxLayout();
    yearFilter = new QComboBox();
    yearFilter->addItems({"2020", "2021", "2022", "2023", "2024"});
    locationFilter = new QComboBox();
    locationFilter->addItems({"All Locations", "London", "Manchester", "Yorkshire"});
    pollutantFilter = new QComboBox();
    pollutantFilter->addItems({"All Pollutants", "Ammonia", "Lead", "Zinc"});
    statusFilter = new QComboBox();
    statusFilter->addItems({"All Statuses", "Compliant", "Non-Compliant"});
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
    detailedTable = new QTableWidget(10, 5); // Example size
    detailedTable->setHorizontalHeaderLabels({"Location", "Pollutant", "Level", "Unit", "Compliance"});
    contentLayout->addWidget(detailedTable);

    // Summary of Important Info
    importantInfo = new QTextEdit();
    importantInfo->setPlaceholderText("Summary of important information...");
    importantInfo->setReadOnly(true);
    contentLayout->addWidget(importantInfo);

    mainLayout->addLayout(contentLayout);

    // Footer
    footer = new QLabel("Data provided by UK Environmental Agency.");
    footer->setAlignment(Qt::AlignCenter);
    footer->setStyleSheet("font-size: 12px; color: gray;");
    mainLayout->addWidget(footer);

    // Set Layout
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    resize(900, 600);
}

void ComplianceDashboard::populateTable(const std::string& filename) {
    WaterDataset dataset;
    dataset.loadData(filename);

    const auto& samples = dataset.getData();
    detailedTable->setRowCount(samples.size());
    detailedTable->setColumnCount(5); // Number of columns
    detailedTable->setHorizontalHeaderLabels({"Location", "Pollutant", "Level", "Unit", "Compliance"});

    for (size_t i = 0; i < samples.size(); ++i) {
        const auto& sample = samples[i];
        detailedTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(sample.getLocation())));
        detailedTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(sample.getPollutant())));
        detailedTable->setItem(i, 2, new QTableWidgetItem(QString::number(sample.getLevel())));
        detailedTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(sample.getUnit())));
        detailedTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(sample.getComplianceStatus())));
    }
}
