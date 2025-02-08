#include "mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <QPaintEvent>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), dt(0.01)
{
    setMinimumSize(400, 400);

    // シミュレーションオブジェクトの生成
    simulation = new DoublePendulumSimulation(this);
    // （必要に応じてシグナルとスロットで連携可能）
    connect(simulation, &DoublePendulumSimulation::simulationUpdated, this, QOverload<>::of(&MainWindow::update));

    // タイマーを使い、定期的にシミュレーションを更新する
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSimulation);
    timer->start(1); // 1ミリ秒間隔で更新（約10fps）
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateSimulation()
{
    simulation->step(dt);
    // シミュレーション更新後、ウィジェットの再描画を要求
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 振り子の固定点（ピボット）はウィジェット上部中央に配置
    int pivotX = width() / 2;
    int pivotY = 50;

    // シミュレーションから現在の振り子の相対座標を取得
    double x1, y1, x2, y2;
    simulation->getPositions(x1, y1, x2, y2);

    // シミュレーション座標をウィジェット座標に変換
    int x1Pix = pivotX + static_cast<int>(x1);
    int y1Pix = pivotY + static_cast<int>(y1);
    int x2Pix = pivotX + static_cast<int>(x2);
    int y2Pix = pivotY + static_cast<int>(y2);

    // 振り子のアームを描画
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(pivotX, pivotY, x1Pix, y1Pix);
    painter.drawLine(x1Pix, y1Pix, x2Pix, y2Pix);

    // 各振り子（質点）の描画
    int radius = 10;
    painter.setBrush(Qt::red);
    painter.drawEllipse(QPoint(x1Pix, y1Pix), radius, radius);
    painter.setBrush(Qt::blue);
    painter.drawEllipse(QPoint(x2Pix, y2Pix), radius, radius);

    // 固定点（ピボット）の描画
    painter.setBrush(Qt::black);
    painter.drawEllipse(QPoint(pivotX, pivotY), 5, 5);
}
