#include <string>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4141) // 'inline': used more than once
#endif
#include <benchmark/benchmark.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

static void BM_StringCreation(benchmark::State& state)
{
  for (auto _ : state)
    std::string empty_string;
}
BENCHMARK(BM_StringCreation);

BENCHMARK_MAIN();
