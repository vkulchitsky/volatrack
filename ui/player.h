#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>

namespace Ui {
class Player;
}

class Player : public QWidget
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = nullptr);
    ~Player();

    void setLabel(const QString& text);
    void setFrame(int frame);

private:
    Ui::Player *ui;
};

#endif // PLAYER_H
