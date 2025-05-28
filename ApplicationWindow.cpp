#include "ApplicationWindow.h"

#include <QScreen>
#include <QGuiApplication>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidgetAction>
#include <QCheckBox>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QToolBar>
#include <QSplitter>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QDebug>
#include <QDir>
#include <QSplitter>
#include <QListView>
#include <QTreeView>
#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QTableView>
#include <QHeaderView>
#include <QStatusBar>
#include <QFileDialog>
#include <QSplitter>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QAbstractBarSeries>
#include <QtCharts/QPercentBarSeries>
#include <QtCharts/QStackedBarSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtCore/QTime>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QChartGlobal>

#include "LinePrinter.h"

namespace {
constexpr int ApplicationWidthDefaultValue = 1222;
constexpr int ApplicationHeightDefaultValue = 777;

constexpr double TreeViewWitdthCoefDefaultValue = 2.4;
constexpr double ChartViewWitdthCoefDefaultValue = 1.6;
}

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Charts Configuration");
    setModal(true);
    resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Setting 1:", this));
    QLineEdit *setting1 = new QLineEdit(this);
    layout->addWidget(setting1);

    // OK/Cancel
    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

ApplicationWindow::ApplicationWindow(QList<GraphData>* data) {
    _setDefaultViewConfiguration();

    QToolBar *toolBar = new QToolBar("Main Toolbar", this);
    addToolBar(toolBar);

    //элементы на панели инструментов
    QComboBox *comboBox = new QComboBox(this);
    comboBox->addItems({"LineSeries", "PieChart"});

    QCheckBox *checkBox = new QCheckBox("Check Option", this);

    QPushButton *printGraphButton = new QPushButton("Печать графика", this);
    QPushButton *chartConfigurationButton = new QPushButton("Конфигурация чартов", this);
    QPushButton *chooseDirecctoryButton = new QPushButton("Выбрать путь", this);
    QWidget *separator = new QWidget(this);
    separator->setSizePolicy(
        QSizePolicy::Expanding, QSizePolicy::Preferred);

    toolBar->addWidget(chooseDirecctoryButton);
    toolBar->addWidget(separator);
    toolBar->addWidget(comboBox);
    toolBar->addWidget(checkBox);
    toolBar->addWidget(printGraphButton);
    toolBar->addWidget(chartConfigurationButton);

    // центральный виджет с разделителем
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setChildrenCollapsible(false);
    splitter->setHandleWidth(5);

    QString homePath = QDir::homePath();
    model = new QFileSystemModel(this);
    model->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    QStringList filters {"*.json", "*.sqlite"};
    model->setNameFilters(filters);
    model->setNameFilterDisables(false);

    tableView = new QTableView;
    tableView->setModel(model);
    tableView->setRootIndex(model->setRootPath(homePath));

    splitter->addWidget(tableView);

    // LinePrinter printer;
    // QChart* chart = printer.get(*data);
    // chartView = new QChartView(chart);

    splitter->addWidget(chartView);

    QList<int> sizes;
    sizes << width() / TreeViewWitdthCoefDefaultValue << width() / ChartViewWitdthCoefDefaultValue;
    splitter->setSizes(sizes);

    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    setCentralWidget(splitter);

    QItemSelectionModel *selectionModel = tableView->selectionModel();

    connect(chooseDirecctoryButton, &QPushButton::clicked, this, &ApplicationWindow::_showFileDialog);
    connect(chartConfigurationButton, &QPushButton::clicked, this, &ApplicationWindow::showSettingsDialog);

    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &ApplicationWindow::_selectionChangedSlot);
}

void ApplicationWindow::showSettingsDialog()
{
    SettingsDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "принято";
    }
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

    model->setRootPath(dirPath);
    tableView->setRootIndex(model->index(dirPath));
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

void ApplicationWindow::_selectionChangedSlot(const QItemSelection &selected) {
    QModelIndexList indexs =  selected.indexes();

    QString filePath = "";

    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = model->filePath(ix);
    }

    qDebug()<<filePath;
}
