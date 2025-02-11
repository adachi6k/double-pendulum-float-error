#include "mainwindow.h"
#include "simulationwidget.h"
#include <QHBoxLayout>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);

    // 各シミュレーションモデルを作成して差し替える
    SimulationInterface *model1 = new StandardDoublePendulumSimulation(this);
    SimulationInterface *model2 = new AlternativeDoublePendulumSimulation(this);
    SimulationInterface *model3 = new ThirdDoublePendulumSimulation(this);

    SimulationWidget *sim1 = new SimulationWidget(model1, this);
    SimulationWidget *sim2 = new SimulationWidget(model2, this);
    SimulationWidget *sim3 = new SimulationWidget(model3, this);


    layout->addWidget(sim1);
    layout->addWidget(sim2);
    layout->addWidget(sim3);
    setLayout(layout);

    // 全体の最低サイズを設定
    setMinimumSize(1200, 400);

    // グローバルタイマー（例：16ms間隔＝約60FPS）
    QTimer *syncTimer = new QTimer(this);
    syncTimer->setInterval(16);
    connect(syncTimer, &QTimer::timeout, this, [=](){
        // 1周期で複数ステップ更新（例：5ステップ分更新）
        const int stepsPerTick = 50;
        for (int i = 0; i < stepsPerTick; i++) {
            sim1->doStep();
            sim2->doStep();
            sim3->doStep();
        }
    });
    syncTimer->start();
}

MainWindow::~MainWindow()
{
}
