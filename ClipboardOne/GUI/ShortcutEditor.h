#ifndef SHORTCUTEDITOR_H
#define SHORTCUTEDITOR_H

class DynamicSVGItem;
class QMLPlugin;

class ShortcutEditorIcon : public QGraphicsView
{
    public :
        ShortcutEditorIcon(QWidget * = nullptr);
        virtual ~ShortcutEditorIcon();

        void setInProgress();
        void setValid(bool);
        void setActivable(bool);

    private :
        inline void setItem(QGraphicsSvgItem &);

        QTimer animateTimer_;
        int rotationIndex_;

        QGraphicsScene scene_;

        std::unique_ptr<DynamicSVGItem> validItem_;
        std::unique_ptr<DynamicSVGItem> invalidItem_;
        std::unique_ptr<DynamicSVGItem> inProgressItem_;
        std::unique_ptr<DynamicSVGItem> nonActivableItem_;

        bool valid_;
};

Constant SHORTCUT_EDITOR_ICON_VALID         = ":/ShortcutEditor/CheckMark";
Constant SHORTCUT_EDITOR_ICON_INVALID       = ":/ShortcutEditor/QuestionMark";
Constant SHORTCUT_EDITOR_ICON_PROGRESS      = ":/ShortcutEditor/Cycle";
Constant SHORTCUT_EDITOR_ICON_NON_ACTIVABLE = ":/ShortcutEditor/CrossMark";

class ShortcutLabel : public QLabel
{
    public :
        ShortcutLabel(QWidget * = nullptr);

        void setInProgress(bool);
        void setActivable(bool);

    protected :
        virtual void paintEvent(QPaintEvent *);
        
        bool inProgress_;
        bool activable_;
};

Constant SHORTCUT_LABEL_CLICK_HERE    = "Click here to define a shortcut";
Constant SHORTCUT_LABEL_NON_ACTIVABLE = "Plugin is not activable";
Constant SHORTCUT_LABEL_PRESS_KEYS    = "Press keys";

class ShortcutEditor : public QWidget
{
    Q_OBJECT

    public :
        ShortcutEditor(QMLPlugin *, QWidget * = nullptr);

        Shortcut shortcut() const;
        void setShortcut(const Shortcut &);

        void edit();

        virtual QSize minimumSizeHint() const;
        virtual QSize sizeHint() const;

    protected :
        virtual void mousePressEvent(QMouseEvent *);

    private :
        Q_SLOT void onKeyDown(const Shortcut &, bool);
        Q_SLOT void onEditTimeout();
        Q_SLOT void onActivableChanged(bool);

        void enableShortcutsForPlugins(bool);

        QHBoxLayout layout_;
        ShortcutLabel labelShortcut_;
        ShortcutEditorIcon iconView_;

        QTimer editTimer_;
        Shortcut shortcut_;

        QMLPlugin * plugin_;
        bool activable_;

        static bool uniqueLock;
};

Constant SHORTCUT_EDITOR_SIZE_HINT     = QSize(250, 50);
Constant SHORTCUT_EDITOR_EDIT_INTERVAL = 3000;

#endif // SHORTCUTEDITOR_H