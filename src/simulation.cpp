// simulation.cpp
#include "simulation.h"
#include <cmath>
#include <cfenv>

// --- StandardDoublePendulumSimulation Implementation ---

StandardDoublePendulumSimulation::StandardDoublePendulumSimulation(QObject *parent)
    : SimulationInterface(parent),
      m1(1.0), m2(1.0),
      L1(100.0), L2(100.0),
      theta1(M_PI/2), theta2(M_PI/2),
      omega1(0.0), omega2(0.0),
      g(9.81)
{
}

void StandardDoublePendulumSimulation::step(double dt)
{
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
    omega1 += a1 * dt;
    omega2 += a2 * dt;
    theta1 += omega1 * dt;
    theta2 += omega2 * dt;
    emit simulationUpdated();
}

void StandardDoublePendulumSimulation::getPositions(double &x1, double &y1, double &x2, double &y2) const
{
    x1 = L1 * sin(theta1);
    y1 = L1 * cos(theta1);
    x2 = x1 + L2 * sin(theta2);
    y2 = y1 + L2 * cos(theta2);
}

QString StandardDoublePendulumSimulation::modelName() const { return "Standard Model"; }

// --- AlternativeDoublePendulumSimulation Implementation ---
// 代替モデルでは、例として重力を高め、丸めモードを FE_UPWARD に変更しています。

AlternativeDoublePendulumSimulation::AlternativeDoublePendulumSimulation(QObject *parent)
    : SimulationInterface(parent),
      m1(1.0), m2(1.0),
      L1(100.0), L2(100.0),
      theta1(M_PI/2), theta2(M_PI/2),
      omega1(0.0), omega2(0.0),
      g(12.0) // 標準より大きい重力
{
}

void AlternativeDoublePendulumSimulation::step(double dt)
{
    // 丸めモードを一時変更（FE_UPWARD: 上向き丸め）
    int old_round = fegetround();
    fesetround(FE_UPWARD);

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
    omega1 += a1 * dt;
    omega2 += a2 * dt;
    theta1 += omega1 * dt;
    theta2 += omega2 * dt;

    fesetround(old_round);
    emit simulationUpdated();
}

void AlternativeDoublePendulumSimulation::getPositions(double &x1, double &y1, double &x2, double &y2) const
{
    x1 = L1 * sin(theta1);
    y1 = L1 * cos(theta1);
    x2 = x1 + L2 * sin(theta2);
    y2 = y1 + L2 * cos(theta2);
}

QString AlternativeDoublePendulumSimulation::modelName() const { return "Alternative Model"; }

// --- ThirdDoublePendulumSimulation Implementation ---
// 3 番目のモデルとして、パラメータを若干変更した例です。

ThirdDoublePendulumSimulation::ThirdDoublePendulumSimulation(QObject *parent)
    : SimulationInterface(parent),
      m1(1.2), m2(0.8),
      L1(110.0), L2(90.0),
      theta1(M_PI/3), theta2(M_PI/3),
      omega1(0.0), omega2(0.0),
      g(9.81)
{
}

void ThirdDoublePendulumSimulation::step(double dt)
{
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
    omega1 += a1 * dt;
    omega2 += a2 * dt;
    theta1 += omega1 * dt;
    theta2 += omega2 * dt;
    emit simulationUpdated();
}

void ThirdDoublePendulumSimulation::getPositions(double &x1, double &y1, double &x2, double &y2) const
{
    x1 = L1 * sin(theta1);
    y1 = L1 * cos(theta1);
    x2 = x1 + L2 * sin(theta2);
    y2 = y1 + L2 * cos(theta2);
}

QString ThirdDoublePendulumSimulation::modelName() const { return "Third Model"; }