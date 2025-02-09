#include "simulationworker.h"
#include <QThread>
#include <QDebug>
#include <QElapsedTimer>

SimulationWorker::SimulationWorker(QObject *parent)
    : QObject(parent), m_running(true), m_dt(0.001)  // 初期 dt = 0.001秒
{
    m_simulation = new DoublePendulumSimulation(this);
}

SimulationWorker::~SimulationWorker()
{
    delete m_simulation;
}

// SimulationWorker::process() 内のループ例
void SimulationWorker::process()
{
    const int targetFrameTimeMs = 16; // 目標更新周期（ミリ秒）
    while (m_running) {
//        QElapsedTimer timer;
//        timer.start();

        // シミュレーションの更新（m_dt は dt の設定値）
        m_simulation->step(m_dt);
        double x1, y1, x2, y2;
        m_simulation->getPositions(x1, y1, x2, y2);
        emit simulationUpdated(x1, y1, x2, y2);

//        // ミリ秒ではなくナノ秒単位で経過時間を取得
//        qint64 elapsedNs = timer.nsecsElapsed();
//        // targetFrameTimeMs をナノ秒に換算（1ms = 1,000,000ns）
//        qint64 targetFrameTimeNs = targetFrameTimeMs * 1000000LL;
//        qint64 remainingNs = targetFrameTimeNs - elapsedNs;
//        // デバッグ出力：remainingNs をコンソールに出力
//        qDebug() << "Remaining ns:" << remainingNs;
        QThread::usleep(5);
//        if (remainingNs > 0) {
//            // マイクロ秒に変換（1μs = 1000ns）
//            qint64 sleepTimeUs = remainingNs / 1000;
//            QThread::usleep(static_cast<unsigned long>(sleepTimeUs));
//        }
        // remainingNs <= 0 の場合は、処理時間が目標を超えているのでそのまま次のループへ
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
