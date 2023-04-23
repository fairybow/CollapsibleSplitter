#pragma once

#include "Layout.hpp"

#include <QDesktopServices>
#include <QEvent>
#include <QObject>
#include <Qt>
#include <QUrl>
#include <QWebChannel>
#include <QWebEnginePage>
#include <QWebEngineView>
#include <QWidget>

class WebDocument : public QObject
{
	//Q_OBJECT

public:
	//explicit WebDocument(QObject* parent = nullptr) : QObject(parent) {}
};

class WebEnginePage : public QWebEnginePage
{
	//Q_OBJECT

public:
	using QWebEnginePage::QWebEnginePage;

protected:
	bool acceptNavigationRequest(const QUrl& url, NavigationType, bool) override
	{
		if (url.scheme() == QStringLiteral("qrc"))
			return true;
		QDesktopServices::openUrl(url);
		return false;
	}
};

class WebEngineView : public QWebEngineView
{
	Q_OBJECT

public:
	WebEngineView(WebDocument& content, QWidget* parent) : QWebEngineView(parent)
	{
		setContextMenuPolicy(Qt::NoContextMenu);
		m_channel->registerObject(QStringLiteral("content"), &content);
		m_page->setWebChannel(m_channel);
		setPage(m_page);
	}

private:
	WebEnginePage* m_page = new WebEnginePage(this);
	QWebChannel* m_channel = new QWebChannel(this);
};

class Preview : public QWidget
{
	Q_OBJECT

public:
	Preview(QWidget* parent) : QWidget(parent)
	{
		setContentsMargins(0, 0, 0, 0);
		Layout::set(this, m_view);
	}

private:
	WebDocument m_content;
	WebEngineView* m_view = new WebEngineView(m_content, this);

	QString url() { return QString("qrc:/Test.html"); }
};