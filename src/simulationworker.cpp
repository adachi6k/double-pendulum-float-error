#include "simulationworker.h"
#include <QThread>

SimulationWorker::SimulationWorker(QObject *parent)
    : QObject(parent), m_running(true)
{
    m_simulation = new DoublePendulumSimulation(this);
}

SimulationWorker::~SimulationWorker()
{
    delete m_simulation;
}

void SimulationWorker::process()
{
    double dt = 0.001; // シミュレーション刻み幅（秒）
    while (m_running) {
        m_simulation->step(dt);
        double x1, y1, x2, y2;
        m_simulation->getPositions(x1, y1, x2, y2);
        emit simulationUpdated(x1, y1, x2, y2);
        // CPU負荷とタイミング調整のために短いスリープ（必要に応じて調整）
        QThread::msleep(1);
    }
}

void SimulationWorker::stop()
{
    m_running = false;
}
