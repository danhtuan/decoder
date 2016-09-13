/* 
 * File:   decoder.cpp
 * Author: Tuan
 *
 * Created on August 31, 2016, 4:05 PM
 */

#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;
const int N = 5;
const int S = 1 << N;
int D[S] = {};
int mark[S] = {};
/**
 * Try to assign i = {0,1} to position pos
 * @param pos
 * @param i
 * @return 1-yes 0-no
 */
int assign(int pos, int i) {
    D[pos] = i;
    if (pos < (S - 1)) {//if not the end of sequence
        int index = D[pos];
        for (int i = 1; i < N; i++) {
            index += D[pos - i] << i;
        }
        //cout<<"index="<<index<<endl;
        if (mark[index] == 1) {
            return 0;
        } else {
            mark[index] = 1;
            return 1;
        }
    } else {
        for (int i = N; i > 0; i--) {
            int first = (pos + 1 - i);
            int index = D[first] << (N-1);            
            for (int j = 1; j < N; j++) {
                index += D[(first + j) % S] << (N - 1 - j);
            }
            //cout<<"index:"<<index<<endl;
            if (mark[index] == 1) {
                return 0;
            }
        }
        return 1;
    }
}

/**
 * undo last assignment to assign new value
 * @param pos
 */
void unassign(int pos) {    
    int index = D[pos];
    for (int i = 1; i < N; i++) {
        index += D[pos - i] << i;
    }
    mark[index] = 0;
    D[pos] = -1;
}

/**
 * print out any array (mark or D)
 * @param D
 * @param S
 */
void printResult(int D[], int S) {
    for (int i = 0; i < S; i++) {
        cout << D[i] << " ";
    }
    cout << endl;
}
/**
 * recursive function to fill out D
 * @param pos
 */
void fillOut(int pos) {
    //cout<<"pos="<<pos<<endl;    
    for (int i = 0; i < 2; i++) {
        if (assign(pos, i)) {//if pos can be assigned i            
            if (pos < S - 1) {
                fillOut(pos + 1);                
            } else {
                //printResult(D, pos+1);
                //printResult(mark,S);
                cout<<"Solution:";
                printResult(D, S);
            }
            unassign(pos);
        }else{
            //cout<<"invalid: "<<i<<endl;
        }
    }
}

/*
 * Main Function
 */
int main(int argc, char** argv) {
    for(int i = 0; i < S; i++){
        D[i] = -1;
        mark[i] = 0;
    }
    //print the size of problem (N sensors, S = 2^N bits    
    cout << "N=" << N << " S=" << S << endl;
    //without losing generality, assume seq start with 1000..01 (N zeros)
    D[0] = 1;
    for (int i = 1; i <= N; i++) {
        D[i] = 0;
    }
    D[N + 1] = 1;
    //mark any exist N codes
    mark[1 << (N - 1)] = 1;
    mark[0] = 1;
    mark[1] = 1;
    //recursively call to fill/check the rest of sequence
    fillOut(N + 2);
    return 0;
}

