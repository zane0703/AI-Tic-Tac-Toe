#ifndef TICTACTOE4X4FORM_H
#define TICTACTOE4X4FORM_H

#include <QWidget>
#include <QPushButton>
#include <qlabel>
QT_BEGIN_NAMESPACE
namespace Ui {
class TicTacToe4x4Form;
}
QT_END_NAMESPACE

class TicTacToe4x4Form : public QWidget
{
    Q_OBJECT

public:
    explicit TicTacToe4x4Form(QWidget *parent = nullptr, QLabel *gameStatus = nullptr);
    ~TicTacToe4x4Form();
    void on_resetButton_Clicked();
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
    void on_buttonBox9_Clicked();
    void on_buttonBox10_Clicked();
    void on_buttonBox11_Clicked();
    void on_buttonBox12_Clicked();
    void on_buttonBox13_Clicked();
    void on_buttonBox14_Clicked();
    void on_buttonBox15_Clicked();


private:
    Ui::TicTacToe4x4Form *ui;
    QPushButton* buttomBox[16];
    bool isPlayerMove;
    unsigned char board[16];
    void playerMove(int index);
    void computerMove();
    QLabel *gameStatus;
};

#endif // TICTACTOE4X4FORM_H
