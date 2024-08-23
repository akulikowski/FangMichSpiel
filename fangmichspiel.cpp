#include "fangmichspiel.h"
#include "ui_fangmichspiel.h"
#include <QMessageBox>

FangMichSpiel::FangMichSpiel(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FangMichSpiel)
{
    ui->setupUi(this);

    setFixedSize(800, 600);
    pushButton = ui->pushButton;

    Punktzahl = 0; // Initialisierung des Punktestands

    // Slot erhoehePunktzahl() mit dem Signal clicked() des Buttons verbinden
    connect(pushButton, &QPushButton::clicked, this, &FangMichSpiel::erhoehePunktzahl);

    // Timer zum Bewegen des Buttons jede Sekunde
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FangMichSpiel::moveButton);
    timer->start(1000); // Timer mit einem Intervall von 1000 ms (1 Sekunde) starten

    // Timer zum Zählen der Spielzeit (2 Minuten)
    SpielzeitinSekunden = 120;
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &FangMichSpiel::Updatezeit);
    gameTimer->start(1000); // Timer mit einem Intervall von 1000 ms (1 Sekunde) starten

    // Anfangsposition des Buttons
    moveButton();
}

FangMichSpiel::~FangMichSpiel()
{
    delete ui;
}

void FangMichSpiel::moveButton()
{
    // Neue zufällige Position für den Button generieren
    int x = QRandomGenerator::global()->bounded(width() - pushButton->width());
    int y = QRandomGenerator::global()->bounded(height() - pushButton->height() - 50);

    // Neue Position des Buttons setzen
    pushButton->move(x, y);
}

void FangMichSpiel::Updatezeit()
{
    // Aktualisierung der Anzeige der Zeit im Interface
    ui->timeLabel->setText(QString("Zeit: %1 Sekunden").arg(SpielzeitinSekunden));

    // Bedingung für das Spielende prüfen
    if (SpielzeitinSekunden <= 0)
    {
        gameTimer->stop(); // Spieltimer stoppen
        timer->stop(); // Bewegungstimer stoppen
        ui->timeLabel->setText("Zeit abgelaufen!");

        QMessageBox::information(this, "Spiel Vorbei", "Leider haben Sie verloren");
        QCoreApplication::quit(); // Anwendung beenden

    } else if (Punktzahl >= 10) {
        gameTimer->stop(); // Spieltimer stoppen
        timer->stop(); // Bewegungstimer stoppen

        QMessageBox::information(this, "Spiel Vorbei", "Gratulation, Sie haben das Spiel gewonnen!");
        QCoreApplication::quit(); // Anwendung beenden

    } else {
        // Spielzeit verringern
        SpielzeitinSekunden--;
    }
}

void FangMichSpiel::erhoehePunktzahl()
{
    Punktzahl++; // Punktestand erhöhen
    ui->scoreLabel->setText(QString("Treffer: %1").arg(Punktzahl)); // Anzeige des Punktestands aktualisieren
}
