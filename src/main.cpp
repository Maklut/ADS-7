// Copyright 2022 NNTU-CS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "train.h"

int main() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  std::cout << "n\tall_off\tall_on\tavg_rand" << std::endl;

  for (int n = 2; n <= 30; n += 2) {
    // Тест 1: все лампочки выключены
    Train train_off;
    for (int i = 0; i < n; ++i) {
      train_off.addCar(false);
    }
    train_off.getLength();
    int off_steps = train_off.getOpCount();

    // Тест 2: все лампочки включены
    Train train_on;
    for (int i = 0; i < n; ++i) {
      train_on.addCar(true);
    }
    train_on.getLength();
    int on_steps = train_on.getOpCount();

    // Тест 3: случайное распределение (среднее из 5 попыток)
    int sum_rand = 0;
    for (int trial = 0; trial < 5; ++trial) {
      Train train_rand;
      for (int i = 0; i < n; ++i) {
        train_rand.addCar(std::rand() % 2 == 1);
      }
      train_rand.getLength();
      sum_rand += train_rand.getOpCount();
    }
    int avg_rand = sum_rand / 5;

    std::cout << n << "\t"
              << off_steps << "\t"
              << on_steps << "\t"
              << avg_rand << std::endl;
  }

  return 0;
}
