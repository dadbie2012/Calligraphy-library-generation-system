#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>


#include <QMainWindow>

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
     void paintEvent(QPaintEvent *);

signals:
     void chooseSceneBack();

public slots:
};

#endif // CHOOSELEVELSCENE_H
