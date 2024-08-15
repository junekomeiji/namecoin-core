// Copyright (c) 2024 Rose Turing

#include <names/applications.h>
#include <names/records.h>
#include <string.h>
#include <test/util/setup_common.h>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(name_records_tests)

std::string test_domain = "namecoin.bit";
Record test_record(test_domain);

BOOST_AUTO_TEST_CASE( record_tests ){
    
    BOOST_TEST(test_record.getDomain() == "namecoin.bitaa");   

}

BOOST_AUTO_TEST_SUITE_END()

