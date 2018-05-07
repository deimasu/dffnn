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
    void on_reset_button_clicked();
    void on_step_button_clicked();
    void on_data_combobox_currentTextChanged(const QString &arg1);

    void on_groupBox_clicked();

private:
    void mousePressEvent(QMouseEvent *event);
    void UpdateTrainingSet();
    void UpdateHeatmap();
    void Reset();
    QLineSeries *series;
    Ui::MainWindow *ui;
    NeuralNetwork *network;
    QTimer *timer;
    float value;
    int r, g, b;
    bool playing = false;
    bool setup_finished = false;
};

#endif
