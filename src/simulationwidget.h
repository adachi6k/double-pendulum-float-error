#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include <QWidget>

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

    // 描画用の現在の位置
    double m_x1, m_y1, m_x2, m_y2;
};

#endif // SIMULATIONWIDGET_H
