// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include "train.h"

void saveData(const std::string& filename,
              const std::vector<int>& sizes,
              const std::vector<int>& operations) {
  std::ofstream out(filename);
  for (size_t i = 0; i < sizes.size(); i++) {
    out << sizes[i] << " " << operations[i] << "\n";
  }
  out.close();
}

int main() {
  std::vector<int> sizes;
  std::vector<int> ops_all_off;
  std::vector<int> ops_all_on;
  std::vector<int> ops_random;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 1);

  std::cout << "=== Вычислительный эксперимент ===\n";
  std::cout << "Тестирование длин поезда от 2 до 100\n\n";

  for (int n = 2; n <= 100; n += 2) {
    sizes.push_back(n);

    // Тест 1: все лампочки выключены
    Train train1;
    for (int i = 0; i < n; i++) {
      train1.addCar(false);
    }
    int len1 = train1.getLength();
    int ops1 = train1.getOpCount();
    ops_all_off.push_back(ops1);

    // Тест 2: все лампочки включены
    Train train2;
    for (int i = 0; i < n; i++) {
      train2.addCar(true);
    }
    int len2 = train2.getLength();
    int ops2 = train2.getOpCount();
    ops_all_on.push_back(ops2);

    // Тест 3: случайное распределение
    Train train3;
    for (int i = 0; i < n; i++) {
      train3.addCar(dist(gen) == 1);
    }
    int len3 = train3.getLength();
    int ops3 = train3.getOpCount();
    ops_random.push_back(ops3);

    std::cout << "n=" << n
              << " | all_off: " << ops1
              << " | all_on: " << ops2
              << " | random: " << ops3 << "\n";
  }

  // Сохраняем данные
  saveData("result/all_off.dat", sizes, ops_all_off);
  saveData("result/all_on.dat", sizes, ops_all_on);
  saveData("result/random.dat", sizes, ops_random);

  std::cout << "\n=== Эксперимент завершен ===\n";
  std::cout << "Данные сохранены в файлы:\n";
  std::cout << "  - result/all_off.dat\n";
  std::cout << "  - result/all_on.dat\n";
  std::cout << "  - result/random.dat\n";

  return 0;
}
