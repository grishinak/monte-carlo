#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include <atomic>

// Функция для подсчета точек внутри круга
int countPointsInsideCircle(int totalPoints) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    
    int insideCircle = 0;
    for (int i = 0; i < totalPoints; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        if (x * x + y * y <= 1.0) {
            insideCircle++;
        }
    }
    return insideCircle;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <number of threads>\n";
        return 1;
    }
    
    int numThreads = std::stoi(argv[1]);
    int totalPoints = 1000000; // Общее количество точек
    
    int pointsPerThread = totalPoints / numThreads;
    std::atomic<int> totalInsideCircle(0);
    
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&]() {
            int insideCircle = countPointsInsideCircle(pointsPerThread);
            totalInsideCircle += insideCircle;
        });
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    double pi = 4.0 * totalInsideCircle / totalPoints;
    std::cout << "Estimated value of Pi: " << pi << std::endl;
    
    return 0;
}
