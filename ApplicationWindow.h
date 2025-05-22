#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>

class ApplicationWindow : public QMainWindow {
public:
    ApplicationWindow();

private:
    void _setCenterAnchor();
    void _setDefaultViewConfiguration();

private:
    QToolBar *_toolbar {nullptr};

};

#endif // APPLICATIONWINDOW_H
