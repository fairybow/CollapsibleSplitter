#pragma once

#include <QMainWindow>
#include <QStackedLayout>
#include <QVector>
#include <QWidget>

namespace Layout
{
	inline void setCentralWidgets(QMainWindow* parentWindow, QVector<QWidget*> widgets)
	{
		auto container = new QWidget(parentWindow);
		auto stack_layout = new QStackedLayout(container);
		stack_layout->setStackingMode(QStackedLayout::StackAll);
		for (auto& widget : widgets)
			stack_layout->addWidget(widget);
		parentWindow->setCentralWidget(container);
	}

	inline void setStack(QWidget* parent, QVector<QWidget*> widgets)
	{
		auto stack_layout = new QStackedLayout(parent);
		stack_layout->setStackingMode(QStackedLayout::StackAll);
		for (auto& widget : widgets)
			stack_layout->addWidget(widget);
		parent->setLayout(stack_layout);
	}

	inline void set(QWidget* parent, QWidget* widget) { setStack(parent, QVector<QWidget*>{ widget }); }
}