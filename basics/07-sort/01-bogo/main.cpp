#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

bool isSorted(const std::vector<int> &arr)
{
    for (size_t i{1}; i < arr.size(); ++i)
    {
        if (arr[i - 1] > arr[i])
            return false;
    }
    return true;
}

void shuffle(std::vector<int> &arr)
{
    static std::random_device rd;
    static std::mt19937 g(rd());
    std::shuffle(arr.begin(), arr.end(), g);
}

void bogoSort(std::vector<int> &arr)
{
    int32_t attempts{0};

    while (!isSorted(arr))
    {
        shuffle(arr);
        attempts++;
    }
    std::cout << "Sorted after " << attempts << " shuffles." << std::endl;
}

int main()
{
    std::vector<int> arr{3, 22, 19, 5, 6, 83, 43, 4, 3, 27};

    std::cout << "BEFORE: ";
    for (auto n : arr)
        std::cout << n << " ";
    std::cout << std::endl;

    bogoSort(arr);

    std::cout << "AFTER: ";
    for (auto n : arr)
        std::cout << n << " ";
    std::cout << std::endl;

    return 0;
}