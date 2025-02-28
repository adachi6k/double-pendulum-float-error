#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include "simulation.h" // DoublePendulumSimulation を含む
#include <QPoint>
#include <QVector>
#include <QWidget>

class SimulationWidget : public QWidget {
    Q_OBJECT
  public:
    explicit SimulationWidget(SimulationInterface *model,
                              QWidget *parent = nullptr);
    ~SimulationWidget();

  public slots:
    // グローバルタイマーから呼ばれて、1ステップ分の更新を行う
    void doStep();

  protected:
    void paintEvent(QPaintEvent *event) override;

  private:
    // シミュレーションオブジェクト（各モデル固有の状態を保持）
    SimulationInterface *m_simulation;
    // シミュレーション上の時間刻み
    double m_dt;

    // 描画用の最新の位置
    double m_x1, m_y1, m_x2, m_y2;
    // 軌跡用の点を保持
    QVector<QPoint> m_tracePoints;
};

#endif // SIMULATIONWIDGET_H
