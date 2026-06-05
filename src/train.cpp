// Copyright 2021 NNTU-CS
#include "train.h"

Train::Train() {
  first = nullptr;
  countOp = 0;
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
    newCar->next = first;
    newCar->prev = last;
    last->next = newCar;
    first->prev = newCar;
  }
}

int Train::getLength() {
  Car* start = first;
  bool saved = start->light;

  start->light = true;

  while (true) {
    Car* cur = start;
    int d = 0;

    do {
      cur = cur->next;
      ++countOp;
      ++d;
    } while (!cur->light);

    cur->light = false;

    for (int i = 0; i < d; ++i) {
      cur = cur->prev;
      ++countOp;
    }

    if (!start->light) {
      start->light = saved;
      return d;
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
