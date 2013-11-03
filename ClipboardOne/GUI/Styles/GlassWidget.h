#ifndef GLASSWIDGET_H
#define GLASSWIDGET_H

#ifdef WIN32 
 #include <Dwmapi.h>

static const MARGINS NO_MARGINS = { -1 };
static const DWM_BLURBEHIND BLUR_BIHIND = {
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

#else
    typedef QWidget GlassWidget;
#endif // OS Switch

#endif // GLASSWIDGET_H
