#include "../src/BigInteger.h"
#include "gtest/gtest.h"
#include "Random.h"
#include "stack_calc.h"
#include "utils.h"
#include "../src/exceptions.h"

static void VerifyGCDString(std::string opstring) {
    StackCalc sc(opstring);
    while (sc.DoNextOperation()) {
        ASSERT_EQ(sc.snCalc.top().to_string(), sc.myCalc.top().to_string());
    }
}

static void VerifyIdentityString(std::string opstring1, std::string opstring2) {
    StackCalc sc1(opstring1);
    while (sc1.DoNextOperation()) {
        //Run the full calculation
        sc1.DoNextOperation();
    }

    StackCalc sc2(opstring2);
    while (sc2.DoNextOperation()) {
        //Run the full calculation
        sc2.DoNextOperation();
    }
    ASSERT_EQ(sc1.snCalc.top().to_string(), sc2.snCalc.top().to_string());
}

static byte_array GetRandomByteArray(Random random, int size) {
    return MyBigIntImp::GetNonZeroRandomByteArray(random, size);
}

static byte_array GetRandomByteArray(Random random) {
    return GetRandomByteArray(random, random.Next(1, 100));
}


static std::string Print(byte_array bytes) {
    return MyBigIntImp::Print(bytes);
}

TEST(gcd, RunGCDTests) {
    int s_samples = 10;
    Random s_random(100);
    byte_array tempByteArray1;
    byte_array tempByteArray2;

    // GCD Method - Two Large BigIntegers
    for (int i = 0; i < s_samples; i++) {
        tempByteArray1 = GetRandomByteArray(s_random);
        tempByteArray2 = GetRandomByteArray(s_random);
        VerifyGCDString(Print(tempByteArray1) + Print(tempByteArray2) + "bGCD");
    }

    // GCD Method - Two Small BigIntegers
    for (int i = 0; i < s_samples; i++) {
        tempByteArray1 = GetRandomByteArray(s_random, 2);
        tempByteArray2 = GetRandomByteArray(s_random, 2);
        VerifyGCDString(Print(tempByteArray1) + Print(tempByteArray2) + "bGCD");
    }

    // GCD Method - One large and one small BigIntegers
    for (int i = 0; i < s_samples; i++) {
        tempByteArray1 = GetRandomByteArray(s_random);
        tempByteArray2 = GetRandomByteArray(s_random, 2);
        VerifyGCDString(Print(tempByteArray1) + Print(tempByteArray2) + "bGCD");

        tempByteArray1 = GetRandomByteArray(s_random, 2);
        tempByteArray2 = GetRandomByteArray(s_random);
        VerifyGCDString(Print(tempByteArray1) + Print(tempByteArray2) + "bGCD");
    }

    // GCD Method - One large BigIntegers and zero
    for (int i = 0; i < s_samples; i++) {
        tempByteArray1 = GetRandomByteArray(s_random);
        tempByteArray2 = byte_array{0};
        VerifyGCDString(Print(tempByteArray1) + Print(tempByteArray2) + "bGCD");

        tempByteArray1 = byte_array{0};
        tempByteArray2 = GetRandomByteArray(s_random);
        VerifyGCDString(Print(tempByteArray1) + Print(tempByteArray2) + "bGCD");
    }

    // GCD Method - One small BigIntegers and zero
    for (int i = 0; i < s_samples; i++) {
        tempByteArray1 = GetRandomByteArray(s_random, 2);
        tempByteArray2 = byte_array{0};
        VerifyGCDString(Print(tempByteArray1) + Print(tempByteArray2) + "bGCD");

        tempByteArray1 = byte_array{0};
        tempByteArray2 = GetRandomByteArray(s_random, 2);
        VerifyGCDString(Print(tempByteArray1) + Print(tempByteArray2) + "bGCD");
    }

    // Identity GCD(GCD(x,y),z) == GCD(GCD(y,z),x)
    // Check some identities
    // (x+y)+z = (y+z)+x

    VerifyIdentityString(
            std::to_string(std::numeric_limits<int64_t>::max()) + " " +
            std::to_string(std::numeric_limits<int32_t>::max()) + " bGCD " +
            std::to_string(std::numeric_limits<int16_t>::max()) + " bGCD",
            std::to_string(std::numeric_limits<int32_t>::max()) + " " +
            std::to_string(std::numeric_limits<int16_t>::max()) + " bGCD " +
            std::to_string(std::numeric_limits<int64_t>::max()) + " bGCD"
    );

    auto x = GetRandomByteArray(s_random);
    auto y = GetRandomByteArray(s_random);
    auto z = GetRandomByteArray(s_random);

    VerifyIdentityString(Print(x) + Print(y) + Print(z) + "bGCD bGCD", Print(y) + Print(z) + Print(x) + "bGCD bGCD");
}