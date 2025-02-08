#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QThread;
class SimulationWorker;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    // シミュレーションからの更新信号を受け取るスロット
    void onSimulationUpdated(double x1, double y1, double x2, double y2);

private:
    QThread *m_simThread;
    SimulationWorker *m_worker;

    // 現在の振り子の位置（描画用）
    double m_x1, m_y1, m_x2, m_y2;
};

#endif // MAINWINDOW_H
