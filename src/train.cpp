// Copyright 2022 NNTU-CS
#include "train.h"

Train::Train() : countOp(0), first(nullptr) {}

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

  Car* current = first;

  current->light = true;
  countOp = 0;

  int length = 0;
  bool found = false;

  while (!found) {
    current = current->next;
    countOp++;
    if (!current->light) {
      current->light = true;
      length = 0;
    } else {
      length++;

      Car* temp = current;
      for (int i = 0; i < length; i++) {
        temp = temp->prev;
        countOp++;
        if (temp == first) {
          found = true;
          break;
        }
      }

      if (!found) {
        for (int i = 0; i < length; i++) {
          current = current->prev;
          countOp++;
        }
      }
    }
  }

  first->light = false;

  return length + 1;
}

int Train::getOpCount() {
  return countOp;
}
