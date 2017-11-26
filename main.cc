#include <iostream>
#include "textdisplay.h"
#include "board.h"
#include "subject.h"
#include "observer.h"
#include "posn.h"
#include "info.h"
#include "block.h"
#include "blockinfo.h"
#include "graphicsdisplay.h"
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <fstream>
using namespace std;


void display_next(char now_displaying) {
    cout << "Next:" << endl;
    if (now_displaying == 'I') {
        cout << "IIII" << endl;
    }
    else if (now_displaying == 'J') {
        cout << "J" << endl;
        cout << "JJJ" << endl;
    }
    else if (now_displaying == 'L') {
        cout << "  L" << endl;
        cout << "LLL" << endl;
    }
    else if (now_displaying == 'O') {
        cout << "OO" << endl;
        cout << "OO" << endl;
    }
    else if (now_displaying == 'S') {
        cout << " SS" << endl;
        cout << "SS" << endl;
    }
    else if (now_displaying == 'Z') {
        cout << "ZZ" << endl;
        cout << " ZZ" << endl;
    }
    else if (now_displaying == 'T') {
        cout << "TTT" << endl;
        cout << " T " << endl;
    }
}


void set_level(int level, int &pos, bool &start, char &now,
  char &next, string file) {
    if (level == 0) {
        ifstream f(file);
        char c;
        vector<char> char_vec;
        char_vec.clear();
        while (f >> c) {
            if (((c == 'T' || c == 'S') || (c == 'L' || c == 'O')) ||
                ((c == 'J' || c == 'Z') || c == 'I'))
            char_vec.push_back(c);
        }
        int size = char_vec.size();
        if (start == false) {
            now = char_vec[pos];
            if (pos == size - 1) {
              pos = 0;
              next = char_vec[pos];
            } else {
              next = char_vec[pos + 1];
            }
            start = true;
            pos++;
        }
        else {
            if (pos >= size - 1) {
                now = next;
                next = char_vec[0];
                pos = 0;
            } else {
                now = next;
                pos++;
                next = char_vec[pos];
            }
        }
    }
    else if (level == 1) {
        char char_vec[] = {'S','Z','I','I','T','T','J','J','L','L','O','O'};
        srand(time(NULL));//seed;
        rand();
        int poss = rand() % 12;
        if (start == false) {
            now = char_vec[poss];
            poss = rand() % 12;
            next = char_vec[poss];
            start = true;
        } else {
            now = next;
            poss = rand() % 12;
            next = char_vec[poss];
        }
    }
    else if (level == 2) {
        char char_vec[] = {'S','Z','I','T','J','L','O'};
        srand(time(NULL));//seed;
        rand();
        int poss = rand() % 6;
        if (start == false) {
            now = char_vec[poss];
            poss = rand() % 6;
            next = char_vec[poss];
            start = true;
        }
        else {
            now = next;
            next = char_vec[poss];
        }
    }
    else if (level == 3 || level == 4) {
      char char_vec[] = {'S','Z','I','T','J','L','O','S','Z'};
      srand(time(NULL)); //seed;
      rand();
      int poss = rand() % 9;
      if (start == false) {
          now = char_vec[poss];
          poss = rand() % 9;
          next = char_vec[poss];
          start = true;
      }
      else {
          now = next;
          next = char_vec[poss];
      }
    }
}

int main(int argc, char *argv[]) {
  int startlevel = 0;
  string defaultfile = "sequence.txt";
  bool onlytext = false;
  for (int i = 1; i < argc; i++) {
      string arg = argv[i];
      if (arg == "startlevel") {
        startlevel = stoi(argv[i+1]);
        i++;
      } else if (arg == "scriptfile") {
        defaultfile = argv[i+1];
        i++;
      } else if (arg == "seed") {
        ///////////////////////////////
      } else if (arg == "text") {
        onlytext = true;
      } else {
        continue;
      }
  }
  bool sequencecommand = false;
  bool restart;
  int high_score = 0;
  while (1) {
    restart = false;
    string cmd;


    vector<BlockInfo> binfo;
    binfo.clear();
    vector<int> * v = nullptr;
    int ith = 0;    // use for score;



    //////////////////////
    Board *b;
    b = new Board;
    b->init();
    b->setHiScore(high_score);

    //////////////////////
    GraphicsDisplay *gd = nullptr;
    gd = new GraphicsDisplay(18, 11, 900, 550);
    b.setObserver(gd);
    //////////////////////

    int level = startlevel;
    b->setlevel(level);

    //////////////////////
    bool start = false;
    int pos = 0;
    char now;
    char next;
    //////////////////////
    bool complete;
    bool multicommand;
    int righttime = 0;
    int lefttime = 0;
    int downtime = 0;
    int leveluptime = 0;
    int leveldowntime = 0;
    int clockwisetime = 0;
    int countertime = 0;
    int droptime = 0;
    //////////////////////
    bool autodrop = false; ////////
    /////////////////////
    //  bool exefileall = false;
    bool random34 = true;
    string file;
    ///////////////////////
    vector <string> scom;
    scom.clear();
    ///////////////////////
    int count_without_clean = 0;

    while (true) {


        int curr_level = level;
        if (random34) {
            set_level(level, pos, start, now, next, defaultfile);
        } else {
            set_level(0, pos, start, now, next, file);
        }
        Block currb(now, b, ith);
        cout << (*b);
        display_next(next);

        if (!autodrop) {
          while (1) {
            cin >> cmd;
            if (((cmd == "T" || cmd == "S") || (cmd == "L" || cmd == "O")) ||
                ((cmd == "J" || cmd == "Z") || cmd == "I")) {
              now = cmd[0];
              currb.clean();
              currb = Block(now, b, ith);
              cout << (*b);
              display_next(next);
            } else {
              complete = true;
              break;
            }
          }
        }

        binfo.push_back(BlockInfo {4, level, true});
        ith++;

        while (complete || autodrop || sequencecommand || cin >> cmd) {
            complete = false;
            multicommand = false;
            if (!autodrop) {
              if (cmd[0] <= '9' && cmd[0] >= '0') {
                multicommand = true;
                int len = cmd.length();
                int numlen = 0;
                for (int i = 0; i < len; i++) {
                    if (cmd[i] > '9' || cmd[i] < '0') {
                      numlen = i;
                      break;
                    }
                }
                string numtime = cmd.substr(0, numlen);
                cmd = cmd.substr(numlen);
                int temp = stoi(numtime);
                if (cmd == "right") {
                  righttime = temp;
                  cout << righttime << endl;
                  cmd = "r";
                } else if (cmd == "drop" || cmd == "d") {
                  droptime = temp - 1;
                  autodrop = true;
                  cmd = "p";
                } else if (cmd == "levelup") {
                  leveluptime = temp;
                  cmd = "levelup";
                } else if (cmd == "leveldown") {
                  leveldowntime = temp;
                  cmd = "leveldown";
                } else if (cmd == "left") {
                  lefttime = temp;
                  cmd = "l";
                } else if (cmd == "down") {
                  downtime = temp;
                  cmd = "d";
                } else if (cmd == "clockwise") {
                  clockwisetime = temp;
                  cmd = "cr";
                } else if (cmd == "counterclockwise") {
                  countertime = temp;
                  cmd = "ccr";
                } else {
                  continue;
                }
              }
            }

            if (cmd == "r") {
                if (multicommand) {
                  for (int i = 0; i < righttime; i++) {
                      currb.right();
                  }
                  multicommand = false;
                } else {
                  currb.right();
                }
                if (level == 3 || level == 4) {
                  currb.down();
                }
                cout << (*b);
                display_next(next);
            } else if (cmd == "l") {
              if (multicommand) {
                for (int i = 0; i < lefttime; i++) {
                    currb.left();
                }
                multicommand = false;
              } else {
                currb.left();
              }
                if (level == 3 || level == 4) {
                  currb.down();
                }
                cout << (*b);
                display_next(next);
            } else if (cmd == "d") {
              if (multicommand) {
                for (int i = 0; i < downtime; i++) {
                    currb.down();
                }
                multicommand = false;
              } else {
                currb.down();
              }
                if (level == 3 || level == 4) {
                  currb.down();
                }
                cout << (*b);
                display_next(next);
            } else if (autodrop || cmd == "p") {
                if (droptime != 0) {
                   droptime--;
                } else {
                   autodrop = false;
                   multicommand = false;
                }
                currb.drop();
                v = b->clean();
                int size = v->size();
                for (int i = 0; i < size; i++) {
                    int k = v->at(i);
                    binfo[k].count--;
                }
                if (level == 4) {
                  if (size == 0) {
                    count_without_clean++;
                  } else {
                    count_without_clean = 0;
                  }
                  if (count_without_clean != 0 && count_without_clean % 5 == 0) {
                    Block extra('*', b, -1);
                    extra.drop();
                    delete v;
                    v = b->clean();
                    for (int i = 0; i < size; i++) {
                        int k = v->at(i);
                        binfo[k].count--;
                    }
                  }
                }
                delete v;
                for (int i = 0; i < ith; i++) {
                    if (binfo[i].cal) {
                        if (binfo[i].count == 0) {
                            int sco = binfo[i].level + 1;
                            b->addScore(sco * sco);
                            binfo[i].cal = false;
                        }
                    }
                }
                if (ith >= 10) {
                    if (binfo[ith - 10].cal) {
                        b->Remove(ith - 10);
                        binfo[ith - 10].cal = false;
                    }
                }
                b->checkHiScore();
                if (curr_level != level) {
                   level = curr_level;
                   b->setlevel(level);
                   if (level == 0) {
                      pos = -1;
                   } else if (level == 4) {
                      count_without_clean = 0;
                   }
                }
                break;
            } else if (cmd == "cr") {
              if (multicommand) {
                for (int i = 0; i < clockwisetime; i++) {
                    currb.clockwise();
                }
                multicommand = false;
              } else {
                currb.clockwise();
              }
                if (level == 3 || level == 4) {
                  currb.down();
                }
                cout << (*b);
                display_next(next);
            } else if (cmd == "ccr") {
              if (multicommand) {
                for (int i = 0; i < countertime; i++) {
                    currb.countclockwise();
                }
                multicommand = false;
              } else {
                currb.countclockwise();
              }
                if (level == 3 || level == 4) {
                  currb.down();
                }
                cout << (*b);
                display_next(next);
            } else if (cmd == "levelup") {
              if (multicommand) {
                for (int i = 0; i < leveluptime; i++) {
                  if (curr_level == 4) {
                    continue;
                  } else {
                    curr_level++;
                  }
                }
              } else {
                if (curr_level == 4) {
                  continue;
                } else {
                  curr_level++;
                }
              }
            } else if (cmd == "leveldown") {
              if (multicommand) {
                for (int i = 0; i < leveldowntime; i++) {
                  if (curr_level == 0) {
                    continue;
                  } else {
                    curr_level--;
                  }
                }
              } else {
                if (curr_level == 0) {
                  continue;
                } else {
                  curr_level--;
                }
              }
            } else if (cmd == "random") {
                if (level != 3 || level != 4) {
                  continue;
                } else {
                  random34 = true;
                }
            } else if (cmd == "norandom") {
                cin >> file;
                if (level < 3) {
                  continue;
                } else {
                  pos = 0;
                  random34 = false;
                }
            } else if (cmd == "sequence") {
                string file;
                cin >> file;
                sequencecommand = true;
                fstream f(file);
                string word;
                while (f >> word) {
                    scom.push_back(word); //////////////////////////
                }
            } else if (cmd == "restart") {
                restart = true;
                break;
            } else if (cmd == "hint") {
                continue;//////////////////////////////
            } else {
                continue;
            }
        }
        if (restart) break;
    }
    high_score = b->getHiscore();
    delete b;
  }
}
