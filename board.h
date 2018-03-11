#ifndef BOARD_H_
#define BOARD_H_
#include <iostream>
#include <vector>
#include <iomanip>
#include "cell.h"
#include "textdisplay.h"
#include "posn.h"


class Board {
    std::vector<std::vector<Cell>> theBoard;;
    std::shared_ptr<TextDisplay> td;
    std::shared_ptr<Observer> ob;
    int level = 0;
    int score = 0;
    int Hi_Score = 0;;
public:
    ~Board();
    // reset the board; 
    void reset();
    // check the cell in the Posn P is empty or not;
    bool checkempty(Posn p);
    
    // get the number of empty cells;
    int getEmpty(int line);
    // use to delete the hint;
    void deletehint(std::vector<Posn> p);
    
    // setter methods;
    void set(std::vector<Posn> p, char type);
    void setith(std::vector<Posn> p, int ith);
    void setlevel(int level);
    void setObserver(std::shared_ptr<Observer> ob);
    void setHiScore(int x);
    
    // getter methods;
    int getScore();
    int getHiscore();
    
    // use to initialize the board;
    void init();

    // check the vector of posn is empty or not;
    bool check(std::vector<Posn> p);

    // clean the vector of posn temporarily;
    void tempclean(std::vector<Posn> p);
    // clean the vector of posn permnantly;
    void clear(std::vector<Posn> p);

    void checkHiScore();
    void Remove(int ith);
    void addScore(int x);
    std::unique_ptr<std::vector<int>> clean();    
    void setback(std::vector<Posn> p);
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};


#endif
