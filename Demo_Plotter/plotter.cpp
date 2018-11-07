#include "plotter.h"
#include <QToolButton>
#include <QStylePainter>
#include <QStyleOptionFocusRect>
#include <QMouseEvent>

Plotter::Plotter(QWidget *parent)
    :QWidget(parent)
{
    qDebug("Plotter()\n");
    /*告诉QWidget使用调色板中的“暗”分量作为重绘窗口部件的颜色，而不是背景色分量*/
    setBackgroundRole(QPalette::Dark);
    /*启动像素填充机制：当把窗口部件重新改变成一个更大的尺寸时，甚至使用paintEvent()绘制那些新近显示的任意像素之前，使用默认颜色来填充这些新的像素。默认情况下，子窗口部件会从它们的父窗口部件中继承相应的背景色*/
    setAutoFillBackground(true);
    /*设置尺寸策略*/
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    /*可以让窗口部件通过单击或者按下Tab键而输入焦点*/
    setFocusPolicy(Qt::StrongFocus);

    rubberBandIsShown = false;
    zoomInButton = new QToolButton(this);
    zoomInButton->setIcon(QIcon(":/images/zoomin.png"));
    /*通过调用adjustSize，可以把图标设置为大小提示所给定的大小*/
    zoomInButton->adjustSize();
    connect(zoomInButton, SIGNAL(clicked(bool)), this, SLOT(zoomIn()));

    zoomOutButton = new QToolButton(this);
    zoomOutButton->setIcon(QIcon(":/images/zoomout.png"));
    zoomOutButton->adjustSize();
    connect(zoomOutButton, SIGNAL(clicked(bool)), this, SLOT(zoomOut()));

    setPlotSettings(PlotSettings());
}

void Plotter::setPlotSettings(const PlotSettings &settings)
{
    qDebug("setPlotSettings()\n");
    zoomStack.clear();
    zoomStack.append(settings);
    curZoom = 0;
    zoomInButton->hide();
    zoomOutButton->hide();
    refreshPixmap();
}

void Plotter::zoomOut()
{
    qDebug("zoomOut()\n");
    if( curZoom > 0 )
    {
        --curZoom;
        zoomOutButton->setEnabled(curZoom > 0);
        zoomInButton->setEnabled(true);
        zoomInButton->show();
        refreshPixmap();
    }
}

void Plotter::zoomIn()
{
    qDebug("zoomIn()\n");
    if( curZoom < zoomStack.count() - 1 )
    {
        ++curZoom;
        zoomInButton->setEnabled(curZoom < zoomStack.count() - 1);
        zoomOutButton->setEnabled(true);
        zoomOutButton->show();
        refreshPixmap();
    }
}

QSize Plotter::minimumSizeHint() const
{
    qDebug("minimumSizeHint()\n");
    return QSize(6 * Margin, 4 * Margin);
}

QSize Plotter::sizeHint() const
{
    qDebug("sizeHint()\n");
    return QSize(12 * Margin, 8 * Margin);
}

void Plotter::paintEvent(QPaintEvent *event)
{
    qDebug("paintEvent()\n");
    QStylePainter painter(this);
    painter.drawPixmap(0, 0, pixmap);

    if( rubberBandIsShown )
    {
        qDebug("paintEvent()-->rubberBandIsShown\n");
        painter.setPen(palette().light().color());
        painter.drawRect(rubberBandRect.normalized().adjusted(0, 0, -1, -1));
    }

    if( hasFocus() )
    {
        qDebug("paintEvent()-->hasFocus()\n");
        QStyleOptionFocusRect option;
        option.initFrom(this);
        option.backgroundColor = palette().dark().color();
        painter.drawPrimitive(QStyle::PE_FrameFocusRect, option);
    }
}

void Plotter::resizeEvent(QResizeEvent *event)
{
    qDebug("resizeEvent()\n");
    int x = width() - (zoomInButton->width() + zoomOutButton->width() + 10);
    zoomInButton->move(x, 5);
    zoomOutButton->move(x + zoomInButton->width() + 5, 5);
    refreshPixmap();
}

void Plotter::mousePressEvent(QMouseEvent *event)
{
    qDebug("mousePressEvent()--> x = %d, y = %d\n", event->pos().rx(), event->pos().ry());
    /*获取当前的绘制区域*/
    QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);

    /*判断是否为左击*/
    if( event->button() == Qt::LeftButton )
    {
        /*点击的坐标点是否为可绘制区域内*/
        if( rect.contains(event->pos()) )
        {
            /*设置Flag，表示已有一个区域正在准备放大*/
            rubberBandIsShown = true;
            /*获取选择框的左上角的坐标，以及右下角的坐标*/
            rubberBandRect.setTopLeft(event->pos());
            rubberBandRect.setBottomRight(event->pos());
            /*描绘选择框*/
            updateRubberBandRegion();
            /*将鼠标光标修改为十字形光标*/
            setCursor(Qt::CrossCursor);
        }
    }
}

/*鼠标移动事件，当鼠标移动时，更新选择框的右下角坐标到rubberBandRect中*/
void Plotter::mouseMoveEvent(QMouseEvent *event)
{
    qDebug("mouseMoveEvent()\n");
    if( rubberBandIsShown )
    {
        updateRubberBandRegion();
        rubberBandRect.setBottomRight(event->pos());
        updateRubberBandRegion();
    }
}

void Plotter::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug("mouseReleaseEvent()\n");
    /*判断当前是否为选择框选择区域事件中*/
    if( (event->button() == Qt::LeftButton) && rubberBandIsShown )
    {
        /*设置为false，表示选择完毕*/
        rubberBandIsShown = false;
        updateRubberBandRegion();
        /*取消鼠标光标的设置*/
        unsetCursor();

        /*返回一个标准的、含有非负的长和宽的矩形（这是因为，在用选择框选择的时候，有可能会向左移动）*/
        QRect rect = rubberBandRect.normalized();
        /*如果选择框的长度和宽度有一个小于4，则不做任何处理*/
        if( rect.width() < 4 || rect.height() < 4 )
            return;
        /*将矩形的x轴坐标移动-Margin，y轴坐标移动-Margin*/
        rect.translate(-Margin, -Margin);

        /*获取当前的缩放设置值，然后根据选择框的坐标，计算出缩放后的值*/
        PlotSettings nowSettings = zoomStack[curZoom];
        PlotSettings settings;
        double dx = nowSettings.spanX() / (width() - 2 * Margin);
        double dy = nowSettings.spanY() / (height() - 2 * Margin);
        settings.minX = nowSettings.minX + dx * rect.left();
        settings.maxX = nowSettings.minX + dx * rect.right();
        settings.minY = nowSettings.maxY - dy * rect.bottom();
        settings.maxY = nowSettings.maxY - dy * rect.top();
        settings.adjust();

        qDebug("minx = %d, maxX = %d, minY = %d, maxY = %d\n", settings.minX, settings.maxX, settings.minY, settings.maxY);
        zoomStack.resize(curZoom + 1);
        zoomStack.append(settings);
        zoomIn();
    }
}

void Plotter::keyPressEvent(QKeyEvent *event)
{
    qDebug("keyPressEvent()\n");
    switch ( event->key() ) {
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Left:
        zoomStack[curZoom].scroll(-1, 0);
        refreshPixmap();
        break;
    case Qt::Key_Right:
        zoomStack[curZoom].scroll(+1, 0);
        refreshPixmap();
        break;
    case Qt::Key_Down:
        zoomStack[curZoom].scroll(0, -1);
        refreshPixmap();
        break;
    case Qt::Key_Up:
        zoomStack[curZoom].scroll(0, +1);
        refreshPixmap();
        break;
    default:
        QWidget::keyPressEvent(event);
        break;
    }
}

void Plotter::wheelEvent(QWheelEvent *event)
{
    qDebug("wheelEvent()\n");
    int numDegrees = event->delta() / 8;
    int numTicks = numDegrees / 15;

    if( event->orientation() == Qt::Horizontal )
    {
        zoomStack[curZoom].scroll(numTicks, 0);
    }
    else
    {
        zoomStack[curZoom].scroll(0, numTicks);
    }

    refreshPixmap();
}

void Plotter::updateRubberBandRegion()
{
    //qDebug("updateRubberBandRegion()\n");
    QRect rect = rubberBandRect.normalized();
    /*选择框的上面那条线*/
    update(rect.left(), rect.top(), rect.width(), 1);
    /*选择框的左边那条线*/
    update(rect.left(), rect.top(), 1, rect.height());
    /*选择框的下面那条线*/
    update(rect.left(), rect.bottom(), rect.width(), 1);
    /*选择框的右边那条线*/
    update(rect.right(), rect.top(), 1, rect.height());
}

/*绘制最新的图*/
void Plotter::refreshPixmap()
{
    //qDebug("refreshPixmap()\n");
    pixmap = QPixmap(size());
    pixmap.fill(this, 0, 0);

    QPainter painter(&pixmap);
    /*initFrom调用，可以设置painter所使用的画笔、背景色和字体，这里将this传进去，表示使用的是当前窗口的画笔、背景色和字体*/
    painter.initFrom(this);
    /*执行绘制*/
    drawGrid(&painter);
    drawCurves(&painter);
    /*为整个窗口部件预约一个绘制事件*/
    update();
}

/**/
void Plotter::drawGrid(QPainter *painter)
{
    qDebug("drawGrid()\n");
    QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);
    if( !rect.isValid() )
        return;

    PlotSettings settings = zoomStack[curZoom];
    QPen quiteDark = palette().dark().color().light();
    QPen light = palette().light().color();

    for( int i = 0; i <= settings.numXTicks; ++i)
    {
        int x = rect.left() + (i * (rect.width() - 1) / settings.numXTicks);
        double label = settings.minX + (i * settings.spanX() / settings.numXTicks);

        painter->setPen(quiteDark);
        painter->drawLine(x, rect.top(), x, rect.bottom());
        painter->setPen(light);
        painter->drawLine(x, rect.bottom(), x, rect.bottom() + 5);
        painter->drawText(x - 50, rect.bottom() + 5, 100, 20, Qt::AlignHCenter | Qt::AlignTop, QString::number(label));
    }

    for( int j = 0; j <= settings.numYTicks; ++j)
    {
        int y = rect.bottom() - (j * (rect.height() - 1) / settings.numYTicks);
        double label = settings.minY + (j * settings.spanY() / settings.numYTicks);

        painter->setPen(quiteDark);
        painter->drawLine(rect.left(), y, rect.right(), y);
        painter->setPen(light);
        painter->drawLine(rect.left() - 5, y, rect.left(), y);
        painter->drawText(rect.left() - Margin, y - 10, Margin - 5, 20, Qt::AlignRight | Qt::AlignVCenter, QString::number(label));
    }

    painter->drawRect(rect.adjusted(0, 0, -1, -1));
}

void Plotter::drawCurves(QPainter *painter)
{
    qDebug("drawCurves()\n");
    static const QColor colorForIds[6] = {Qt::red, Qt::green, Qt::blue, Qt::cyan, Qt::magenta, Qt::yellow};
    PlotSettings settings = zoomStack[curZoom];
    QRect rect(Margin, Margin, width() - 2 * Margin, height() - 2 * Margin);

    if( !rect.isValid() )
        return;

    painter->setClipRect(rect.adjusted(+1, +1, -1, -1));

    QMapIterator<int, QVector<QPointF> > i(curveMap);

    while( i.hasNext() )
    {
        i.next();

        int id = i.key();
        QVector<QPointF> data = i.value();
        QPolygonF polyline(data.count());
        for( int j = 0; j < data.count(); ++j)
        {
            double dx = data[j].x() - settings.minX;
            double dy = data[j].y() - settings.minY;
            double x = rect.left() + (dx * (rect.width() - 1) / settings.spanX());
            double y = rect.bottom() + (dy * (rect.height() - 1) / settings.spanY());
            polyline[j] = QPointF(x, y);
        }

        painter->setPen(colorForIds[uint(id)%6]);
        painter->drawPolyline(polyline);
    }
}

void Plotter::setCurveData(int id, const QVector<QPointF> &data)
{
    qDebug("setCurveData()\n");
    curveMap[id] = data;
    refreshPixmap();
}

void Plotter::clearCurve(int id)
{
    qDebug("clearCurve()\n");
    curveMap.remove(id);
    refreshPixmap();
}

PlotSettings::PlotSettings()
{
    qDebug("PlotSettings()\n");
    minX = 0.0;
    maxX = 10.0;
    numXTicks = 5;

    minY = 0.0;
    maxY = 10.0;
    numYTicks = 5;
}

void PlotSettings::scroll(int dx, int dy)
{
    qDebug("scroll()\n");
    double stepX = spanX() / numXTicks;
    minX += dx * stepX;
    maxX += dx * stepX;

    double stepY = spanY() / numYTicks;
    minY += dy * stepY;
    maxY += dy * stepY;
}

void PlotSettings::adjust()
{
    qDebug("adjust()\n");
    adjustAxis(minX, maxX, numXTicks);
    adjustAxis(minY, maxY, numYTicks);
}

void PlotSettings::adjustAxis(double &min, double &max, int &numTicks)
{
    qDebug("adjustAxis()\n");
    const int MinTicks = 4;
    double grossStep = (max - min) / MinTicks;
    double step = std::pow(10.0, std::floor(std::log10(grossStep)));

    if( 5 * step < grossStep )
    {
        step *= 5;
    }
    else if( 2 * step < grossStep )
    {
        step *= 2;
    }

    numTicks = int(std::ceil(max / step) - std::floor(min / step));
    if( numTicks < MinTicks )
        numTicks = MinTicks;

    min = std::floor(min / step) * step;
    max = std::ceil(max / step) * step;
}
