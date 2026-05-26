// Copyright 2022 NNTU-CS
#include <iostream>
#include <string>
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
              << " | len1=" << len1 << " ops1=" << ops1
              << " | len2=" << len2 << " ops2=" << ops2
              << " | len3=" << len3 << " ops3=" << ops3 << "\n";
  }

  // Сохраняем данные
  saveData("result/all_off.dat", sizes, ops_all_off);
  saveData("result/all_on.dat", sizes, ops_all_on);
  saveData("result/random.dat", sizes, ops_random);

  // Создаем Python скрипт для построения графика
  std::ofstream pyScript("result/plot.py");
  pyScript << "import matplotlib.pyplot as plt\n"
           << "import numpy as np\n\n"
           << "# Загрузка данных\n"
           << "data_off = np.loadtxt('all_off.dat')\n"
           << "data_on = np.loadtxt('all_on.dat')\n"
           << "data_rand = np.loadtxt('random.dat')\n\n"
           << "# Создание графика\n"
           << "plt.figure(figsize=(10, 6))\n"
           << "plt.plot(data_off[:,0], data_off[:,1], 'b-o', "
           << "label='Все лампочки выключены', linewidth=2, markersize=4)\n"
           << "plt.plot(data_on[:,0], data_on[:,1], 'r-s', "
           << "label='Все лампочки включены', linewidth=2, markersize=4)\n"
           << "plt.plot(data_rand[:,0], data_rand[:,1], 'g-^', "
           << "label='Случайное распределение', linewidth=2, markersize=4)\n"
           << "plt.xlabel('Длина поезда (n)', fontsize=12)\n"
           << "plt.ylabel('Число операций', fontsize=12)\n"
           << "plt.title('Зависимость числа операций от длины поезда', "
           << "fontsize=14)\n"
           << "plt.legend(loc='best', fontsize=10)\n"
           << "plt.grid(True, alpha=0.3)\n"
           << "plt.tight_layout()\n"
           << "plt.savefig('plot.png', dpi=150)\n"
           << "print('График сохранен в result/plot.png')\n";
  pyScript.close();

  std::cout << "\n=== Эксперимент завершен ===\n";
  std::cout << "Данные сохранены в result/*.dat\n";
  std::cout << "Для построения графика выполните:\n";
  std::cout << "  cd result && python3 plot.py\n";

  return 0;
}
