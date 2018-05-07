#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <trainingdata.cpp>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // fill data type combo-box
    ui->data_combobox->addItem("Gaussian");
    ui->data_combobox->addItem("Exclusive Or");
    ui->data_combobox->addItem("Circle");
    ui->data_combobox->addItem("User Defined");

    // fill color combo-box for user devined mode and making it invisible
    ui->color_combobox->addItem("Red");
    ui->color_combobox->addItem("Blue");
    ui->color_combobox->setVisible(false);

    ui->flush_button->setVisible(false);

    // heatmap image
    image = new QImage(100, 100, QImage::Format_RGB32);

    // image for points displaying
    image_points = new QImage(ui->points_label->width(), ui->points_label->height(), QImage::Format_RGBA8888);

    // series for training loss graph
    series = new QLineSeries();

    // creating neural network instance
    network = new NeuralNetwork({ 2, 5, 5, 1 });

    // adding blur effect to heatmap label
    QGraphicsBlurEffect *blur = new QGraphicsBlurEffect();
    blur->setBlurRadius(4);
    ui->heatmap_label->setGraphicsEffect(blur);

    // now on_data_combobox_currentTextChanged
    setup_finished = true;

    // display training set
    UpdateTrainingSet();

    // setting up timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TrainAndUpdate()));

    // displaying the first state of heatmap when network's weights are random
    UpdateHeatmap();
}

void MainWindow::TrainAndUpdate()
{
    network->Train();
    UpdateHeatmap();
}

// draws the heatmap and then updating epoch number
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

// draws training set according to currently selected data type
void MainWindow::UpdateTrainingSet()
{
    QString selected = ui->data_combobox->currentText();
    std::vector<TrainingSample> set;

    if (selected == "Gaussian")
    {
        set = gaussian_data;
    }
    else if (selected == "Exclusive Or")
    {
        set = exclusive_or_data;
    }
    else if (selected == "Circle")
    {
        set = circle_data;
    }

    for (const auto& sample : set)
    {
        network->AddTrainingSample(sample);
    }

    image_points->fill(Qt::transparent);

    QPainter p(image_points);

    QPen pen(Qt::white);
    p.setPen(pen);

    p.fillRect(image_points->rect(), QColor(0, 0, 0, 0));

    int x, y, radius = 3;

    for (const auto& sample : network->training_set)
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

void MainWindow::on_points_label_clicked(QMouseEvent *event)
{
    if (!user_definition) return;

    int local_x = event->x();
    int local_y = event->y();

    float point_x = (float)local_x / ui->points_label->width();
    float point_y = 1 - (float)local_y / ui->points_label->height();

    network->AddTrainingSample({ { point_x, point_y },
                                 ui->color_combobox->currentText() == "Red" ? 1.0f : -1.0f });

    UpdateTrainingSet();
}

void MainWindow::on_play_button_clicked()
{
    if (!playing)
    {
        timer->start();
        ui->play_button->setText("Pause");
    }
    else
    {
        timer->stop();
        ui->play_button->setText("Play");
    }

    playing = !playing;
}

void MainWindow::Reset(bool save_tr_set = false)
{
    if (!setup_finished) return;

    std::vector<TrainingSample> saved_set;

    if (save_tr_set)
    {
        saved_set = network->training_set;
    }

    delete network;

    playing = false;
    ui->play_button->setText("Play");

    timer->stop();
    network = new NeuralNetwork({ 2, 5, 5, 1 });

    if (save_tr_set)
    {
        for (const auto& sample : saved_set)
        {
            network->AddTrainingSample(sample);
        }
    }

    UpdateTrainingSet();

    UpdateHeatmap();
}


void MainWindow::on_reset_button_clicked()
{
    Reset(user_definition);
}

void MainWindow::on_step_button_clicked()
{
    timer->stop();
    playing = false;
    ui->play_button->setText("Play");
    TrainAndUpdate();
}

void MainWindow::on_data_combobox_currentTextChanged(const QString &combo_text)
{
    user_definition = combo_text == "User Defined";
    ui->color_combobox->setVisible(user_definition);
    ui->flush_button->setVisible(user_definition);
    Reset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_flush_button_clicked()
{
    Reset();
}
