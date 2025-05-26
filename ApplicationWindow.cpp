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

namespace {
constexpr int ApplicationWidthDefaultValue = 1222;
constexpr int ApplicationHeightDefaultValue = 777;
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

ApplicationWindow::ApplicationWindow() {
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


    QString homePath = QDir::homePath();
    model = new QFileSystemModel(this);
    // rightPartModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    //model->setRootPath("/Users/dmitriy/Downloads");
    //Показатьв виде "дерева". Пользуемся готовым видом(TreeView):

    tableView = new QTableView;
    tableView->setModel(model);
    tableView->setRootIndex(model->setRootPath(homePath));

    // Правый виджет
    QTextEdit *contentWidget = new QTextEdit(splitter);
    contentWidget->setText("This is the content area.\nSelect items from the left menu.");

    splitter->addWidget(tableView);
    splitter->addWidget(contentWidget);

    // установил центральный виджет
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
