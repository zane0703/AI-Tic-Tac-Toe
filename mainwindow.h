#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

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
     void on_buttonBox_Clicked(int index);

private slots:
    void on_buttonBox0_Clicked();
    void on_buttonBox1_Clicked();
    void on_buttonBox2_Clicked();
    void on_buttonBox3_Clicked();
    void on_buttonBox4_Clicked();
    void on_buttonBox5_Clicked();
    void on_buttonBox6_Clicked();
    void on_buttonBox7_Clicked();
    void on_buttonBox8_Clicked();
    void on_resetButton_Clicked();


private:
    Ui::MainWindow *ui;
    QPushButton* buttomBox[9];
    bool gameEnd;
    unsigned char board[9];
};
#endif // MAINWINDOW_H
