QT += testlib
QT -= gui
QT += sql

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testscontacts.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../contacts/release/ -lcontacts
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../contacts/debug/ -lcontacts
else:unix: LIBS += -L$$OUT_PWD/../contacts/ -lcontacts

INCLUDEPATH += $$PWD/../contacts
DEPENDPATH += $$PWD/../contacts
