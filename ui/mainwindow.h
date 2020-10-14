/*!
    Main Window and process for GUI file
    @file mainwindow.h
    @author Vladimir A Kulchitsky
    @version 1.0 10/06/2020
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "io/projectcontroller.hpp"

#include <QMainWindow>

class QFileDialog;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief The MainWindow UI, including main GUI process in some connects
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*!
     * \brief Constructor
     * \param parent
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow *ui;
    QFileDialog* m_fileDialog;
    volatrack::ProjectController m_controller;
};
#endif // MAINWINDOW_H
