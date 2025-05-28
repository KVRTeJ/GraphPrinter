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

#include "SqlLiteParser.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = nullptr);
};

class ApplicationWindow : public QMainWindow {
    Q_OBJECT
public:
    ApplicationWindow(QList<GraphData>* data);

private:
    void _setCenterAnchor();
    void _setDefaultViewConfiguration();

private slots:
    void showSettingsDialog();
    void _showFileDialog();
    void _selectionChangedSlot(const QItemSelection &selected);

private:
    QFileSystemModel *model;
    QTableView *tableView;
    QtCharts::QChartView *chartView = nullptr;
};

#endif // APPLICATIONWINDOW_H
