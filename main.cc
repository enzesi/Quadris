#include <iostream>
#include "textdisplay.h"
#include "board.h"
#include "subject.h"
#include "observer.h"
#include "posn.h"
#include "info.h"
#include "block.h"
#include "blockinfo.h"
#include "combination.h"
#include "command.h"
#include "level.h"
#include "window.h"
#include "graphicsdisplay.h"
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <memory>
using namespace std;


int main(int argc, char *argv[]) {
    cin.exceptions(ios::eofbit|ios::failbit);
    int startlevel = 0;
    string defaultfile = "sequence.txt";
    bool onlytext = false;
    bool seedexist = false;
    int seed = -1;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-startlevel") {
            startlevel = stoi(argv[i+1]);
            i++;
        } else if (arg == "-scriptfile") {
            defaultfile = argv[i+1];
            i++;
        } else if (arg == "-seed") {
            seed = stoi(argv[i+1]);
            i++;
            seedexist = true;
        } else if (arg == "-text") {
            onlytext = true;
        } else {
            continue;
        }

    }
    
    bool restart = false;
    bool gameover = false;
    
    Block currb;
    shared_ptr<Board> b;
    b = make_shared<Board>();
    shared_ptr<GraphicsDisplay> gd;
    int high_score = 0;   // record the highest score for the game.
    
    // use for sequence file command.
    bool sequencecommand = false;
    int sequtime = 0;
    int sequnum = 0;
    vector <string> scom;
    
    // use for hint command.
    Combination hintpos;
    bool hint = false;
    vector<Posn> hinttemp;
    
    try {
        while (1) {
            
            string cmd;
            Command cmdcheck;
            gameover = false;         // Reset the gameover.
            restart = false;          // Reset the restart.
            
            vector<BlockInfo> binfo;  // Use to record the block info in order
            int ith = 0;              // to calculate the score.
            
            b->init();                // initialize the board and set the
            b->setHiScore(high_score);// highest score for it.
            b->setlevel(startlevel);  // set the level for board.
            
            //   check whether need graphics display
            if (!onlytext) {
                gd = make_shared<GraphicsDisplay>(18, 11, 630, 600);
                b->setObserver(gd);
            }
            
            Level levelgene(startlevel, defaultfile, seedexist, seed);
            // set the board generator;
            
            int pos = 0;                // use for level generator.
            
            // use for the command I,J,L etc.
            bool multicommand = false;  // use for the multicommand.
            int multitime = 0;
            int droptime = 0;
            bool autodrop = false;
            
            //use for the norandom file.
            bool random34 = true;
            string file;
            
            // use to clean the block;
            int count_without_clean = 0; // use for levelfour;
            
            while (true) {
                
                int curr_level = levelgene.getlevel();
                int level = levelgene.getlevel(); // record the startlevel of
                                                  // this block;
                
                try {
                    currb = levelgene.generateBlock(b, ith, pos, 
                                                    random34, file);
                } catch(...){
                    if (autodrop) {      // autodrop is used for multi drop. 
                    cout << (*b);
                    if (!onlytext){
                        gd->updatenext(levelgene.getnext());
                        gd->updatelevel(level);
                        gd->updatescore(b->getScore());
                        gd->updatehiscore(b->getHiscore());
                    }
                    levelgene.display_next();
                    }
                    cout << "Game is over" << endl;
                    gameover = true;
                    break;
                }
                
                if (!autodrop) {
                    cout << (*b);
                    if (!onlytext){
                        gd->updatenext(levelgene.getnext());
                        gd->updatelevel(level);
                        gd->updatescore(b->getScore());
                        gd->updatehiscore(b->getHiscore());
                    }
                    levelgene.display_next();
                }
                
                if (gameover) break;
                binfo.push_back(BlockInfo {4, level, true});
                ith++;
                
                while (autodrop || sequencecommand || cin >> cmd) {
                    if (!autodrop) {
                        try {
                            cmdcheck.check(cmd);
                        } catch (...) {
                            cout << "Ambiguous command!" << endl;
                        }
                    }
                    multicommand = false;
                    if (!autodrop) {
                        if (sequencecommand) { 
                            cmd = scom[sequnum];
                            try {
                                cmdcheck.check(cmd);
                            } catch (...) {
                                cout << "Ambiguous command!" << endl;
                            }
                            sequnum++;
                            if (sequnum == sequtime) {
                                sequencecommand = false;
                                sequtime = 0;
                                sequnum = 0;
                                scom.clear();
                            }
                        }
                    }
                    
                
                    if(!autodrop) {
                        if (((cmd == "T" || cmd == "S") || (cmd == "L"
                                        || cmd == "O")) ||
                            ((cmd == "J" || cmd == "Z") || cmd == "I")) {
                            char letter = cmd[0];
                            currb.clean();
                            try {
                                currb = Block(letter, b, ith - 1); 
                                 // change the current block;
                            } catch(...) {
                                cout << "Game is over!" << endl;
                                gameover = true;
                                break;
                            }
                            // The hint is for the previous block, since
                            // we create a new block, the hint disappears.
                            if (hint) {
                                b->deletehint(hinttemp);
                                hinttemp.clear();
                                hint = false;
                            }
                            cout << (*b);
                            levelgene.display_next();
                        }
                    }
                    // Use for the multicommand.
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
                            if (numlen == len) continue;
                            string numtime = cmd.substr(0, numlen);
                            cmd = cmd.substr(numlen);
                            multitime = stoi(numtime);
                            try {
                                cmdcheck.check(cmd);
                            } catch (int) {
                                cout << "Ambiguous command!" << endl;
                            }
                            if (multitime == 0) continue;
                            if (cmd == cmdcheck.getdrop()) {
                                droptime = multitime - 1;
                                autodrop = true;
                            }
                        }
                    }
                    
                    if (cmd == cmdcheck.getright()) {
                        if (multicommand) {
                            currb.right(multitime);
                            multicommand = false;
                        } else {
                            currb.right();
                        }
                        if (level == 3 || level == 4) {
                            currb.down();
                        }
                        if (hint) {
                            b->deletehint(hinttemp);
                            hinttemp.clear();
                            hint = false;
                        }
                        cout << (*b);
                        levelgene.display_next();
                    } else if (cmd == cmdcheck.getleft()) {
                        if (multicommand) {
                            currb.left(multitime);
                            multicommand = false;
                        } else {
                            currb.left();
                        }
                        if (level == 3 || level == 4) {
                            currb.down();
                        }
                        if (hint) {
                            b->deletehint(hinttemp);
                            hinttemp.clear();
                            hint = false;
                        }
                        cout << (*b);
                        levelgene.display_next();
                    } else if (cmd == cmdcheck.getdown()) {
                        if (multicommand) {
                            currb.down(multitime);
                            multicommand = false;
                        } else {
                            currb.down();
                        }
                        if (level == 3 || level == 4) {
                            currb.down();
                        }
                        if (hint) {
                            b->deletehint(hinttemp);
                            hinttemp.clear();
                            hint = false;
                        }
                        cout << (*b);
                        levelgene.display_next();
                    } else if (autodrop || cmd == cmdcheck.getdrop()) {
                        if (droptime != 0) {
                            droptime--;
                        } else {
                            autodrop = false;
                            multicommand = false;
                        }
                        currb.drop();
                        unique_ptr<vector<int>> v;
                        v = make_unique<vector<int>>();
                        v = b->clean();  // check the line we clean;
                        int size = v->size();
                        for (int i = 0; i < size; i++) {
                            int k = v->at(i);
                            if (k != -1) {
                                binfo[k].count--;
                            }
                        }
                        if (level == 4) {
                            if (size == 0) {
                                count_without_clean++;
                            } else {
                                count_without_clean = 0;
                            }
                            if (count_without_clean != 0 && 
                                 count_without_clean % 5 == 0) {
                                Block extra('*', b, -1);
                                extra.drop();
                                unique_ptr<vector<int>> v2;
                                v2 = make_unique<vector<int>>();
                                v2 = b->clean();
                                for (int i = 0; i < size; i++) {
                                    int k = v2->at(i);
                                    if (k != -1) {
                                        binfo[k].count--;
                                    }
                                }
                            }
                        }
                        for (int i = 0; i < ith; i++) {   
                            // use to delete the num of parts on the board;
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
                        
                        b->checkHiScore();      // update the highest score;
                        // curr level is different from the 
                        // start level of this block;
                        
                        if (curr_level != level) {
                            b->setlevel(curr_level);// set the board level;
                            random34 = true;
                            if (curr_level == 0) {
                                pos = -1;
                            } else if (curr_level == 4) {
                                count_without_clean = 0;
                            }
                        }
                        
                        if (hint) {
                            b->deletehint(hinttemp);
                            hinttemp.clear();
                            hint = false;
                        }
                        
                        break;
                    } else if (cmd == cmdcheck.getclockwise()) {
                        if (multicommand) {
                            currb.clockwise(multitime);
                            multicommand = false;
                        } else {
                            currb.clockwise();
                        }
                        if (level == 3 || level == 4) {
                            currb.down();
                        }
                        if (hint) {
                            b->deletehint(hinttemp);
                            hinttemp.clear();
                            hint = false;
                        }
                        cout << *b;
                        levelgene.display_next();
                    } else if (cmd == cmdcheck.getcounterclockwise()) {
                        if (multicommand) {
                            currb.countclockwise(multitime);
                            multicommand = false;
                        } else {
                            currb.countclockwise();
                        }
                        if (level == 3 || level == 4) {
                            currb.down();
                        }
                        if (hint) {
                            b->deletehint(hinttemp);
                            hinttemp.clear();
                            hint = false;
                        }
                        cout << *b;
                        levelgene.display_next();
                    } else if (cmd == cmdcheck.getlevelup()) {
                        if (multicommand) {
                            for (int i = 0; i < multitime; i++) {
                                if (curr_level == 4) {
                                    continue;
                                } else {
                                    levelgene.levelup();
                                    curr_level++;
                                }
                            }
                        } else {
                            if (curr_level == 4) {
                                continue;
                            } else {
                                levelgene.levelup();
                                curr_level++;
                            }
                        }
                        if (hint) {
                            b->deletehint(hinttemp);
                            hinttemp.clear();
                            hint = false;
                        }
                    } else if (cmd == cmdcheck.getleveldown()) {
                        if (multicommand) {
                            for (int i = 0; i < multitime; i++) {
                                if (curr_level == 0) {
                                    continue;
                                } else {
                                    levelgene.leveldown();
                                    curr_level--;
                                }
                            }
                        } else {
                            if (curr_level == 0) {
                                continue;
                            } else {
                                levelgene.leveldown();
                                curr_level--;
                            }
                        }
                        if (hint) {
                            b->deletehint(hinttemp);
                            hinttemp.clear();
                            hint = false;
                        }
                    } else if (cmd == "random") {
                        if (hint) {
                            b->deletehint(hinttemp);
                            hinttemp.clear();
                            hint = false;
                        }
                        if (level == 3 || level == 4) {
                            random34 = true;
                        } else {
                            continue;
                        }
                    } else if (cmd == "norandom") {
                        if (sequencecommand) {
                            file = scom[sequnum];
                            sequnum++;
                        } else {
                            cin >> file;
                        }
                        if (hint) {
                            b->deletehint(hinttemp);
                            hinttemp.clear();
                            hint = false;
                        }
                        if (level < 3) {
                            continue;
                        } else {
                            pos = -1;
                            random34 = false;
                        }
                    } else if (cmd == "sequence") {
                        string files;
                        cin >> files;
                        if (hint) {
                            b->deletehint(hinttemp);
                            hinttemp.clear();
                            hint = false;
                        }
                        sequencecommand = true;
                        fstream ff(files);
                        string word;
                        while (ff >> word) {
                            scom.push_back(word);
                        }
                        sequtime = scom.size();
                    } else if (cmd == "restart") {
                        restart = true;
                        break;
                    } else if (cmd == "hint") {
                        hinttemp.clear();
                        hintpos = currb.hint();
                        hint = true;
                        hinttemp.push_back(hintpos.a);
                        hinttemp.push_back(hintpos.b);
                        hinttemp.push_back(hintpos.c);
                        hinttemp.push_back(hintpos.d);
                        b->set(hinttemp,'?');
                        cout << (*b);
                        levelgene.display_next();
                    } else if (cmd == "rename") {
                        string newcmd;
                        string oldcmd;
                        cin >> oldcmd;
                        cin >> newcmd;
                        cmdcheck.renamecmd(oldcmd, newcmd);
                    } else {
                        continue;
                    }
                }
                if (restart || gameover) break;
            }
            high_score = b->getHiscore();
            b->reset();
            if (gameover) {
                while(cin >> cmd) {
                    if (cmd == "restart") break;
                    cout << "Restart the game!" << endl;
                }
            }
        }
    }
    catch (ios::failure &) {
        cout << "End of the game!" << endl;
    }
}
