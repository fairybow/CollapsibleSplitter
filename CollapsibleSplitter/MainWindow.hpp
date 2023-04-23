#pragma once

#include "Preview.hpp"
#include "Splitter.hpp"

#include <QMainWindow>
#include <QMenuBar>
#include <QPlainTextEdit>
#include <QStatusBar>
#include <QTreeView>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr)
		: QMainWindow(parent)
	{
		setGeometry(0, 0, 1000, 600);
		Layout::setCentralWidgets(this, { m_splitter });
		setMenuBar(m_menuBar);
		setStatusBar(m_statusBar);
		connect(m_splitter, &Splitter::askWindowSize, this, [&]() { return geometry(); });
		auto toggle_tree_view = new QPushButton(this);
		auto toggle_editor = new QPushButton(this);
		auto toggle_preview = new QPushButton(this);
		toggle_tree_view->setText("Toggle QTreeView");
		toggle_editor->setText("Central widget (QPlainTextEdit) not toggleable");
		toggle_preview->setText("Toggle Preview");
		for (auto& button : { toggle_tree_view, toggle_editor, toggle_preview }) {
			m_statusBar->addPermanentWidget(button, 1);
			button->setCheckable(true);
			button->setChecked(true);
		}
		toggle_editor->setDisabled(true);
		connect(toggle_tree_view, &QPushButton::toggled, this, [&](bool checked) { m_treeView->setVisible(checked); });
		connect(toggle_preview, &QPushButton::toggled, this, [&](bool checked) { m_preview->setVisible(checked); });
		m_splitter->initialize({ 0.2, 0.4, 0.4 }, 1);
	}

private:
	QMenuBar* m_menuBar = new QMenuBar(this);
	QTreeView* m_treeView = new QTreeView(this);
	QPlainTextEdit* m_editor = new QPlainTextEdit(this);
	Preview* m_preview = new Preview(this);
	//QTreeView* m_preview = new QTreeView(this);
	Splitter* m_splitter = new Splitter(Qt::Horizontal, { m_treeView, m_editor, m_preview }, this);
	QStatusBar* m_statusBar = new QStatusBar(this);
};
