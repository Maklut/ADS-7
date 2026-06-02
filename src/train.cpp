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

  // Шаг 1: Выключаем свет во всех вагонах
  Car* current = first;
  do {
    current->light = false;
    current = current->next;
    countOp++;
  } while (current != first);

  // Шаг 2: Включаем свет в первом вагоне
  first->light = true;
  current = first;
  int length = 0;

  // Шаг 3: Алгоритм поиска длины
  while (true) {
    // Идем вперед, пока не встретим вагон с выключенным светом
    while (true) {
      current = current->next;
      countOp++;
      length++;

      if (!current->light) {
        // Включаем свет в этом вагоне
        current->light = true;
        length = 0;
        break;
      } else {
        // Нашли включенный свет, проверяем
        Car* test = current;
        int backSteps = 0;
        
        for (int i = 0; i < length; i++) {
          test = test->prev;
          backSteps++;
          countOp++;
          if (test == first) break;
        }
        
        if (test == first && backSteps == length) {
          return length;
        }
      }
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
