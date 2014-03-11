#include <igloo/igloo.h>
#include "benchmark.h"
using namespace igloo;

int main(int argc, const char *argv[])
{
    int ret = TestRunner::RunAllTests(argc, argv);
    if (ret == 0) run_benchmark();
    return ret;
}
