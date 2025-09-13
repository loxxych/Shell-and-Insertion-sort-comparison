#include <iostream>
#include <vector>
#include <random>
#include <format>

std::pair<size_t, size_t> shellSortOperations(std::vector<int> arr) {
    // first - comparisons, second - swaps
    std::pair<size_t, size_t> res = {0, 0};

    size_t N = arr.size();
    for (size_t interval = N / 2; interval > 0; interval /= 2) {
        for (size_t i = interval; i < N; ++i) {
            int tmp = arr[i];
            size_t j;
            for (j = i; j >= interval && arr[j - interval] > tmp; j -= interval) {
                arr[j] = arr[j - interval]; // one swap

                res.second++;
                res.first++; // one comparison for each iteration
            }
            res.first++; // (last comparison) loop exit condition

            arr[j] = tmp;
        }
    }
    return res;
}

std::pair<size_t, size_t> insertionSortOperations(std::vector<int> arr) {
    // first - comparisons, second - swaps
    std::pair<size_t, size_t> res = {0, 0};

    size_t N = arr. size();
    for (size_t i = 1; i < N; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // swap
            j = j - 1;

            res.first++;
            res.second++;
        }
        res.first++; // exit condition

        arr[j + 1] = key;
    }
    return res;
}


int main()
{
    int valueStartGap = 1;
    int valueEndGap = 100;

    std::cout << "               ||          Comparisons          ||            Swaps             |\n";
    std::cout << "        N      ||---------------------------------------------------------------|\n";
    std::cout << "               ||   Insertion   |     Shell     ||   Insertion   |     Shell    |\n";
    std::cout << "---------------||---------------------------------------------------------------|\n";

    for (size_t n = 10; n < 10000; n *= 2) {
        std::uniform_int_distribution<int> distribution(valueStartGap, valueEndGap);
        std::mt19937_64 mt;
        mt.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());

        // create array of size n and fill with random values
        std::vector<int> arr(n);
        for (size_t i = 0; i < n; ++i) { arr[i] = distribution(mt); }

        // num of operations as pairs: first el - comparisons, second el - swaps
        std::pair<size_t, size_t> shellOperations = shellSortOperations(arr);
        std::pair<size_t, size_t> insertionOperations = insertionSortOperations(arr);

        std::cout << std::format("\t{}\t||\t{}\t|\t{}\t||\t{}\t|\t{}\t|\n", n, insertionOperations.first,
            shellOperations.first, insertionOperations.second, shellOperations.second);

    }

    return 0;
}