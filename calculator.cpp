#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
double inMemVal = 0.0;
bool inMemTrigger = false;
bool divTrigger  = false;
bool multTrigger  = false;
bool addTrigger  = false;
bool subTrigger  = false;


Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0; i<10;++i){
        QString butName = "Button"+QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Substract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearScreen()));
    connect(ui->MemClear, SIGNAL(released()), this, SLOT(ClearMem()));
    connect(ui->MemGet, SIGNAL(released()), this, SLOT(GetFromMem()));
    connect(ui->MemAdd, SIGNAL(released()), this, SLOT(AddToMem()));
    connect(ui->Comma, SIGNAL(released()), this, SLOT(CommaPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}



void Calculator::MathButtonPressed(){
    divTrigger = false;
    multTrigger=false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else {
        subTrigger=true;
    }
    ui->Display->setText("");
}

void Calculator::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger ||divTrigger){
        if(addTrigger){
            solution = calcVal+dblDisplayVal;
        } else if(subTrigger){
            solution = calcVal-dblDisplayVal;
        } else if(multTrigger){
            solution = calcVal*dblDisplayVal;
        } else {
            solution = calcVal/dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution,'f', 12));
}

void Calculator::ChangeNumberSign(){
    QString displayVal = ui->Display->text();
    QRegExp reg("[-]?[0-9]*");
    if(reg.exactMatch(displayVal)){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1*dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}

void Calculator::ClearScreen(){
    addTrigger = false;
    subTrigger = false;
    multTrigger = false;
    divTrigger = false;
       ui->Display->setText("0");
}

void Calculator::AddToMem(){
    QString displayVal = ui->Display->text();
    inMemVal = displayVal.toDouble();
    inMemTrigger = true;
}

void Calculator::GetFromMem(){
    if(inMemTrigger){
        ui->Display->setText(QString::number(inMemVal));
    }
}

void Calculator::ClearMem(){
    if(inMemTrigger){
        inMemTrigger = false;
    }
}
void Calculator::CommaPressed(){
    QString displayVal = ui->Display->text();
    //std::cout << displayVal.toUtf8().constData() << std::endl;//
    qDebug()<<displayVal<<"before comma pressed";//
    qDebug()<<displayVal.indexOf('.')<<"try search";
    if(displayVal.indexOf(".")!=-1){
        qDebug()<<displayVal<<"comma already exists:nothing happened";//
        qDebug() << displayVal<<"after comma pressed";//
        return;
    }
    if((displayVal.toDouble() == 0)){
        ui->Display->setText("0.");
    }
    else{
        QString newVal = QString::number(displayVal.toDouble(), 'g', 40)+".";
        ui->Display->setText(newVal);
    }
    displayVal = ui->Display->text();qDebug() << displayVal<<"after comma pressed";//
}


void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString ch = "0.";
    QString displayVal = ui->Display->text();
    qDebug() << displayVal;//
    qDebug() << ch.toDouble()<<"ch this broski";//

    if(displayVal == "0"){
        ui->Display->setText(butVal);
    }
    else{
        qDebug() << ch.toDouble()<<"wtf broski";//
        QString newVal = displayVal+butVal;
//        double dblNewVal = newVal.toDouble();
//        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
        ui->Display->setText(newVal);
    }
//    if(displayVal == "0."){
//        qDebug() << ch.toDouble()<<"wtf broski";//
//        QString newVal = displayVal+butVal;
////        double dblNewVal = newVal.toDouble();
////        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
//        ui->Display->setText(newVal);
//    }
//    else if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
//        ui->Display->setText(butVal);
//    }
//    else{
//        QString newVal = displayVal+butVal;
//        double dblNewVal = newVal.toDouble();
//        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
//    }
}





























