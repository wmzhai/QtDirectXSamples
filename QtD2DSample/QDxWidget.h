#pragma once


#include <QWidget.h>

#include "../common/common.h"

class QDxWidget : public QWidget
{
	Q_OBJECT

public:
	QDxWidget(QWidget *parent = 0) : QWidget(parent)
	{
	}
	virtual ~QDxWidget()
	{
	}

};