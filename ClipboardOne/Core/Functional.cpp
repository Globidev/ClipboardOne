#include "stdafx.h"
#include "Functional.h"

Functional & Functional::instance()
{
    static Functional functional;
    return functional;
}

Functional::Functional() : QObject()
{
    setObjectName(FUNCTIONAL_OBJECT_NAME);
}
