#ifndef SIMULATION_H
#define SIMULATION_H

#include "simulation_interface.h"  // SimulationInterface を定義したファイル
#include <cmath>

// --- Standard Model ---
class StandardDoublePendulumSimulation : public SimulationInterface {
    Q_OBJECT
public:
    explicit StandardDoublePendulumSimulation(QObject *parent = nullptr);
    virtual void step(double dt) override;
    virtual void getPositions(double &x1, double &y1, double &x2, double &y2) const override;
    virtual QString modelName() const override;

    double m1, m2, L1, L2, theta1, theta2, omega1, omega2, g;
};

// --- Alternative Model ---
class AlternativeDoublePendulumSimulation : public SimulationInterface {
    Q_OBJECT
public:
    explicit AlternativeDoublePendulumSimulation(QObject *parent = nullptr);
    virtual void step(double dt) override;
    virtual void getPositions(double &x1, double &y1, double &x2, double &y2) const override;
    virtual QString modelName() const override;

    double m1, m2, L1, L2, theta1, theta2, omega1, omega2, g;
};

// --- Third Model ---
class ThirdDoublePendulumSimulation : public SimulationInterface {
    Q_OBJECT
public:
    explicit ThirdDoublePendulumSimulation(QObject *parent = nullptr);
    virtual void step(double dt) override;
    virtual void getPositions(double &x1, double &y1, double &x2, double &y2) const override;
    virtual QString modelName() const override;

    double m1, m2, L1, L2, theta1, theta2, omega1, omega2, g;
};

#endif // SIMULATION_H
