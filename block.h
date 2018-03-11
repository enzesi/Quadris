#ifndef BLOCK_H
#define BLOCK_H
#include "board.h"
#include "posn.h"
#include "combination.h"
#include <vector>


class Block {
    char type;
    std::vector<Posn> block;
    std::shared_ptr<Board> board;
    int ith;
public:
    Block();
    Block(char type, std::shared_ptr<Board>board, int ith);
    void clean();  // used to clean the current block;
    // move the block leftward;
    void left(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);
    // move the block rightward;
    void right(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);
    // move the block downward;
    void down(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);
    // drop the block;
    void drop();
    // clockwise the current block;
    void clockwise(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);
    // counterclockwise the current block;
    void countclockwise(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);
    // The below function are same as above, they are used for hint methods to do the mutual recursion.
    void clockwiselhelp(int times, bool hint = false, std::vector<Combination> *choice = nullptr);
    void clockwiserhelp(int times, bool hint = false, std::vector<Combination> *choice = nullptr);
void counterclockwisehelp(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);
    void lefthelp(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);
    void righthelp(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);
    void downhelp(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);

    void lefthelp2(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);
    void righthelp2(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);
    void downhelp2(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);

    void lefthelp3(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);
    void righthelp3(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);
    void downhelp3(int times = 1, bool hint = false, std::vector<Combination> *choice = nullptr);


    Combination hint();
};


#endif
