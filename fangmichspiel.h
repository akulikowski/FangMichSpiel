#ifndef FANGMICHSPIEL_H
#define FANGMICHSPIEL_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class FangMichSpiel; }
QT_END_NAMESPACE

class FangMichSpiel : public QMainWindow
{
    Q_OBJECT

public:
    FangMichSpiel(QWidget *parent = nullptr);
    ~FangMichSpiel();

private slots:
    void moveButton();
    void Updatezeit();
    void erhoehePunktzahl();


private:
    Ui::FangMichSpiel *ui;
    QPushButton *pushButton;
    QTimer *timer;
    QTimer *gameTimer;
    int SpielzeitinSekunden;
    int Punktzahl;
};

#endif // FANGMICHSPIEL_H
