#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_fileDialog = new QFileDialog(nullptr, {}, "../../Volatrack/io", "*.json");
    m_fileDialog->setFileMode(QFileDialog::FileMode::ExistingFiles);

    ui->player->setMinimum(0);

    connect(ui->actionSelect_files, &QAction::triggered, [this]()
    {
        m_fileDialog->show();
    });

    connect(m_fileDialog, &QFileDialog::filesSelected, [this]()
    {
        ui->player->setMaximum(m_fileDialog->selectedFiles().size() - 1);

        ui->player->setLabel(m_fileDialog->selectedFiles()[0]);
        ui->player->setFrame(0);
        m_controller.setFiles(m_fileDialog->selectedFiles());
    });

    connect(ui->player, &Player::slidTo, [this](const int value)
    {
        if (m_fileDialog->selectedFiles().size())
        {
            ui->player->setLabel(m_fileDialog->selectedFiles()[value]);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

