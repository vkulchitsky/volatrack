#include "player.h"
#include "ui_player.h"

#include <QPushButton>
#include <QStyle>
#include <QCommonStyle>

Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);

    setLabel({});

    QCommonStyle style;
    ui->first->setIcon(style.standardIcon(QStyle::SP_MediaSkipBackward));
    ui->previous->setIcon(style.standardIcon(QStyle::SP_MediaSeekBackward));
    ui->play->setIcon(style.standardIcon(QStyle::SP_MediaPlay));
    ui->next->setIcon(style.standardIcon(QStyle::SP_MediaSeekForward));
    ui->last->setIcon(style.standardIcon(QStyle::SP_MediaSkipForward));

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

    connect(ui->horizontalSlider, &QSlider::valueChanged, [this]
            (const int value)
    {
        slidTo(value);
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

void Player::setMinimum(int min)
{
    ui->horizontalSlider->setMinimum(min);
}

void Player::setMaximum(int max)
{
    ui->horizontalSlider->setMaximum(max);
}
