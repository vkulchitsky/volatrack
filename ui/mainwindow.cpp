#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "physics/data/data.hpp"
#include "rendering/rendersphere.hpp"
#include "rendering/rendercontroller.hpp"

#include <random>

#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_fileDialog = new QFileDialog(nullptr, {}, QDir::homePath(), "*.json");
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

        RenderController rc;

        ui->openGLWidget->setSpheres(rc.spheresFromData(m_controller
                                                        .getData(0)));
    });

    connect(ui->player, &Player::slidTo, [this](const int value)
    {
        if (m_fileDialog->selectedFiles().size())
        {
            ui->player->setLabel(m_fileDialog->selectedFiles()[value]);
            RenderController rc;

            ui->openGLWidget->setSpheres(rc.spheresFromData(m_controller
                                                            .getData(value)));
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

