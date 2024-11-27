#include "ComplianceDashboard.hpp"

ComplianceDashboard::ComplianceDashboard(QWidget *parent) : QMainWindow(parent) {
    setupUI();
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
    detailedTable = new QTableWidget(10, 3); // Example size
    detailedTable->setHorizontalHeaderLabels({"Pollutant", "Level", "Compliance"});
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
