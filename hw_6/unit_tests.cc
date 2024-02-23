#include <gtest/gtest.h>
#include "stopwatch.h"
#include "RandomProcess.h"
#include "filter.h"
#include "integrator.h"

// Test case for Stopwatch class
TEST(StopwatchTest, StartStopReset) {
    Stopwatch w;
    w.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Sleep for 1 second
    w.stop();
    ASSERT_GE(w.get_seconds(), 1.0); // Expect elapsed time to be at least 1 second
    w.reset();
    ASSERT_EQ(w.get_seconds(), 0.0); // Expect elapsed time to be 0 after reset
}

// Test case for RandomProcess class
TEST(RandomProcessTest, SendRandomValues) {
    RandomProcess r("random numbers");
    elma::Channel link("link");
    double last_value = 0;
    r.init();
    r.start();
    for (int i = 0; i < 10; ++i) {
        r.update();
        ASSERT_NE(link.latest(), last_value); // Expect each value sent to be different from the last one
        last_value = link.latest();
    }
}

// Test case for Filter class
TEST(FilterTest, RunningAverage) {
    Filter f("filter");
    elma::Channel link("link");
    f.init();
    f.start();
    for (int i = 1; i <= 10; ++i) {
        link.send(i);
    }
    ASSERT_DOUBLE_EQ(f.value(), 5.5); // Expect running average of 1 to 10 to be 5.5
}

// Test case for Integrator class
TEST(IntegratorTest, NumericalIntegration) {
    Integrator i("integrator", 0.1); // delta = 0.1
    elma::Channel link("link");
    i.init();
    i.start();
    for (int i = 1; i <= 10; ++i) {
        link.send(i);
    }
    // Expect integral of values from 1 to 10 to be approximately 27.5 (sum of 1 to 10 multiplied by delta)
    ASSERT_NEAR(i.value(), 27.5, 0.01);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
