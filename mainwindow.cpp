#include "mainwindow.h"
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), graphWidget(new GraphWidget(this)) {

    setWindowTitle("Touchstone Data Visualizer");

    QPushButton *loadButton = new QPushButton("Load File", this);
    loadButton->setGeometry(10, 10, 100, 30);

    graphWidget->setGeometry(10, 50, 600, 400);

    this->setMinimumSize(900, 700); // Минимальная ширина - 800, высота - 600.
    this->setMaximumSize(1600,1200);


    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadFile);
}

MainWindow::~MainWindow() {}

void MainWindow::loadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Touchstone File"), "", tr("Touchstone Files (*.s2p *.txt *.s1p)"));
    qDebug() << fileName;

    if (!fileName.isEmpty()) {
        DataParser parser;
        QVector<QPointF> data = parser.parse(fileName);

        if (data.isEmpty()) {
            QMessageBox::critical(this, "Error", "Invalid file format or file can't be opened.");
            return;
        }

        graphWidget->setData(data);
        graphWidget->update();
        graphWidget->show();
    }
}
