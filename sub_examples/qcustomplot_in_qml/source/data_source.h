#ifndef QCHART_SIMPLE_DATA_SOURCE_H
#define QCHART_SIMPLE_DATA_SOURCE_H

#include <QObject>

class data_source : public QObject
{
	Q_OBJECT
    public:
	explicit data_source(QObject* parent = nullptr);
};

#endif // QCHART_SIMPLE_DATA_SOURCE_H
