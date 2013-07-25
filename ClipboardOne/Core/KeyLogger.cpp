#include "stdafx.h"
#include "KeyLogger.h"

KeyLogger & KeyLogger::instance()
{
    static KeyLogger logger;
    return logger;
}

KeyLogger::KeyLogger() : QObject()
{
    hHook_ = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)hookCallback, nullptr, 0);
    qAddPostRoutine(clean);
}

void KeyLogger::clean()
{
    UnhookWindowsHookEx(instance().hHook_);
}

LRESULT WINAPI KeyLogger::hookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    auto & self = instance();
    auto hookStruct = (KBDLLHOOKSTRUCT*)lParam;

    std::unique_ptr<DelayedNotifier> notifier;

    if(nCode == HC_ACTION)
    {
        auto keyFound = KEY_MAP.find(hookStruct->vkCode);
        int keyCode = (keyFound != KEY_MAP.end() ? keyFound->second : -1);

        if(wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
        {
            self.sequence_.insert(keyCode);
            notifier.reset(new DelayedNotifier(true));
        }
        else if(wParam == WM_KEYUP || wParam == WM_SYSKEYUP)
        {
            self.sequence_.erase(keyCode);
            notifier.reset(new DelayedNotifier(false));
        }
    }

    return CallNextHookEx(self.hHook_, nCode, wParam, lParam);
}

void KeyLogger::notify(bool keyDown)
{
    if(sequence_.size()) // no keys ...
        Q_EMIT sequence(sequence_, keyDown);
}

QKeySequence KeyLogger::keySequence(const Sequence & sequence)
{
    int sum = std::accumulate(sequence.begin(),
                              sequence.end(),
                              0, std::plus<int>());
    return QKeySequence(sum);
}

QString KeyLogger::sequenceString(const Sequence & sequence)
{
    QStringList keys;

    std::vector<int> keyList(sequence.cbegin(), sequence.cend());
    std::sort(keyList.begin(), keyList.end(), std::greater<int>());

    for(int keyCode : keyList)
    {
        auto stringFound = KEY_STRING_MAP.find(keyCode);

        keys << (stringFound != KEY_STRING_MAP.end() ? 
                 stringFound->second :
                 KEY_TO_STRING(keyCode));
    }

    return keys.join(" + ");
}

KeyLogger::DelayedNotifier::DelayedNotifier(bool keyDown) : 
    keyDown_(keyDown)
{

}

KeyLogger::DelayedNotifier::~DelayedNotifier()
{
    instance().notify(keyDown_);
}