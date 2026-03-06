#include "doctest.h"
#include "math_utils.h"

TEST_SUITE("clamp") {

    TEST_CASE("within bounds returns value unchanged") {
        CHECK(clamp(5, 0, 10) == 5);
        CHECK(clamp(0, 0, 10) == 0);   // edge: at min
        CHECK(clamp(10, 0, 10) == 10); // edge: at max
    }

    TEST_CASE("clamps to min when below") {
        CHECK(clamp(-1, 0, 10) == 0);
        CHECK(clamp(-999, 0, 10) == 0);
    }

    TEST_CASE("clamps to max when above") {
        CHECK(clamp(11, 0, 10) == 10);
        CHECK(clamp(999, 0, 10) == 10);
    }
}

TEST_SUITE("moving_average") {

    TEST_CASE("basic average") {
        uint32_t buf[] = {10, 20, 30, 40};
        CHECK(moving_average(buf, 4) == 25);
    }

    TEST_CASE("single element") {
        uint32_t buf[] = {42};
        CHECK(moving_average(buf, 1) == 42);
    }

    TEST_CASE("null or zero length returns 0") {
        CHECK(moving_average(nullptr, 0) == 0);
    }
}