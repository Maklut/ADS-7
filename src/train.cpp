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
  int steps = 0;

  // Начинаем движение
  while (true) {
    // Переходим в следующий вагон
    current = current->next;
    countOp++;
    steps++;

    // Если свет выключен - включаем и начинаем отсчет заново
    if (current->light == false) {
      current->light = true;
      steps = 0;
      continue;
    }

    // Нашли включенный свет. Проверяем, не вернулись ли в начало
    // Идем назад на steps шагов
    Car* back = current;
    int backCount = 0;

    for (int i = 0; i < steps; i++) {
      back = back->prev;
      backCount++;
      countOp++;
    }

    // Если вернулись в начало - длина найдена
    if (back == first && backCount == steps) {
      break;
    }
  }

  return steps;
}

int Train::getOpCount() {
  return countOp;
}
