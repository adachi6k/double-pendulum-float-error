#include "simulationworker.h"
#include "simulation.h"
#include <QThread>
#include <QDebug>
#include <QElapsedTimer>

SimulationWorker::SimulationWorker(QObject *parent)
    : QObject(parent), m_running(true), m_dt(0.001)  // 初期 dt = 0.001秒
{
    m_simulation = new StandardDoublePendulumSimulation(this);
}

SimulationWorker::~SimulationWorker()
{
    delete m_simulation;
}

// SimulationWorker::process() 内のループ例
void SimulationWorker::process()
{
    const int targetFrameTimeMs = 16; // 目標更新周期（ミリ秒）
    int updateCounter = 0;
    const int updateInterval = 10; // 10回に1回更新信号を送る    
    while (m_running) {
//        QElapsedTimer timer;
//        timer.start();

        // シミュレーションの更新（m_dt は dt の設定値）
        m_simulation->step(m_dt);

        updateCounter++;
        if (updateCounter >= updateInterval) {
            double x1, y1, x2, y2;
            m_simulation->getPositions(x1, y1, x2, y2);
            emit simulationUpdated(x1, y1, x2, y2);
            updateCounter = 0;
        }
        QThread::usleep(5);
    }
}


void SimulationWorker::stop()
{
    m_running = false;
}

void SimulationWorker::setSpeed(int speedFactor)
{
    // ここでは、スライダーの値 100 を基準に dt = 0.005秒とします。
    // つまり、200 なら dt = 0.010秒（2倍速）、50 なら dt = 0.0025秒（半分の速度）になります。
    m_dt = 0.005 * (static_cast<double>(speedFactor) / 100.0);
    qDebug() << "Simulation dt set to:" << m_dt << " (speed factor:" << speedFactor << ")";
}
