#ifndef QTD2DSAMPLE_H
#define QTD2DSAMPLE_H

#include <QtWidgets/QWidget>
#include "ui_qtd2dsample.h"

class QtD2DSample : public QWidget
{
	Q_OBJECT

public:
	QtD2DSample(QWidget *parent = 0);
	~QtD2DSample();

private:
	Ui::QtD2DSampleClass ui;
};

#endif // QTD2DSAMPLE_H
