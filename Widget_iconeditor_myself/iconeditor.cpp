#include <QtGui>

#include "iconeditor.h"

IconEditor::IconEditor(QWidget *parent)
    :QWidget(parent)
{
    /*告诉Qt，当重新改变窗口部件的大小时，这个窗口部件的内容并没有发生变化，而且它的内容仍旧保留从窗口部件左上角开始的特性，当重新定义窗口部件的大小时，通过这个信息，Qt就可以避免对已经显示区域进行重新绘制*/
    setAttribute(Qt::WA_StaticContents);
    /*设置尺寸策略，将水平尺寸和垂直尺寸设置一个最小值*/
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);

    /*画笔的颜色为黑色，缩放因子被设置为8，也就是说，图标中的每一个像素都将会显示成一个8*8的正方形*/
    curColor = Qt::black;
    zoom = 8;

    /*这里把image初始化为一个16*16的像素大小和32位的ARGB颜色格式，这种颜色格式可以支持半透明效果*/
    image = QImage(16, 16, QImage::Format_ARGB32);
    /*qRgb只是unsigned int类型的一个tpedef，qRgba函数，把4个参数组合成一个32位ARGB整数值的内联函数，例如：0xFFFF0000，第一个FF对应于alpha分量，第二个FF对应于红色分量，第三个00对应于绿色分量，第四个00对应于蓝色分量*/
    image.fill(qRgba(0, 0, 0, 0));
    printf("\nwang ----> %x\n", qRgba(0xff, 0xf1, 0xf2, 0xf3));
}

/*sizeHint函数是从QWidget中重新实现的，并且返回一个窗口部件的理想大小*/
QSize IconEditor::sizeHint() const
{
    /*这里，使用缩放因子乘以图像的尺寸大小作为这个窗口部件的理想大小，如果缩放因子是3或者更大，那么在每个方向上需要再额外增加一个像素，以便可以容纳一个网格线*/
    QSize size = zoom * image.size();
    if( zoom >= 3 )
        size += QSize(1, 1);
    return size;
}

/*设置画笔的当前颜色*/
void IconEditor::setPenColor(const QColor &newColor)
{
    curColor = newColor;
}

/*设置需要编辑的图像*/
void IconEditor::setIconImage(const QImage &newImage)
{
    if( newImage != image )
    {
        image = newImage.convertToFormat(QImage::Format_ARGB32);
        /*设置完image后，使用QWidget::update()，它会使用新的图像强制重绘这个窗口部件*/
        update();
        /*然后调用QWidget::updateGeometry()，告诉包含这个窗口部件的任意布局，这个窗口部件的大小提示已经发生改变了，于是，该布局将会自动适应这个新的大小提示*/
        updateGeometry();
    }
}

/*设置图像的缩放因子，为了避免在其它地方被0除，应纠正任何小于1的值，之后再次调用update和updateGeometry来重绘该窗口部件*/
void IconEditor::setZoomFactor(int newZoom)
{
    if( newZoom < 1 )
        newZoom = 1;

    if( newZoom != zoom )
    {
        zoom = newZoom;
        update();
        updateGeometry();
    }
}

/*重载paintEvent函数*/
void IconEditor::paintEvent(QPaintEvent *event)
{
    /*首先，构建一个QPainter对象*/
    QPainter painter(this);

    /*
     * 如果缩放因子是3或比3大，就使用QPainter::drawLine()函数绘制构成网格的水平线段和垂直线段。
     * painter.drawLine(x1,y1,x2,y2)；其中x1，y1是线段的一个端点的位置，x2，y2是线段的另一个端点的位置。
     * 这个函数还有另一个重载版本的形式，它使用两个QPoint来代替这里给出的4个int值。
     * 关于坐标，左上角的位置为（0,0），右下角的位置为（width()-1, height()-1)。
     *
     * 在画网格线前，使用QPainter::setPen()设置线段的颜色，本来也可以直接通过代码来指定像黑色或灰色这样的颜色，
     * 但是使用窗口部件的调色板(palette)会更好一些。
     * 每一个窗口部件都会配备一个调色板，由它来确定做什么事应该使用什么颜色。例如：
     * 对窗口部件的背景色会有一个对应的调色板条目（通常是亮灰色），并且对于文本的背景色也会对应一个调色板条目（通常是黑色）。
     * 默认情况下，一个窗口部件的调色板会采用窗口系统的颜色主题。通过使用调色板中的这些颜色，可以确保IconEditor能够尊重用户的选择。
     * 一个窗口部件的调色板由三个颜色组构成：激活组（active）、非激活组（inactive）、不可用组（disabled）。应该使用哪一个颜色组取决于该窗口部件的当前状态。
     * active颜色组可用于当前激活窗口中的那些窗口部件。
     * inactive颜色组可用于其他窗口中的那些窗口部件。
     * disabled颜色组可用于任意窗口中的那些不可用窗口部件。
     * QWidget:palette()函数可以返回窗口部件的调色板，它是一个QPalette型对象，颜色组给定为QPalette::ColorGroup型枚举变量值。
     */
    if( zoom >= 3 )
    {
        painter.setPen(palette().foreground().color());
        for( int i = 0; i <= image.width(); ++i )
            painter.drawLine(zoom*i, 0, zoom*i, zoom*image.height());

        for( int j = 0; j <= image.height(); ++j )
            painter.drawLine(0, zoom*j, zoom*image.width(), zoom*j );
    }

    for( int i = 0; i < image.width(); ++i )
    {
        for( int j = 0; j < image.height(); ++j )
        {
            /*通过调用IconEditor::pixelRect,返回一个QRect，传递进去的i和j是image中的坐标，而不是窗口部件中的坐标，所以pixelRect的作用是将image中的坐标转化为窗口部件中的坐标。
             * QRect(x, y, width, height)，这里的x，y是窗口部件左上角的位置坐标，而width*height是这个窗口部件的尺寸大小。
            */
            QRect rect = pixelRect(i, j);
            if( !event->region().intersected(rect).isEmpty() )
            {
                /*最后通过QPainter::fillRect来绘制一个缩放后的像素，fillRect有两个参数，一个QRect，一个QBrush，Qrect是窗口部件中的坐标，而QBrush是要填充的像素
                 * 通过传递一个用作画笔的QColor，我们获得一个实心填充图案，如果该暗色并非完全不透明（它的alpha通道小于255），就会先绘制出一个白色的背景来。
                */
                QColor color = QColor::fromRgba(image.pixel(i, j));
                if( color.alpha() < 255 )
                    painter.fillRect(rect, Qt::white);

                painter.fillRect(rect, color);
            }
        }
    }
}

QRect IconEditor::pixelRect(int i, int j) const
{
    if( zoom >= 3 )
    {
        return QRect(zoom * i + 1, zoom * j + 1, zoom - 1, zoom -1 );
    }
    else
    {
        return QRect(zoom * i, zoom * j, zoom, zoom );
    }
}

/*重载mousePressEvent，鼠标点击事件*/
void IconEditor::mousePressEvent(QMouseEvent *event)
{
    /*调用setImagePixel（这个函数要自己实现），当鼠标左击时，将鼠标点击的位置设置为当前画笔的颜色（通过第二个参数判断），当右击时，将当前位置的颜色清除。*/
    if( event->button() == Qt::LeftButton )
    {
        setImagePixel(event->pos(), true);
    }
    else if( event->button() == Qt::RightButton )
    {
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::mouseMoveEvent(QMouseEvent *event)
{
    if( event->buttons() & Qt::LeftButton )
    {
        setImagePixel(event->pos(), true);
    }
    else if( event->buttons() & Qt::RightButton )
    {
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::setImagePixel(const QPoint &pos, bool isPaint)
{
    int i = pos.x() / zoom;
    int j = pos.y() / zoom;

    if( image.rect().contains(i, j) )
    {
        if( isPaint )
        {
            /*设置像素，需要把QColor转换为一个用于调用QImage::setPixel的32位的ARGB值*/
            image.setPixel(i, j, penColor().rgba());
        }
        else
        {
            /*清空一个像素，其实就是把它设置为透明*/
            image.setPixel(i, j, qRgba(0, 0, 0, 0));
        }

        update(pixelRect(i, j));
    }
}
