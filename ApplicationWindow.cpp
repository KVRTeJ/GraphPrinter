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

    toolBar->addWidget(comboBox);
    toolBar->addWidget(checkBox);
    toolBar->addWidget(printGraphButton);
    toolBar->addWidget(chartConfigurationButton);

    // центральный виджет с разделителем
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);


    QString homePath = QDir::homePath();
    // Определим  файловой системы:
    leftPartModel =  new QFileSystemModel(this);
    leftPartModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    leftPartModel->setRootPath(homePath);

    rightPartModel = new QFileSystemModel(this);
    rightPartModel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    rightPartModel->setRootPath("/Users/dmitriy/Downloads");

    //Показатьв виде "дерева". Пользуемся готовым видом(TreeView):
    treeView = new QTreeView();
    // Устанавливаем модель данных для отображения
    treeView->setModel(leftPartModel);
    //Раскрываем все папки первого уровня
    treeView->expandAll();
    // Создаем объект "сплиттер(разделитель)"

    tableView = new QTableView;
    tableView->setModel(rightPartModel);
    QItemSelectionModel *selectionModel = treeView->selectionModel();
    treeView->header()->resizeSection(0, 200);

    // Правый виджет
    QTextEdit *contentWidget = new QTextEdit(splitter);
    contentWidget->setText("This is the content area.\nSelect items from the left menu.");

    splitter->addWidget(tableView);
    splitter->addWidget(treeView);
    splitter->addWidget(contentWidget);

    // установил центральный виджет
    setCentralWidget(splitter);

    connect(chartConfigurationButton, &QPushButton::clicked, this, &ApplicationWindow::showSettingsDialog);
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &ApplicationWindow::on_selectionChangedSlot);
    QItemSelection toggleSelection;
    //Объявили модельный индекс topLeft
    QModelIndex topLeft;
    //Получили индекс из модели
    topLeft = leftPartModel->index(homePath);
    toggleSelection.select(topLeft, topLeft);
    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);
}

void ApplicationWindow::showSettingsDialog()
{
    SettingsDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        qDebug() << "принято";
    }
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

void ApplicationWindow::on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected)
{
    //Q_UNUSED(selected);
    Q_UNUSED(deselected);

    QModelIndex index = treeView->selectionModel()->currentIndex();

    QModelIndexList indexs =  selected.indexes();

    QString filePath = "";

    // Размещаем информацию в statusbar относительно выделенного модельного индекса
    /*
     * Смотрим, сколько индексов было выделено.
     * В нашем случае выделяем только один, следовательно всегда берем только первый.
    */
    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = leftPartModel->filePath(ix);
        this->statusBar()->showMessage("Выбранный путь : " + leftPartModel->filePath(indexs.constFirst()));
    }

    /*
     * Получив выбранные данные из левой части filePath(путь к папке/файлу).
     * Для представления в правой части устанваливаем корневой индекс относительно filePath.
     * Табличное представление отображает только файлы, находящиеся в filePath(папки не отображает)
     */
    tableView->setRootIndex(rightPartModel->setRootPath(filePath));
    qDebug() <<filePath;
}
