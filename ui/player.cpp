#include "player.h"
#include "ui_player.h"

#include <QPushButton>

Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);

    connect(ui->first, &QPushButton::clicked, [this]()
    {
        ui->horizontalSlider->setValue(ui->horizontalSlider->minimum());
    });

    connect(ui->previous, &QPushButton::clicked, [this]()
    {
        if (ui->horizontalSlider->value() == ui->horizontalSlider->minimum())
        {
            return;
        }
        ui->horizontalSlider->setValue(ui->horizontalSlider->value() - 1);
    });

    connect(ui->play, &QPushButton::clicked, [this]()
    {
        //
    });

    connect(ui->next, &QPushButton::clicked, [this]()
    {
        if (ui->horizontalSlider->value() == ui->horizontalSlider->maximum())
        {
            return;
        }
        ui->horizontalSlider->setValue(ui->horizontalSlider->value() + 1);
    });

    connect(ui->last, &QPushButton::clicked, [this]()
    {
        ui->horizontalSlider->setValue(ui->horizontalSlider->maximum());
    });
}

Player::~Player()
{
    delete ui;
}

void Player::setLabel(const QString &text)
{
    ui->label->setText(text);
}

void Player::setFrame(int frame)
{
    ui->horizontalSlider->setValue(frame);
}
