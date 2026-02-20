#ifndef TICTACTOE3X3FORM_H
#define TICTACTOE3X3FORM_H

#include <QWidget>
#include <QPushButton>
#include <qlabel>
QT_BEGIN_NAMESPACE
namespace Ui {
class TicTacToe3x3Form;
}
QT_END_NAMESPACE
class TicTacToe3x3Form : public QWidget
{
    Q_OBJECT

public:
    explicit TicTacToe3x3Form(QWidget *parent = nullptr, QLabel *gameStatus = nullptr);
    ~TicTacToe3x3Form();
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

private:
    Ui::TicTacToe3x3Form *ui;
    QPushButton* buttomBox[9];
    bool isPlayerMove;
    unsigned char board[9];
    void playerMove(int index);
    void computerMove();
    QLabel *gameStatus;
};

#endif // TICTACTOE3X3FORM_H
