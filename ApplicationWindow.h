#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>
#include <QDialogButtonBox>
#include <QDialog>

#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>
#include <QtCharts/QChartGlobal>
#include <QtCharts/qchartview.h>

#include "DataModel.h"

class ApplicationWindow : public QMainWindow {
    Q_OBJECT
public:
    ApplicationWindow();

private:
    void _setCenterAnchor();
    void _setDefaultViewConfiguration();

private slots:
    void _showFileDialog();
    void _selectionChangedSlot(const QItemSelection &selected);

private:
    QFileSystemModel *model = nullptr;
    QTableView *tableView = nullptr;
    QtCharts::QChartView *chartView = nullptr;
};

#endif // APPLICATIONWINDOW_H
