#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <cmath>

/* シミュレーション部分の抽象インターフェース（拡張用） */
class SimulationInterface : public QObject {
    Q_OBJECT
public:
    explicit SimulationInterface(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~SimulationInterface() {}

    // dt秒だけシミュレーションを進める
    virtual void step(double dt) = 0;

signals:
    void simulationUpdated();
};

/* 2重振り子のシミュレーション（Euler法による簡易実装） */
class DoublePendulumSimulation : public SimulationInterface {
    Q_OBJECT
public:
    explicit DoublePendulumSimulation(QObject *parent = nullptr);

    // シミュレーションパラメータ
    double m1, m2;            // 質量
    double L1, L2;            // 振り子の長さ
    double theta1, theta2;    // 角度（ラジアン）
    double omega1, omega2;    // 角速度
    double g;                 // 重力加速度

    // dt秒だけシミュレーションを進める
    virtual void step(double dt) override;

    // 現在の各振り子の位置を返す（原点を固定点とする）
    void getPositions(double &x1, double &y1, double &x2, double &y2) const;
};

#endif // SIMULATION_H
