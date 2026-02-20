#include "tictactoe4x4form.h"
#include "ui_tictactoe4x4form.h"
#include "Tic-Tac-Toe-4x4.h"
#include <stdlib.h>
#include <QString>

TicTacToe4x4Form::TicTacToe4x4Form(QWidget *parent, QLabel *gameStatus)
    : QWidget(parent)
    , ui(new Ui::TicTacToe4x4Form)
{
    ui->setupUi(this);
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
    connect(ui->buttonBox0, SIGNAL(clicked()), this ,SLOT(on_buttonBox0_Clicked()));
    connect(ui->buttonBox1, SIGNAL(clicked()), this ,SLOT(on_buttonBox1_Clicked()));
    connect(ui->buttonBox2, SIGNAL(clicked()), this ,SLOT(on_buttonBox2_Clicked()));
    connect(ui->buttonBox3, SIGNAL(clicked()), this ,SLOT(on_buttonBox3_Clicked()));
    connect(ui->buttonBox4, SIGNAL(clicked()), this ,SLOT(on_buttonBox4_Clicked()));
    connect(ui->buttonBox5, SIGNAL(clicked()), this ,SLOT(on_buttonBox5_Clicked()));
    connect(ui->buttonBox6, SIGNAL(clicked()), this ,SLOT(on_buttonBox6_Clicked()));
    connect(ui->buttonBox7, SIGNAL(clicked()), this ,SLOT(on_buttonBox7_Clicked()));
    connect(ui->buttonBox8, SIGNAL(clicked()), this ,SLOT(on_buttonBox8_Clicked()));
    connect(ui->buttonBox9, SIGNAL(clicked()), this ,SLOT(on_buttonBox9_Clicked()));
    connect(ui->buttonBox10, SIGNAL(clicked()), this ,SLOT(on_buttonBox10_Clicked()));
    connect(ui->buttonBox11, SIGNAL(clicked()), this ,SLOT(on_buttonBox11_Clicked()));
    connect(ui->buttonBox12, SIGNAL(clicked()), this ,SLOT(on_buttonBox12_Clicked()));
    connect(ui->buttonBox13, SIGNAL(clicked()), this ,SLOT(on_buttonBox13_Clicked()));
    connect(ui->buttonBox14, SIGNAL(clicked()), this ,SLOT(on_buttonBox14_Clicked()));
    connect(ui->buttonBox15, SIGNAL(clicked()), this ,SLOT(on_buttonBox15_Clicked()));
}

TicTacToe4x4Form::~TicTacToe4x4Form()
{
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
    computeChoice = smartChoice4(board, 'X',deapLimit);
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
