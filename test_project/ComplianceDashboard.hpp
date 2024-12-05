#ifndef COMPLIANCEDASHBOARD_HPP
#define COMPLIANCEDASHBOARD_HPP

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QMovie>
#include <QDialog>
#include <QMessageBox>
#include <string>

class ComplianceDashboard : public QMainWindow {
    Q_OBJECT

public:
    ComplianceDashboard(QWidget *parent = nullptr);
    ~ComplianceDashboard();

    // Method to populate the table with data from a CSV file
    void populateTable(const std::string& filename);
    
    // Method to apply filters
    void applyFilters();

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    
    // Header
    QLabel *header;

    // Summary Cards
    QHBoxLayout *cardsLayout;
    QFrame *summaryCards[4];

    // Filters Section
    QHBoxLayout *filtersLayout;
    QComboBox *yearFilter;
    QComboBox *locationFilter;
    QComboBox *pollutantFilter;
    QComboBox *statusFilter;
    QPushButton *filterButton;

    // Main Content Area
    QHBoxLayout *contentLayout;
    QTableWidget *detailedTable;
    QTextEdit *importantInfo;

    // Footer
    QLabel *footer;

    // Method to setup UI elements
    void setupUI();
};

#endif // COMPLIANCEDASHBOARD_HPP
