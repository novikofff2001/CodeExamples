#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csv_exception.h"
#include "csv_reader.h"
#include "json_reader.h"
#include "qtexterror.h"

vector <s_passenger_cars> cars;
//
void MainWindow::ReadNPrint(AbstractReader &abs_r, string filename)
{
    QString output;
    abs_r.Open(filename);
    cars = abs_r.Read();
    output += QString::fromStdString("Your DB:\n"+abs_r.DrawTable());
    for(auto& car: cars)
        output += QString::fromStdString(abs_r.GetFormattedString(car)+'\n');
    ui->Field_Output->append(output);
}
//

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
//

MainWindow::~MainWindow()
{
    delete ui;
}
//

void MainWindow::SearchPosition()
{
    QString output;
    ui->Field_Output->clear();
    CSV csv;
    string year = ui->Find_Year->text().toStdString();
    try
    {
        if(!cars.size())
            throw CSVException("Error! DB is empty. Read from file and try again...");
        cars = csv.SortByChoice(cars, stoi(year), COLOR_GREEN);
        output += QString::fromStdString(csv.DrawTable());
        for(auto& car: cars)
            output += QString::fromStdString(csv.GetFormattedString(car)+'\n');
        ui->Field_Output->append(output);
    }
    catch(CSVException &e)
    {
        ui->Field_Output->appendRed(e.what());
    }
}
//

void MainWindow::AddPosition()
{
    QString output;
    ui->Field_Output->clear();
    CSV csv;
    //
    try
    {
        string mark = ui->Add_Mark->text().toStdString();
        int year = ui->Add_Year->text().toInt();
        e_Colors color = static_cast<e_Colors>(ui->Add_Color->currentText().toInt());
        if ( !mark.length() || year<=0 || ui->Add_Color->currentIndex()==0)
            throw CSVException("Please, input correct data and try again...");
        stringstream ss;
        ss<<year;
        cars = csv.Add(cars, mark, color, year);
        output += QString::fromStdString("Position added Successfully!");
        ui->Field_Output->append(output);
    }
    catch(CSVException &e)
    {
        ui->Field_Output->appendRed(e.what());
    }
}
//

void MainWindow::PrintDB()
{
    ui->Field_Output->clear();
    QString output;
    CSV csv;
    if(cars.size())
    {
        output += QString::fromStdString("Your DB:\n"+csv.DrawTable());
        for(auto& car: cars)
            output += QString::fromStdString(csv.GetFormattedString(car)+'\n');
    }
    else
        output += QString::fromStdString("DB is empty!");
    ui->Field_Output->append(output);
}
//

void MainWindow::DumpDB()
{
    ui->Field_Output->clear();
    QString output;
    CSV csv;
    try
    {
        csv.Write(cars, CSV_OUT);
        output += QString::fromStdString("DB saved to \n"+CSV_OUT);
        ui->Field_Output->append(output);
    }
    catch(CSVException& e)
    {
        ui->Field_Output->appendRed(e.what());
    }
}
//

void MainWindow::ReadDB()
{
    ui->Field_Output->clear();
    QString output;
    CSV csv;
    try
    {
        cars = csv.Read();
        output += QString::fromStdString("DB loaded!");
        ui->Field_Output->append(output);
    }
    catch(CSVException& e)
    {
        ui->Field_Output->appendRed(e.what());
    }
}
//

void MainWindow::ChooseDBFile()
{
    ui->Field_Output->clear();
    try
    {
        QFileDialog q;
        QString name = q.getOpenFileName();
        string extension = name.toStdString();
        extension = extension.substr(extension.find('.'));
        if(extension == ".csv")
        {
            CSV csv;
            ReadNPrint(csv, name.toStdString());
        }
        else if(extension == ".json")
        {
            JSON json;
            ReadNPrint(json, name.toStdString());
        }
        else
            throw CSVException("Incorrect file extension! Choose between '.csv' and '.json'");
    }
    catch(CSVException& e)
    {
        ui->Field_Output->appendRed(e.what());
    }
    catch(std::out_of_range& oor){};
}
//


