#ifndef SIMULATION_INTERFACE_H
#define SIMULATION_INTERFACE_H

#include <QObject>

class SimulationInterface : public QObject {
    Q_OBJECT
public:
    explicit SimulationInterface(QObject *parent = nullptr) : QObject(parent) {}
    virtual ~SimulationInterface();  // 非インライン宣言にする

    // dt秒だけシミュレーションを進める
    virtual void step(double dt) = 0;
    // 現在の振り子の位置を返す
    virtual void getPositions(double &x1, double &y1, double &x2, double &y2) const = 0;

signals:
    void simulationUpdated();
};

#endif // SIMULATION_INTERFACE_H
