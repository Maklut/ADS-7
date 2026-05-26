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

  // Классический алгоритм: включаем свет, идем вперед,
  // выключаем свет в новых вагонах, считаем шаги
  first->light = true;
  Car* current = first;
  int steps = 0;

  while (true) {
    current = current->next;
    countOp++;
    steps++;

    if (!current->light) {
      current->light = true;
      steps = 0;
    } else {
      // Нашли вагон с включенным светом
      // Проверяем, не вернулись ли в начало
      Car* temp = current;
      int backSteps = 0;

      while (temp != first && backSteps < steps) {
        temp = temp->prev;
        countOp++;
        backSteps++;
      }

      if (temp == first && backSteps == steps) {
        break;
      }
    }
  }

  first->light = false;

  return steps;
}

int Train::getOpCount() {
  return countOp;
}
