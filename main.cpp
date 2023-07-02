#include <TaskScheduler.h>

#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>

int main(int argc, char** argv) {
  enki::TaskScheduler task_scheduler;
  task_scheduler.Initialize();

  std::cout << "hardware threads: " << enki::GetNumHardwareThreads() << '\n';

  const int number_count = 10000000;

  {
    std::cout << "serial\n";

    std::vector<float> numbers(number_count);
    std::iota(numbers.begin(), numbers.end(), 1);

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < numbers.size(); ++i) {
      numbers[i] = std::sqrt(numbers[i]);
    }
    auto finish = std::chrono::steady_clock::now();

    std::chrono::duration<double> delta = finish - start;
    std::cout << delta.count() << '\n';
  }

  {
    std::cout << "parallel\n";

    std::vector<float> numbers(number_count);
    std::iota(numbers.begin(), numbers.end(), 1);

    auto start = std::chrono::steady_clock::now();
    enki::TaskSet task(
      number_count,
      [&numbers](enki::TaskSetPartition range, uint32_t thread_number) {
        for (int i = range.start; i < range.end; ++i) {
          numbers[i] = std::sqrt(numbers[i]);
        }
      });
    task_scheduler.AddTaskSetToPipe(&task);
    task_scheduler.WaitforTask(&task);
    auto finish = std::chrono::steady_clock::now();

    std::chrono::duration<double> delta = finish - start;
    std::cout << delta.count() << '\n';
  }

  return 0;
}
