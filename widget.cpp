#include "widget.h"
#include "ui_widget.h"
#include <QShortcut>
#include <QDebug>
#include <QRandomGenerator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    makeGameState();
    updateUi();

    new QShortcut(QKeySequence(Qt::Key_Right), this, SLOT(righClicked()));
    new QShortcut(QKeySequence(Qt::Key_Up), this, SLOT(upClicked()));
    new QShortcut(QKeySequence(Qt::Key_Down), this, SLOT(downClicked()));
    new QShortcut(QKeySequence(Qt::Key_Left), this, SLOT(leftClicked()));

}



Widget::~Widget()
{
    delete ui;
}

void Widget::makeGameState()
{
    QVector<qint64> tmp;
    for(int i=0;i<4;i++)
        tmp.append(0);

    tmp[2] = 2;
    tmp[3] = 2;
    gameState.append(tmp);
    tmp[2] = 0;
    gameState.append(tmp);
    tmp[3] = 0;
    gameState.append(tmp);
    gameState.append(tmp);
}

void Widget::updateUi()
{
    ui->label00->setText((gameState[0][0]==0 ? "-" : QString::number(gameState[0][0])));
    ui->label01->setText((gameState[0][1]==0 ? "-" : QString::number(gameState[0][1])));
    ui->label02->setText((gameState[0][2]==0 ? "-" : QString::number(gameState[0][2])));
    ui->label03->setText((gameState[0][3]==0 ? "-" : QString::number(gameState[0][3])));
    ui->label10->setText((gameState[1][0]==0 ? "-" : QString::number(gameState[1][0])));
    ui->label11->setText((gameState[1][1]==0 ? "-" : QString::number(gameState[1][1])));
    ui->label12->setText((gameState[1][2]==0 ? "-" : QString::number(gameState[1][2])));
    ui->label13->setText((gameState[1][3]==0 ? "-" : QString::number(gameState[1][3])));
    ui->label20->setText((gameState[2][0]==0 ? "-" :  QString::number(gameState[2][0])));
    ui->label21->setText((gameState[2][1]==0 ? "-" : QString::number(gameState[2][1])));
    ui->label22->setText((gameState[2][2]==0 ? "-" : QString::number(gameState[2][2])));
    ui->label23->setText((gameState[2][3]==0 ? "-" : QString::number(gameState[2][3])));
    ui->label30->setText((gameState[3][0]==0 ? "-" : QString::number(gameState[3][0])));
    ui->label31->setText((gameState[3][1]==0 ? "-" : QString::number(gameState[3][1])));
    ui->label32->setText((gameState[3][2]==0 ? "-" : QString::number(gameState[3][2])));
    ui->label33->setText((gameState[3][3]==0 ? "-" : QString::number(gameState[3][3])));

}

bool Widget::luck()
{
    qint64 rand = QRandomGenerator::global()->bounded(3);
    if(rand == 2)
        return true;
    return false;
}

void Widget::righClicked()
{

    for(int j=0;j<4;j++){
        bool moveOccured = false;
        qInfo()<<"j"<<QString::number(j);
        for(int i=0;i<3;i++){
            qInfo()<<QString::number(i);
            if(gameState[j][i] == gameState[j][i+1] && gameState[j][i] != 0){
                gameState[j][i]=0;
                gameState[j][i+1] *= 2;
                i++;
                moveOccured = true;
            }
        }
        qint64 q = 10;
        while(q--){
            for(int i=2;i>=0;i--){
                if(gameState[j][i] != 0 && gameState[j][i+1]==0){
                    gameState[j][i+1] = gameState[j][i];
                    gameState[j][i] = 0;
                }
            }
        }
        if(gameState[j][0] == 0 && moveOccured){
            if(luck()){
                for(int i=3;i>=0;i--){
                    if(gameState[j][i] == 0){
                        gameState[j][i] = 2;
                        break;
                    }
                }
            }
        }

    }
    updateUi();
}

void Widget::leftClicked()
{

    for(int j=0;j<4;j++){
        bool moveOccured = false;
        qInfo()<<"j"<<QString::number(j);
        for(int i=3;i>=1;i--){
            qInfo()<<QString::number(i);
            if(gameState[j][i] == gameState[j][i-1] && gameState[j][i] != 0){
                gameState[j][i]=0;
                gameState[j][i-1] *= 2;
                i++;
                moveOccured = true;
            }
        }
        QVector<qint64> tmp;
        for(int i=0;i<4;i++){
            if(gameState[j][i]!=0)
                tmp.append(gameState[j][i]);
        }
        for(int i=0;i<4;i++){
            if(i<tmp.size()){
                gameState[j][i] = tmp[i];
            }else{
                gameState[j][i] = 0;
            }
        }
        qint64 q = 10;
        while(q--){
            for(int i=1;i<4;i++){
                if(gameState[j][i] != 0 && gameState[j][i-1]==0){
                    gameState[j][i-1] = gameState[j][i];
                    gameState[j][i] = 0;
                }
            }
        }
        if(gameState[j][0] == 0 && moveOccured){
            if(luck()){
                for(int i=0;i<4;i++){
                    if(gameState[j][i] == 0){
                        gameState[j][i] = 2;
                        break;
                    }
                }
            }
        }

    }
    updateUi();
}

void Widget::upClicked()
{

    for(int j=0;j<4;j++){
        bool moveOccured = false;
        for(int i=3;i>=1;i--){
            if(gameState[i][j] == gameState[i-1][j]){
                gameState[i-1][j] *= 2;
                gameState[i][j] = 0;
                i--;
                moveOccured = true;
            }
        }
        int q = 10;
        while(q--){
            for(int i=1;i<4;i++){
                if(gameState[i][j] != 0 && gameState[i-1][j] == 0){
                    gameState[i-1][j] = gameState[i][j];
                    gameState[i][j] =0;
                }
            }
        }
        if(gameState[3][j] == 0 && moveOccured){
            if(luck()){
                bool flag = false;
                for(int i=3;i>=0;i--){
                    if(gameState[i][j] != 0){
                        gameState[i+1][j] = 2;
                        flag = true;
                        break;
                    }
                }
                if(!flag)
                    gameState[0][j] = 2;
            }
        }
    }
    updateUi();
}

void Widget::downClicked()
{

    for(int j=0;j<4;j++){
        bool moveOccured = false;
        for(int i=0;i<3;i++){
            if(gameState[i][j] == gameState[i+1][j]){
                gameState[i+1][j] *= 2;
                gameState[i][j] = 0;
                i++;
                moveOccured = true;
            }
        }
        int q = 10;
        while(q--){
            for(int i=2;i>=0;i--){
                if(gameState[i][j] != 0 && gameState[i+1][j] == 0){
                    gameState[i+1][j] = gameState[i][j];
                    gameState[i][j] =0;
                }
            }
        }
        if(gameState[0][j] == 0 && moveOccured){
            if(luck()){
                bool flag = false;
                for(int i=0;i<4;i++){
                    if(gameState[i][j] != 0){
                        gameState[i-1][j] = 2;
                        flag = true;
                        break;
                    }
                }
                if(!flag)
                    gameState[3][j] = 2;
            }
        }
    }
    updateUi();
    return;
}

