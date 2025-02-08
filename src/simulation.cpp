#include "simulation.h"

DoublePendulumSimulation::DoublePendulumSimulation(QObject *parent)
    : SimulationInterface(parent),
      m1(1.0), m2(1.0),
      L1(100.0), L2(100.0),
      theta1(M_PI / 2), theta2(M_PI / 2),
      omega1(0.0), omega2(0.0),
      g(9.81)
{
}

void DoublePendulumSimulation::step(double dt)
{
    // 2重振り子の角加速度の計算（一般的な式の一例）
    double denominator = 2 * m1 + m2 - m2 * cos(2 * theta1 - 2 * theta2);

    double a1 = (-g * (2 * m1 + m2) * sin(theta1)
                 - m2 * g * sin(theta1 - 2 * theta2)
                 - 2 * sin(theta1 - theta2) * m2 *
                   (omega2 * omega2 * L2 + omega1 * omega1 * L1 * cos(theta1 - theta2)))
                / (L1 * denominator);

    double a2 = (2 * sin(theta1 - theta2) *
                 (omega1 * omega1 * L1 * (m1 + m2)
                  + g * (m1 + m2) * cos(theta1)
                  + omega2 * omega2 * L2 * m2 * cos(theta1 - theta2)))
                / (L2 * denominator);

    // Euler法による更新
    omega1 += a1 * dt;
    omega2 += a2 * dt;
    theta1 += omega1 * dt;
    theta2 += omega2 * dt;

    emit simulationUpdated();
}

void DoublePendulumSimulation::getPositions(double &x1, double &y1, double &x2, double &y2) const
{
    x1 = L1 * sin(theta1);
    y1 = L1 * cos(theta1);
    x2 = x1 + L2 * sin(theta2);
    y2 = y1 + L2 * cos(theta2);
}
