#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QTableWidget>
#include <vector>
#include "coord.h"
#include "tile.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_solveButton_clicked();

    void on_pushButton_clicked();

    void onAddSourceClicked();

    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    QSpinBox *straightPipeBox;
    QSpinBox *curvedPipeBox;
    QSpinBox *tSplitterBox;
    QSpinBox *crossPipeBox;
    QSpinBox *straightPipeBox_2;
    QSpinBox *curvedPipeBox_2;
    QSpinBox *tSplitterBox_2;
    QSpinBox *crossPipeBox_2;
    QSpinBox *crossPipeBox_3;

    std::vector<std::tuple<coord, Color, int, int>> sources;
    std::vector<std::tuple<coord, Color, int, int>> sinks;

    std::vector<std::pair<int,std::vector<Color>>> phases;
    std::vector<int> get_supplies_value();
    int phase_counter = 0;
    int current_phase = -1;

    void getDataForSourcesAndSinks(QVector<QPair<QPoint, QPair<QString, QPair<QString, QString>>>> &positions);

    QVector<QPair<QPoint, QPair<QString, QPair<QString, QString>>>> positions;

private:
    QPixmap straightPipe;
    QPixmap curvePipe1;
    QPixmap sourceRed;
    QPixmap sinkGreen;





};
#endif // MAINWINDOW_H
