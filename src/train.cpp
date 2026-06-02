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
  
  // Сбрасываем все лампочки в исходное состояние (выключаем)
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
  
  while (true) {
    // Переходим в следующий вагон
    current = current->next;
    countOp++;
    steps++;
    
    // Если свет выключен, включаем и начинаем отсчет заново
    if (!current->light) {
      current->light = true;
      steps = 0;
      continue;
    }
    
    // Нашли вагон с включенным светом
    // Проверяем, не вернулись ли мы в начало
    Car* test = current;
    int backSteps = 0;
    
    for (int i = 0; i < steps; i++) {
      test = test->prev;
      backSteps++;
      countOp++;
    }
    
    if (test == first && backSteps == steps) {
      // Успешно вернулись в начало
      break;
    }
  }
  
  return steps;
}

int Train::getOpCount() {
  return countOp;
}
