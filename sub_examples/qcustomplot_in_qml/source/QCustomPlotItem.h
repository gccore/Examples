#ifndef QCUSTOMPLOTITEM_H
#define QCUSTOMPLOTITEM_H

#include <QtQuick>
#include <QTimer>

class QCustomPlot;
class QCPAbstractPlottable;

class CustomPlotItem : public QQuickPaintedItem
{
	Q_OBJECT

    public:
	CustomPlotItem(QQuickItem* parent = 0);
	virtual ~CustomPlotItem();

	void paint(QPainter* painter);

	Q_INVOKABLE void initCustomPlot();

    protected:
	void routeMouseEvents(QMouseEvent* event);

	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);

	void setupQuadraticDemo(QCustomPlot* customPlot);

	void realtime_data_slot(QCustomPlot* customPlot);

    private:
	QCustomPlot* m_CustomPlot;
	QTimer m_generator;

    private slots:
	void graphClicked(QCPAbstractPlottable* plottable);
	void onCustomReplot();
	void updateCustomPlotSize();
};

#endif // QCUSTOMPLOTITEM_H
