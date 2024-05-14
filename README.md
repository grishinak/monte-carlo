## Monte-Carlo method
### Оценка числа π

Эта программа на C++ оценивает значение числа Пи с использованием метода Монте-Карло. Она генерирует заданное количество случайных точек внутри квадрата и определяет, сколько из них попадает в четверть круга единичного радиуса. Сравнивая отношение точек, попавших в круг, к общему числу точек, программа оценивает значение числа Пи.

#### Использование

Скомпилируйте программу с помощью CMake:

```bash
mkdir build
cd build
cmake ..
make
```

Запустите скомпилированный исполняемый файл, указав количество потоков в качестве аргумента командной строки:

```bash
./monte_carlo <количество_потоков>
```

### Проверка оценки метода

```bash
grishinakseniya@grishinakseniya:~/gitrepo/monte-carlo/build$ make
[100%] Built target monte-carlo
grishinakseniya@grishinakseniya:~/gitrepo/monte-carlo/build$ ./monte-carlo 
Usage: ./monte-carlo <number of threads>
grishinakseniya@grishinakseniya:~/gitrepo/monte-carlo/build$ ./monte-carlo 1
Estimated value of Pi: 3.14217
Time taken: 1.02395 seconds
grishinakseniya@grishinakseniya:~/gitrepo/monte-carlo/build$ ./monte-carlo 10
Estimated value of Pi: 3.14056
Time taken: 0.324088 seconds
grishinakseniya@grishinakseniya:~/gitrepo/monte-carlo/build$ ./monte-carlo 100
Estimated value of Pi: 3.14344
Time taken: 0.298318 seconds
grishinakseniya@grishinakseniya:~/gitrepo/monte-carlo/build$ ./monte-carlo 1000
Estimated value of Pi: 3.14036
Time taken: 0.0280568 seconds
grishinakseniya@grishinakseniya:~/gitrepo/monte-carlo/build$ ./monte-carlo 10000
Estimated value of Pi: 3.14054
Time taken: 0.0684602 seconds
```
Многократно запустив подсчёт с заданным количеством точек убедилась, что представленная на презентации оценка справедлива.

#### Детали

- `main(int argc, char* argv[])`: Это главная функция программы. Она принимает количество потоков в качестве аргумента командной строки и инициализирует указанное количество потоков. Каждый поток вызывает функцию `countPointsInsideCircle`, чтобы подсчитать количество точек внутри круга. После завершения всех потоков программа вычисляет оценку числа Пи на основе отношения точек внутри круга к общему числу точек. Кроме того, она измеряет время выполнения с использованием библиотеки `<chrono>`.
