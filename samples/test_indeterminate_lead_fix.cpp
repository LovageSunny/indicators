
#include <indicators/details/stream_helper.hpp>
#include <sstream>
#include <cassert>
#include <iostream>
#include <string>

int main() {
    // Test 1: Empty lead should not cause infinite loop
    // The function must return (no hang) and produce non-empty output
    {
        std::ostringstream os;
        indicators::details::IndeterminateProgressScaleWriter writer(os, 10, ".", "");
        writer.write(5);
        std::string out = os.str();
        assert(!out.empty());
        std::cout << "PASS: Empty lead at progress=5 -> \"" << out << "\" (len=" << out.size() << ")\n";
    }

    // Test 2: Normal lead (regression test) — output must contain the lead text
    {
        std::ostringstream os;
        indicators::details::IndeterminateProgressScaleWriter writer(os, 10, ".", "<==>");
        writer.write(5);
        std::string out = os.str();
        assert(out.find("<==>") != std::string::npos);
        std::cout << "PASS: Normal lead at progress=5 -> \"" << out << "\" (len=" << out.size() << ")\n";
    }

    // Test 3: Empty lead at end of bar
    {
        std::ostringstream os;
        indicators::details::IndeterminateProgressScaleWriter writer(os, 10, ".", "");
        writer.write(9);
        std::string out = os.str();
        assert(!out.empty());
        std::cout << "PASS: Empty lead at progress=9 -> \"" << out << "\" (len=" << out.size() << ")\n";
    }

    // Test 4: Empty lead at start of bar
    {
        std::ostringstream os;
        indicators::details::IndeterminateProgressScaleWriter writer(os, 10, ".", "");
        writer.write(0);
        std::string out = os.str();
        assert(!out.empty());
        std::cout << "PASS: Empty lead at progress=0 -> \"" << out << "\" (len=" << out.size() << ")\n";
    }

    // Test 5: Very wide bar with empty lead (stress test)
    {
        std::ostringstream os;
        indicators::details::IndeterminateProgressScaleWriter writer(os, 100, "=", "");
        writer.write(50);
        std::string out = os.str();
        assert(!out.empty());
        std::cout << "PASS: Empty lead, bar_width=100, progress=50 -> length=" << out.size() << "\n";
    }

    std::cout << "\nAll tests passed!\n";
    return 0;
}
