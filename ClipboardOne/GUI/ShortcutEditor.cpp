#include "stdafx.h"
#include "ShortcutEditor.h"

#include "Core/KeyLogger.h"
#include "Core/Settings.h"

#include "DynamicSvgItem.h"

#include "QML/QMLEnvironment.h"
#include "QML/QMLPlugin.h"
#include "QML/QMLClipboard.h"

ShortcutEditorIcon::ShortcutEditorIcon(QWidget * parent) : QGraphicsView(parent),
    validItem_       (new DynamicSVGItem(SHORTCUT_EDITOR_ICON_VALID)),
    invalidItem_     (new DynamicSVGItem(SHORTCUT_EDITOR_ICON_INVALID)),
    inProgressItem_  (new DynamicSVGItem(SHORTCUT_EDITOR_ICON_PROGRESS)),
    nonActivableItem_(new DynamicSVGItem(SHORTCUT_EDITOR_ICON_NON_ACTIVABLE)),
    valid_(false)
{
    setScene(&scene_);

    inProgressItem_->setTransformOriginPoint(
        inProgressItem_->boundingRect().center());

    QObject::connect(&animateTimer_, &QTimer::timeout, [this]
    {
        inProgressItem_->setRotation(rotationIndex_ += 3);
    });

    setStyleSheet("border: 0px"); // removing ugly border
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFixedSize(32, 32);
}

ShortcutEditorIcon::~ShortcutEditorIcon()
{

}

void ShortcutEditorIcon::setInProgress()
{
    rotationIndex_ = 0;
    inProgressItem_->setRotation(0);
    setItem(*inProgressItem_);
    animateTimer_.start(25);
}

void ShortcutEditorIcon::setValid(bool valid)
{
    setItem(valid ? *validItem_ : *invalidItem_);
    animateTimer_.stop();
    valid_ = valid;
}

void ShortcutEditorIcon::setActivable(bool activable)
{
    setItem(activable ?  valid_ ? *validItem_ : *invalidItem_ : *nonActivableItem_);
}

void ShortcutEditorIcon::setItem(QGraphicsSvgItem & newItem)
{
    for(auto item : scene_.items()) scene_.removeItem(item);
    scene_.addItem(&newItem);
    fitInView(&newItem);
}

ShortcutLabel::ShortcutLabel(QWidget * parent) : QLabel(parent),
    inProgress_(false),
    activable_(true)
{
    setAlignment(Qt::AlignCenter);
    QFont _font = font();
    _font.setBold(true);
    setFont(_font);
    setWordWrap(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void ShortcutLabel::setInProgress(bool inProgress)
{
    inProgress_ = inProgress;
    repaint();
}

void ShortcutLabel::setActivable(bool activable)
{
    activable_ = activable;
    repaint();
}

void ShortcutLabel::paintEvent(QPaintEvent * event)
{
    if(text().isEmpty() || !activable_)
    {
        QPainter painter(this);
        painter.setPen(Qt::gray);
        QString text = activable_ ? inProgress_ ? SHORTCUT_LABEL_PRESS_KEYS : SHORTCUT_LABEL_CLICK_HERE : SHORTCUT_LABEL_NON_ACTIVABLE;
        painter.drawText(rect(), Qt::AlignCenter, text);
    }
    else QLabel::paintEvent(event);
}

bool ShortcutEditor::uniqueLock = false;

ShortcutEditor::ShortcutEditor(QMLPlugin * plugin, 
                               QWidget * parent) : QWidget(parent),
    layout_(this), 
    labelShortcut_(this),
    plugin_(plugin),
    activable_(true)
{
    layout_.addWidget(&labelShortcut_);
    layout_.addWidget(&iconView_);

    editTimer_.setSingleShot(true);
    editTimer_.setInterval(SHORTCUT_EDITOR_EDIT_INTERVAL);

    if(plugin_->clipboard()) setShortcut(plugin_->clipboard()->shortcut());

    QObject::connect(&KeyLogger::instance(), 
                     &KeyLogger::sequence, 
                     this, &ShortcutEditor::onKeyDown);

    QObject::connect(&editTimer_, &QTimer::timeout,
                     this, &ShortcutEditor::onEditTimeout);

    QObject::connect(plugin, &QMLPlugin::activableChanged,
                     this, &ShortcutEditor::onActivableChanged);
    onActivableChanged(plugin->activable());
}

Shortcut ShortcutEditor::shortcut() const
{
    return shortcut_;
}

void ShortcutEditor::setShortcut(const Shortcut & shortcut)
{
    shortcut_ = shortcut;

    labelShortcut_.setInProgress(false);
    labelShortcut_.setText(KeyLogger::sequenceString(shortcut));

    iconView_.setValid(!labelShortcut_.text().isEmpty());

    enableShortcutsForPlugins(true);
    if(plugin_->clipboard()) plugin_->clipboard()->setShortcut(shortcut_);
    Settings::setValue(plugin_->name(), QVariant::fromValue(shortcut_), "shortcuts");
}

void ShortcutEditor::edit()
{
    uniqueLock = true;
    shortcut_.clear();

    labelShortcut_.clear();
    labelShortcut_.setInProgress(true);

    iconView_.setInProgress();

    enableShortcutsForPlugins(false);

    editTimer_.start();
}

void ShortcutEditor::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton && activable_ && !uniqueLock) 
        edit();
}

void ShortcutEditor::onKeyDown(const Shortcut & shortcut, bool keyDown)
{
    if(keyDown && editTimer_.isActive())
    {
        shortcut_ = shortcut;
        labelShortcut_.setText(KeyLogger::sequenceString(shortcut));
        editTimer_.start();
    }
}

void ShortcutEditor::onEditTimeout()
{
    setShortcut(shortcut_);
    uniqueLock = false;
}

void ShortcutEditor::enableShortcutsForPlugins(bool enable)
{
    QMLEnvironment::apply([enable](QMLPlugin * plugin)
    {
        if(plugin->clipboard())
            plugin->clipboard()->setIgnoreShortcut(!enable);
    });
}

QSize ShortcutEditor::sizeHint() const
{
    return SHORTCUT_EDITOR_SIZE_HINT;
}

QSize ShortcutEditor::minimumSizeHint() const
{
    return SHORTCUT_EDITOR_SIZE_HINT;
}

void ShortcutEditor::onActivableChanged(bool activable)
{
    labelShortcut_.setActivable(activable);
    iconView_.setActivable(activable);
    activable_ = activable;
}