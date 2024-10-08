// That's dangerous to use this code for production...

#include <string.h>
#include <wchar.h>
#include <stdbool.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

char results[256][256] = { 0 };
bool dividors[256][256] = { 0 };

typedef struct {
    bool withDivision;
    int prob1, prob2;
} ProbDivInfo;

ProbDivInfo divProbs[256] = { 0 };

int maxDepth = 0;

void __shannonFanoRecursion(
        wchar_t* symbols, 
        int* probs, 
        int l, 
        int r,
        int depth,
        char appendSymbol
        )
{
    if(depth>=0)
        results[l][depth] = appendSymbol;

    if(maxDepth < depth)
        maxDepth = depth;

    if(r - l <= 1) {
        return;
    }

    // Let get sum.
    int probSum = 0;
    for(int i  = l; i < r; ++i) {
        probSum += probs[i];
    }

    // Let find division.
    int prob = probs[l];
    int divPoint = l;
    int minDiff = -1;

    int takenProb = 0;

    for(int x = l + 1; x <= r - 1; ++ x) {
        int leftP = probSum - prob;
        int diff = prob - leftP;
        
        if(diff < 0)
            diff = -diff;
                
        if(minDiff == -1 | diff < minDiff) {
            divPoint = x;
            minDiff = diff;
            takenProb = prob;
        }
        prob += probs[x];
    }
   
    divProbs[divPoint] = (ProbDivInfo){
        .withDivision = true,
        .prob1 = takenProb,
        .prob2 = probSum - takenProb
    }; 

    for(int i = depth + 1; i < 255; ++i)
        dividors[divPoint][i] = true;
    
    __shannonFanoRecursion(
            symbols,
            probs,
            l,
            divPoint,
            depth + 1,
            '0'
            );

    __shannonFanoRecursion(
            symbols,
            probs,
            divPoint,
            r,
            depth + 1,
            '1'
            );
}

void makeShannonFanoCoding(
        wchar_t* symbols, 
        int* probs, 
        size_t size 
        )
{
    __shannonFanoRecursion(
            symbols,
            probs,
            0,
            size,
            -1,
            'w'
            );
}

void outputResults(wchar_t* symbols, int size) {
    int prevDepth = 0;
    int currDepth = 0;
    char codes[maxDepth + 1];

    memset(codes, 0, maxDepth + 1); 

    for(int y = 0; y < size; ++y) {
      
        if(!y)
            wprintf(L"┌─");
        else
            wprintf(L"│ ");
        
        for(int x = 0; x <= maxDepth + 1; ++x) {
            if(!y)
                wprintf(L"─");
            else
                wprintf(L" ");
        }

        
        for(int x = 0; x < 255; ++x) {
            if(results[y][x] && currDepth < x + 1)
                currDepth = x + 1;
        } 

        // wprintf(L"  │", symbols[y]);
        if(!y)
            wprintf(L"──┬");
        else if(dividors[y][0])
            wprintf(L"  ├");
        else
            wprintf(L"  │");
        
        for(int x = 0; x < currDepth; ++ x) {
            if(!y) {
                if(x == currDepth - 1)
                    wprintf(L"──┐");
                else
                    wprintf(L"──┬");
            }
            else if(dividors[y][x]) {
                wprintf(L"──");

                if(prevDepth != currDepth && x == currDepth - 1)
                    wprintf(L"┐");
                else if(dividors[y][x+1] && x < prevDepth && x < currDepth - 1)
                        wprintf(L"┼");
                else if(dividors[y][x+1] && x < currDepth - 1)
                    wprintf(L"┬");
                else
                    wprintf(L"┤");
            }
            else if(dividors[y][x+1])
                wprintf(L"  ├");
            else
                wprintf(L"  │");
        }
     
        if(divProbs[y].withDivision) {
            wprintf(L" ← %i/%i", divProbs[y].prob1, divProbs[y].prob2);
        }

        wprintf(L"\n");
       
        wprintf(L"│ ");
        int codeSize = 0; 
        int lastCodeY = 0;
        for(int x = 0; x <= maxDepth; ++x) {
            codes[x] = 0;
            for(int codeY = lastCodeY; codeY <= y; ++codeY) {
                if(results[codeY][x]) {
                    codes[x] = results[codeY][x];
                    lastCodeY = codeY;
                }
            }

            if(codes[x])
                codeSize = x + 1;
        }

        for(int x = 0; x <= (maxDepth - codeSize); ++x)
            wprintf(L".");
       
        for(int x = 0; x < codeSize; ++x)
            wprintf(L"%lc", codes[x]);

        wprintf(L" ");
        
        wprintf(L"%lc │", symbols[y]);
        
        for(int x = 0; x < currDepth; ++ x) {
            if (results[y][x])
                wprintf(L"%c │", results[y][x]);
            else
                wprintf(L"  │");
        }

        wprintf(L"\n");
        
        prevDepth = currDepth;
    }
    wprintf(L"└─");
    for(int x = 0; x <= maxDepth + 3; ++x) {
            wprintf(L"─");
    }
        
    wprintf(L"┴");
    for(int x = 0; x <= maxDepth; ++x) {
        wprintf(L"──");

        if(x == maxDepth)
            wprintf(L"┘");
        else
            wprintf(L"┴");
    }
    wprintf(L"\n");
}

void readInputs(FILE* file, int* outLen, wchar_t** outSymbols, int** outProbs) {
    
    int len;
    fwscanf(file, L"%i\n", &len);

    *outLen = len;

    *outSymbols = calloc(len, sizeof(wchar_t));
    *outProbs = calloc(len, sizeof(int));

    for(int x = 0; x < len; ++x) {
        wchar_t  cc;
        int pr;
        
        fwscanf(
                file, 
                (x == len - 1) ?
                L"%lc %i" :
                L"%lc %i\n", 
                &cc, &pr);

        (*outSymbols)[x] = cc;
        (*outProbs)[x] = pr;
    }

    bool touched;

    do {
        touched = false;

        for(int x = 1; x < len; ++x) {
            if((*outProbs)[x - 1] < (*outProbs)[x]) {
                int tmp1 = (*outProbs)[x - 1];
                wchar_t tmp2 = (*outSymbols)[x - 1];

                (*outProbs)[x - 1] = (*outProbs)[x];
                (*outSymbols)[x - 1] = (*outSymbols)[x];

                (*outProbs)[x] = tmp1;
                (*outSymbols)[x] = tmp2;
                
                touched = true;
            }
        }

    } while(touched);    
}

int main(int args, char** vars) {
    setlocale(LC_ALL, "");

    if(args > 1 && !strcmp(vars[1], "--help")) {
        wprintf(L"**DESCRIPTION**\n");
        wprintf(L"Program for Shannon-Fano coding calculation.\n");
        wprintf(L"Made as a result of eduactional process so not safe.\n");
        wprintf(L"2024, Kozlov Egor, 2/278, ISUCT.\n");
        wprintf(L"\n");
        wprintf(L"**ARGUMENTS**\n");
        wprintf(L"You can pass filepath as an argument to the program.\n\n");
        wprintf(L"%s ./example.txt\n\n", vars[0]);
        wprintf(L"If no file passed, stdin is used.\n");
        wprintf(L"\n");
        wprintf(L"Use --help key to show this menu.\n\n");
        wprintf(L"%s --help\n\n", vars[0]);
        wprintf(L"\n");
        wprintf(L"**INPUT FORMAT**\n");
        wprintf(L"<n - count of symbols>\n");
        wprintf(L"<symbol 1> <probability 1>\n");
        wprintf(L"...\n");
        wprintf(L"<symbol n> <probability n>\n");
        wprintf(L"\n");
        wprintf(L"For simplicity probabilities present as integers.\n");
        wprintf(L"That means that you have multiply probabilities by 10^x.\n"
                "to exclude point part.\n");
        wprintf(L"For example, symbols:\n"
                 "symbol  probability\n\n"
                 "a       0.75\n"
                 "b       0.05\n"
                 "c       0.2\n\n"
                 "Must be written as:\n\n"
                 "3\n"
                 "a 75\n"
                 "b  5\n"
                 "c 20\n\n"
               );
        wprintf(L"Records may be written in any order.\n"
                 "Program sort list by probability by itself.\n");
        return 0; 
    }

    FILE* source = args > 1 ? fopen(vars[1], "r") : stdin; 

    wchar_t* chars;
    int* probs;
    int len;

    readInputs(
            source,
            &len,
            &chars,
            &probs
            );

    int prob = 0;
    for(int x = 0; x < len; ++x)
        prob += probs[x];

    wprintf(L"Symbol readen: %i\n", len);
    wprintf(L"Total prob sum: %i\n", prob);

    bool validProbs = prob != 0;
    while(prob) {
        int digit = prob % 10;
        if(digit > 1 || (digit == 1 && prob != 1))
            validProbs = false;
        prob /= 10;
    }

    if(!validProbs) {
        
        wprintf(L"%sWARNING%s: PROBBILITY SUM IS NOT 1!\n",
                "\x1b[0;33m", "\x1b[0;0m");
        wprintf(L"Consider to check your inputs.\n");
    }
    else
        wprintf(L"Probability is %sOK%s.\n",
                 "\x1b[0;32m", "\x1b[0;0m");

    makeShannonFanoCoding(chars, probs, len);
    outputResults(chars, len); 


    return 0;
}
