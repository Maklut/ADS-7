// Copyright 2022 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
  if (first == nullptr) return;

  Car* current = first;
  Car* nextCar = nullptr;
  do {
    nextCar = current->next;
    delete current;
    current = nextCar;
  } while (current != first);
}

void Train::addCar(bool light) {
  Car* newCar = new Car;
  newCar->light = light;
  newCar->next = nullptr;
  newCar->prev = nullptr;

  if (first == nullptr) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
}

int Train::getLength() {
  if (first == nullptr) return 0;

  countOp = 0;
  Car* current = first;

  // Алгоритм:
  // 1. Включаем свет в текущем вагоне
  // 2. Идем вперед, выключая свет в вагонах, пока не встретим включенный
  // 3. Когда встречаем включенный - это наш начальный вагон

  // Включаем свет в первом вагоне
  current->light = true;

  int steps = 0;
  bool found = false;

  while (!found) {
    // Переходим в следующий вагон
    current = current->next;
    countOp++;
    steps++;

    // Если свет выключен, включаем его и сбрасываем счетчик
    if (!current->light) {
      current->light = true;
      steps = 0;
    } else {
      // Нашли включенный свет - проверяем, не первый ли это вагон
      // Идем назад на steps шагов
      Car* check = current;
      bool isFirst = true;

      for (int i = 0; i < steps; i++) {
        check = check->prev;
        countOp++;
        if (check != first) {
          isFirst = false;
        }
      }

      if (isFirst && check == first) {
        found = true;
      }
    }
  }

  // Выключаем свет в первом вагоне
  first->light = false;

  return steps;
}

int Train::getOpCount() {
  return countOp;
}
