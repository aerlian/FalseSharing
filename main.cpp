#include <benchmark/benchmark.h>
#include <vector>
#include <thread>

constexpr size_t iterations = 1'000'000;
constexpr size_t thread_count = 8;

struct unaligned_thing {
    long X;
};

std::vector<unaligned_thing> unaligned_vec{thread_count};

struct alignas(64) aligned_thing {
    long X;
};

std::vector<aligned_thing> aligned_vec{thread_count};

template<typename TThing>
void onWrite(TThing &t)
{
    for(long j = 0; j < iterations; j++){
        t.X = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    }
}

static void BM_AllowFalseSharing(benchmark::State& state){
    auto &item = unaligned_vec[state.thread_index()];
    for (auto _ : state) {
        onWrite(item);
    }
}

static void BM_DisallowFalseSharing(benchmark::State& state){
    auto &item = aligned_vec[state.thread_index()];
    for (auto _ : state) {
        onWrite(item);
    }
}

BENCHMARK(BM_AllowFalseSharing)->Threads(thread_count);
BENCHMARK(BM_DisallowFalseSharing)->Threads(thread_count);

BENCHMARK_MAIN();