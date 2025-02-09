#include "mainwindow.h"
#include "simulationwidget.h"
#include <QHBoxLayout>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    // ３つの SimulationWidget インスタンスを生成
    SimulationWidget *sim1 = new SimulationWidget(this);
    SimulationWidget *sim2 = new SimulationWidget(this);
    SimulationWidget *sim3 = new SimulationWidget(this);

    layout->addWidget(sim1);
    layout->addWidget(sim2);
    layout->addWidget(sim3);
    setLayout(layout);

    // メインウィンドウの最低サイズを設定
    setMinimumSize(1200, 400);

    // グローバルタイマー（例：16ms間隔＝約60FPS）で同期的に全モデルの doStep() を呼び出す
    QTimer *syncTimer = new QTimer(this);
    syncTimer->setInterval(16);
    connect(syncTimer, &QTimer::timeout, this, [=](){
        sim1->doStep();
        sim2->doStep();
        sim3->doStep();
    });
    syncTimer->start();
}

MainWindow::~MainWindow()
{
}
