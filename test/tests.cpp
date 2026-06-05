// Copyright 2021 NNTU-CS
#include <gtest/gtest.h>
#include "train.h"

TEST(lab8, test1) {
  Train train;
  int count = 2;

  while (count--) {
    train.addCar(false);
  }

  int len = train.getLength();
  int op = train.getOpCount();

  ASSERT_EQ(len, 2);
  ASSERT_EQ(op, 4);
}

TEST(lab8, test2) {
  Train train;
  int count = 8;

  while (count--) {
    train.addCar(false);
  }

  int len = train.getLength();
  int op = train.getOpCount();

  ASSERT_EQ(len, 8);
  ASSERT_EQ(op, 16);
}

TEST(lab8, test3) {
  Train train;
  int count = 1000;

  while (count--) {
    train.addCar(false);
  }

  int len = train.getLength();
  int op = train.getOpCount();

  ASSERT_EQ(len, 1000);
  ASSERT_EQ(op, 2000);
}

TEST(lab8, test4) {
  Train train;
  int count = 4;

  while (count--) {
    train.addCar(true);
  }

  int len = train.getLength();
  int op = train.getOpCount();

  ASSERT_EQ(len, 4);
  ASSERT_EQ(op, 20);
}

TEST(lab8, test5) {
  Train train;
  int count = 6;

  while (count--) {
    train.addCar(true);
  }

  int len = train.getLength();
  int op = train.getOpCount();

  ASSERT_EQ(len, 6);
  ASSERT_EQ(op, 42);
}
