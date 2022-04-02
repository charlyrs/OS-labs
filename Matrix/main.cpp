#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <ctime>
#include <map>

std::mutex mutex;

std::vector<std::vector<int>> generate_matrix(int size) {
    std::vector<std::vector<int>> res(size);
    for (auto &x : res) {
        for (size_t i = 0; i < size; ++i) {
            int num = (rand() % 20);
            x.push_back(num);
        }
    }
    return res;
}

void multiply_blocks(const std::vector<std::vector<int>> &A,
                     const std::vector<std::vector<int>> &B,
                     std::vector<std::vector<int>> &D,
                     size_t start1, size_t start2, size_t mul_st, size_t count) {
    for (size_t i = start1; i < start1 + count; i++) {
        for (size_t j = start2; j < start2 + count; j++) {
            int sum = 0;
            for (size_t k = 0; k < count; k++)
                sum += A[i][mul_st + k] * B[mul_st + k][j];
            std::unique_lock<std::mutex> locker(mutex);
            D[i][j] += sum;
            locker.unlock();
        }
    }
}

unsigned int multiply_matrix_with_threads(const std::vector<std::vector<int>> &A,
                                          const std::vector<std::vector<int>> &B,
                                          std::vector<std::vector<int>> &D,
                                          unsigned int blocks) {
    size_t size = A.size();
    size_t count = size / blocks;
    std::vector<std::thread> threads;
    for (size_t i = 0; i < size; i += count) {
        for (size_t j = 0; j < size; j += count) {
            for (size_t k = 0; k < size; k += count) {
                std::thread thread(multiply_blocks, std::ref(A), std::ref(B), std::ref(D), i, j, k, count);
                threads.push_back(std::move(thread));
            }
        }
    }
    for (auto &x: threads) x.join();
    return threads.size();
}

std::map<unsigned int, std::pair<unsigned int, unsigned int>> experiment_threads(const std::vector<std::vector<int>> &A,
                                                                                 const std::vector<std::vector<int>> &B,
                                                                                 std::vector<std::vector<int>> &D) {
    std::map<unsigned int, std::pair<unsigned int, unsigned int>> res;
    size_t N = A.size();
    for (size_t i = 1; i <= N; i++) {
        if (N % i != 0) continue;
        unsigned int one = clock();
        auto threads = multiply_matrix_with_threads(A, B, D, i);
        unsigned int two = clock();
        res[i] = std::make_pair(threads, two - one);
    }
    return res;
}

unsigned int experiment_basic_multiplication(const std::vector<std::vector<int>> &A,
                                             const std::vector<std::vector<int>> &B,
                                             std::vector<std::vector<int>> &D) {
    unsigned int start = clock();
    multiply_blocks(A, B, D, 0, 0, 0, A.size());
    unsigned int end = clock();
    return end - start;
}

void print_matrix(const std::vector<std::vector<int>> &vec) {
    for (auto &x : vec) {
        for (auto y : x) std::cout << y << ' ';
        std::cout << '\n';
    }
    std::cout << '\n';
}

void print_map(std::map<unsigned int, std::pair<unsigned int, unsigned int>> map) {
    auto it = map.begin();
    while (it != map.end()) {
        std::cout << "Blocks: " << it->first << ", time: "
                  << it->second.second << ", threads: " << it->second.first << '\n';
        it++;
    }
}

int main() {
    srand(time(nullptr));
    int N = 20;
    std::vector<int> temp(N, 0);
    std::vector<std::vector<int>> a = generate_matrix(N), b = generate_matrix(N), d(N, temp);
    std::cout << "Basic multiplication time: " << experiment_basic_multiplication(a, b, d) << '\n';
    std::vector<std::vector<int>> dest(N, temp);
    print_map(experiment_threads(a, b, dest));
    return 0;
}
