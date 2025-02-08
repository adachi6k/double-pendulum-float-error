#ifndef SIMULATION_H
#define SIMULATION_H

#include <QObject>
#include <cmath>

/* シミュレーション部分のインターフェース（必要に応じて拡張可能） */
class SimulationInterface : public QObject {
    Q_OBJECT
public:
    explicit SimulationInterface(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~SimulationInterface() {}

    // dt秒だけシミュレーションを進める
    virtual void step(double dt) = 0;

signals:
    // シミュレーション更新時に通知するシグナル（オプション）
    void simulationUpdated();
};

/* 2重振り子のシミュレーション（Euler法による簡易実装） */
class DoublePendulumSimulation : public SimulationInterface {
    Q_OBJECT
public:
    explicit DoublePendulumSimulation(QObject *parent = nullptr);

    // シミュレーションパラメータ
    double m1, m2;       // 質量
    double L1, L2;       // 振り子の長さ（ピクセル単位でも可）
    double theta1, theta2;  // 角度（ラジアン）
    double omega1, omega2;  // 角速度
    double g;            // 重力加速度

    // dt秒だけシミュレーションを進める
    virtual void step(double dt) override;

    // 現在の各振り子の位置（相対座標）を返す
    // （原点は振り子の固定点）
    void getPositions(double &x1, double &y1, double &x2, double &y2) const;
};

#endif // SIMULATION_H
