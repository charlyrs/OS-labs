#include <iostream>
#include <pthread.h>
#include <vector>
#include <ctime>
#include <map>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct ThreadParams {
    std::vector<std::vector<int>>& A;
    std::vector<std::vector<int>>& B;
    std::vector<std::vector<int>>& D;
    size_t start1, start2, mul_st, count;
    ThreadParams(std::vector<std::vector<int>>& a,
                 std::vector<std::vector<int>>& b,
                 std::vector<std::vector<int>>& d,
                 size_t i, size_t j, size_t k, size_t count) :
            A(a), B(b), D(d), start1(i), start2(j), mul_st(k), count(count) {}
};

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

void* multiply_blocks(void* params) {
    ThreadParams p = *(ThreadParams*)params;
    for (size_t i = p.start1; i < p.start1 + p.count; i++) {
        for (size_t j = p.start2; j < p.start2 + p.count; j++) {
            int sum = 0;
            for (size_t k = 0; k < p.count; k++)
                sum += p.A[i][p.mul_st + k] * p.B[p.mul_st + k][j];
            pthread_mutex_lock(&mutex);
            p.D[i][j] += sum;
            pthread_mutex_unlock(&mutex);
        }
    }
    return nullptr;
}

unsigned int multiply_matrix_with_threads(std::vector<std::vector<int>> &A,
                                          std::vector<std::vector<int>> &B,
                                          std::vector<std::vector<int>> &D,
                                          unsigned int blocks) {
    size_t size = A.size();
    size_t count = size / blocks;
    std::vector<pthread_t> threads(blocks*blocks*blocks);
    short threads_count = 0;
    for (size_t i = 0; i < size; i += count) {
        for (size_t j = 0; j < size; j += count) {
            for (size_t k = 0; k < size; k += count) {
                auto* params = new ThreadParams(A,B,D,i,j,k,count);
                pthread_create(&threads[threads_count], nullptr,&multiply_blocks,(void*)params);
                threads_count++;
            }
        }
    }
    for (auto &x: threads) pthread_join(x,nullptr);
    return threads.size();
}

std::map<unsigned int, std::pair<unsigned int, unsigned int>> experiment_threads(std::vector<std::vector<int>> &A,
                                                                                 std::vector<std::vector<int>> &B,
                                                                                 std::vector<std::vector<int>> &D) {
    std::map<unsigned int, std::pair<unsigned int, unsigned int>> res;
    size_t N = A.size();
    for (size_t i = 1; i <= N; i++) {
        if (N % i != 0) continue;
        std::vector<int> temp(N, 0);
        D = std::vector<std::vector<int>>(N,temp);
        unsigned int one = clock();
        auto threads = multiply_matrix_with_threads(A, B, D, i);
        unsigned int two = clock();
        res[i] = std::make_pair(threads, two - one);
    }
    return res;
}

unsigned int experiment_basic_multiplication(std::vector<std::vector<int>> &A,
                                             std::vector<std::vector<int>> &B,
                                             std::vector<std::vector<int>> &D) {
    unsigned int start = clock();
    auto* p = new ThreadParams(A, B, D, 0, 0, 0, A.size());
    multiply_blocks(p);
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