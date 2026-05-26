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
  int length = 0;

  // Выключаем свет во всех вагонах (сбрасываем состояние)
  Car* current = first;
  do {
    current->light = false;
    current = current->next;
    countOp++;
  } while (current != first);

  // Включаем свет в текущем вагоне
  first->light = true;
  current = first;

  while (true) {
    // Перемещаемся вперед
    current = current->next;
    countOp++;
    length++;

    // Если свет выключен, включаем его и сбрасываем счетчик
    if (!current->light) {
      current->light = true;
      length = 0;
    } else {
      // Нашли включенный свет - проверяем, не вернулись ли в начало
      Car* backward = current;
      int backwardSteps = 0;
      bool foundFirst = false;

      for (int i = 0; i < length; i++) {
        backward = backward->prev;
        backwardSteps++;
        countOp++;
        if (backward == first) {
          foundFirst = true;
          break;
        }
      }

      if (foundFirst && backwardSteps == length && backward == first) {
        break;
      }
    }
  }

  return length;
}

int Train::getOpCount() {
  return countOp;
}
