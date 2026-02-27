#include "tictactoe3x3form.hpp"
#include "ui_tictactoe3x3form.h"
#include "Tic-Tac-Toe.h"
#include <QDebug>

TicTacToe3x3Form::TicTacToe3x3Form(QWidget *parent, QLabel *gameStatus)
    : QWidget(parent)
    , ui(new Ui::TicTacToe3x3Form)
{
    ui->setupUi(this);
    worker = nullptr;
    thread = nullptr;
    defaultBtnColor = ui->buttonBox0->palette().color(QPalette::Button);
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

    connect(ui->buttonBox0, &QPushButton::clicked, this, &TicTacToe3x3Form::on_buttonBox0_Clicked);
    connect(ui->buttonBox1, &QPushButton::clicked, this, &TicTacToe3x3Form::on_buttonBox1_Clicked);
    connect(ui->buttonBox2, &QPushButton::clicked, this, &TicTacToe3x3Form::on_buttonBox2_Clicked);
    connect(ui->buttonBox3, &QPushButton::clicked, this, &TicTacToe3x3Form::on_buttonBox3_Clicked);
    connect(ui->buttonBox4, &QPushButton::clicked, this, &TicTacToe3x3Form::on_buttonBox4_Clicked);
    connect(ui->buttonBox5, &QPushButton::clicked, this, &TicTacToe3x3Form::on_buttonBox5_Clicked);
    connect(ui->buttonBox6, &QPushButton::clicked, this, &TicTacToe3x3Form::on_buttonBox6_Clicked);
    connect(ui->buttonBox7, &QPushButton::clicked, this, &TicTacToe3x3Form::on_buttonBox7_Clicked);
    connect(ui->buttonBox8, &QPushButton::clicked, this, &TicTacToe3x3Form::on_buttonBox8_Clicked);
}

TicTacToe3x3Form::~TicTacToe3x3Form()
{
    if(!worker.isNull()) {
        worker->abort();
    }
    delete ui;
}


void TicTacToe3x3Form::on_buttonBox0_Clicked() {
    playerMove(0);
}
void TicTacToe3x3Form::on_buttonBox1_Clicked() {
    this->playerMove(1);
}
void TicTacToe3x3Form::on_buttonBox2_Clicked() {
    this->playerMove(2);
}
void TicTacToe3x3Form::on_buttonBox3_Clicked() {
    this->playerMove(3);
}
void TicTacToe3x3Form::on_buttonBox4_Clicked() {
    this->playerMove(4);
}
void TicTacToe3x3Form::on_buttonBox5_Clicked() {
    this->playerMove(5);
}
void TicTacToe3x3Form::on_buttonBox6_Clicked() {
    this->playerMove(6);
}
void TicTacToe3x3Form::on_buttonBox7_Clicked() {
    this->playerMove(7);
}
void TicTacToe3x3Form::on_buttonBox8_Clicked() {
    this->playerMove(8);
}
void TicTacToe3x3Form::playerMove(int playerChoice){
    unsigned char winline;
    if(this->board[playerChoice] != ' ' || !this->isPlayerMove) {
        return;
    }
    this->isPlayerMove = false;
    this->board[playerChoice] = 'O';
    this->buttomBox[playerChoice]->setText("O");
    winline = isWinner(board, 'O');
    if (winline) {
        gameStatus->setText("You Win!");
        setWinLine(Qt::green, winline);
        return;
    }
    if (isBoardFull(board)) {
        gameStatus->setText( "It's a draw!");
        return;
    }
    computerMove();
}

void TicTacToe3x3Form::computerMove(){
    int computeChoice;
    if(ui->dumpModeCheck->isChecked()) {
        do {
            computeChoice = rand() % 9;
        }while(board[computeChoice] != ' ');
        on_computerMove_Result(computeChoice);
        return;
    }
    gameStatus->setText("Computer Move");
    worker = new Worker3x3(board);
    thread = new QThread;
    worker->moveToThread(thread);
    connect(thread, &QThread::started, worker, &Worker3x3::doWork );
    connect(worker, &Worker3x3::onResult, this, &TicTacToe3x3Form::on_computerMove_Result);
    connect(worker, &Worker3x3::finished, thread, &QThread::quit);

    connect(worker, &Worker3x3::finished, worker, &Worker3x3::deleteLater);
    connect(thread, &QThread::finished,  thread, &QThread::deleteLater);
    thread->start();
}

void TicTacToe3x3Form::on_resetButton_Clicked() {
    int i;
    for (i = 0; i< 9;++i) {
        buttomBox[i]->setText(" ");
        setBtnColour(defaultBtnColor, i);
        board[i] = ' ';
    }
    this->isPlayerMove = rand()&1;
    if(!worker.isNull()) {
        worker->abort();
    }
    if (this->isPlayerMove) {
        gameStatus->setText("Player Move");
    } else {
        computerMove();
    }

}
void TicTacToe3x3Form::on_computerMove_Result(int computeChoice){
    unsigned char winline;
    this->board[computeChoice] = 'X';
    this->buttomBox[computeChoice]->setText("X");
    winline = isWinner(board, 'X');
    if (winline) {
        gameStatus->setText("You lost!");
        setWinLine(Qt::red, winline);
        return;
    }
    if (isBoardFull(board)) {
        gameStatus->setText( "It's a draw!");
        return;
    }
    this->isPlayerMove = true;
    gameStatus->setText("Player Move");
}
void TicTacToe3x3Form::setWinLine(QColor colour, unsigned char winLine) {

    switch (winLine) {
    case 1:
        setBtnColour(colour, 0);
        setBtnColour(colour, 1);
        setBtnColour(colour, 2);
        break;
    case 2:
        setBtnColour(colour, 3);
        setBtnColour(colour, 4);
        setBtnColour(colour, 5);
        break;
    case 3:
        setBtnColour(colour, 6);
        setBtnColour(colour, 7);
        setBtnColour(colour, 8);
        break;
    case 4:
        setBtnColour(colour, 0);
        setBtnColour(colour, 3);
        setBtnColour(colour, 6);
        break;
    case 5:
        setBtnColour(colour, 1);
        setBtnColour(colour, 4);
        setBtnColour(colour, 7);
        break;
    case 6:
        setBtnColour(colour, 2);
        setBtnColour(colour, 5);
        setBtnColour(colour, 8);
        break;
    case 7:
        setBtnColour(colour, 0);
        setBtnColour(colour, 4);
        setBtnColour(colour, 8);
        break;
    case 8:
        setBtnColour(colour, 2);
        setBtnColour(colour, 4);
        setBtnColour(colour, 6);
        break;
    }
}
void TicTacToe3x3Form::setBtnColour(QColor colour, unsigned int btnIndex) {
    QPalette palette = buttomBox[btnIndex]->palette();
    palette.setColor(QPalette::Button, colour);
    buttomBox[btnIndex]->setPalette(palette);
}

void TicTacToe3x3Form::abort() {
    if(!worker.isNull()) {
        worker->abort();
    }
}

Worker3x3::Worker3x3(unsigned char * board) {
    this->board = board;
    isAbort = false;
}

void Worker3x3::doWork() {
    int computeChoice = smartChoice(board, 'X', &isAbort);
    if(isAbort) {
        emit finished();
        return;
    }
    emit onResult(computeChoice);
    emit finished();
}


void Worker3x3::abort() {
    isAbort = true;
}


