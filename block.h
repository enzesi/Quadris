#ifndef BLOCK_H
#define BLOCK_H
#include <cstddef>
#include "subject.h"
#include "observer.h"
#include "info.h"
#include "board.h"
#include "posn.h"
#include <vector>


class Block {
  char type;
  std::vector<Posn> block;
  Board *board;
  int ith;
public:
  Block(char type, Board *board, int ith);
  void clean();
  void left();
  void right();
  void down();
  void drop();
  void clockwise();
  void countclockwise();
};


#endif
