#include "stdafx.h"

QDataStream & operator<<(QDataStream & s, const Shortcut & set)
{
    s << set.size();
    for(auto i : set) s << i;
    return s;
}

QDataStream & operator>>(QDataStream & s, Shortcut & set)
{
    int size;
    s >> size;
    for(int i(0); i < size; ++ i)
    {
        int v;
        s >> v;
        set.insert(v);
    }
    return s;
}