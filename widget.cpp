#include "widget.h"
#include "ui_widget.h"
#include <QStringList>
#include <chrono>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->DataStructure->setVisible(false);
    ui->progressBar->setRange(0,187);
    ui->progressBar->setVisible(false);
    ui->ResetButton->hide();
    ui->SearchButton->setVisible(false);
    ui->SearchBar->setVisible(false);
    ui->SearchBar->setClearButtonEnabled(true);
    ui->SearchBar->setPlaceholderText("Search Stock Database...");
    connect(ui->MapButton, SIGNAL(clicked(bool)), this, SLOT(onMapButtonClicked()));
    connect(ui->SearchButton, SIGNAL(clicked(bool)), this, SLOT(onSearchButtonClicked()));
    connect(ui->SearchBar,SIGNAL(returnPressed()), this, SLOT(onSearchButtonClicked()));
    connect(ui->AVLButton, SIGNAL(clicked(bool)), this, SLOT(onAVLButtonClicked()));
    connect(ui->ResetButton, SIGNAL(clicked(bool)), this, SLOT(onResetButtonClicked()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::onMapButtonClicked()
{
    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);
    QFile f("C:/Test/StockNames.csv");
    QStringList dataList;
    if(!f.open(QFile::ReadOnly|QFile::Text)) {
           qDebug() << "File not there";
    }
    QTextStream stream(&f);
    int stockCount = 0;
    int progressCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    while (!f.atEnd()) {
        dataList.clear();
        QString line = stream.readLine();
        dataList = line.split(",");
        Stock* newStock = new Stock(dataList[0].toUtf8().constData(),dataList[1].toDouble(),dataList[2].toDouble(),dataList[3].toDouble(),dataList[4].toDouble(),dataList[5].toDouble(),dataList[6].toDouble());
        stockContainer.insert(newStock->name,newStock);
        stockCount++;
        if (stockCount/1000 != progressCount) {
            progressCount++;
            updateProgressBar(progressCount);
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> s_double = stop - start;
    mapLoadTime = s_double.count();
    ui->TotalLoadTime->display(mapLoadTime);
    ui->LoadUnits->setText("seconds");
    mapStructure = true;
    ui->DataStructure->setVisible(true);
    ui->DataStructure->setText("Map");
    disableButtons();
    ui->ResetButton->setText("Switch to AVL Tree");
    ui->ResetButton->show();
    ui->progressBar->setVisible(false);
    ui->SearchBar->setVisible(true);
    ui->SearchButton->setVisible(true);
    mapExists = true;

}

void Widget::onAVLButtonClicked()
{

    ui->progressBar->setVisible(true);
    ui->progressBar->setValue(0);
    QFile f("C:/Test/StockNames.csv");
    QStringList dataList;
    if(!f.open(QFile::ReadOnly|QFile::Text)) {
           qDebug() << "File not there";
    }
    QTextStream stream(&f);
    int stockCount = 0;
    int progressCount = 0;
    auto start = std::chrono::high_resolution_clock::now();

    while (!f.atEnd()) {
        dataList.clear();
        QString line = stream.readLine();
        dataList = line.split(",");
        Stock* newStock = new Stock(dataList[0].toUtf8().constData(),dataList[1].toDouble(),dataList[2].toDouble(),dataList[3].toDouble(),dataList[4].toDouble(),dataList[5].toDouble(),dataList[6].toDouble());
        stockTree.rootNode = stockTree.InsertStock(stockTree.rootNode,newStock);
        stockCount++;
        if (stockCount/1000 != progressCount) {
            progressCount++;
            updateProgressBar(progressCount);
        }
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> s_double = stop - start;
    treeLoadTime = s_double.count();
    ui->TotalLoadTime->display(treeLoadTime);
    ui->LoadUnits->setText("seconds");
    disableButtons();
    ui->DataStructure->setText("AVL Tree");
    ui->DataStructure->setVisible(true);
    ui->ResetButton->setText("Switch to Map");
    ui->ResetButton->show();
    ui->progressBar->setVisible(false);
    ui->SearchBar->setVisible(true);
    ui->SearchButton->setVisible(true);
    avlStructure = true;
    avlExists = true;
}

void Widget::onSearchButtonClicked()
{
    std::string input = ui->SearchBar->text().toStdString();
    //Search through valid data structure.
    if (mapStructure == true) {
        for (unsigned int i = 0; i < input.size(); i++) {
            input[i] = toupper(input[i]);
        }
        auto start = std::chrono::high_resolution_clock::now();
        Stock* foundStock = stockContainer.find(input);
        auto stop = std::chrono::high_resolution_clock::now();
        if (foundStock != nullptr) {
            ui->Current->setText("$" + QString::number(foundStock->currentPrice));
            ui->History->setText("$" + QString::number(foundStock->historicPrice));
            ui->Average->setText("$" + QString::number(foundStock->yearAvg));
            ui->YearHigh->setText("$" + QString::number(foundStock->yearHigh));
            ui->YearLow->setText("$" + QString::number(foundStock->yearLow));
            ui->Return->setText(QString::number(foundStock->yearReturn) + "%");
            ui->StockName->setText(QString::fromStdString(foundStock->name));
        }

        else {
            ui->StockName->setText("Try another stock.");
            ui->Current->setText("");
            ui->History->setText("");
            ui->Average->setText("");
            ui->YearHigh->setText("");
            ui->YearLow->setText("");
            ui->Return->setText("");
        }

        std::chrono::duration<double, std::nano> ns_double = stop - start;
        ui->SearchTime->display(ns_double.count());
        ui->SearchUnits->setText("nanoseconds");

    }
    else if(avlStructure == true) {
        for (unsigned int i = 0; i < input.size(); i++) {
            input[i] = toupper(input[i]);
        }
        auto start = std::chrono::high_resolution_clock::now();
        TreeNode* foundStock = stockTree.SearchStock(stockTree.rootNode, input);
        auto stop = std::chrono::high_resolution_clock::now();
        if (foundStock != nullptr) {
            ui->Current->setText("$" + QString::number(foundStock->data->currentPrice));
            ui->History->setText("$" + QString::number(foundStock->data->historicPrice));
            ui->Average->setText("$" + QString::number(foundStock->data->yearAvg));
            ui->YearHigh->setText("$" + QString::number(foundStock->data->yearHigh));
            ui->YearLow->setText("$" + QString::number(foundStock->data->yearLow));
            ui->Return->setText(QString::number(foundStock->data->yearReturn) + "%");
            ui->StockName->setText(QString::fromStdString(foundStock->data->name));
        }

        else {
            ui->StockName->setText("Try another stock.");
            ui->Current->setText("");
            ui->History->setText("");
            ui->Average->setText("");
            ui->YearHigh->setText("");
            ui->YearLow->setText("");
            ui->Return->setText("");
        }

        std::chrono::duration<double, std::nano> ms_double = stop - start;
        ui->SearchTime->display(ms_double.count());
        ui->SearchUnits->setText("nanoseconds");

    }
}

void Widget::disableButtons()
{
    ui->MapButton->setVisible(false);
    ui->AVLButton->setVisible(false);
}

void Widget::onResetButtonClicked()
{
    if (mapStructure == true && avlExists == false) {
        mapStructure = false;
        Widget::onAVLButtonClicked();
        ui->ResetButton->setText("Switch to Map");
    }

    else if (avlStructure == true && mapExists == false) {
        avlStructure = false;
        Widget::onMapButtonClicked();
        ui->ResetButton->setText("Switch to AVL Tree");
    }
    else if (mapStructure == true && avlExists == true) {
        mapStructure = false;
        avlStructure = true;
        ui->TotalLoadTime->display(treeLoadTime);
        ui->DataStructure->setText("AVL Tree");
        ui->ResetButton->setText("Switch to Map");
    }
    else if (avlStructure == true && mapExists == true) {
        avlStructure = false;
        mapStructure = true;
        ui->TotalLoadTime->display(mapLoadTime);
        ui->DataStructure->setText("Map");
        ui->ResetButton->setText("Switch to AVL Tree");
    }

}

void Widget::updateProgressBar(int value)
{
    ui->progressBar->setValue(value);
}

