add_executable(
        unit_tests
        bigint_test_sa.cpp
        BigInteger_AddTests.cpp
        BigInteger_SubtractTests.cpp
        TobyteArray.cpp
        MyBigInt.cpp
        MyBigInt.h
        Random.cpp
        Random.h
        BitArray.cpp
        BitArray.h
        scratch_test.cpp
        stack_calc.cpp
        utils.h
        utils.cpp
        op_leftshift.cpp
        op_rightshift.cpp
        op_xor.cpp
        op_or.cpp
        op_not.cpp
        op_modulus.cpp
        op_and.cpp
        op_decrement.cpp
        op_increment.cpp
        op_divide.cpp
        op_multiply.cpp
        IsEven.cpp
        IsOne.cpp
        IsZero.cpp
        IsPowerOfTwo.cpp
        max.cpp
        min.cpp
        sign.cpp
        remainder.cpp
        pow.cpp
        modpow.cpp
        log.cpp
        log02.cpp
        log10.cpp
        divide.cpp
        multiply.cpp
        absolutevalue.cpp
        divrem.cpp
        gcd.cpp
        properties.cpp)

target_link_libraries(
        unit_tests
        gtest_main
        BigInteger
)

add_test(
        NAME
        add
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)
