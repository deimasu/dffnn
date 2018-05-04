#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <ctime>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // heatmap image
    image = new QImage(100, 100, QImage::Format_RGB32);

    image_points = new QImage(ui->points_label->width(), ui->points_label->height(), QImage::Format_RGBA8888);

    // series for training loss graph
    series = new QLineSeries();

    // creating neural network instance
    network = new NeuralNetwork({ 2, 5, 5, 1 });

    // adding blur effect to heatmap label
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
    blur->setBlurRadius(4);
    ui->heatmap_label->setGraphicsEffect(blur);

    std::vector<TrainingSample> data2 =
        {
            { { 0.41f, 0.55f }, -1.0f },
            { {0.42f, 0.55f }, -1.0f},
            { {0.44f, 0.59f }, -1.0f},
            { {0.47f, 0.63f }, -1.0f},
            { {0.53f, 0.64f }, -1.0f},
            { {0.56f, 0.62f }, -1.0f},
            { {0.59f, 0.57f }, -1.0f},
            { {0.6f, 0.54f }, -1.0f},
            { {0.60f, 0.47f }, -1.0f},
            { {0.60f, 0.42f }, -1.0f},
            { {0.56f, 0.35f }, -1.0f},
            { {0.5f, 0.34f }, -1.0f},
            { {0.44f, 0.34f }, -1.0f},
            { {0.37f, 0.36f }, -1.0f},
            { {0.38f, 0.4f }, -1.0f},
            { {0.44f, 0.40f }, -1.0f},
            { {0.48f, 0.41f }, -1.0f},
            { {0.54f, 0.41f }, -1.0f},
            { {0.55f, 0.41f }, -1.0f},
            { {0.57f, 0.48f }, -1.0f},
            { {0.52f, 0.51f }, -1.0f},
            { {0.47f, 0.49f }, -1.0f},
            { {0.41f, 0.54f }, -1.0f},
            { {0.48f, 0.55f }, -1.0f},
            { {0.49f, 0.51f }, -1.0f},
            { {0.44f, 0.50f }, -1.0f},
            { {0.43f, 0.50f }, -1.0f},
            { {0.41f, 0.43f }, -1.0f},
            { {0.46f, 0.43f }, -1.0f},
            { {0.47f, 0.46f }, -1.0f},
            { {0.51f, 0.47f }, -1.0f},
            { {0.57f, 0.50f }, -1.0f},
            { {0.58f, 0.54f }, -1.0f},
            { {0.62f, 0.47f }, -1.0f},
            { {0.61f, 0.4f }, -1.0f},
            { {0.48f, 0.35f }, -1.0f},
            { {0.48f, 0.40f }, -1.0f},
            { {0.53f, 0.44f }, -1.0f},
            { {0.57f, 0.4f }, -1.0f},
            { {0.61f, 0.49f }, -1.0f},
            { {0.60f, 0.53f }, -1.0f},
            { {0.55f, 0.58f }, -1.0f},
            { {0.54f, 0.58f }, -1.0f},
            { {0.51f, 0.58f }, -1.0f},
            { {0.44f, 0.57f }, -1.0f},
            { {0.42f, 0.49f }, -1.0f},
            { {0.42f, 0.44f }, -1.0f},
            { {0.46f, 0.40f }, -1.0f},
            { {0.53f, 0.40f }, -1.0f},


            { { 0.15f, 0.31f }, 1.0f },
            { {0.18f, 0.21f }, 1.0f},
            { {0.23f, 0.16f }, 1.0f},
            { {0.29f, 0.13f }, 1.0f},
            { {0.36f, 0.13f }, 1.0f},
            { {0.44f, 0.13f }, 1.0f},
            { {0.49f, 0.12f }, 1.0f},
            { {0.53f, 0.11f }, 1.0f},
            { {0.58f, 0.13f }, 1.0f},
            { {0.64f, 0.16f }, 1.0f},
            { {0.76f, 0.2f }, 1.0f},
            { {0.78f, 0.27f }, 1.0f},
            { {0.82f, 0.46f }, 1.0f},
            { {0.86f, 0.56f }, 1.0f},
            { {0.81f, 0.72f }, 1.0f},
            { {0.75f, 0.78f }, 1.0f},
            { {0.69f, 0.79f }, 1.0f},
            { {0.50f, 0.86f }, 1.0f},
            { {0.37f, 0.86f }, 1.0f},
            { {0.29f, 0.85f }, 1.0f},
            { {0.19f, 0.79f }, 1.0f},
            { {0.13f, 0.71f }, 1.0f},
            { {0.21f, 0.70f }, 1.0f},
            { {0.33f, 0.77f }, 1.0f},
            { {0.50f, 0.79f }, 1.0f},
            { {0.62f, 0.79f }, 1.0f},
            { {0.66f, 0.76f }, 1.0f},
            { {0.74f, 0.65f }, 1.0f},
            { {0.75f, 0.60f }, 1.0f},
            { {0.74f, 0.49f }, 1.0f},
            { {0.76f, 0.46f }, 1.0f},
            { {0.77f, 0.42f }, 1.0f},
            { {0.75f, 0.33f }, 1.0f},
            { {0.69f, 0.28f }, 1.0f},
            { {0.67f, 0.19f }, 1.0f},
            { {0.48f, 0.12f }, 1.0f},
            { {0.38f, 0.15f }, 1.0f},
            { {0.24f, 0.23f }, 1.0f},
            { {0.17f, 0.27f }, 1.0f},
            { {0.17f, 0.29f }, 1.0f},
            { {0.22f, 0.36f }, 1.0f},
            { {0.14f, 0.53f }, 1.0f},
            { {0.17f, 0.59f }, 1.0f},
            { {0.18f, 0.61f }, 1.0f},
            { {0.21f, 0.71f }, 1.0f},
            { {0.26f, 0.75f }, 1.0f},
            { {0.43f, 0.79f }, 1.0f},
            { {0.48f, 0.75f }, 1.0f},
            { {0.59f, 0.78f }, 1.0f},
            { {0.64f, 0.79f }, 1.0f},
            { {0.66f, 0.69f }, 1.0f},
            { {0.72f, 0.66f }, 1.0f},
            { {0.78f, 0.64f }, 1.0f},
            { {0.81f, 0.57f }, 1.0f},
            { {0.75f, 0.50f }, 1.0f},
            { {0.74f, 0.48f }, 1.0f},
            { {0.79f, 0.41f }, 1.0f},
            { {0.79f, 0.36f }, 1.0f},
            { {0.66f, 0.26f }, 1.0f},
            { {0.53f, 0.23f }, 1.0f},
            { {0.33f, 0.19f }, 1.0f},
            { {0.30f, 0.17f }, 1.0f},
            { {0.21f, 0.31f }, 1.0f},
            { {0.21f, 0.40f }, 1.0f},
            { {0.24f, 0.51f }, 1.0f},
            { {0.23f, 0.6f }, 1.0f},
            { {0.31f, 0.72f }, 1.0f},
            { {0.44f, 0.78f }, 1.0f},
            { {0.60f, 0.80f }, 1.0f},
            { {0.69f, 0.75f }, 1.0f},
            { {0.75f, 0.71f }, 1.0f},
        };

    UpdateTrainingSet(data2);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TrainAndUpdate()));

    UpdateHeatmap();


}

void MainWindow::TrainAndUpdate()
{
    network->Train();
    UpdateHeatmap();
}

void MainWindow::UpdateHeatmap()
{
    series->append(network->epoch, network->loss);

    for (int y = 0 ; y < image->height(); y++)
    {
        for (int x = 0; x < image->width(); x++)
        {
            value = network->Process({ (float)x / image->width(), 1.0f - (float)y / image->height() });

            g = (1 - std::abs(value)) * 255;

            if (value > 0)
            {
                r = 255;
                b = g;
            }
            else
            {
                b = 255;
                r = g;
            }

            image->setPixelColor(x, y, QColor::fromRgb(r, g, b));
        }
    }

    ui->heatmap_label->setPixmap(QPixmap::fromImage(*image).scaled(ui->heatmap_label->width(), ui->heatmap_label->height(), Qt::KeepAspectRatio));
    ui->epoch_label_count->setText(QString::number(network->epoch));
}

void MainWindow::UpdateTrainingSet(std::vector<TrainingSample> tr_set)
{
    for (const auto& sample : tr_set)
    {
        network->AddTrainingSample(sample);
    }

    QPainter p(image_points);

    QPen pen(Qt::white);
    p.setPen(pen);

    p.fillRect(image_points->rect(), QColor(0, 0, 0, 0));

    int x, y, radius = 3;

    for (const auto& sample : tr_set)
    {
        x = sample.inputs[0] * image_points->width();
        y = (1 - sample.inputs[1]) * image_points->height();

        QBrush brush(sample.output > 0 ? QColor::fromRgb(255, 187, 0) : QColor::fromRgb(0, 153, 255));
        p.setBrush(brush);

        QRectF rect(x - radius, y - radius, radius * 2, radius * 2);
        p.drawEllipse(rect);
    }

    ui->points_label->setPixmap(QPixmap::fromImage(*image_points).scaled(ui->points_label->width(), ui->points_label->height(), Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_play_button_clicked()
{
    timer->start();
}

void MainWindow::on_pause_button_clicked()
{
    timer->stop();
}

void MainWindow::on_reset_button_clicked()
{
    delete network;

    timer->stop();
    network = new NeuralNetwork({ 2, 5, 5, 1 });

    std::vector<TrainingSample> data2 =
        {
            { { 0.41f, 0.55f }, -1.0f },
            { {0.42f, 0.55f }, -1.0f},
            { {0.44f, 0.59f }, -1.0f},
            { {0.47f, 0.63f }, -1.0f},
            { {0.53f, 0.64f }, -1.0f},
            { {0.56f, 0.62f }, -1.0f},
            { {0.59f, 0.57f }, -1.0f},
            { {0.6f, 0.54f }, -1.0f},
            { {0.60f, 0.47f }, -1.0f},
            { {0.60f, 0.42f }, -1.0f},
            { {0.56f, 0.35f }, -1.0f},
            { {0.5f, 0.34f }, -1.0f},
            { {0.44f, 0.34f }, -1.0f},
            { {0.37f, 0.36f }, -1.0f},
            { {0.38f, 0.4f }, -1.0f},
            { {0.44f, 0.40f }, -1.0f},
            { {0.48f, 0.41f }, -1.0f},
            { {0.54f, 0.41f }, -1.0f},
            { {0.55f, 0.41f }, -1.0f},
            { {0.57f, 0.48f }, -1.0f},
            { {0.52f, 0.51f }, -1.0f},
            { {0.47f, 0.49f }, -1.0f},
            { {0.41f, 0.54f }, -1.0f},
            { {0.48f, 0.55f }, -1.0f},
            { {0.49f, 0.51f }, -1.0f},
            { {0.44f, 0.50f }, -1.0f},
            { {0.43f, 0.50f }, -1.0f},
            { {0.41f, 0.43f }, -1.0f},
            { {0.46f, 0.43f }, -1.0f},
            { {0.47f, 0.46f }, -1.0f},
            { {0.51f, 0.47f }, -1.0f},
            { {0.57f, 0.50f }, -1.0f},
            { {0.58f, 0.54f }, -1.0f},
            { {0.62f, 0.47f }, -1.0f},
            { {0.61f, 0.4f }, -1.0f},
            { {0.48f, 0.35f }, -1.0f},
            { {0.48f, 0.40f }, -1.0f},
            { {0.53f, 0.44f }, -1.0f},
            { {0.57f, 0.4f }, -1.0f},
            { {0.61f, 0.49f }, -1.0f},
            { {0.60f, 0.53f }, -1.0f},
            { {0.55f, 0.58f }, -1.0f},
            { {0.54f, 0.58f }, -1.0f},
            { {0.51f, 0.58f }, -1.0f},
            { {0.44f, 0.57f }, -1.0f},
            { {0.42f, 0.49f }, -1.0f},
            { {0.42f, 0.44f }, -1.0f},
            { {0.46f, 0.40f }, -1.0f},
            { {0.53f, 0.40f }, -1.0f},


            { { 0.15f, 0.31f }, 1.0f },
            { {0.18f, 0.21f }, 1.0f},
            { {0.23f, 0.16f }, 1.0f},
            { {0.29f, 0.13f }, 1.0f},
            { {0.36f, 0.13f }, 1.0f},
            { {0.44f, 0.13f }, 1.0f},
            { {0.49f, 0.12f }, 1.0f},
            { {0.53f, 0.11f }, 1.0f},
            { {0.58f, 0.13f }, 1.0f},
            { {0.64f, 0.16f }, 1.0f},
            { {0.76f, 0.2f }, 1.0f},
            { {0.78f, 0.27f }, 1.0f},
            { {0.82f, 0.46f }, 1.0f},
            { {0.86f, 0.56f }, 1.0f},
            { {0.81f, 0.72f }, 1.0f},
            { {0.75f, 0.78f }, 1.0f},
            { {0.69f, 0.79f }, 1.0f},
            { {0.50f, 0.86f }, 1.0f},
            { {0.37f, 0.86f }, 1.0f},
            { {0.29f, 0.85f }, 1.0f},
            { {0.19f, 0.79f }, 1.0f},
            { {0.13f, 0.71f }, 1.0f},
            { {0.21f, 0.70f }, 1.0f},
            { {0.33f, 0.77f }, 1.0f},
            { {0.50f, 0.79f }, 1.0f},
            { {0.62f, 0.79f }, 1.0f},
            { {0.66f, 0.76f }, 1.0f},
            { {0.74f, 0.65f }, 1.0f},
            { {0.75f, 0.60f }, 1.0f},
            { {0.74f, 0.49f }, 1.0f},
            { {0.76f, 0.46f }, 1.0f},
            { {0.77f, 0.42f }, 1.0f},
            { {0.75f, 0.33f }, 1.0f},
            { {0.69f, 0.28f }, 1.0f},
            { {0.67f, 0.19f }, 1.0f},
            { {0.48f, 0.12f }, 1.0f},
            { {0.38f, 0.15f }, 1.0f},
            { {0.24f, 0.23f }, 1.0f},
            { {0.17f, 0.27f }, 1.0f},
            { {0.17f, 0.29f }, 1.0f},
            { {0.22f, 0.36f }, 1.0f},
            { {0.14f, 0.53f }, 1.0f},
            { {0.17f, 0.59f }, 1.0f},
            { {0.18f, 0.61f }, 1.0f},
            { {0.21f, 0.71f }, 1.0f},
            { {0.26f, 0.75f }, 1.0f},
            { {0.43f, 0.79f }, 1.0f},
            { {0.48f, 0.75f }, 1.0f},
            { {0.59f, 0.78f }, 1.0f},
            { {0.64f, 0.79f }, 1.0f},
            { {0.66f, 0.69f }, 1.0f},
            { {0.72f, 0.66f }, 1.0f},
            { {0.78f, 0.64f }, 1.0f},
            { {0.81f, 0.57f }, 1.0f},
            { {0.75f, 0.50f }, 1.0f},
            { {0.74f, 0.48f }, 1.0f},
            { {0.79f, 0.41f }, 1.0f},
            { {0.79f, 0.36f }, 1.0f},
            { {0.66f, 0.26f }, 1.0f},
            { {0.53f, 0.23f }, 1.0f},
            { {0.33f, 0.19f }, 1.0f},
            { {0.30f, 0.17f }, 1.0f},
            { {0.21f, 0.31f }, 1.0f},
            { {0.21f, 0.40f }, 1.0f},
            { {0.24f, 0.51f }, 1.0f},
            { {0.23f, 0.6f }, 1.0f},
            { {0.31f, 0.72f }, 1.0f},
            { {0.44f, 0.78f }, 1.0f},
            { {0.60f, 0.80f }, 1.0f},
            { {0.69f, 0.75f }, 1.0f},
            { {0.75f, 0.71f }, 1.0f},
        };

    UpdateTrainingSet(data2);

    UpdateHeatmap();
}
