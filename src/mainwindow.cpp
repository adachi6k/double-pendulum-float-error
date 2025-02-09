#include "mainwindow.h"
#include "simulationwidget.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    // ３つのシミュレーションウィジェットを生成して横に配置
    SimulationWidget *sim1 = new SimulationWidget(this);
    SimulationWidget *sim2 = new SimulationWidget(this);
    SimulationWidget *sim3 = new SimulationWidget(this);

    layout->addWidget(sim1);
    layout->addWidget(sim2);
    layout->addWidget(sim3);

    setLayout(layout);

    // 全体の最低サイズを広く設定
    setMinimumSize(1200, 400);
}

MainWindow::~MainWindow()
{
}
