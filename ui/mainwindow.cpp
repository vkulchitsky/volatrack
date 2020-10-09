#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_fileDialog = new QFileDialog(nullptr, {}, "../../Volatrack/io", "*.json");

//    connect(ui->pushButton, &QPushButton::clicked, [this]()
//    {
//        m_fileDialog->show();
//    });

    connect(m_fileDialog, &QFileDialog::filesSelected, [this]()
    {
        ui->player->setLabel(m_fileDialog->selectedFiles()[0]);
        ui->player->setFrame(0);
        m_controller.setFiles(m_fileDialog->selectedFiles());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

