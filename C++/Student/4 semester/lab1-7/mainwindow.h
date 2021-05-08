#ifndef ABSTRACT_READER_H
#include "abstract_reader.h"
#endif

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QColor error_text_color;
    QColor normal_text_color;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void SearchPosition();
    void AddPosition();
    void ReadDB();
    void DumpDB();
    void PrintDB();
    void ChooseDBFile();
    void ReadNPrint(AbstractReader &abs_r, string filename);
private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
