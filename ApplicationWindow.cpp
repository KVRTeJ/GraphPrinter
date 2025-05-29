#include "ApplicationWindow.h"

#include "DependencyInversion.h"

#include <QScreen>
#include <QGuiApplication>
#include <QComboBox>
#include <QPushButton>
#include <QCheckBox>
#include <QToolBar>
#include <QSplitter>
#include <QFileSystemModel>
#include <QTableView>
#include <QItemSelectionModel>
#include <QFileDialog>
#include <QDir>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QDebug>
#include <QStatusBar>

const QStringList ApplicationWindow::FILE_MODEL_FILTERS {"*.json", "*.sqlite"};

namespace {
constexpr int ApplicationWidthDefaultValue = 1222;
constexpr int ApplicationHeightDefaultValue = 777;

constexpr double TreeViewWitdthCoefDefaultValue = 2.4;
constexpr double ChartViewWitdthCoefDefaultValue = 1.6;
}

ApplicationWindow::ApplicationWindow() {
    _setDefaultViewConfiguration();

    QToolBar *toolBar = new QToolBar("Main Toolbar", this);
    addToolBar(toolBar);

    statusBar()->showMessage("Ready", 2000);

    _comboBox = new QComboBox(this);
    _comboBox->addItems({"Line chart",
                        "Area chart",
                        "Spline chart",
                        "Scatter chart"});

    QCheckBox *checkBox = new QCheckBox("Ч/Б", this);
    QPushButton *printGraphButton = new QPushButton("Печать графика", this);
    QPushButton *chooseDirecctoryButton = new QPushButton("Выбрать путь", this);
    QWidget *separator = new QWidget(this);
    separator->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    toolBar->addWidget(chooseDirecctoryButton);
    toolBar->addWidget(separator);
    toolBar->addWidget(_comboBox);
    toolBar->addSeparator();
    toolBar->addWidget(checkBox);
    toolBar->addSeparator();
    toolBar->addWidget(printGraphButton);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setChildrenCollapsible(false);
    splitter->setHandleWidth(5);

    QString homePath = QDir::homePath();
    _model = new QFileSystemModel(this);
    _model->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    _model->setNameFilters(FILE_MODEL_FILTERS);
    _model->setNameFilterDisables(false);

    _tableView = new QTableView;
    _tableView->setModel(_model);
    _tableView->setRootIndex(_model->setRootPath(homePath));
    QItemSelectionModel *selectionModel = _tableView->selectionModel();

    splitter->addWidget(_tableView);

    _chart = new QtCharts::QChart();
    _chartView = new QtCharts::QChartView(_chart, this);

    splitter->addWidget(_chartView);

    QList<int> sizes;
    sizes << width() / TreeViewWitdthCoefDefaultValue
          << width() / ChartViewWitdthCoefDefaultValue;
    splitter->setSizes(sizes);

    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    setCentralWidget(splitter);

    connect(chooseDirecctoryButton, &QPushButton::clicked,
            this, &ApplicationWindow::_showFileDialog);
    connect(checkBox, &QCheckBox::toggled,
            this, &ApplicationWindow::_bwToggled);
    connect(printGraphButton, &QPushButton::clicked,
            this, &ApplicationWindow::_printButtonClicked);

    connect(selectionModel, &QItemSelectionModel::selectionChanged,
            this, &ApplicationWindow::_selectionChanged);

    connect(_comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &ApplicationWindow::_chartTypeChanged);
}

ApplicationWindow::~ApplicationWindow() {
    delete _chart;
}

void ApplicationWindow::displayChart(QtCharts::QChart* chart) {
    if(!chart)
        return;

    _chartView->setChart(chart);

    if (_chart) {
        delete _chart;
        _chart = nullptr;
    }

    _chart = chart;

    showStatus("График успешно обновлен");
}

void ApplicationWindow::cleanChart() {
    if (!_chart)
        return;

    QtCharts::QChart* empty = new QtCharts::QChart();
    _chartView->setChart(empty);
    delete _chart;
    _chart = empty;
}

void ApplicationWindow::_showFileDialog() {
    QFileDialog dlg(this);
    dlg.setFileMode(QFileDialog::Directory);
    dlg.setOption(QFileDialog::ShowDirsOnly, true);

    if (dlg.exec() == QDialog::Rejected) {
        return;
    }

    const QStringList selected = dlg.selectedFiles();
    const QString dirPath = selected.first();
    if (dirPath.isEmpty()) {
        return;
    }

    _model->setRootPath(dirPath);
    _tableView->setRootIndex(_model->index(dirPath));
}

void ApplicationWindow::_setCenterAnchor() {
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();

    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;

    move(x, y);
}

void ApplicationWindow::_setDefaultViewConfiguration() {
    resize(ApplicationWidthDefaultValue,
           ApplicationHeightDefaultValue);
    _setCenterAnchor();

    setWindowTitle("Graph printer");
}

void ApplicationWindow::_selectionChanged(const QItemSelection &selected) {
    QModelIndexList indexs =  selected.indexes();

    QString filePath = "";

    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = _model->filePath(ix);
    }

    if(filePath != "") {
        emit fileSelected(filePath);
    }
}

void ApplicationWindow::_chartTypeChanged(int index) {
    QString chartType = _comboBox->itemText(index);
    if (chartType == "Line chart") {
        DIConfiguration::switchToLineChart();
    } else if (chartType == "Area chart") {
        DIConfiguration::switchToAreaChart();
    } else if (chartType == "Spline chart") {
        DIConfiguration::switchToSplineChart();
    } else if (chartType == "Scatter chart") {
        DIConfiguration::switchToScatterChart();
    } else {
        qDebug() << "Unknown chart type selected";
        return;
    }

    emit chartsTypeChanged();
}
