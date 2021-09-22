#ifndef TEST_H
#define TEST_H

#include <qtest.h>

#define EPSILON 1E-15

#define VERIFY(statement, description) \
do {\
    if (!QTest::qVerify(static_cast<bool>(statement), #statement, description, __FILE__, __LINE__))\
        return;\
} while (false)

#define FAIL(message) \
do {\
    QTest::qFail(static_cast<const char *>(message), __FILE__, __LINE__);\
    return;\
} while (false)

#define ISEQUAL(val1, val2) ((val1 - val2 < EPSILON) && (val1 - val2 > -EPSILON))

#endif // TEST_H
