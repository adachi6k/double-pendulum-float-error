#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include <QWidget>
#include <QVector>
#include <QPoint>

class QThread;
class SimulationWorker;

class SimulationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SimulationWidget(QWidget *parent = nullptr);
    ~SimulationWidget();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onSimulationUpdated(double x1, double y1, double x2, double y2);

private:
    QThread *m_simThread;
    SimulationWorker *m_worker;

    // 現在の振り子の位置（描画用）
    double m_x1, m_y1, m_x2, m_y2;

    // 青いボールの軌跡を保持するためのリスト
    QVector<QPoint> m_tracePoints;
};

#endif // SIMULATIONWIDGET_H
