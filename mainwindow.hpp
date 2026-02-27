#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "tictactoe3x3form.hpp"
#include "tictactoe4x4form.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_resetButton_Clicked();
    void on_changeButton_Clicked();


private:
    TicTacToe3x3Form* m_3x3Form;
    TicTacToe4x4Form* m_4x4Form;
    Ui::MainWindow *ui;
    bool is4x4;

};
#endif // MAINWINDOW_H
