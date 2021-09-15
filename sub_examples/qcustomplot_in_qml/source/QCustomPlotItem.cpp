#include "QCustomPlotItem.h"

#include <qcustomplot.h>
#include <QDebug>

CustomPlotItem::CustomPlotItem(QQuickItem* parent)
	: QQuickPaintedItem(parent)
	, m_CustomPlot(nullptr)
{
	setFlag(QQuickItem::ItemHasContents, true);
	// setRenderTarget(QQuickPaintedItem::FramebufferObject);
	// setAcceptHoverEvents(true);
	setAcceptedMouseButtons(Qt::AllButtons);

	connect(this, &QQuickPaintedItem::widthChanged, this, &CustomPlotItem::updateCustomPlotSize);
	connect(this,
		&QQuickPaintedItem::heightChanged,
		this,
		&CustomPlotItem::updateCustomPlotSize);
}

CustomPlotItem::~CustomPlotItem()
{
	delete m_CustomPlot;
	m_CustomPlot = nullptr;
}

void CustomPlotItem::initCustomPlot()
{
	m_CustomPlot = new QCustomPlot();

	updateCustomPlotSize();

	setupQuadraticDemo(m_CustomPlot);

	connect(m_CustomPlot, &QCustomPlot::afterReplot, this, &CustomPlotItem::onCustomReplot);

	m_CustomPlot->replot();
}

void CustomPlotItem::paint(QPainter* painter)
{
	if(m_CustomPlot)
	{
		QPixmap picture(boundingRect().size().toSize());
		QCPPainter qcpPainter(&picture);

		//m_CustomPlot->replot();
		m_CustomPlot->toPainter(&qcpPainter);

		painter->drawPixmap(QPoint(), picture);
	}
}

void CustomPlotItem::mousePressEvent(QMouseEvent* event)
{
	qDebug() << Q_FUNC_INFO;
	routeMouseEvents(event);
}

void CustomPlotItem::mouseReleaseEvent(QMouseEvent* event)
{
	qDebug() << Q_FUNC_INFO;
	routeMouseEvents(event);
}

void CustomPlotItem::mouseMoveEvent(QMouseEvent* event)
{
	routeMouseEvents(event);
}

void CustomPlotItem::mouseDoubleClickEvent(QMouseEvent* event)
{
	qDebug() << Q_FUNC_INFO;
	routeMouseEvents(event);
}

void CustomPlotItem::graphClicked(QCPAbstractPlottable* plottable)
{
	qDebug() << Q_FUNC_INFO << QString("Clicked on graph '%1 ").arg(plottable->name());
}

void CustomPlotItem::routeMouseEvents(QMouseEvent* event)
{
	if(m_CustomPlot)
	{
		QMouseEvent* newEvent = new QMouseEvent(event->type(),
							event->localPos(),
							event->button(),
							event->buttons(),
							event->modifiers());
		//QCoreApplication::sendEvent( m_CustomPlot, newEvent );
		QCoreApplication::postEvent(m_CustomPlot, newEvent);
	}
}

void CustomPlotItem::updateCustomPlotSize()
{
	if(m_CustomPlot)
	{
		m_CustomPlot->setGeometry(0, 0, width(), height());
	}
}

void CustomPlotItem::onCustomReplot()
{
	qDebug() << Q_FUNC_INFO;
	update();
}

void CustomPlotItem::setupQuadraticDemo(QCustomPlot* customPlot)
{
	customPlot->addGraph();
	customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
	customPlot->addGraph();
	customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

	QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
	timeTicker->setTimeFormat("%h:%m:%s");
	customPlot->xAxis->setTicker(timeTicker);
	customPlot->axisRect()->setupFullAxesBox();
	customPlot->yAxis->setRange(-1.2, 1.2);

	connect(customPlot->xAxis,
		qOverload<QCPRange const&>(&QCPAxis::rangeChanged),
		customPlot->xAxis2,
		qOverload<QCPRange const&>(&QCPAxis::setRange));
	connect(customPlot->yAxis,
		qOverload<QCPRange const&>(&QCPAxis::rangeChanged),
		customPlot->yAxis2,
		qOverload<QCPRange const&>(&QCPAxis::setRange));

	connect(&m_generator, &QTimer::timeout, this, [this, customPlot] {
		realtime_data_slot(customPlot);
	});
	m_generator.start(0);

	customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
	connect(customPlot,
		SIGNAL(plottableClick(QCPAbstractPlottable*, QMouseEvent*)),
		this,
		SLOT(graphClicked(QCPAbstractPlottable*)));
}

void CustomPlotItem::realtime_data_slot(QCustomPlot* customPlot)
{
	static QTime time(QTime::currentTime());
	double key = time.elapsed() / 1000.0;
	static double lastPointKey = 0;

	if(key - lastPointKey > 0.002)
	{
		customPlot->graph(0)->addData(key,
					      qSin(key) + qrand() / static_cast<double>(RAND_MAX) *
								  1 * qSin(key / 0.3843));
		customPlot->graph(1)->addData(key,
					      qCos(key) + qrand() / static_cast<double>(RAND_MAX) *
								  0.5 * qSin(key / 0.4364));
		lastPointKey = key;
	}

	customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
	customPlot->replot();
}
