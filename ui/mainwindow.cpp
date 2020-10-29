#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "physics/data/data.hpp"
#include "rendering/rendersphere.hpp"

#include <random>

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

    connect(ui->player, &Player::randomness, [this]()
    {
        std::default_random_engine gen;
        std::uniform_real_distribution<double> distColor(0.3, 2.0);
        std::uniform_real_distribution<double> distPos(-5.0, 5.0);
        std::uniform_real_distribution<double> distScale(0.1, 0.5);
        std::uniform_real_distribution<double> distCout(1000, 1000);

        // test
        int spheresCount = distCout(gen);
        QVector<RenderSphere> spheres(spheresCount);
        for(int count = 0; count < spheresCount; count++)
        {
            RenderSphere rs;
            rs.color = QVector4D{static_cast<float>(distColor(gen)),
                    static_cast<float>(distColor(gen)),
                    static_cast<float>(distColor(gen)),
                    static_cast<float>(distColor(gen))};
            rs.model.setToIdentity();
            rs.model.translate(QVector3D{static_cast<float>(distPos(gen)),
                                         static_cast<float>(distPos(gen)),
                                         static_cast<float>(distPos(gen))});
            auto scale = distScale(gen);
            rs.model.scale(QVector3D{static_cast<float>(scale),
                                     static_cast<float>(scale),
                                     static_cast<float>(scale)});
            spheres[count] = rs;
        }

        ui->openGLWidget->setSpheres(spheres);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

