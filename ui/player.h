/*!
    Player UI
    @file player.h
    @author Vladimir A Kulchitsky
    @version 1.0 10/06/2020
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>

namespace Ui {
class Player;
}

/*!
 * \brief The Player UI with slider, buttons, and label
 */
class Player : public QWidget
{
    Q_OBJECT

public:

    /*!
     * \brief Constructor
     * \param parent
     */
    explicit Player(QWidget *parent = nullptr);

    ~Player();

    /*!
     * \brief set label below slider
     * \param text to be set
     */
    void setLabel(const QString& text);

    /*!
     * \brief set slider frame
     * \param frame number to be set
     */
    void setFrame(int frame);

    /*!
     * \brief set minimum slider value
     * \param min to be set
     */
    void setMinimum(int min);

    /*!
     * \brief set maximum slider value
     * \param max to be set
     */
    void setMaximum(int max);

signals:
    /*!
     * \brief slidTo a frame
     * \param val - value of frame
     */
    void slidTo(int val);

private:
    Ui::Player *ui;
    QTimer* m_playTimer;
    bool m_isPlaying;
    void play();
    void pause();
    void playToNext();
};

#endif // PLAYER_H
