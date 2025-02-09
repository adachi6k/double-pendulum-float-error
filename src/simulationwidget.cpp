#include "simulationwidget.h"
#include "simulationworker.h"
#include <QThread>
#include <QPainter>
#include <QPaintEvent>

SimulationWidget::SimulationWidget(QWidget *parent)
    : QWidget(parent), m_x1(0), m_y1(0), m_x2(0), m_y2(0)
{
    setMinimumSize(600, 300);

    m_worker = new SimulationWorker();
    m_simThread = new QThread(this);
    m_worker->moveToThread(m_simThread);

    connect(m_simThread, &QThread::started, m_worker, &SimulationWorker::process);
    connect(m_worker, &SimulationWorker::simulationUpdated,
            this, &SimulationWidget::onSimulationUpdated);
    connect(this, &QWidget::destroyed, m_worker, &SimulationWorker::stop);
    connect(this, &QWidget::destroyed, m_simThread, &QThread::quit);

    m_simThread->start();
}

SimulationWidget::~SimulationWidget()
{
    m_simThread->quit();
    m_simThread->wait();
}

void SimulationWidget::onSimulationUpdated(double x1, double y1, double x2, double y2)
{
    m_x1 = x1; m_y1 = y1; m_x2 = x2; m_y2 = y2;
    
    // 青いボール（ここでは質点2）の現在のピクセル座標を計算
    int pivotX = width() / 2;
    int pivotY = 50;
    int ballX = pivotX + static_cast<int>(m_x2);
    int ballY = pivotY + static_cast<int>(m_y2);
    
    // 軌跡に追加
    m_tracePoints.append(QPoint(ballX, ballY));
    
    // 軌跡の点数が多くなりすぎないように、古い点を削除（ここでは最大500000点まで保持）
    const int maxTracePoints = 500000;
    if(m_tracePoints.size() > maxTracePoints)
    {
        m_tracePoints.remove(0, m_tracePoints.size() - maxTracePoints);
    }
    
    update();
}

void SimulationWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 固定点（ピボット）の位置（ウィジェット上部中央）
    int pivotX = width() / 2;
    int pivotY = 50;
    
    // 軌跡の描画（薄いグレー、半透明）
    if (!m_tracePoints.isEmpty()) {
//        QPen tracePen(QColor(211, 211, 211, 100)); // 薄いグレー
        QPen tracePen(QColor(180, 180, 180, 100)); // もう少し濃いグレー
        tracePen.setWidth(1);  // 線幅1
        painter.setPen(tracePen);
        painter.drawPolyline(m_tracePoints.data(), m_tracePoints.size());
    }
    
    // シミュレーション結果の変換
    int x1Pix = pivotX + static_cast<int>(m_x1);
    int y1Pix = pivotY + static_cast<int>(m_y1);
    int x2Pix = pivotX + static_cast<int>(m_x2);
    int y2Pix = pivotY + static_cast<int>(m_y2);

    // 振り子のアーム描画
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(pivotX, pivotY, x1Pix, y1Pix);
    painter.drawLine(x1Pix, y1Pix, x2Pix, y2Pix);

    // 質点の描画
    int radius = 10;
    painter.setBrush(Qt::red);
    painter.drawEllipse(QPoint(x1Pix, y1Pix), radius, radius);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(QPoint(x2Pix, y2Pix), radius, radius);

    // 固定点（ピボット）の描画
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(pivotX, pivotY), 5, 5);
}