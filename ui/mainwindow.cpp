#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "physics/data/data.hpp"
#include "rendering/rendersphere.hpp"

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

        {
            QVector4D sphereColor(1, 0, 0, 0.5);
            QVector4D volatileColor(0, 1, 0, 1);

            int spheresCount = 1000;
            QVector<RenderSphere> spheres(spheresCount);
            for(int count = 0; count < spheresCount; count++)
            {
                RenderSphere rs;
                rs.color = (count % 2) ? sphereColor : volatileColor;
                rs.model.setToIdentity();
                rs.model.translate(QVector3D{0, 0, static_cast<float>(count)});
                auto scale = 0.3;
                rs.model.scale(QVector3D{static_cast<float>(scale),
                                         static_cast<float>(scale),
                                         static_cast<float>(scale)});
                spheres[count] = rs;
            }

            ui->openGLWidget->setSpheres(spheres);
        }
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

