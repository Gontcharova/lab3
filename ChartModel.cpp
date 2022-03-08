#include "ChartModel.h"
#include <algorithm>

ChartModel::ChartModel(QLayout *layout, QObject *parent) : QObject(parent)
{
    model = new QChart();
    view = new QChartView();
    view->setChart(model);
    layout->addWidget(view);
    model->legend()->setAlignment(Qt::AlignRight);
}

void ChartModel::updateData(const QList<Data> &data)
{
    setDataToModel(data);
}

void ChartModel::setDataToModel(const QList<Data> &data)
{
    model->setTitle("");
    qint64 total_size = 0;
    for (auto& x : data) {
        total_size += x.m_size;
    }
    if (total_size == 0) {
        model->setTitle("Folder is empty");
        model->removeAllSeries();
        return;
    }
    if (data.size() > 5)
    {
        QList<Data> data_others = data;
        qint64 others_size = 0;
        std::sort(std::begin(data_others), std::end(data_others),
                  [](Data &left, Data &right) {
            return left.m_size > right.m_size;
        });
        for (int i = 5; i < data.size(); i++)
        {
            others_size += data.at(i).m_size;
        }
        data_others.erase(std::begin(data_others) + 5, std::end(data_others));
        data_others.push_back(Data("Others", others_size,
                                  (qreal)others_size * 100 / total_size));
        setDataToChart(data_others);
    } else {
        setDataToChart(data);
    }
}

void ChartModel::setDataToChart(const QList<Data> &data) const
{
    model->removeAllSeries();
    model->addSeries(dataToSeries(data));
}

BarChart::BarChart(QLayout* layout) : ChartModel(layout) {}

QAbstractSeries *BarChart::dataToSeries(const QList<Data> &data) const
{
    QBarSeries* bar_series = new QBarSeries();
    bar_series->setBarWidth(1);
    for (auto& x : data) {
        if (x.m_ratio < 0) {
            QBarSet* set = new QBarSet(x.m_name +
                                       QString("(< 0.01 %)").toHtmlEscaped());
            set->append(std::abs(x.m_ratio));
            bar_series->append(set);
        } else {
            QBarSet* set = new QBarSet(x.m_name + "(" +
                                       QString::number(x.m_ratio, 'f', 2) + " %)");
            set->append(x.m_ratio);
            bar_series->append(set);
        }
    }
    return bar_series;
}

PieChart::PieChart(QLayout* layout) : ChartModel(layout) {}

QAbstractSeries *PieChart::dataToSeries(const QList<Data> &data) const
{
    QPieSeries* pie_series = new QPieSeries();
    pie_series->setPieSize(1);
    for (auto& item : data) {
        if (item.m_ratio < 0) {
            pie_series->append(item.m_name + QString("(< 0.01 %)")
                           .toHtmlEscaped(), std::abs(item.m_ratio));
        } else {
            pie_series->append(item.m_name + "(" + QString::number(item.m_ratio,
                            'f', 2) + " %)", item.m_ratio);
        }
    }
    return pie_series;
}
