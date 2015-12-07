#pragma once


#include <QWidget.h>

#include "../common/common.h"
#include "../common/camera.h"

class QDxWidget : public QWidget
{
	Q_OBJECT

public:
	BT_DECLARE_ALIGNED_ALLOCATOR()

	QDxWidget(QWidget *parent = 0, Qt::WindowFlags flags = 0) : QWidget(parent, flags)
	{
		setAttribute(Qt::WA_PaintOnScreen);
		setAttribute(Qt::WA_NoSystemBackground);

		m_standBy = false;
		m_lastRendered = 0;
		m_fTime = 0;
		m_camera = (Camera*)_aligned_malloc(sizeof(Camera), 16);
		m_camera->initialize();
	}
	virtual ~QDxWidget()
	{
		_aligned_free(m_camera);
	}

protected:

	//! Pointer of Camera for 16-byte alignment
	Camera*	m_camera;

	//! if stand-by mode
	bool	m_standBy;

	//! Last updated time
	double	m_lastRendered;

	//! Clicked mouse position
	QPointF	m_clickPos;

	//! Time
	double	m_fTime;
};