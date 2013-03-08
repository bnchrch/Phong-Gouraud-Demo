#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QListWidgetItem>

void MainWindow::newGeometryAdded(std::string m_GeometryName)
{
    ui->listWidget->addItem(QString(m_GeometryName.c_str()));
}

void MainWindow::geometryRemoved(std::string m_GeometryName)
{
    QString geometryName(m_GeometryName.c_str());
    QList<QListWidgetItem *> items = ui->listWidget->findItems(geometryName, Qt::MatchFixedString);

    QList<QListWidgetItem *>::iterator it = items.begin();

    while(it != items.end())
    {
        delete ui->listWidget->takeItem(ui->listWidget->row((*it)));
        ++it;
    }
}

void MainWindow::addGeometry()
{
    this->on_actionAdd_Model_triggered();
}

void MainWindow::removeGeometry()
{
    this->on_actionRemove_Selected_triggered();
}

void MainWindow::on_actionAdd_Model_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Files (*.obj)"));

    if(!fileName.isNull())
        ui->oglwidget->loadGeometry(fileName.toStdString());
}

void MainWindow::on_actionRemove_Selected_triggered()
{
    QList<QListWidgetItem *> items = ui->listWidget->selectedItems();
    QList<QListWidgetItem *>::iterator it = items.begin();

    while(it != items.end())
    {
        ui->oglwidget->removeGeometry((*it)->text().toStdString());
        ++it;
    }
}
