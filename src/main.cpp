#include <atomic>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

int countPointsInsideCircle(int totalPoints) {
  std::random_device rd;  // объект для генерации случайных чисел
  std::mt19937 gen(rd());  // генератор псевдослучайных чисел
  std::uniform_real_distribution<> dis(
      -1.0,
      1.0);  // равномерное распределение от -1 до 1 (квадрат. сторона = 2, площадь = 4)

  int insideCircle = 0;
  for (int i = 0; i < totalPoints; ++i) {
    double x = dis(gen);
    double y = dis(gen);
    if (x * x + y * y <=
        1.0) {  // Проверяем, попадает ли точка внутрь круга (радиус = 1, площадь = π)
      insideCircle++;
    }
  }
  return insideCircle;
}

int main(int argc, char* argv[]) {
  if (argc !=
      2) {  // Проверяем, передано ли правильное количество аргументов командной строки
    std::cerr << "Usage: " << argv[0] << " <number of threads>\n";
    return 1;
  }

  int numThreads = std::stoi(argv[1]);
  const int totalPoints = 1000000;  // Общее количество точек для генерации

  int pointsPerThread =
      totalPoints /
      numThreads;  // Количество точек для генерации в каждом потоке
  std::atomic<int> totalInsideCircle(0);

  std::vector<std::thread> threads;
  for (int i = 0; i < numThreads; ++i) {
    threads.emplace_back([&]() {
      int insideCircle = countPointsInsideCircle(pointsPerThread);
      totalInsideCircle += insideCircle;
    });
  }

  auto start = std::chrono::high_resolution_clock::
      now();  // Засекаем время начала выполнения

  for (auto& t : threads) {  // Ждем завершения всех потоков
    t.join();
  }

  auto end = std::chrono::high_resolution_clock::
      now();  // Засекаем время окончания выполнения
  std::chrono::duration<double> elapsed_seconds =
      end - start;  // Вычисляем время выполнения программы

  double pi = 4.0 * totalInsideCircle /
              totalPoints;  // Вычисляем оценку числа π. (S квадрата = 4.0)
  std::cout << "Estimated value of Pi: " << pi << std::endl;
  std::cout << "Time taken: " << elapsed_seconds.count() << " seconds"
            << std::endl;

  return 0;
}
