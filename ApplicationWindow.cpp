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

namespace {

constexpr int ApplicationWidthDefaultValue = 1222;
constexpr int ApplicationHeightDefaultValue = 777;

}

ApplicationWindow::ApplicationWindow() {
    _setDefaultViewConfiguration();

    QToolBar *toolBar = new QToolBar("Main Toolbar", this);
    addToolBar(toolBar);

    //элементы на панели инструментов
    QComboBox *comboBox = new QComboBox(this);
    comboBox->addItems({"Option 1", "Option 2", "Option 3"});

    QCheckBox *checkBox = new QCheckBox("Check Option", this);

    QPushButton *button = new QPushButton("Action", this);

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
