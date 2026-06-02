// Copyright 2022 NNTU-CS
#include <gtest/gtest.h>
#include "train.h"

TEST(lab8, test1) {
  Train train;
  train.addCar(false);
  train.addCar(false);
  int len = train.getLength();
  EXPECT_EQ(len, 2);
}

TEST(lab8, test2) {
  Train train;
  for (int i = 0; i < 8; i++) {
    train.addCar(false);
  }
  int len = train.getLength();
  EXPECT_EQ(len, 8);
}

TEST(lab8, test3) {
  Train train;
  for (int i = 0; i < 1000; i++) {
    train.addCar(false);
  }
  int len = train.getLength();
  EXPECT_EQ(len, 1000);
}

TEST(lab8, test4) {
  Train train;
  train.addCar(true);
  train.addCar(false);
  train.addCar(true);
  train.addCar(false);
  int len = train.getLength();
  EXPECT_EQ(len, 4);
}

TEST(lab8, test5) {
  Train train;
  train.addCar(true);
  train.addCar(true);
  train.addCar(false);
  train.addCar(false);
  train.addCar(true);
  train.addCar(false);
  int len = train.getLength();
  EXPECT_EQ(len, 6);
}
