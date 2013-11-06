#include "stdafx.h"
#include "GlassWidget.h"

#if defined WIN32 && GLASS_EFFECT
GlassWidget::GlassWidget(QWidget * parent) : QWidget(parent), 
    shouldMove_(false)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_NoSystemBackground);

    DwmEnableBlurBehindWindow((HWND)winId(), &BLUR_BEHIND);
}

bool GlassWidget::nativeEvent(const QByteArray &, void * data, long * result)
{
    auto msg = static_cast<MSG *>(data);

    if (msg->message == WM_ACTIVATE)
    {
        DwmExtendFrameIntoClientArea(msg->hwnd, &NO_MARGINS);
        *result = 0;
        return true;
    }
    return false;
}

void GlassWidget::mousePressEvent(QMouseEvent * event)
{
    shouldMove_ = true;
    lastPosition_ = event->globalPos();
    QWidget::mousePressEvent(event);
}

void GlassWidget::mouseReleaseEvent(QMouseEvent * event)
{
    shouldMove_ = false;
    QWidget::mouseReleaseEvent(event);
}

void GlassWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (shouldMove_)
    {
        QPoint delta = event->globalPos() - lastPosition_;
        move(pos() + delta);
        lastPosition_ = event->globalPos();
    }
    else
        QWidget::mouseMoveEvent(event);
}

#endif // WIN32 && GLASS_EFFECT
