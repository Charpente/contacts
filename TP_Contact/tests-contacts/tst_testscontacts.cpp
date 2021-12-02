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
}

void TestsContacts::cleanupTestCase()
{

}

void TestsContacts::test_case1()
{
    //QCOMPARE(c.method(),0);
}

QTEST_MAIN(TestsContacts)

#include "tst_testscontacts.moc"
