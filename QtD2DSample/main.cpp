#include "qtd2dsample.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtD2DSample w;
	w.show();
	return a.exec();
}
