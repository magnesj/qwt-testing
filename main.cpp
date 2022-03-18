#include <QApplication>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_point_data.h>
#include <qwt_plot_canvas.h>
#include <qwt_axis_id.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QwtAxisId axisY1(QwtPlot::yLeft, 0);
    QwtAxisId axisY2(QwtPlot::yLeft, 1);

    QwtPlot plot;
    plot.setTitle("Plot Demo");
    plot.setCanvasBackground(Qt::white);
    plot.setAxesCount(QwtPlot::yLeft, 2);

    plot.setAxisAutoScale(axisY1, true);
    plot.setAxisAutoScale(axisY2, true);

    plot.enableAxis(QwtPlot::xBottom, false);

    plot.setAxisVisible(axisY1, false); // Comment this to show the axis 1
    plot.setAxisVisible(axisY2, false); // Comment this to show the axis 2

    plot.insertLegend(new QwtLegend());

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setLineWidth(1);
    canvas->setFrameStyle(QFrame::Box | QFrame::Plain);

    QPalette canvasPalette(Qt::white);
    canvasPalette.setColor(QPalette::Foreground, QColor(131, 131, 131));
    canvas->setPalette(canvasPalette);

    plot.setCanvas(canvas);

    QVector<double> listX;
    QVector<double> list1y, list2y;

    for (int var = 0.1; var < 6.28; ++var)
    {
        listX.push_back(var);
        list1y.push_back(sin(var));
        list2y.push_back(2 * cos(var));
    }

    QwtPointArrayData *data1 = new QwtPointArrayData(listX, list1y);
    QwtPointArrayData *data2 = new QwtPointArrayData(listX, list2y);

    QwtPlotCurve *curve1 = new QwtPlotCurve();
    QwtPlotCurve *curve2 = new QwtPlotCurve();

    curve1->setTitle("Curve Sin(x)");
    curve1->setPen(Qt::blue, 4),
        curve1->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    curve1->setSamples(data1);

    curve2->setTitle("Curve 2*cos(x)");
    curve2->setPen(Qt::red, 4),
        curve2->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    curve2->setSamples(data2);

    curve1->setYAxis(axisY1);
    curve2->setYAxis(axisY2);

    curve1->attach(&plot);
    curve2->attach(&plot);

    plot.replot();
    plot.resize(600, 400);
    plot.show();

    return a.exec();
}