#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <neuralnetwork.h>
#include <vector>
#include <QtCharts>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    QImage *image;
    QImage *image_points;
    ~MainWindow();

private slots:
    void TrainAndUpdate();
    void on_play_button_clicked();
    void on_pause_button_clicked();
    void on_reset_button_clicked();

private:
    void UpdateTrainingSet(std::vector<TrainingSample> tr_set);
    void UpdateHeatmap();
    QLineSeries *series;
    Ui::MainWindow *ui;
    NeuralNetwork *network;
    QTimer *timer;
    float value;
    int r, g, b;
};

#endif // MAINWINDOW_H
