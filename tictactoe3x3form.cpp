#include "tictactoe3x3form.h"
#include "ui_tictactoe3x3form.h"
#include "Tic-Tac-Toe.h"

TicTacToe3x3Form::TicTacToe3x3Form(QWidget *parent, QLabel *gameStatus)
    : QWidget(parent)
    , ui(new Ui::TicTacToe3x3Form)
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
    connect(ui->buttonBox0, SIGNAL(clicked()), this ,SLOT(on_buttonBox0_Clicked()));
    connect(ui->buttonBox1, SIGNAL(clicked()), this ,SLOT(on_buttonBox1_Clicked()));
    connect(ui->buttonBox2, SIGNAL(clicked()), this ,SLOT(on_buttonBox2_Clicked()));
    connect(ui->buttonBox3, SIGNAL(clicked()), this ,SLOT(on_buttonBox3_Clicked()));
    connect(ui->buttonBox4, SIGNAL(clicked()), this ,SLOT(on_buttonBox4_Clicked()));
    connect(ui->buttonBox5, SIGNAL(clicked()), this ,SLOT(on_buttonBox5_Clicked()));
    connect(ui->buttonBox6, SIGNAL(clicked()), this ,SLOT(on_buttonBox6_Clicked()));
    connect(ui->buttonBox7, SIGNAL(clicked()), this ,SLOT(on_buttonBox7_Clicked()));
    connect(ui->buttonBox8, SIGNAL(clicked()), this ,SLOT(on_buttonBox8_Clicked()));
}

TicTacToe3x3Form::~TicTacToe3x3Form()
{
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
    int computeChoice;
    if(this->board[playerChoice] != ' ' || !this->isPlayerMove) {
        return;
    }
    this->isPlayerMove = false;
    this->board[playerChoice] = 'O';
    this->buttomBox[playerChoice]->setText("O");
    if (isWinner(board, 'O')) {
        gameStatus->setText("You Win!");
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
    gameStatus->setText("Computer Move");
    computeChoice = smartChoice(board, 'X');
    this->board[computeChoice] = 'X';
    this->buttomBox[computeChoice]->setText("X");
    if (isWinner(board, 'X')) {
        gameStatus->setText("You lost!");
        return;
    }
    if (isBoardFull(board)) {
        gameStatus->setText( "It's a draw!");
        return;
    }
    this->isPlayerMove = true;
    gameStatus->setText("Player Move");
}

void TicTacToe3x3Form::on_resetButton_Clicked() {
    int i;
    for (i = 0; i< 9;++i) {
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
