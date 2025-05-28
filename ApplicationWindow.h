#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include "IChartView.h"

#include <QMainWindow>
#include <QFileSystemModel>
#include <QTableView>
#include <QtCharts/QChartView>
#include <QtGui/qpdfwriter.h>
#include <QFileDialog>

class ApplicationWindow : public QMainWindow, public IChartView {
    Q_OBJECT
public:
    static const QStringList FILE_MODEL_FILTERS;

public:
    ApplicationWindow();

    void displayChart(QtCharts::QChart* chart) override;
    void cleanChart() override;

signals:
    void fileSelected(const QString& filePath);
    void recreateChart();
    void chartsTypeModified(); //TODO

private slots:
    void _showFileDialog();
    void _selectionChanged(const QItemSelection &selected);
    void _bwToggled(bool checked) {
        if(!checked)
            emit recreateChart();

        _chartView->chart()->setTheme(QtCharts::QChart::ChartThemeHighContrast);
        if (auto *xAxis = _chartView->chart()->axes(Qt::Horizontal).value(0)) {
            xAxis->setShadesVisible(false);
        }
        if (auto *yAxis = _chartView->chart()->axes(Qt::Vertical).value(0)) {
            yAxis->setShadesVisible(false);
        }
    }
    void _printButtonClicked()
    {
        QString filePath = QFileDialog::getSaveFileName(this, "Сохранить график", "", "PDF (*.pdf)");
        if (!filePath.isEmpty())
        {
            QPdfWriter pdfWriter(filePath);
            QPainter painter(&pdfWriter);
            _chartView->render(&painter);
        }
    }

private:
    void _setCenterAnchor();
    void _setDefaultViewConfiguration();


private:
    QFileSystemModel *_model = nullptr;
    QTableView *_tableView = nullptr;
    QtCharts::QChartView *_chartView = nullptr;
};

#endif // APPLICATIONWINDOW_H
