#include "../src/BigInteger.h"
#include "gtest/gtest.h"
#include "Random.h"
#include "stack_calc.h"
#include "../src/exceptions.h"

static void VerifyRemainderString(std::string opstring)
{
    StackCalc sc(opstring);
    while (sc.DoNextOperation())
    {
        ASSERT_EQ(sc.snCalc.top().to_string(), sc.myCalc.top().to_string());
    }
}

static void VerifyIdentityString(std::string opstring1, std::string opstring2)
{
    StackCalc sc1(opstring1);
    while (sc1.DoNextOperation())
    {
        //Run the full calculation
        sc1.DoNextOperation();
    }

    StackCalc sc2(opstring2);
    while (sc2.DoNextOperation())
    {
        //Run the full calculation
        sc2.DoNextOperation();
    }
    ASSERT_EQ(sc1.snCalc.top().to_string(), sc2.snCalc.top().to_string());
}

static byte_array GetRandomByteArray(Random random, int size)
{
    return MyBigIntImp::GetRandomByteArray(random, size);
}

static byte_array GetRandomByteArray(Random random)
{
    return GetRandomByteArray(random, random.Next(1, 100));
}


static std::string Print(byte_array bytes)
{
    return MyBigIntImp::Print(bytes);
}

TEST(remainder_tests, RunRemainderPositive) {
    int s_samples = 10;
    Random s_random(100);

    byte_array tempByteArray1;
    byte_array tempByteArray2;

    // Remainder Method - Two Large BigIntegers
    for (int i = 0; i < s_samples; i++)
    {
        tempByteArray1 = GetRandomByteArray(s_random);
        tempByteArray2 = GetRandomByteArray(s_random);
        VerifyRemainderString(Print(tempByteArray1) + Print(tempByteArray2) + "bRemainder");
    }

    // Remainder Method - Two Small BigIntegers
    for (int i = 0; i < s_samples; i++)
    {
        tempByteArray1 = GetRandomByteArray(s_random, 2);
        tempByteArray2 = GetRandomByteArray(s_random, 2);
        VerifyRemainderString(Print(tempByteArray1) + Print(tempByteArray2) + "bRemainder");
    }

    // Remainder Method - one large and one small BigIntegers
    for (int i = 0; i < s_samples; i++)
    {
        tempByteArray1 = GetRandomByteArray(s_random);
        tempByteArray2 = GetRandomByteArray(s_random, 2);
        VerifyRemainderString(Print(tempByteArray1) + Print(tempByteArray2) + "bRemainder");

        tempByteArray1 = GetRandomByteArray(s_random, 2);
        tempByteArray2 = GetRandomByteArray(s_random);
        VerifyRemainderString(Print(tempByteArray1) + Print(tempByteArray2) + "bRemainder");
    }
}

TEST(remainder_tests, RunRemainderNegative) {
    int s_samples = 10;
    Random s_random(100);

    byte_array tempByteArray1;
    byte_array tempByteArray2;

    // Remainder Method - one large BigIntegers and zero
    for (int i = 0; i < s_samples; i++)
    {
        tempByteArray1 = GetRandomByteArray(s_random);
        tempByteArray2 = byte_array{ 0 };
        VerifyRemainderString(Print(tempByteArray1) + Print(tempByteArray2) + "bRemainder");

        EXPECT_THROW(VerifyRemainderString(Print(tempByteArray2) + Print(tempByteArray1) + "bRemainder"), DivideByZero);
    }

    // Remainder Method - one small BigIntegers and zero
    for (int i = 0; i < s_samples; i++)
    {
        tempByteArray1 = GetRandomByteArray(s_random, 2);
        tempByteArray2 = byte_array{ 0 };
        VerifyRemainderString(Print(tempByteArray1) + Print(tempByteArray2) + "bRemainder");

        EXPECT_THROW(VerifyRemainderString(Print(tempByteArray2) + Print(tempByteArray1) + "bRemainder"), DivideByZero);
    }
}

TEST(remainder_tests, RunRemainderBoundary) {
    // Check interesting cases for boundary conditions
    // You'll either be shifting a 0 or 1 across the boundary
    // 32 bit boundary  n2=0
    VerifyRemainderString(std::to_string(pow(2, 32)) + " 2 bRemainder");

    // 32 bit boundary  n1=0 n2=1
    VerifyRemainderString(std::to_string(pow(2, 33)) + " 2 bRemainder");
}

TEST(remainder_tests, RunRemainderAxioms) {
    int s_samples = 10;
    Random s_random(100);

    // Axiom: X%1 = 0
    auto int_max_value = std::to_string(std::numeric_limits<int>::max());
    auto long_max_value = std::to_string(std::numeric_limits<long>::max());
    VerifyIdentityString(BigInteger::one().to_string() + " " + int_max_value + " bRemainder", BigInteger::zero().to_string());
    VerifyIdentityString(BigInteger::one().to_string() + " " + long_max_value + " bRemainder", BigInteger::zero().to_string());

    for (int i = 0; i < s_samples; i++)
    {
        auto randBigInt = Print(GetRandomByteArray(s_random));
        VerifyIdentityString(BigInteger::one().to_string() + " " + randBigInt + "bRemainder", BigInteger::zero().to_string());
    }

    // Axiom: 0%X = 0
    VerifyIdentityString(int_max_value + " " + BigInteger::zero().to_string() + " bRemainder", BigInteger::zero().to_string());
    VerifyIdentityString(long_max_value + " " + BigInteger::zero().to_string() + " bRemainder", BigInteger::zero().to_string());

    for (int i = 0; i < s_samples; i++)
    {
        auto randBigInt = Print(GetRandomByteArray(s_random));
        VerifyIdentityString(randBigInt + BigInteger::zero().to_string() + " bRemainder", BigInteger::zero().to_string());
    }

    // Axiom: X%X = 0
    VerifyIdentityString(int_max_value + " " + int_max_value + " bRemainder", BigInteger::zero().to_string());
    VerifyIdentityString(long_max_value + " " + long_max_value + " bRemainder", BigInteger::zero().to_string());

    for (int i = 0; i < s_samples; i++)
    {
        auto randBigInt = Print(GetRandomByteArray(s_random));
        VerifyIdentityString(randBigInt + randBigInt + "bRemainder", BigInteger::zero().to_string());
    }

    // Axiom: X%(X + Y) = X where Y is 1 if x>=0 and -1 if x<0
    VerifyIdentityString((BigInteger(std::numeric_limits<int>::max()) + BigInteger(1)).to_string() + " " + int_max_value + " bRemainder", int_max_value);
    VerifyIdentityString((BigInteger(std::numeric_limits<int64_t>::max()) + BigInteger(1)).to_string() + " " + long_max_value + " bRemainder", long_max_value);

    for (int i = 0; i < s_samples; i++)
    {
        auto test = GetRandomByteArray(s_random);
        auto randBigInt = Print(test);
        BigInteger modify(1);
        if ((test[test.size() - 1] & 0x80) != 0)
        {
            modify = BigInteger::negate(modify);
        }
        VerifyIdentityString(randBigInt + modify.to_string() + " bAdd " + randBigInt + "bRemainder", randBigInt.substr(0, randBigInt.size() - 1));
    }
}