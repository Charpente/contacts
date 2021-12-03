#include <QtTest>
#include <QCoreApplication>
#include "../contacts/contacts.h"

// add necessary includes here

class TestsContacts : public QObject
{
    Q_OBJECT
    Contacts c;

public:
    TestsContacts();
    ~TestsContacts();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

TestsContacts::TestsContacts()
{

}

TestsContacts::~TestsContacts()
{

}

void TestsContacts::initTestCase()
{
    c.m_exitAsked = false;
}

void TestsContacts::cleanupTestCase()
{

}

void TestsContacts::test_case1()
{
    QCOMPARE(c.m_exitAsked,false);
}

QTEST_MAIN(TestsContacts)

#include "tst_testscontacts.moc"
