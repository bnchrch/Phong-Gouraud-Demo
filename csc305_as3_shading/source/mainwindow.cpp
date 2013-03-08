#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    animationTimer(NULL)
{
    ui->setupUi(this);

    // we create a simple timer, with the widget being its parent
    animationTimer = new QTimer(this);
    // the timer will send a signal timeout at regular intervals.
    // whenever this timeout signal occurs, we want it to call our drawOpenGL
    // function
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(drawOpenGL()));
    // we start the timer with a timeout interval of 20ms
    animationTimer->start(20);

    connect(ui->oglwidget, SIGNAL(addedNewGeometry(std::string)), this, SLOT(newGeometryAdded(std::string)));
    connect(ui->oglwidget, SIGNAL(removedGeometry(std::string)), this, SLOT(geometryRemoved(std::string)));

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addGeometry()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(removeGeometry()));

    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->oglwidget->setOrtho(false);
    ui->oglwidget->setPostMultiply(false);
}

void MainWindow::drawOpenGL()
{
    // whenever drawOpenGL gets called, we only want to repaint our opengl widget
    ui->oglwidget->repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBox_toggled(bool checked)
{
    ui->oglwidget->setOrtho(checked);
}

void MainWindow::on_translateX_valueChanged(int value)
{
    float modifiedValue = (float)(value);

    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    QList<QListWidgetItem *>::iterator it = items.begin();

    while(it != items.end())
    {
        ui->oglwidget->translateX(modifiedValue, (*it)->text().toStdString());
        ++it;
    }
}

void MainWindow::on_translateY_valueChanged(int value)
{
    float modifiedValue = (float)(value);

    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    QList<QListWidgetItem *>::iterator it = items.begin();

    while(it != items.end())
    {
        ui->oglwidget->translateY(modifiedValue, (*it)->text().toStdString());
        ++it;
    }
}

void MainWindow::on_translateZ_valueChanged(int value)
{
    float modifiedValue = (float)(value);

    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    QList<QListWidgetItem *>::iterator it = items.begin();

    while(it != items.end())
    {
        ui->oglwidget->translateZ(modifiedValue, (*it)->text().toStdString());
        ++it;
    }
}

void MainWindow::on_rotateX_valueChanged(int value)
{
    float modifiedValue = ((float)value) * 360.0f / ((float)ui->rotateX->maximum() - (float)ui->rotateX->minimum());

    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    QList<QListWidgetItem *>::iterator it = items.begin();

    while(it != items.end())
    {
        ui->oglwidget->rotateX(modifiedValue, (*it)->text().toStdString());
        ++it;
    }
}

void MainWindow::on_rotateY_valueChanged(int value)
{
    float modifiedValue = ((float)value) * 360.0f / ((float)ui->rotateY->maximum() - (float)ui->rotateY->minimum());

    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    QList<QListWidgetItem *>::iterator it = items.begin();

    while(it != items.end())
    {
        ui->oglwidget->rotateY(modifiedValue, (*it)->text().toStdString());
        ++it;
    }
}

void MainWindow::on_rotateZ_valueChanged(int value)
{
    float modifiedValue = ((float)value) * 360.0f / ((float)ui->rotateZ->maximum() - (float)ui->rotateZ->minimum());

    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    QList<QListWidgetItem *>::iterator it = items.begin();

    while(it != items.end())
    {
        ui->oglwidget->rotateZ(modifiedValue, (*it)->text().toStdString());
        ++it;
    }
}

void MainWindow::on_scaleX_valueChanged(int value)
{
    float modifiedValue = (float)(value + 1.0f);

    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    QList<QListWidgetItem *>::iterator it = items.begin();

    while(it != items.end())
    {
        ui->oglwidget->scaleX(modifiedValue, (*it)->text().toStdString());
        ++it;
    }
}

void MainWindow::on_scaleY_valueChanged(int value)
{
    float modifiedValue = (float)(value + 1.0f);

    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    QList<QListWidgetItem *>::iterator it = items.begin();

    while(it != items.end())
    {
        ui->oglwidget->scaleY(modifiedValue, (*it)->text().toStdString());
        ++it;
    }
}

void MainWindow::on_scaleZ_valueChanged(int value)
{
    float modifiedValue = (float)(value + 1.0f);

    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    QList<QListWidgetItem *>::iterator it = items.begin();

    while(it != items.end())
    {
        ui->oglwidget->scaleZ(modifiedValue, (*it)->text().toStdString());
        ++it;
    }
}

void MainWindow::on_checkBox_2_toggled(bool checked)
{
    ui->oglwidget->setPostMultiply(checked);
}

void MainWindow::on_actionLoad_Shader_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Files (*.material)"));

    if(!fileName.isNull())
        ui->oglwidget->loadMaterial(fileName.toStdString());
}
