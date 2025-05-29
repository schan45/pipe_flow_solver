#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "coord.h"
#include "tilemap.h"

#include <iostream>
#include <string>
#include <tuple>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>
#include <QPixmap>

#include <QGridLayout>
#include <QLayoutItem>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<QPair<QPoint, QPair<QString, QPair<QString, QString>>>> positions;

    ui->SourceColorComboBox->addItems({"RED", "CYAN", "BLUE", "GREEN", "YELLOW"});
    ui->SourceShapeComboBox->addItems({"fent", "lent", "jobb", "bal", "dupla vízszintes", "dupla függőleges", "négyes", "t fel", "t jobb", "t bal", "t le", "dupla fel és jobbra", "dupla fel és balra", "dupla le és balra", "dupla le és jobbra"});

    // Connect button click to the handler
    connect(ui->addSourcePushButton, &QPushButton::clicked, this, &MainWindow::onAddSourceClicked);

    // Initialize map to display initial state
    QVector<QPair<QPoint, QPair<QString, QPair<QString, QString>>>> dummyPositions;
    std::vector<std::pair<int, std::vector<Color>>> dummyPhases;
    std::vector<int> dummySupply = {0};
    tilemap tempMap(sources, sinks, dummyPhases, dummySupply);



    // Clear the layout (if tileGrid is a layout container)
    if (auto layout = dynamic_cast<QGridLayout*>(ui->tileGrid->layout())) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
    } else {
        ui->tileGrid->setLayout(new QGridLayout());
    }

    // Populate the grid layout with labels
    for (int y = 0; y < tilemap::HEIGHT; ++y) {
        for (int x = 0; x < tilemap::WIDTH; ++x) {
            QLabel* label = new QLabel();

            // For debugging: show coordinates or placeholders
            label->setText(QString("(%1, %2)").arg(x).arg(y));
            label->setAlignment(Qt::AlignCenter);

            // Add the label to the grid layout
            if (auto gridLayout = dynamic_cast<QGridLayout*>(ui->tileGrid->layout())) {
                gridLayout->addWidget(label, tilemap::HEIGHT - y - 1, x);
            }
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAddSourceClicked()
{
    QString input = ui->SourceTextLabel->toPlainText();
    if (input.isEmpty()) {
        QMessageBox::warning(this, "Hiba", "Adjon meg egy helyet és típust (pl.: '1 2 forras')");
        return;
    }

    QStringList parts = input.split(' ');
    if (parts.size() != 3) {
        QMessageBox::warning(this, "Nem megfelelő bemenet", "Kérem 'x y típus' formában adja meg a bemenetet.");
        return;
    }

    bool ok1, ok2;
    int x = parts[0].toInt(&ok1);
    int y = parts[1].toInt(&ok2);
    QString type = parts[2];

    if (!ok1 || !ok2) {
        QMessageBox::warning(this, "Hibás bemenet", "Kérem, hogy az x és y értékek számok legyenek.");
        return;
    }

    QString color = ui->SourceColorComboBox->currentText();
    QString shape = ui->SourceShapeComboBox->currentText();

    if (color.isEmpty() || shape.isEmpty()) {
        QMessageBox::warning(this, "Hiányzó adat", "Kérem válasszon színt és formát.");
        return;
    }

    // Add to positions
    positions.append(qMakePair(QPoint(x, y), qMakePair(type, qMakePair(color, shape))));

    // Update sources or sinks
    Color tileColor;
    if (color == "RED") tileColor = RED;
    else if (color == "CYAN") tileColor = CYAN;
    else if (color == "BLUE") tileColor = BLUE;
    else if (color == "GREEN") tileColor = GREEN;
    else if (color == "YELLOW") tileColor = YELLOW;
    else tileColor = NONE;

    int _shape;
    int rotate;
    if (shape == "négyes") {_shape = 3; rotate = 0;}
    else if (shape == "t fel") {_shape = 2; rotate = 0;}
    else if (shape == "t jobb") {_shape = 2; rotate = 3;}
    else if (shape == "dupla fel és jobbra") {_shape = 1; rotate = 0;}
    else if (shape == "t bal") {_shape = 2; rotate = 1;}
    else if (shape == "dupla fel és balra") {_shape = 1; rotate = 1;}
    else if (shape == "fent") {_shape = 4; rotate = 1;}
    else if (shape == "lent") {_shape = 4; rotate = 3;}
    else if (shape == "dupla függőleges") {_shape = 0; rotate = 1;}
    else if (shape == "t le") {_shape = 3; rotate = 2;}
    else if (shape == "dupla le és balra") {_shape = 1; rotate = 6;}
    else if (shape == "dupla le és jobbra") {_shape = 1; rotate = 3;}
    else if (shape == "dupla vízszintes") {_shape = 0; rotate = 0;}
    else if (shape == "jobb") {_shape = 4; rotate = 0;}
    else if (shape == "bal") {_shape = 4; rotate = 2;}

    if (type == "forras") {
        sources.push_back(std::make_tuple(coord(x, y), tileColor, _shape, rotate));
    } else if (type == "fogyaszto") {
        sinks.push_back(std::make_tuple(coord(x, y), tileColor, _shape, rotate));
    } else {
        QMessageBox::warning(this, "Ismeretlen típus", QString("Ismeretlen típus: %1").arg(type));
        return;
    }

    // Update label_14 to display the added sources and sinks
    QString displayText;
    for (const auto &pos : positions) {
        displayText += QString("Hely: (%1, %2), Típus: %3, Szín: %4, Forma: %5\n")
                           .arg(pos.first.x())
                           .arg(pos.first.y())
                           .arg(pos.second.first)
                           .arg(pos.second.second.first)
                           .arg(pos.second.second.second);
    }
    ui->label_14->setText(displayText);

    // Debug output
    qDebug() << "Current sources:";
    for (const auto &src : sources) {
        qDebug() << "Forras:" << std::get<0>(src).x << std::get<0>(src).y
                 << std::get<1>(src) << std::get<2>(src) << std::get<3>(src);
    }

    qDebug() << "Current sinks:";
    for (const auto &sink : sinks) {
        qDebug() << "Fogyaszto:" << std::get<0>(sink).x << std::get<0>(sink).y
                 << std::get<1>(sink) << std::get<2>(sink) << std::get<3>(sink);
    }
}

void MainWindow::getDataForSourcesAndSinks(QVector<QPair<QPoint, QPair<QString, QPair<QString, QString>>>> &positions)
{
    this->positions = positions;
}

std::vector<int> MainWindow::get_supplies_value() {
    std::vector<int> supply;
    supply.push_back(ui->straightPipeSpinBox->value());
    supply.push_back(ui->curvedPipeSpinBox->value());
    supply.push_back(ui->tSplitterSpinBox->value());
    supply.push_back(ui->crossPipeSpinBox->value());
    supply.push_back(ui->crossPipeSpinBox_3->value());

    supply.push_back(ui->straightPipeSpinBox_2->value());
    supply.push_back(ui->curvedPipeSpinBox_2->value());
    supply.push_back(ui->tSplitterSpinBox_2->value());
    supply.push_back(ui->crossPipeSpinBox_2->value());

    return supply;
}

void MainWindow::on_solveButton_clicked() {
    // Get supply data
    std::vector<int> supply = get_supplies_value();

    // Create the map and solve
    tilemap map(sources, sinks, phases, supply);
    bool is_solved = map.solver_algorithm();

    if (auto layout = dynamic_cast<QGridLayout*>(ui->tileGrid->layout())) {
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget(); // Deletes widget
            delete item;           // Deletes layout item
        }
    } else {
        ui->tileGrid->setLayout(new QGridLayout());
    }

    // Populate the grid layout with labels
    for (int y = 0; y < tilemap::HEIGHT; ++y) {
        for (int x = 0; x < tilemap::WIDTH; ++x) {
            Tile tile = map.get_tile_at(coord(x, y));
            QLabel* label = new QLabel();
            label->setPixmap(QPixmap(":/images/" + QString::fromStdString(tile.image_path())));
            label->setAlignment(Qt::AlignCenter);

            if (auto gridLayout = dynamic_cast<QGridLayout*>(ui->tileGrid->layout())) {
                gridLayout->addWidget(label, tilemap::HEIGHT - y - 1, x); // Correct addWidget call
            }
        }
    }

    // Handle unsolved cases
    if (!is_solved) {
        QMessageBox::warning(this, "Solver Error", "Could not find solution!");
    }
}


void MainWindow::on_pushButton_clicked()
{
    QTableWidgetItem *NewItem = new QTableWidgetItem;
    int newRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(newRow);

    ui->tableWidget->setItem(newRow,0,NewItem);

    NewItem->setText(ui->textEdit->toPlainText());

    std::pair<int,std::vector<Color>> current_phase;
    std::vector<Color> current_phase_colors;

    QString input_colors = ui->textEdit->toPlainText();
    QStringList color_list = input_colors.split(" ");

    for(int i = 0; i<color_list.size();i++){
        Color c;
        if(color_list[i] == "red"){
            for(int i = 0; i<sinks.size();i++){
                if(std::get<1>(sinks[i]) == RED){
                    c = RED;
                }
            }

        }else if(color_list[i] == "blue"){
            for(int i = 0; i<sinks.size();i++){
                if(std::get<1>(sinks[i]) == BLUE){
                    c = BLUE;
                }
            }
        }else if(color_list[i] == "cyan"){
            for(int i = 0; i<sinks.size();i++){
                if(std::get<1>(sinks[i]) == CYAN){
                    c = CYAN;
                }
            }
        }else if(color_list[i] == "green"){
            for(int i = 0; i<sinks.size();i++){
                if(std::get<1>(sinks[i]) == GREEN){
                    c = GREEN;
                }
            }
        }else if(color_list[i] == "yellow"){
            for(int i = 0; i<sinks.size();i++){
                if(std::get<1>(sinks[i]) == YELLOW){
                    c = YELLOW;
                }
            }
        }else {
            std::cout<<"Nincs ilyen szinű folyadék!"<<std::endl;
            continue;
        }
        current_phase_colors.push_back(c);
    }

    std::pair currentphaseinfo = std::make_pair(phase_counter+1,current_phase_colors);

    phases.push_back(currentphaseinfo);

    phase_counter ++;
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    current_phase = row;
}
