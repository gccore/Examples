#ifndef QCHART_SIMPLE_DATA_SOURCE_H
#define QCHART_SIMPLE_DATA_SOURCE_H

#include <QAbstractSeries>
#include <QObject>
#include <QPointF>
#include <QList>

class data_source : public QObject
{
	Q_OBJECT
    public:
	explicit data_source(QObject* parent = nullptr);

    public slots:
	void generateData(int type, int rowCount, int colCount);
	void update(QAbstractSeries* series);

    private:
	QList<QList<QPointF>> m_data;
	int m_index;
};

#endif // QCHART_SIMPLE_DATA_SOURCE_H
