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
                   // Initialization of the score

    // Slot erhoehePunktzahl() mit dem Signal clicked() des Buttons verbinden
    // Connect the clicked() signal of the button to the slot erhoehePunktzahl()
    connect(pushButton, &QPushButton::clicked, this, &FangMichSpiel::erhoehePunktzahl);

    // Timer zum Bewegen des Buttons jede Sekunde
    // Timer to move the button every second
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FangMichSpiel::moveButton);
    timer->start(1000); // Timer mit einem Intervall von 1000 ms (1 Sekunde) starten
                       // Start the timer with an interval of 1000 ms (1 second)

    // Timer zum Zählen der Spielzeit (2 Minuten)
    // Timer to count the game time (2 minutes)
    SpielzeitinSekunden = 120;
    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &FangMichSpiel::Updatezeit);
    gameTimer->start(1000); // Timer mit einem Intervall von 1000 ms (1 Sekunde) starten
                            // Start the game timer with an interval of 1000 ms (1 second)

    // Anfangsposition des Buttons
    // Initial position of the button
    moveButton();
}

FangMichSpiel::~FangMichSpiel()
{
    delete ui;
}

void FangMichSpiel::moveButton()
{
    // Neue zufällige Position für den Button generieren
    // Generate a new random position for the button
    int x = QRandomGenerator::global()->bounded(width() - pushButton->width());
    int y = QRandomGenerator::global()->bounded(height() - pushButton->height() - 50);

    // Neue Position des Buttons setzen
    // Set the new position of the button
    pushButton->move(x, y);
}

void FangMichSpiel::Updatezeit()
{
    // Aktualisierung der Anzeige der Zeit im Interface
    // Update the display of the time in the interface
    ui->timeLabel->setText(QString("Zeit: %1 Sekunden").arg(SpielzeitinSekunden));

    // Bedingung für das Spielende prüfen
    // Check the condition for the end of the game
    if (SpielzeitinSekunden <= 0)
    {
        gameTimer->stop(); // Spieltimer stoppen
                           // Stop the game timer
        timer->stop(); // Bewegungstimer stoppen
                       // Stop the movement timer
        ui->timeLabel->setText("Zeit abgelaufen!");

        QMessageBox::information(this, "Spiel Vorbei", "Leider haben Sie verloren");
        QCoreApplication::quit(); // Anwendung beenden
                                  // Quit the application

    } else if (Punktzahl >= 10) {
        gameTimer->stop(); // Spieltimer stoppen
                           // Stop the game timer
        timer->stop(); // Bewegungstimer stoppen
                       // Stop the movement timer

        QMessageBox::information(this, "Spiel Vorbei", "Gratulation, Sie haben das Spiel gewonnen!");
        QCoreApplication::quit(); // Anwendung beenden
                                  // Quit the application

    } else {
        // Spielzeit verringern
        // Decrease the game time
        SpielzeitinSekunden--;
    }
}

void FangMichSpiel::erhoehePunktzahl()
{
    Punktzahl++; // Punktestand erhöhen
                 // Increase the score
    ui->scoreLabel->setText(QString("Treffer: %1").arg(Punktzahl)); // Anzeige des Punktestands aktualisieren
                                                                      // Update the score display
}
