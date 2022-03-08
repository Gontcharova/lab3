#ifndef CHARTMODEL_H
#define CHARTMODEL_H
#include "Data.h"
#include "QtCharts"


class ChartModel : public QObject
{
    Q_OBJECT
private:
    QChart* model;
    QChartView* view;
public slots:
    void updateData(const QList<Data> &data);
public:
    ChartModel(QLayout *layout, QObject *parent = nullptr);
    void setDataToModel(const QList<Data>& data);
    void setDataToChart(const QList<Data>& data) const;
    virtual QAbstractSeries* dataToSeries(const QList<Data>& data) const = 0;
    virtual ~ChartModel() {}
};


class BarChart : public ChartModel
{
public:
    explicit BarChart(QLayout* layout);
    QAbstractSeries *dataToSeries(const QList<Data> &data) const override;
};

class PieChart : public ChartModel
{
public:
    explicit PieChart(QLayout* layout);
    // Chart interface
    QAbstractSeries *dataToSeries(const QList<Data> &data) const override;
};

#endif // CHARTMODEL_H
