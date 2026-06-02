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

  // Сначала выключаем свет во всех вагонах
  Car* current = first;
  do {
    current->light = false;
    current = current->next;
    countOp++;
  } while (current != first);

  // Включаем свет в текущем вагоне
  first->light = true;
  current = first;
  int length = 0;

  while (true) {
    // Делаем шаг вперед
    current = current->next;
    countOp++;
    length++;

    if (!current->light) {
      // Включаем свет в этом вагоне
      current->light = true;
      length = 0;
    } else {
      // Нашли включенный свет
      // Идем назад, проверяя, не вернулись ли в начало
      Car* back = current;
      int stepBack = 0;

      for (int i = 0; i < length; i++) {
        back = back->prev;
        stepBack++;
        countOp++;
        if (back == first) {
          break;
        }
      }

      if (back == first && stepBack == length) {
        return length;
      }
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
