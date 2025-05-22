#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H

#include <QMainWindow>
#include <QDialogButtonBox>
#include <QDialog>

#include <QFileSystemModel>
#include <QTreeView>
#include <QTableView>


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
    void on_selectionChangedSlot(const QItemSelection &selected, const QItemSelection &deselected);

private:
    QFileSystemModel *rightPartModel;
    QFileSystemModel *leftPartModel;
    QTreeView *treeView;
    QTableView *tableView;
};

#endif // APPLICATIONWINDOW_H
