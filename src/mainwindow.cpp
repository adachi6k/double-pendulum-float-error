#include "mainwindow.h"
#include "simulationworker.h"
#include <QThread>
#include <QPainter>
#include <QPaintEvent>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      m_x1(0), m_y1(0), m_x2(0), m_y2(0)
{
    setMinimumSize(400, 400);

    // シミュレーションワーカーと専用スレッドの生成
    m_worker = new SimulationWorker();
    m_simThread = new QThread(this);
    m_worker->moveToThread(m_simThread);

    // スレッド開始時にシミュレーション処理開始
    connect(m_simThread, &QThread::started, m_worker, &SimulationWorker::process);
    // シミュレーションから位置データを受け取って更新
    connect(m_worker, &SimulationWorker::simulationUpdated,
            this, &MainWindow::onSimulationUpdated);
    // ウィンドウ破棄時にシミュレーション停止とスレッド終了
    connect(this, &QWidget::destroyed, m_worker, &SimulationWorker::stop);
    connect(this, &QWidget::destroyed, m_simThread, &QThread::quit);

    m_simThread->start();
}

MainWindow::~MainWindow()
{
    m_simThread->quit();
    m_simThread->wait();
    // m_worker は親により自動削除（必要に応じて明示的に削除してください）
}

void MainWindow::onSimulationUpdated(double x1, double y1, double x2, double y2)
{
    // 受け取ったシミュレーション結果をメンバ変数に保存し、再描画を要求
    m_x1 = x1;
    m_y1 = y1;
    m_x2 = x2;
    m_y2 = y2;
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 振り子の固定点（ピボット）はウィンドウ上部中央に配置
    int pivotX = width() / 2;
    int pivotY = 50;

    // シミュレーション結果（相対座標）をウィジェット座標に変換
    int x1Pix = pivotX + static_cast<int>(m_x1);
    int y1Pix = pivotY + static_cast<int>(m_y1);
    int x2Pix = pivotX + static_cast<int>(m_x2);
    int y2Pix = pivotY + static_cast<int>(m_y2);

    // 振り子のアームの描画
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(pivotX, pivotY, x1Pix, y1Pix);
    painter.drawLine(x1Pix, y1Pix, x2Pix, y2Pix);

    // 各質点（振り子部分）の描画
    int radius = 10;
    painter.setBrush(Qt::red);
    painter.drawEllipse(QPoint(x1Pix, y1Pix), radius, radius);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(QPoint(x2Pix, y2Pix), radius, radius);

    // 固定点（ピボット）の描画
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(pivotX, pivotY), 5, 5);
}
