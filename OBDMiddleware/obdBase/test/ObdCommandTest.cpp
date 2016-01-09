#include "ObdCommandTest.h"
#include "../src/ObdCommand.h"
#include "../src/AbstractOBDValue.h"
#include <string>

void ObdCommandTest::setUp()
{
    obdcommand_under_test_ = new ObdCommand();

    input_.pid_ = 0x66;
    input_.description_ = "Luftmassenmesser";
    input_.validity_mapping_mode_ = ValidityMappingMode::AUTO;

    {
        OBDCommandValueInput value;
        value.is_mapping_ = false;
        value.name_ = "MAF Sensor A";
        value.bytes_ = 2;
        value.min_ = 0;
        value.max_ = 2047.96875;
        value.unit_ = "g/s";

        input_.values_.push_back(value);
    }
    {
        OBDCommandValueInput value;
        value.is_mapping_ = false;
        value.name_ = "MAF Sensor B";
        value.bytes_ = 2;
        value.min_ = 0;
        value.max_ = 2047.96875;
        value.unit_ = "g/s";

        input_.values_.push_back(value);
    }

    expected_sids_.push_back(1);
    expected_sids_.push_back(2);
}

void ObdCommandTest::tearDown()
{
    delete obdcommand_under_test_;
}

void ObdCommandTest::testConstruction()
{
    std::string expectedDescription = "";
    unsigned int expectedPid = 0;
    std::vector<unsigned int> expectedSids = { };

    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            obdcommand_under_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedPid, obdcommand_under_test_->getPid());
    CPPUNIT_ASSERT_EQUAL(expectedSids.size(),
            obdcommand_under_test_->getSids().size());
    CPPUNIT_ASSERT_EQUAL((size_t) 0,
            obdcommand_under_test_->getValues().size());
}

void ObdCommandTest::testParameterConstruction()
{
    unsigned int expectedPid = 0x65;
    std::string expectedDescription = "Zusätzliche Ein- und Ausgänge";

    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, expectedPid,
            expectedDescription);

    CPPUNIT_ASSERT_EQUAL(expectedDescription,
            obdcommand_under_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(expectedPid, obdcommand_under_test_->getPid());
    CPPUNIT_ASSERT_EQUAL(expected_sids_.size(),
            obdcommand_under_test_->getSids().size());
    CPPUNIT_ASSERT_EQUAL((size_t) 0,
            obdcommand_under_test_->getValues().size());
}

void ObdCommandTest::testInputStructConstruction()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, input_);

    CPPUNIT_ASSERT_EQUAL(expected_sids_.size(),
            obdcommand_under_test_->getSids().size());
    for(unsigned i = 0; i < expected_sids_.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expected_sids_.at(i),
                obdcommand_under_test_->getSids().at(i));
    }

    CPPUNIT_ASSERT_EQUAL(input_.pid_, obdcommand_under_test_->getPid());
    CPPUNIT_ASSERT_EQUAL(input_.description_,
            obdcommand_under_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(input_.values_.size(),
            obdcommand_under_test_->getValues().size());

}

void ObdCommandTest::testValidityMappingConstruction()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, input_);

    CPPUNIT_ASSERT_EQUAL(expected_sids_.size(),
            obdcommand_under_test_->getSids().size());
    for(unsigned int i = 0; i < expected_sids_.size(); i++)
    {
        CPPUNIT_ASSERT_EQUAL(expected_sids_.at(i),
                obdcommand_under_test_->getSids().at(i));
    }
    CPPUNIT_ASSERT_EQUAL(input_.description_,
            obdcommand_under_test_->getDescription());
    CPPUNIT_ASSERT_EQUAL(input_.pid_, obdcommand_under_test_->getPid());

    CPPUNIT_ASSERT_EQUAL(input_.values_.size(),
            obdcommand_under_test_->getValues().size());
}

void ObdCommandTest::testRequestString()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, input_);

    std::stringstream expected;
    expected << "0" << expected_sids_.at(0) << " " << std::hex << input_.pid_
            << std::dec;
    unsigned int selected_sid = 1;
    CPPUNIT_ASSERT_EQUAL(expected.str(),
            obdcommand_under_test_->getRequestString(selected_sid));

    expected.str("");
    expected << "0" << expected_sids_.at(1) << " " << std::hex << input_.pid_
            << std::dec;
    selected_sid = 2;
    CPPUNIT_ASSERT_EQUAL(expected.str(),
            obdcommand_under_test_->getRequestString(selected_sid));
}

void ObdCommandTest::testInterpretReceivedBytes()
{
    delete obdcommand_under_test_;
    obdcommand_under_test_ = new ObdCommand(expected_sids_, input_);

    uint8_t input_bytes[] = { 3, 2, 0, 4, 0 };
    double expected_result1 = 512;
    double expected_result2 = 1024;

    obdcommand_under_test_->interpretReceivedBytes(input_bytes);

    CPPUNIT_ASSERT_EQUAL((size_t) 2,obdcommand_under_test_->getValues().size());
    CPPUNIT_ASSERT_EQUAL(expected_result1, obdcommand_under_test_->getValues().at(0)->getInterpretedValue());
    CPPUNIT_ASSERT_EQUAL(expected_result2, obdcommand_under_test_->getValues().at(1)->getInterpretedValue());

}
