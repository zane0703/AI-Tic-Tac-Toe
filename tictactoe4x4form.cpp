#include "tictactoe4x4form.h"
#include "ui_tictactoe4x4form.h"
#include "Tic-Tac-Toe-4x4.h"
#include <stdlib.h>
#include <QString>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QRandomGenerator>
#include <time.h>
#include <QDebug>

TicTacToe4x4Form::TicTacToe4x4Form(QWidget *parent, QLabel *gameStatus)
    : QWidget(parent)
    , ui(new Ui::TicTacToe4x4Form)
{
    ui->setupUi(this);
    worker = nullptr;
    thread = nullptr;
    this->gameStatus = gameStatus;
    this->buttomBox[0] = ui->buttonBox0;
    this->buttomBox[1] = ui->buttonBox1;
    this->buttomBox[2] = ui->buttonBox2;
    this->buttomBox[3] = ui->buttonBox3;
    this->buttomBox[4] = ui->buttonBox4;
    this->buttomBox[5] = ui->buttonBox5;
    this->buttomBox[6] = ui->buttonBox6;
    this->buttomBox[7] = ui->buttonBox7;
    this->buttomBox[8] = ui->buttonBox8;
    this->buttomBox[9] = ui->buttonBox9;
    this->buttomBox[10] = ui->buttonBox10;
    this->buttomBox[11] = ui->buttonBox11;
    this->buttomBox[12] = ui->buttonBox12;
    this->buttomBox[13] = ui->buttonBox13;
    this->buttomBox[14] = ui->buttonBox14;
    this->buttomBox[15] = ui->buttonBox15;

    connect(ui->buttonBox0, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox0_Clicked);
    connect(ui->buttonBox1, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox1_Clicked);
    connect(ui->buttonBox2, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox2_Clicked);
    connect(ui->buttonBox3, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox3_Clicked);
    connect(ui->buttonBox4, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox4_Clicked);
    connect(ui->buttonBox5, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox5_Clicked);
    connect(ui->buttonBox6, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox6_Clicked);
    connect(ui->buttonBox7, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox7_Clicked);
    connect(ui->buttonBox8, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox8_Clicked);
    connect(ui->buttonBox9, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox9_Clicked);
    connect(ui->buttonBox10, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox10_Clicked);
    connect(ui->buttonBox11, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox11_Clicked);
    connect(ui->buttonBox12, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox12_Clicked);
    connect(ui->buttonBox13, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox13_Clicked);
    connect(ui->buttonBox14, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox14_Clicked);
    connect(ui->buttonBox15, &QPushButton::clicked, this , &TicTacToe4x4Form::on_buttonBox15_Clicked);

}

TicTacToe4x4Form::~TicTacToe4x4Form()
{
    // if (worker != nullptr){
    //     delete worker;
    // }
    // if (thread != nullptr) {
    //     delete thread;
    // }
    delete ui;
}


void TicTacToe4x4Form::on_buttonBox0_Clicked() {
    this->playerMove(0);
}
void TicTacToe4x4Form::on_buttonBox1_Clicked() {
    this->playerMove(1);
}
void TicTacToe4x4Form::on_buttonBox2_Clicked() {
    this->playerMove(2);
}
void TicTacToe4x4Form::on_buttonBox3_Clicked() {
    this->playerMove(3);
}
void TicTacToe4x4Form::on_buttonBox4_Clicked() {
    this->playerMove(4);
}
void TicTacToe4x4Form::on_buttonBox5_Clicked() {
    this->playerMove(5);
}
void TicTacToe4x4Form::on_buttonBox6_Clicked() {
    this->playerMove(6);
}
void TicTacToe4x4Form::on_buttonBox7_Clicked() {
    this->playerMove(7);
}
void TicTacToe4x4Form::on_buttonBox8_Clicked() {
    this->playerMove(8);
}
void TicTacToe4x4Form::on_buttonBox9_Clicked() {
    this->playerMove(9);
}
void TicTacToe4x4Form::on_buttonBox10_Clicked() {
    this->playerMove(10);
}
void TicTacToe4x4Form::on_buttonBox11_Clicked() {
    this->playerMove(11);
}
void TicTacToe4x4Form::on_buttonBox12_Clicked() {
    this->playerMove(12);
}
void TicTacToe4x4Form::on_buttonBox13_Clicked() {
    this->playerMove(13);
}
void TicTacToe4x4Form::on_buttonBox14_Clicked() {
    this->playerMove(14);
}
void TicTacToe4x4Form::on_buttonBox15_Clicked() {
    this->playerMove(15);
}

void TicTacToe4x4Form::playerMove(int playerChoice){
    if(this->board[playerChoice] != ' ' || !this->isPlayerMove) {
        return;
    }
    this->isPlayerMove = false;
    this->board[playerChoice] = 'O';
    this->buttomBox[playerChoice]->setText("O");
    if (isWinner4(board, 'O')) {
        gameStatus->setText("You Win!");
        return;
    }
    if (isBoardFull4(board)) {
        gameStatus->setText( "It's a draw!");
        return;
    }
    computerMove();

}
void TicTacToe4x4Form::computerMove(){
    int computeChoice;
    int deapLimit;

    gameStatus->setText("Computer Move");
    deapLimit = ui->depthLimitcomboBox->currentIndex() + 5;
    worker = new Worker(board, deapLimit);
    thread = new QThread;
    worker->moveToThread(thread);
    connect(thread, &QThread::started, worker, &Worker::doWork );
    connect(worker, &Worker::workFinished, this, &TicTacToe4x4Form::on_computerMove_Result);
    connect(worker, &Worker::workFinished, thread, &QThread::quit);

    connect(worker, &Worker::workFinished, worker, &Worker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();
}
void TicTacToe4x4Form::on_computerMove_Result(int computeChoice) {
    this->board[computeChoice] = 'X';
    this->buttomBox[computeChoice]->setText("X");
    if (isWinner4(board, 'X')) {
        gameStatus->setText("You lost!");
        return;
    }
    if (isBoardFull4(board)) {
        gameStatus->setText( "It's a draw!");
        return;
    }
    this->isPlayerMove = true;
    gameStatus->setText("Player Move");
}

void TicTacToe4x4Form::on_resetButton_Clicked() {
    int i;

    for (i = 0; i< 16;++i) {
        buttomBox[i]->setText(" ");
        board[i] = ' ';
    }
    this->isPlayerMove = rand()%2;
    if (this->isPlayerMove) {
        gameStatus->setText("Player Move");
    } else {
        computerMove();
    }
}
Worker::Worker(unsigned char * board, unsigned char deapLimit) {
    this->board = board;
    this->depthLimit = deapLimit;
}


void Worker::doWork() {
    unsigned char player ='X';
    signed char score, bestScore = SCHAR_MIN;
    int pos, i, j = 0 , bestMove = 0, storePos[16];
    srand ( time(NULL) );
    pos = (int)(rand() % 16);
    qDebug()<< pos;
    QFuture<int> futures[16];
    for (i = 0; i< 16; ++i){
        pos = (pos + 1) % 16;
        if (board[pos] != ' ') continue;
        //# Simulate the move
        storePos[j] = pos;
        futures[j++] = QtConcurrent::run(smartChoice4,
                                         board,// # use board's copy
                                         player,         // # maximize for Computer (O)
                                         depthLimit,
                                         pos);
    }
    for (i = 0; i <j; ++i) {
        futures[i].waitForFinished();
        score = futures[i].result();
        if (score > bestScore){
            bestScore = score;
            bestMove = storePos[i];

        }
    }

    //# Return the best move
    emit workFinished(bestMove);
}
