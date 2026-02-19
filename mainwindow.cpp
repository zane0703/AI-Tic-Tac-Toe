#include "mainwindow.h"
#include <string.h>
#include "ui_mainwindow.h"
#include "Tic-Tac-Toe.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int i;
    setWindowTitle("Tic-tac-toe");
    ui->setupUi(this);
    memset(this->board, ' ', 9);
    this->gameEnd = false;
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
    connect(ui->resetButton, SIGNAL(clicked()), this ,SLOT(on_resetButton_Clicked()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonBox0_Clicked() {
    on_buttonBox_Clicked(0);
}
void MainWindow::on_buttonBox1_Clicked() {
    this->on_buttonBox_Clicked(1);
}
void MainWindow::on_buttonBox2_Clicked() {
    this->on_buttonBox_Clicked(2);
}
void MainWindow::on_buttonBox3_Clicked() {
    this->on_buttonBox_Clicked(3);
}
void MainWindow::on_buttonBox4_Clicked() {
    this->on_buttonBox_Clicked(4);
}
void MainWindow::on_buttonBox5_Clicked() {
    this->on_buttonBox_Clicked(5);
}
void MainWindow::on_buttonBox6_Clicked() {
    this->on_buttonBox_Clicked(6);
}
void MainWindow::on_buttonBox7_Clicked() {
    this->on_buttonBox_Clicked(7);
}
void MainWindow::on_buttonBox8_Clicked() {
    this->on_buttonBox_Clicked(8);
}
void MainWindow::on_buttonBox_Clicked(int playerChoice){
    int computeChoice;
    if(this->board[playerChoice] != ' ' || this->gameEnd) {
        return;
    }
    this->board[playerChoice] = 'O';
    this->buttomBox[playerChoice]->setText("O");
    if (isWinner(board, 'O')) {
        ui->gameStatus->setText("You Win!");
        this->gameEnd = true;
        return;
    }
    if (isBoardFull(board)) {
        ui->gameStatus->setText( "It's a draw!");
        this->gameEnd = true;
    }
    computeChoice = smartChoice(board, 'X');
    this->board[computeChoice] = 'X';
    this->buttomBox[computeChoice]->setText("X");
    if (isWinner(board, 'X')) {
        ui->gameStatus->setText("You lost!");
        this->gameEnd = true;
        return;
    }
    if (isBoardFull(board)) {
        ui->gameStatus->setText( "It's a draw!");
        this->gameEnd = true;
    }
}
void MainWindow::on_resetButton_Clicked() {
    int i;
    this->gameEnd = false;
    ui->gameStatus->setText( "");
    for (i = 0; i< 9;++i) {
        buttomBox[i]->setText(" ");
        board[i] = ' ';
    }
}

