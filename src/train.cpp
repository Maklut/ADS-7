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
  bool allVisited = false;
  while (!allVisited) {
    current->light = false;
    current = current->next;
    countOp++;
    if (current == first) allVisited = true;
  }

  // Шаг 2: Включаем свет в начальном вагоне
  first->light = true;
  current = first;
  int length = 0;

  // Шаг 3: Идем вперед и считаем
  bool found = false;
  while (!found) {
    current = current->next;
    countOp++;
    length++;

    if (current->light == false) {
      current->light = true;
      length = 0;
    } else {
      // Проверяем, не вернулись ли в начало
      Car* backward = current;
      int backSteps = 0;

      while (backward != first && backSteps < length) {
        backward = backward->prev;
        backSteps++;
        countOp++;
      }

      if (backward == first && backSteps == length) {
        found = true;
      }
    }
  }

  return length;
}

int Train::getOpCount() {
  return countOp;
}
