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

    QPushButton *button = new QPushButton("Печать графика", this);

    toolBar->addWidget(comboBox);
    toolBar->addWidget(checkBox);
    toolBar->addWidget(button);

    // центральный виджет с разделителем
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);

    // Левый виджет
    QListWidget *menuWidget = new QListWidget(splitter);
    menuWidget->addItems({"Item 1", "Item 2", "Item 3"});

    // Правый виджет
    QTextEdit *contentWidget = new QTextEdit(splitter);
    contentWidget->setText("This is the content area.\nSelect items from the left menu.");

    splitter->addWidget(menuWidget);
    splitter->addWidget(contentWidget);

    // установил центральный виджет
    setCentralWidget(splitter);

    connect(button, &QPushButton::clicked, this, &ApplicationWindow::showSettingsDialog);
}

void ApplicationWindow::showSettingsDialog()
{
    SettingsDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        // при принятии настроек
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
