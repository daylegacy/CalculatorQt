#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QtDebug>
#include <iostream>
namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;
private slots:
    void NumPressed();
    void CommaPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
    void ClearScreen();
    void AddToMem();
    void GetFromMem();
    void ClearMem();
};

#endif // CALCULATOR_H
