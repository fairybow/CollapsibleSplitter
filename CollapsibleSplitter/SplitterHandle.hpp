#pragma once

#include <QPainter>
#include <QSize>
#include <QSplitterHandle>

class SplitterHandle : public QSplitterHandle
{
	Q_OBJECT

public:
	SplitterHandle(Qt::Orientation orientation, QSplitter* parent) : QSplitterHandle(orientation, parent) {}

	virtual QSize sizeHint() const override
	{
		QSize size = QSplitterHandle::sizeHint();
		auto i = 5;
		(orientation() != Qt::Horizontal) ? size.setHeight(i) : size.setWidth(i);
		return size;
	}
};