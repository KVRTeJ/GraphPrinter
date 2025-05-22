#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>
#include <QDialogButtonBox>
#include <QDialog>

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent = nullptr);
};

class ApplicationWindow : public QMainWindow {
    Q_OBJECT
public:
    ApplicationWindow();

private:
    void _setCenterAnchor();
    void _setDefaultViewConfiguration();

private slots:
    void showSettingsDialog();

private:
};

#endif // APPLICATIONWINDOW_H
