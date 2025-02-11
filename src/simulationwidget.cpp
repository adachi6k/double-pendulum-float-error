#include "simulationwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

SimulationWidget::SimulationWidget(SimulationInterface *model, QWidget *parent)
    : QWidget(parent),
      m_dt(0.005), // dt の初期値（必要に応じて調整）
      m_x1(0), m_y1(0), m_x2(0), m_y2(0),
      m_simulation(model)
{
    setMinimumSize(600, 300);
}

SimulationWidget::~SimulationWidget()
{
    delete m_simulation;
}

void SimulationWidget::doStep()
{
    // 同じ dt でシミュレーションを更新
    m_simulation->step(m_dt);
    m_simulation->getPositions(m_x1, m_y1, m_x2, m_y2);

    // 軌跡の更新（質点2、青いボールの位置を例に）
    int pivotX = width() / 2;
    int pivotY = 50;
    int ballX = pivotX + static_cast<int>(m_x2);
    int ballY = pivotY + static_cast<int>(m_y2);
    m_tracePoints.append(QPoint(ballX, ballY));

    // 軌跡の点数制限（例：最大10000点）
    const int maxTracePoints = 100000;
    if (m_tracePoints.size() > maxTracePoints)
        m_tracePoints.remove(0, m_tracePoints.size() - maxTracePoints);

    update();
}

void SimulationWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int pivotX = width() / 2;
    int pivotY = 50;

    // 軌跡の描画：薄いグレー（例：RGB(180, 180, 180) でアルファ値100）
    if (!m_tracePoints.isEmpty()) {
        QPen tracePen(QColor(180, 180, 180, 100));
        tracePen.setWidth(1);
        painter.setPen(tracePen);
        painter.drawPolyline(m_tracePoints.data(), m_tracePoints.size());
    }

    // 振り子の各位置をウィジェット座標に変換
    int x1Pix = pivotX + static_cast<int>(m_x1);
    int y1Pix = pivotY + static_cast<int>(m_y1);
    int x2Pix = pivotX + static_cast<int>(m_x2);
    int y2Pix = pivotY + static_cast<int>(m_y2);

    // 振り子のアームを描画
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
