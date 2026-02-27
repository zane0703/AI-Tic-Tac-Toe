#ifndef TICTACTOE4X4FORM_H
#define TICTACTOE4X4FORM_H

#include <QWidget>
#include <QPushButton>
#include <qlabel>
#include <QObject>
#include <qthread>
#include <qpointer>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <stdlib.h>
#include <QString>
#include <time.h>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui {
class TicTacToe4x4Form;
}
QT_END_NAMESPACE

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(unsigned char * board, unsigned char deapLimit);
    void abort();
public slots:
    void doWork();
signals:
    void finished();
    void onResult(int computeChoice);
private:
    unsigned char * board;
    unsigned char depthLimit;
    QFuture<int> futures[16];
    bool isAbort;
};

class TicTacToe4x4Form : public QWidget
{
    Q_OBJECT

public:
    explicit TicTacToe4x4Form(QWidget *parent = nullptr, QLabel *gameStatus = nullptr);
    ~TicTacToe4x4Form();
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
    void on_buttonBox9_Clicked();
    void on_buttonBox10_Clicked();
    void on_buttonBox11_Clicked();
    void on_buttonBox12_Clicked();
    void on_buttonBox13_Clicked();
    void on_buttonBox14_Clicked();
    void on_buttonBox15_Clicked();
    void on_computerMove_Result(int computeChoice);


private:
    bool isPlayerMove;
    unsigned char board[16];
    void playerMove(int index);
    void computerMove();
    void setWinLine(QColor colour, unsigned char winLine);
    void setBtnColour(QColor colour, unsigned int btnIndex);
    Ui::TicTacToe4x4Form *ui;
    QPushButton* buttomBox[16];
    QLabel *gameStatus;
    QPointer<Worker> worker;
    QPointer<QThread> thread;
    QPalette defaultBtnPalette;
};



#endif // TICTACTOE4X4FORM_H
