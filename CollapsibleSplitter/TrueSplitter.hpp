#pragma once

#include "SplitterHandle.hpp"

#include <QChildEvent>
#include <QEvent>
#include <QResizeEvent>
#include <QSplitter>
#include <QTimer>

class TrueSplitter : public QSplitter
{
	Q_OBJECT

public:
	enum class WidgetSet {
		Hidden,
		Shown
	};

	TrueSplitter(QWidget* parent) : QSplitter(parent) {}

signals:
	void resized();
	void widgetVisibilityChanged(int widgetIndex, WidgetSet visibility);

protected:
	virtual void childEvent(QChildEvent* event) override
	{
		if (event->type() == QEvent::ChildAdded && event->child()->isWidgetType())
			installFilters();
		QSplitter::childEvent(event);
	}

	virtual bool eventFilter(QObject* object, QEvent* event) override
	{
		if (event->type() == QEvent::Show || event->type() == QEvent::Hide) {
			for (auto i = 0; i < count(); ++i) {
				!widget(i)->isVisible()
					? emit widgetVisibilityChanged(i, WidgetSet::Hidden)
					: emit widgetVisibilityChanged(i, WidgetSet::Shown);
			}
		}
		return QSplitter::eventFilter(object, event);
	}

	virtual void resizeEvent(QResizeEvent* event) override
	{
		QSplitter::resizeEvent(event);
		emit resized();
	}

	virtual QSplitterHandle* createHandle() override { return new SplitterHandle(orientation(), this); }

private:
	void installFilters()
	{
		for (auto i = 0; i < count(); ++i) {
			widget(i)->installEventFilter(this);
		}
	}
};