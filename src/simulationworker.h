#ifndef SIMULATIONWORKER_H
#define SIMULATIONWORKER_H

#include <QObject>
#include "simulation.h"

class SimulationWorker : public QObject
{
    Q_OBJECT
public:
    explicit SimulationWorker(QObject *parent = nullptr);
    ~SimulationWorker();

public slots:
    // メインループ（この関数は QThread 上で実行される）
    void process();

    // シミュレーション停止用のスロット
    void stop();

    // 速度調整用スロット
    // speedFactor: スライダーの値（例：1～200、100が通常）
    void setSpeed(int speedFactor);

signals:
    // シミュレーション更新時に現在の各質点の位置を渡す
    void simulationUpdated(double x1, double y1, double x2, double y2);

private:
    bool m_running;
    DoublePendulumSimulation *m_simulation;
    double m_dt; // シミュレーションの時間刻み（秒）
};

#endif // SIMULATIONWORKER_H
