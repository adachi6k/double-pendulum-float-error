#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "simulation.h"

class QTimer;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // カスタム描画のためのイベントハンドラ
    void paintEvent(QPaintEvent *event) override;

private:
    DoublePendulumSimulation *simulation;
    QTimer *timer;
    double dt;  // シミュレーション刻み幅（秒）

private slots:
    // タイマーにより定期的に呼ばれるスロット
    void updateSimulation();
};

#endif // MAINWINDOW_H
