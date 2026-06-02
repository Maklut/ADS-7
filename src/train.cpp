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

  // Выключаем свет во всех вагонах
  Car* current = first;
  do {
    current->light = false;
    current = current->next;
    countOp++;
  } while (current != first);

  // Включаем свет в первом вагоне
  first->light = true;
  current = first;
  int steps = 0;

  while (true) {
    current = current->next;
    countOp++;
    steps++;

    if (!current->light) {
      current->light = true;
      steps = 0;
      continue;
    }

    // Проверяем, вернулись ли в начало
    // cppcheck-suppress constVariablePointer
    Car* check = current;
    int back = 0;

    for (int i = 0; i < steps; i++) {
      check = check->prev;
      back++;
      countOp++;
    }

    if (check == first && back == steps) {
      return steps;
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
