#include "mainwindow.hpp"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QPalette palette;
    QStyleHints *styleHints;

    setWindowTitle("Tic-tac-toe");
    is4x4 = false;
    ui->setupUi(this);
    styleHints = QGuiApplication::styleHints();
    switch (styleHints->colorScheme()){
        case Qt::ColorScheme::Light:
            palette = this->palette();
            palette.setColor(QPalette::Window,Qt::lightGray);
            this->setPalette(palette);
            break;
        default:
            palette = this->palette();
            palette.setColor(QPalette::Window,Qt::black);
            this->setPalette(palette);

    }
    m_3x3Form = new TicTacToe3x3Form(this, ui->gameStatus);
    m_4x4Form = new TicTacToe4x4Form(this, ui->gameStatus);
    ui->stackedWidget->addWidget(m_3x3Form);
    ui->stackedWidget->addWidget(m_4x4Form);
    ui->stackedWidget->setCurrentWidget(m_3x3Form);
    m_3x3Form->on_resetButton_Clicked();
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::on_resetButton_Clicked);
    connect(ui->changeButton, &QPushButton::clicked, this, &MainWindow::on_changeButton_Clicked);
    connect(styleHints,&QStyleHints::colorSchemeChanged, this, &MainWindow::on_colorScheme_Changed);
}

MainWindow::~MainWindow()
{
    delete m_3x3Form;
    delete m_4x4Form;
    delete ui;
}


void MainWindow::on_changeButton_Clicked() {
    if (is4x4) {
        is4x4 = false;
        ui->stackedWidget->setCurrentWidget(m_3x3Form);
        m_4x4Form->abort();
        m_3x3Form->on_resetButton_Clicked();
        ui->changeButton->setText("4x4");
    } else {
        is4x4 = true;
        ui->stackedWidget->setCurrentWidget(m_4x4Form);
        m_3x3Form->abort();
        m_4x4Form->on_resetButton_Clicked();
        ui->changeButton->setText("3x3");

    }
}

void MainWindow::on_resetButton_Clicked() {
    ui->gameStatus->setText("");
    if (is4x4) {
        m_4x4Form->on_resetButton_Clicked();
    }else {
        m_3x3Form->on_resetButton_Clicked();
    }
}


void MainWindow::on_colorScheme_Changed(Qt::ColorScheme colorScheme) {
    QPalette palette;
    switch (colorScheme){
        case Qt::ColorScheme::Light:
            palette = this->palette();
            palette.setColor(QPalette::Window,Qt::lightGray);
            this->setPalette(palette);
            break;
        default:
            palette = this->palette();
            palette.setColor(QPalette::Window,Qt::black);
            this->setPalette(palette);

    }
}
