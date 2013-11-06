#ifndef GLASSWIDGET_H
#define GLASSWIDGET_H

#if defined WIN32 && GLASS_EFFECT
 #include <Dwmapi.h>

static const MARGINS NO_MARGINS = { -1 };
static const DWM_BLURBEHIND BLUR_BEHIND = {
    DWM_BB_ENABLE,
    true,
    nullptr,
    true
};

class GlassWidget : public QWidget
{
    public :
        GlassWidget(QWidget * = nullptr);

    protected :
        virtual bool nativeEvent(const QByteArray &, void *, long *);

        virtual void mousePressEvent(QMouseEvent *);
        virtual void mouseReleaseEvent(QMouseEvent *);
        virtual void mouseMoveEvent(QMouseEvent *);

    private :
        QPoint lastPosition_;
        bool shouldMove_;
};

class GlassWidgetEventFilter : public QAbstractNativeEventFilter
{
protected :
    virtual bool nativeEventFilter(const QByteArray &, void * data, long * result)
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
};

#else
    typedef QWidget GlassWidget;
#endif // OS Switch

#endif // GLASSWIDGET_H
