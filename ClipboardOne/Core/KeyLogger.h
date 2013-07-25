#ifndef KEYLOGGER_H
#define KEYLOGGER_H

namespace KeyMapping
{
    typedef std::map<DWORD, int> KeyMap;
    typedef std::map<int, QString> KeyStringMap;

    static KeyMap keyMap()
    {
        static KeyMap _keyMap;

        _keyMap[VK_ESCAPE]      = Qt::Key_Escape;
        _keyMap[VK_F1]          = Qt::Key_F1;
        _keyMap[VK_F2]          = Qt::Key_F2;
        _keyMap[VK_F3]          = Qt::Key_F3;
        _keyMap[VK_F4]          = Qt::Key_F4;
        _keyMap[VK_F5]          = Qt::Key_F5;
        _keyMap[VK_F6]          = Qt::Key_F6;
        _keyMap[VK_F7]          = Qt::Key_F7;
        _keyMap[VK_F8]          = Qt::Key_F8;
        _keyMap[VK_F9]          = Qt::Key_F9;
        _keyMap[VK_F10]         = Qt::Key_F10;
        _keyMap[VK_F11]         = Qt::Key_F11;
        _keyMap[VK_F12]         = Qt::Key_F12;

        _keyMap[VK_SNAPSHOT]    = Qt::Key_Print;
        _keyMap[VK_SCROLL]      = Qt::Key_ScrollLock;
        _keyMap[VK_PAUSE]       = Qt::Key_Pause;

        _keyMap[VK_OEM_7]       = Qt::Key_twosuperior;
        _keyMap[0x31]           = Qt::Key_Ampersand;
        _keyMap[0x32]           = Qt::Key_AsciiTilde;
        _keyMap[0x33]           = Qt::Key_QuoteDbl;
        _keyMap[0x34]           = Qt::Key_Apostrophe;
        _keyMap[0x35]           = Qt::Key_ParenLeft;
        _keyMap[0x36]           = Qt::Key_Minus;
        _keyMap[0x37]           = Qt::Key_Egrave;
        _keyMap[0x38]           = Qt::Key_Underscore;
        _keyMap[0x39]           = Qt::Key_Ccedilla;
        _keyMap[0x30]           = Qt::Key_Agrave;
        _keyMap[VK_OEM_4]       = Qt::Key_ParenRight;
        _keyMap[VK_OEM_PLUS]    = Qt::Key_Equal;
        _keyMap[VK_BACK]        = Qt::Key_Backspace;

        _keyMap[VK_TAB]         = Qt::Key_Tab;
        _keyMap[0x41]           = Qt::Key_A;
        _keyMap[0x5A]           = Qt::Key_Z;
        _keyMap[0x45]           = Qt::Key_E;
        _keyMap[0x52]           = Qt::Key_R;
        _keyMap[0x54]           = Qt::Key_T;
        _keyMap[0x59]           = Qt::Key_Y;
        _keyMap[0x55]           = Qt::Key_U;
        _keyMap[0x49]           = Qt::Key_I;
        _keyMap[0x4F]           = Qt::Key_O;
        _keyMap[0x50]           = Qt::Key_P;
        _keyMap[VK_OEM_6]       = Qt::Key_Acircumflex;
        _keyMap[VK_OEM_1]       = Qt::Key_Dollar;
        _keyMap[VK_RETURN]      = Qt::Key_Return;

        _keyMap[VK_CAPITAL]     = Qt::Key_CapsLock;
        _keyMap[0x51]           = Qt::Key_Q;
        _keyMap[0x53]           = Qt::Key_S;
        _keyMap[0x44]           = Qt::Key_D;
        _keyMap[0x46]           = Qt::Key_F;
        _keyMap[0x47]           = Qt::Key_G;
        _keyMap[0x48]           = Qt::Key_H;
        _keyMap[0x4A]           = Qt::Key_J;
        _keyMap[0x4B]           = Qt::Key_K;
        _keyMap[0x4C]           = Qt::Key_L;
        _keyMap[0x4D]           = Qt::Key_M;
        _keyMap[VK_OEM_3]       = Qt::Key_Ugrave;
        _keyMap[VK_OEM_5]       = Qt::Key_Asterisk;

        _keyMap[VK_LSHIFT]      = Qt::Key_Shift;
        _keyMap[0x57]           = Qt::Key_W;
        _keyMap[0x58]           = Qt::Key_X;
        _keyMap[0x43]           = Qt::Key_C;
        _keyMap[0x56]           = Qt::Key_V;
        _keyMap[0x42]           = Qt::Key_B;
        _keyMap[0x4E]           = Qt::Key_N;
        _keyMap[VK_OEM_COMMA]   = Qt::Key_Comma;
        _keyMap[VK_OEM_PERIOD]  = Qt::Key_Semicolon;
        _keyMap[VK_OEM_2]       = Qt::Key_Colon;
        _keyMap[VK_OEM_8]       = Qt::Key_Exclam;
        _keyMap[VK_RSHIFT]      = Qt::Key_Shift;

        _keyMap[VK_LCONTROL]    = Qt::Key_Control;
        _keyMap[VK_LWIN]        = Qt::Key_Meta;
        _keyMap[VK_LMENU]       = Qt::Key_Alt;
        _keyMap[VK_SPACE]       = Qt::Key_Space;
        _keyMap[VK_RMENU]       = Qt::Key_AltGr;
        _keyMap[VK_RWIN]        = Qt::Key_Meta;
        _keyMap[VK_APPS]        = Qt::Key_Menu;
        _keyMap[VK_RCONTROL]    = Qt::Key_Control;

        _keyMap[VK_INSERT]      = Qt::Key_Insert;
        _keyMap[VK_HOME]        = Qt::Key_Home;
        _keyMap[VK_PRIOR]       = Qt::Key_PageUp;
        _keyMap[VK_DELETE]      = Qt::Key_Delete;
        _keyMap[VK_END]         = Qt::Key_End;
        _keyMap[VK_NEXT]        = Qt::Key_PageDown;

        _keyMap[VK_LEFT]        = Qt::Key_Left;
        _keyMap[VK_UP]          = Qt::Key_Up;
        _keyMap[VK_RIGHT]       = Qt::Key_Right;
        _keyMap[VK_DOWN]        = Qt::Key_Down;

        _keyMap[VK_NUMLOCK]     = Qt::Key_NumLock;
        _keyMap[VK_DIVIDE]      = Qt::Key_Slash;
        _keyMap[VK_MULTIPLY]    = Qt::Key_Asterisk;
        _keyMap[VK_SUBTRACT]    = Qt::Key_Minus;
        _keyMap[VK_NUMPAD7]     = Qt::Key_7;
        _keyMap[VK_NUMPAD8]     = Qt::Key_8;
        _keyMap[VK_NUMPAD9]     = Qt::Key_9;
        _keyMap[VK_ADD]         = Qt::Key_Plus;
        _keyMap[VK_NUMPAD4]     = Qt::Key_4;
        _keyMap[VK_NUMPAD5]     = Qt::Key_5;
        _keyMap[VK_NUMPAD6]     = Qt::Key_6;
        _keyMap[VK_NUMPAD1]     = Qt::Key_1;
        _keyMap[VK_NUMPAD2]     = Qt::Key_2;
        _keyMap[VK_NUMPAD3]     = Qt::Key_3;
        _keyMap[VK_RETURN]      = Qt::Key_Enter;
        _keyMap[VK_NUMPAD0]     = Qt::Key_0;
        _keyMap[VK_DECIMAL]     = Qt::Key_Period;

        return _keyMap;
    }

    static KeyStringMap keyStringMap()
    {
        static KeyStringMap _keyStringMap;

        _keyStringMap[Qt::Key_Control] = "CTRL";
        _keyStringMap[Qt::Key_Shift]   = "SHIFT";
        _keyStringMap[Qt::Key_Alt]     = "ALT";
        _keyStringMap[Qt::Key_Meta]    = "WINDOWS";
        _keyStringMap[Qt::Key_AltGr]   = "ALTGR";

        return _keyStringMap;
    }
};

Constant KEY_MAP        = KeyMapping::keyMap();
Constant KEY_STRING_MAP = KeyMapping::keyStringMap();

Constant KEY_TO_STRING = [](int keyCode) { return QKeySequence(keyCode).toString(); };

class KeyLogger : public QObject, boost::noncopyable
{
    Q_OBJECT

    typedef Shortcut Sequence;

    struct DelayedNotifier      // RAII class to be able to send keystrokes 
    {                           // back to the os before acting on them
        DelayedNotifier(bool);  // Avoid weird freezes on Windows
        ~DelayedNotifier();
        private : bool keyDown_;
    };

    public :
        static KeyLogger & instance();

        static QKeySequence keySequence(const Sequence &);
        static QString sequenceString(const Sequence &);

        Q_SIGNAL void sequence(const Sequence &, bool);

    private :
        KeyLogger();
        static void clean();

        static LRESULT WINAPI hookCallback(int, WPARAM, LPARAM);
        inline void notify(bool);
        
        HHOOK hHook_;
        Sequence sequence_;
};

#endif // KEYLOGGER_H