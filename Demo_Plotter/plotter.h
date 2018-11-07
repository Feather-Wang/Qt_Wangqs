#ifndef PLOTTER_H
#define PLOTTER_H

/*
 * 选择框的工作流程：
 * 1、首先，当在绘制区点击鼠标左键，触发mousePressEvent，获得鼠标点击的坐标
*/
#include <QMap>
#include <QPixmap>
#include <QVector>
#include <QWidget>

class QToolButton;
class PlotSettings;

class Plotter : public QWidget
{
    Q_OBJECT

public:
    Plotter(QWidget *parent = 0);

    /*用于指定显示绘图区时所用到的PlotSettings*/
    void setPlotSettings(const PlotSettings &settings);
    /*设置用于给定曲线ID中的数据*/
    void setCurveData(int id, const QVector<QPointF> &data);
    /*从curveMap中移除指定id*/
    void clearCurve(int id);
    /*minimumSizeHint和sizeHint类似，可以指定一个窗口部件理想的最小大小*/
    QSize minimumSizeHint() const;
    /*指定一个窗口部件的理想大小*/
    QSize sizeHint() const;

public slots:
    void zoomIn();
    void zoomOut();

protected:
    /*这些都是QWidget类的事件处理器*/
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    /*鼠标移动事件，当鼠标移动时，更新选择框的右下角坐标到rubberBandRect中*/
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    /*声明了一些用于绘制这个窗口部件的函数、一个常量和几个成员变量*/
    /*预约一个绘制事件*/
    void updateRubberBandRegion();
    /*更新显示*/
    void refreshPixmap();
    /*绘制坐标系*/
    void drawGrid(QPainter *painter);
    /*绘制在坐标系中，画出的曲线，因为这里没有实现画曲线的程序，所以这个函数目前没有用*/
    void drawCurves(QPainter *painter);

    /*Margin常量可以为图形区域的周围提供一些空间*/
    enum { Margin = 50 };

    QToolButton *zoomInButton;
    QToolButton *zoomOutButton;
    /*保存曲线的数据*/
    QMap<int, QVector<QPointF> > curveMap;
    /*保存不同的缩放级设置值，这样就可以知道每一次缩小、放大的数据，进而通过zoomIn或zoomOut回到上一次或上上次的状态*/
    QVector<PlotSettings> zoomStack;
    /*curZoom保存zoomStack使用的当前索引值*/
    int curZoom;
    /*判断当前是否正在使用选择框选择区域*/
    bool rubberBandIsShown;
    /*保存选中框选中区域的左上角的坐标，以及右下角的坐标，通过这两个坐标，可以得到一个矩形*/
    QRect rubberBandRect;
    /*这个变量对整个窗口部件的绘制数据的进行了复制保存，即保存了即将要绘制的图*/
    QPixmap pixmap;
};

/*类PlotSettings给定了x轴和y轴的范围，以及在这些轴上刻度标记符的数量*/
class PlotSettings
{
public:
    PlotSettings();

    void scroll(int dx, int dy);
    void adjust();
    double spanX() const { return maxX - minX; }
    double spanY() const { return maxY - minY; }

    double minX;
    double maxX;
    int numXTicks;
    double minY;
    double maxY;
    int numYTicks;

private:
    /*将min和max参数转换成“合适的”数值，并且在给定的[min, max]范围内计算出合适的标记符个数，然后把它的numTicks参数设置成该值*/
    static void adjustAxis(double &min, double &max, int &numTicks);
};
#endif // PLOTTER_H
