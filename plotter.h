#ifndef PLOTTER_H
#define PLOTTER_H
#include <QWidget>
#include "mainwindow.h"

class Plotter : public QWidget{
    Q_OBJECT

private:
    float ampl, freq;
    float teta;
    float velocidade;

public:
    explicit Plotter(QWidget *parent = 0);
    void paintEvent(QPaintEvent *e);

signals:
    void posx(int);
    void posy(int);

public slots:
    void setAmplitude(int ampl);
    void setFrequencia(int freq);
    void timerEvent(QTimerEvent *e, std::vector<int> &data);
    void setVelocidade(int velocidade);

};

#endif // PLOTTER_H
