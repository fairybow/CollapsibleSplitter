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
	enum class WidgetWas {
		Hidden,
		Shown
	};

	TrueSplitter(QWidget* parent) : QSplitter(parent) {}

signals:
	void resized();
	void widgetVisibilityChanged(int widgetIndex, WidgetWas visibility);

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
				if (!widget(i)->isVisible()) {
					emit widgetVisibilityChanged(i, WidgetWas::Hidden);
					qDebug() << "!!!" << widget(i) << ": eventFilter widgetVisibilityChanged signal (Hidden)";
				}
				else {
					emit widgetVisibilityChanged(i, WidgetWas::Shown);
					qDebug() << "!!!" << widget(i) << ": eventFilter widgetVisibilityChanged signal (Shown)";
				}
			}
			
			for (int i = 0; i < count(); ++i) {
				auto widget = this->widget(i);
				if (widget == nullptr) {
					qDebug() << "Widget at index" << i << "has been removed from the QSplitter";
				}
				else {
					qDebug() << "Widget at index" << i << "is still a child of the QSplitter";
				}
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
		for (auto i = 0; i < count(); ++i)
			widget(i)->installEventFilter(this);
	}
};