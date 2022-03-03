#ifndef CHARTMODEL_H
#define CHARTMODEL_H
#include "Observer.h"
#include "Data.h"
#include "QtCharts"


class ChartModel : public Observer
{
private:
    QChart* model;
    QChartView* view;
public:
    ChartModel(QLayout *layout);
    void setChart(const QList<Data>& data);
    void updateData(const QList<Data> &data) override;
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
