QT      += core sql

# 引入源码
HEADERS  += $$PWD/zsqlitecipherdriver.h \
            $$PWD/zsqliteciphercachedresult.h

SOURCES  += $$PWD/zsqlitecipherdriver.cpp \
            $$PWD/zsqliteciphercachedresult.cpp
# 引入查找路径
INCLUDEPATH += $$PWD
