#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include "IChartView.h"

#include <QMainWindow>
#include <QFileSystemModel>
#include <QTableView>
#include <QtCharts/QChartView>

class ApplicationWindow : public QMainWindow, public IChartView {
    Q_OBJECT
public:
    static const QStringList filters;
public:
    ApplicationWindow();

    void displayChart(QtCharts::QChart* chart) override;
    void cleanChart() override;

private:
    void _setCenterAnchor();
    void _setDefaultViewConfiguration();

signals:
    void fileSelected(const QString& filePath);
    void chartsTypeModified(); //TODO

private slots:
    void _showFileDialog();
    void _selectionChanged(const QItemSelection &selected);

private:
    QFileSystemModel *_model = nullptr;
    QTableView *_tableView = nullptr;
    QtCharts::QChartView *_chartView = nullptr;
};

#endif // APPLICATIONWINDOW_H
