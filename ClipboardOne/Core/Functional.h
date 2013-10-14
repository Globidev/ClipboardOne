#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <boost/preprocessor.hpp>

#define JS_UNAMED_VALUE const QJSValue &
#define NAMED_VALUE_N(z, n, x) BOOST_PP_COMMA_IF(n) x##n
#define JS_NAMED_VALUE_N(z, n, x) BOOST_PP_COMMA_IF(n) JS_UNAMED_VALUE x##n

#define PP_FOR_BIND_END(r, state) BOOST_PP_NOT_EQUAL(state, 20)
#define PP_INC(r, state) BOOST_PP_INC(state)

#define DEFINE_BIND(r, n)                                                    \
        Q_INVOKABLE QJSValue bind(JS_UNAMED_VALUE func,                      \
                                  BOOST_PP_REPEAT(n, JS_NAMED_VALUE_N, arg)) \
        {                                                                    \
            return jsBind(func, BOOST_PP_REPEAT(n, NAMED_VALUE_N, arg));     \
        }

#define DEFINE_BINDS BOOST_PP_FOR(1, PP_FOR_BIND_END, PP_INC, DEFINE_BIND)

class Functional : public QObject, boost::noncopyable
{
    Q_OBJECT

    public :
        static Functional & instance();

        DEFINE_BINDS

    private :
        Functional();
};

Constant FUNCTIONAL_OBJECT_NAME = "Functional";

#endif // FUNCTIONAL_H
