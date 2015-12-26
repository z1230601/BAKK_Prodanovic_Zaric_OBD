#include "ObdCommandTest.h"
#include "../src/ObdCommand.h"

void ObdCommandTest::setUp() {
    obdcommand_for_test_ = new ObdCommand(sid, pid, minVal, maxVal, unit, description, data_bytes_returned);
}

void ObdCommandTest::tearDown() {
    delete obdcommand_for_test_;
}

void ObdCommandTest::test() {

}

