#include "player.h"
#include "ui_player.h"

#include <QPushButton>
#include <QStyle>
#include <QCommonStyle>
#include <QTimer>

Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player),
    m_isPlaying(false)
{
    ui->setupUi(this);

    setLabel({});

    QCommonStyle style;
    ui->first->setIcon(style.standardIcon(QStyle::SP_MediaSkipBackward));
    ui->previous->setIcon(style.standardIcon(QStyle::SP_MediaSeekBackward));
    ui->play->setIcon(style.standardIcon(QStyle::SP_MediaPlay));
    ui->next->setIcon(style.standardIcon(QStyle::SP_MediaSeekForward));
    ui->last->setIcon(style.standardIcon(QStyle::SP_MediaSkipForward));

    ui->horizontalSlider->setMaximum(ui->horizontalSlider->minimum());

    m_playTimer = new QTimer;

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
        m_isPlaying ? pause() : play();
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

    connect(m_playTimer, &QTimer::timeout, [this]()
    {
        if (!m_isPlaying) return;

        if (ui->horizontalSlider->value() == ui->horizontalSlider->maximum())
        {
            pause();
            return;
        }
        ui->horizontalSlider->setValue(ui->horizontalSlider->value() + 1);

        playToNext();
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

void Player::play()
{
    QCommonStyle style;
    ui->play->setIcon(style.standardIcon(QStyle::SP_MediaPause));

    ui->first->setEnabled(false);
    ui->previous->setEnabled(false);
    ui->next->setEnabled(false);
    ui->last->setEnabled(false);

    m_isPlaying = true;

    playToNext();
}

void Player::pause()
{
    QCommonStyle style;
    ui->play->setIcon(style.standardIcon(QStyle::SP_MediaPlay));

    ui->first->setEnabled(true);
    ui->previous->setEnabled(true);
    ui->next->setEnabled(true);
    ui->last->setEnabled(true);

    m_isPlaying = false;
}

void Player::playToNext()
{
    const int slideLength = 100; // milliseconds

    m_playTimer->start(slideLength);
}
