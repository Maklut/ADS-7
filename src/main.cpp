// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include "train.h"

void runExperiment(const std::string& filename,
                   const std::string& label,
                   std::vector<int>& sizes,
                   std::vector<int>& operations) {
  std::ofstream out(filename);
  out << "# " << label << "\n";
  out << "# n\toperations\n";

  for (int n : sizes) {
    Train train;

    if (label == "all_off") {
      for (int i = 0; i < n; i++) {
        train.addCar(false);
      }
    } else if (label == "all_on") {
      for (int i = 0; i < n; i++) {
        train.addCar(true);
      }
    } else if (label == "random") {
      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dist(0, 1);
      for (int i = 0; i < n; i++) {
        train.addCar(dist(gen) == 1);
      }
    }

    int length = train.getLength();
    int opCount = train.getOpCount();

    sizes.push_back(n);
    operations.push_back(opCount);

    out << n << " " << opCount << "\n";
    std::cout << label << ": n=" << n
              << ", length=" << length
              << ", ops=" << opCount << "\n";
  }
  out.close();
}

int main() {
  std::vector<int> sizes;
  for (int i = 2; i <= 100; i += 2) {
    sizes.push_back(i);
  }

  std::vector<int> ops_all_off;
  std::vector<int> ops_all_on;
  std::vector<int> ops_random;

  std::cout << "=== Вычислительный эксперимент ===\n\n";

  runExperiment("result/all_off.dat", "all_off",
                sizes, ops_all_off);
  runExperiment("result/all_on.dat", "all_on",
                sizes, ops_all_on);
  runExperiment("result/random.dat", "random",
                sizes, ops_random);

  std::ofstream plotScript("result/plot.gp");
  plotScript << "set terminal png size 800,600 enhanced font 'Arial,12'\n";
  plotScript << "set output 'plot.png'\n";
  plotScript << "set title 'Зависимость числа операций от длины поезда'\n";
  plotScript << "set xlabel 'Длина поезда (n)'\n";
  plotScript << "set ylabel 'Число операций (countOp)'\n";
  plotScript << "set grid\n";
  plotScript << "set key left top\n";
  plotScript << "set style data linespoints\n";
  plotScript << "set pointsize 1.5\n";
  plotScript << "plot 'all_off.dat' using 1:2 title 'Все лампочки выкл' "
             << "with linespoints lt 1 lc rgb 'blue' lw 2, \\\n";
  plotScript << "     'all_on.dat' using 1:2 title 'Все лампочки вкл' "
             << "with linespoints lt 1 lc rgb 'red' lw 2, \\\n";
  plotScript << "     'random.dat' using 1:2 title 'Случайное распределение' "
             << "with linespoints lt 1 lc rgb 'green' lw 2\n";
  plotScript.close();

  std::cout << "\n=== Эксперимент завершен ===\n";
  std::cout << "Данные сохранены в result/*.dat\n";
  std::cout << "Для построения графика выполните:\n";
  std::cout << "cd result && gnuplot plot.gp\n";

  return 0;
}
