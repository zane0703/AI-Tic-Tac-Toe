#ifndef TICTACTOE3X3FORM_H
#define TICTACTOE3X3FORM_H

#include <QWidget>
#include <QPushButton>
#include <qlabel>
#include <QObject>
#include <qthread>
#include <qpointer.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class TicTacToe3x3Form;
}
QT_END_NAMESPACE

class Worker3x3 : public QObject
{
    Q_OBJECT
public:
    Worker3x3(unsigned char * board);
    void abort();
public slots:
    void doWork();
signals:
    void finished();
    void onResult(int computeChoice);
private:
    unsigned char * board;
    bool isAbort;
};

class TicTacToe3x3Form : public QWidget
{
    Q_OBJECT

public:
    explicit TicTacToe3x3Form(QWidget *parent = nullptr, QLabel *gameStatus = nullptr);
    ~TicTacToe3x3Form();
    void on_resetButton_Clicked();
    void abort();
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
    void on_computerMove_Result(int computeChoice);

private:
    bool isPlayerMove;
    unsigned char board[9];
    void playerMove(int index);
    void computerMove();
    void setWinLine(QColor colour, unsigned char winLine);
    void setBtnColour(QColor colour, unsigned int btnIndex);
    Ui::TicTacToe3x3Form *ui;
    QPushButton* buttomBox[9];
    QLabel *gameStatus;
    QPointer<Worker3x3> worker;
    QPointer<QThread> thread;
    QColor defaultBtnColor;

};

#endif // TICTACTOE3X3FORM_H
