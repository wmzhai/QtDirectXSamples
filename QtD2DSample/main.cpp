#include "qtd2dsample.h"
#include <QtWidgets/QApplication>

#include "QDxWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QDxWidget w;
	w.show();
	return a.exec();
}
