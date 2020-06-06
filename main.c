/*  
    LICENCE
    Provided with an MIT Licence and Licenced as Share-Alike CC 6/5/2020

    NAME
    Keyboard Math '75

    DEPENDENCIES
    You must add constant.h to your project

    DESCRIPTION
    This file is used for testing linear algebraic algorithms, and describing the 
    most fundamental aspects of computing bidimentional arrays. This simple application
    program is intended as starting point for more complex algorithms involving arrays
    and linear algebra. This application performs only the fundamentals and computes
    under the standard practice of functional programming. 

    ASSIGNMENT
    Assignment Type: Final Project
    Course: Programming Logic
    Date: 6/4/2020

    RUN
    gcc main.c -o main

    MODIFIED
    * Created       5 Jun 2020      Michaus M. , &. Romero M.A.;
*/

/***********************************************************/
/***********************************************************/
/***********************************************************/

/*
Declaration of Include files 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "constants.h"

/*
Declaration of Global Variables
*/

float res[21][21];       // (global) ANS as matrix
float sys[10];           // (global) ANS as system
float matrix_a[10][10];  // (global) matrix A
float matrix_b[10][10];  // (global) matriz B
int mn = 0;              // (global) current size of matrix
bool is_valid_a = false; // (global) matrix is usable
bool is_valid_b = false; // (global) matrix is usable

/************* START FUNCTION DECLARATIONS  ***************/
/**********************************************************/

int KM75_printTitle();
char KM75_scanSelect(const char *text, const int size);
float KM75_scanNumber(const char *text, bool int_only);
char KM75_listSelect(const char *texts[], const int size);
void KM75_exitApp(const char *text);
int KM75_arraySizer(bool edit_mn);
int KM75_arrayEditor(bool zero_only, bool is_res, bool is_a);
int KM75_arrayMenu(bool is_a);
int KM75_arrayPrinter(bool is_res, bool is_sys, bool is_a);
int KM75_arrayDot();
int KM75_arraySum();
int KM75_arrayMemcpy();
int KM75_scanConstants();
int KM75_arrayTransRow(int r1, int r2);
int KM75_arrayFwdElim();
int KM75_arrayBkwdSubs();
int KM75_arrayGaussian();
int KM75_arraySarrus();
int KM75_arrayTranspose();
bool KM75_appBootstrapper();

/***********************************************************/
/***********************************************************/
/***********************************************************/

/*
* $console KM75_printTitle
* This block will print ACSII art  with a neat title just below, all lines are printed to welcome the user.
* Time complexity: the execution time is defined by O(1).
* 
* @return int 0: this block returns 0 when it ends its execution 
*/
int KM75_printTitle()
{
    printf("\n");
    printf("\n");
    printf("\t     ::.----.`    `.---..:////:-.       \n");
    printf("\t     ymh-:::::-  -:::::-dmmmmmmmmds:    \n");
    printf("\t     ymm:::::::  `````` .-::::/+ohmmd:  \n");
    printf("\t     ymm:::::::       `   `-:::::-/hmmo \n");
    printf("\t     ymm:::::::      .:-    .::::::-hmm/\n");
    printf("\t     ymm:::::::     -:::-o-  .:::::::mmy\n");
    printf("\t     ymm:::::::   `-:::-syy-  :::::::mmy\n");
    printf("\t     ymm:::::::  `:::::yyyy.  :::::::mmy\n");
    printf("\t     ymm:::::::  .::-/yyyy-   :::::::mmy\n");
    printf("\t     ymm:::::::`  --/yyys.    :::::::mmy\n");
    printf("\t     omms-::::::`   :yyo`     :::::::mmy\n");
    printf("\t     `hmmo-::::::.   .+`      :::::::mmy\n");
    printf("\t      `smmdo/--:::-.`         :::::::mmy\n");
    printf("\t        -sdmmdhyyyyyy-::::::  ::::::-dmy\n");
    printf("\t          `-+osyyyys/-::::-`   .-:::-:oo\n");
    printf("\n");
    printf("\t :::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\t ::            KEYBOARD MATH '75            ::\n");
    printf("\t :::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("\n");
    printf("\n");
    system("pause");
    return 0;
}

/*
* $console KM75_scanSelect
* This function will read and validate the user's input as a character, and then flush stdin. An invalid input means this function will return SELECT_INVALID.
* Time complexity: unknown, execution time is completely user dependant.
*
* @param char *text: string to print before scanning input
* @param int size: the count of allowed inputs starting from Aa
* @return char scanned or SELECT_INVALID;
*/
char KM75_scanSelect(const char *text, const int size)
{
    char scanned[1];
    printf("\n %s", text);
    fgets(scanned, 2, stdin);
    char selected = (char)scanned[0];

    selected = ((int)selected >= 97 && (int)selected < 97 + size) || ((int)selected >= 65 && ((int)selected < 65 + size))
                   ? selected
                   : SELECT_INVALID;

    if (selected == SELECT_INVALID)
    {
        printf("%s \n", SELECT_INVALID_TEXT);
    }
    fflush(stdin);
    return selected;
}

/*
* $console KM75_scanNumber\
* This function is a mirrored <<KM75_scanSelect>>, it will read and validate input as an integer number, and then flush stdin. An invalid input means this function will return 0.
* Time complexity: unknown, execution time is completely user dependant.
*
* @param char *text: string to print before scanning input
* @return int scanned or 0
*/
float KM75_scanNumber(const char *text, bool int_only)
{
    char scanned[10000];
    printf("\n %s", text);
    fgets(scanned, 10001, stdin);
    float selected = int_only ? (float)atoi(scanned) : atof(scanned);
    fflush(stdin);
    return selected;
}

/*
* $console KM75_listSelect
* This function will list options from {texts} to the user through the process' console as a list, and capture the selected option as a char, if an invalid choice is detected a loop is performed.
* Time complexity: unknown, execution time is completely user dependant.
*
* @param char *texts[] : the menu as an array of strings,
* @param int size : sizeof *texts[].
* @return select char : selected option.
*/
char KM75_listSelect(const char *texts[], const int size)
{
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%s \n", texts[i]);
    }

    char selected = SELECT_INVALID;

    while (selected == SELECT_INVALID)
    {
        selected = KM75_scanSelect(SELECT_TEXT, MENU_SIZE);
    }

    return selected;
}

/*
* $console KM75_exitApp
* Will pause the execution system and then close the main thread therefore terminating the execution process.
* Time complexity: unknown, execution time is completely user dependant.
*
* @param char *text : the text to print when closing
* @return void: the app closes within this block
*/
void KM75_exitApp(const char *text)
{
    printf("\n%s, ", text);
    system("pause");
    exit(0);
}

/*
* $console KM75_arraySizer 
* This block will return the captured current global matrix size, validate for a minimum allowed and maximum allowed and loop until the captured value is valid.
* Time complexity: if param edit_mn == false, then the execution time will be defined by O(1); otherwise it's unknown, as it's user dependant.
* 
* @param bool edit_mn : true to read input mn or false for default
* @param bool is_m : true to scan for M or false for N
* @return int mn : valid size of mn
*/
int KM75_arraySizer(bool edit_mn)
{
    bool mn_invalid = true;
    int mn = MAX_MATRIX_SIZE;
    while (mn_invalid)
    {
        if (edit_mn)
        {
            mn = (int)KM75_scanNumber(INPUT_MATRIX_SIZE, true);
            if (mn <= MAX_MATRIX_SIZE && mn >= MIN_MATRIX_SIZE)
                mn_invalid = false;
            else
                printf("\n %s%i", ERROR_MATRIX_SIZE, MAX_MATRIX_SIZE);
        }
        else
            mn_invalid = false;
    }

    return mn;
}

/*
* $console KM75_arrayEditor
* This function will zero selected matrixes or capture matrix data from the user.
* Time complexity: if param zero_only == true, then the execution time will be defined by O(N^2); otherwise it's unknown, as it's user dependant.
* 
* @param bool fill_only : if true block will reset the selected array to a zeroed array
* @param bool fill_only : if true block will edit a, otherwise false it will edit b
* @return int 0 : this block returns 0 when it ends its execution 
*/
int KM75_arrayEditor(bool zero_only, bool is_res, bool is_a)
{

    if (!zero_only)
    {
        printf("\n %s \n", EDIT_MATRIX_TEXT);
    }

    int aux_mn = mn;
    mn = mn == 0 ? KM75_arraySizer(!zero_only) : mn; // O(1) ~ O(0)

    for (int i = 0; i < mn; i++)

        for (int j = 0; j < mn; j++)
        {
            char text[255];
            snprintf(text, sizeof(text), "[%i,%i]: ", i, j);

            if (is_res)
                res[i][j] = 0;

            else
            {
                if (is_a)
                    matrix_a[i][j] = zero_only ? 0 : KM75_scanNumber(text, false);
                else if (!is_a && !is_res)
                    matrix_b[i][j] = zero_only ? 0 : KM75_scanNumber(text, false);
            }
        }

    if (zero_only)
    {
        mn = !is_valid_a && !is_valid_b ? 0 : aux_mn;
    }

    return 0;
}

/* 
* $exec KM75_arrayMenu
* This function bootstraps all other important functions to edit arrays, validates said arrays and executes selected blocks.
* Time complexity: if a or b are not being edited, then the execution time is O(2N^2); otherwise it will be unknown, as execution time is user dependant,
*
* @param bool is_a : if true this block will let the user define matrix a, if false matrix b
* @return int 0 : this block returns 0 when it ends its execution 
*/
int KM75_arrayMenu(bool is_a)
{
    bool wants_to_continue = true;
    if ((is_valid_a && is_a) || (is_valid_b && !is_a))
    {
        printf("\n %s \n", RESET_MATRIX_WARNING);
        char selected_continue = KM75_listSelect(CONTINUE_LIST, CONTINUE_SIZE);
        wants_to_continue = selected_continue == 'a' || selected_continue == 'A';
    }

    if (wants_to_continue)
    {
        if ((is_valid_a && is_a) || (is_valid_b && !is_a))
        {
            is_valid_a = false;
            is_valid_b = false;
            mn = 0;
            KM75_arrayEditor(true, false, true);
            KM75_arrayEditor(true, false, false);
        }

        KM75_arrayEditor(true, false, is_a);  //O(N^2)
        KM75_arrayEditor(false, false, is_a); //O(N^2)
        if (is_a)
            is_valid_a = true;
        else
            is_valid_b = true;
    }

    return 0;
}

/*
* $console KM75_arrayPrinter
* This function may be called to print a matrix, the selected matrix will be logged with its corresponding columns, rows and spaces.
* Time complexity: this block's execution time is defined by O(N^2 + N);
*
* @param bool is_res : if true this block will print the res matrix
* @param bool is_a : if true this block will print matrix a, if false matrix b
* @return int 0 : this block returns 0 when it ends its execution 
*/
int KM75_arrayPrinter(bool is_res, bool is_sys, bool is_a)
{
    printf("\n%s\n", is_sys || is_res ? PRINT_RES_TEXT : PRINT_MATRIX_TEXT); //O(1)
    printf("\n");                                                            //O(1)

    for (int i = 0; i < mn; i++)
    {
        char var = (char)(97 + i);
        if (is_sys)
            printf("%c: %.2f", var, sys[i]); // O(1)

        for (int j = 0; j < mn; j++)
            if (!is_sys)
                printf("%.2f ", is_res ? res[i][j] : is_a ? matrix_a[i][j] : matrix_b[i][j]); // O(1)
        printf("\n");                                                                         // O(1)
    }
    return 0;
}

/*
* $exec KM75_arrayDot
* This function will perform a matmul operation of two matrixes, matrixes a and b (Global Variables), using Eric Weiser's method. 
* Time complexity: O(N^3 + 2N^2 + N), the total execution time from child functions is O(2N^2 + N).
*
* @return int 0 : this block returns 0 when it ends its execution 
*/
int KM75_arrayDot()
{
    printf("\n%s\n", DOT_MATRIX_TEXT); //O(1)
    float aux;
    KM75_arrayEditor(true, true, false); //O(N^2)
    for (int i = 0; i < mn; i++)
        for (int j = 0; j < mn; j++)
        {
            aux = 0;
            for (int k = 0; k < mn; ++k)
            {
                aux += matrix_a[i][k] * matrix_b[k][j];
            }
            res[i][j] = aux;
        }

    KM75_arrayPrinter(true, false, false); //O(N^2 + N)
    return 0;
}

/*
* $exec KM75_arraySum
* This function performs a sum of two matrixes, namely a and b (Global Variables). 
* Time complexity: the time complexity of this function is O(3N^2 + N + 1), mainly because this block contains two other functions of the time complexity O(N^2 +  N + 1). 
*
* @return int 0 : this block returns 0 when it ends its execution 
*/
int KM75_arraySum()
{
    printf("\n%s\n", SUM_MATRIX_TEXT);   //O(1)
    KM75_arrayEditor(true, true, false); // O(N^2)
    for (int i = 0; i < mn; i++)
        for (int j = 0; j < mn; j++)
            res[i][j] = matrix_a[i][j] + matrix_b[i][j];
    KM75_arrayPrinter(true, false, false); // O(N^2 + N + 1)
    return 0;
}

/*
* $exec KM75_arrayMemcpy
* This block performs a memcpy operation. similar to numpy's for phyton, res recieves all values stored in matrix a.
* Time complexity: O(N^2)
*
* @return int 0 : this block returns 0 when it ends its execution 
*/
int KM75_arrayMemcpy()
{
    for (int i = 0; i < mn; i++)
        for (int j = 0; j < mn; j++)
            res[i][j] = matrix_a[i][j];
    return 0;
}

/*
* $exec KM75_scanConstants
* This block adds an extra column to res with a set of defined constants, procedural linear equations are calculated here.
* Time complexity: unknown, time of execution is completely user dependant.
*
* @return int 0 : this block returns 0 when it ends its execution 
*/
int KM75_scanConstants()
{
    KM75_arrayMemcpy();

    for (int i = 0; i < mn; i++)
    {
        char text[255] = "";
        for (int j = 0; j < mn; j++)
        {
            char var = (char)(97 + j);
            char partial[20];

            if (j == 0)
                snprintf(partial, sizeof(partial), "(%.2f%c)", res[i][j], var);
            else if (j == (mn - 1))
            {
                snprintf(partial, sizeof(partial), " %c (%.2f%c) %c ", '+', res[i][j], var, '=');
            }
            else
                snprintf(partial, sizeof(partial), " %c (%.2f%c)", '+', res[i][j], var);

            strcat(text, partial);
        }

        res[i][mn] = KM75_scanNumber(text, false);
    }
    return 0;
}

/*
* $exec KM75_arrayTransRow
* This block swaps instructed rows from {{res}}, so basically r1 and r2 swap positions inside the array.
* Time complexity: O(N).
*
* @return int 0 : this block returns 0 when it ends its execution 
*/
int KM75_arrayTransRow(int r1, int r2)
{
    float aux;
    for (int i = 0; i <= mn; i++)
    {
        aux = res[r2][i];
        res[r2][i] = res[r1][i];
        res[r1][i] = aux;
    }
    return 0;
}

/*
* $exec KM75_arrayFwdElim 
* This block expects {{res}} to be a square matrix with an extra column of defined constants <<res[mn-1][mn] is defined>>. This block will swap rows and perform other matrix operations to zero all numbers below {{res}}'s main diagonal. If the main diagonal has a row with a zeroed pivot that cannot be swapped for another row then this system returns the index of said pivot. 
* Time complexity: O(N^3).
*
* @return int -1 : this block returns -1 when the system can be solved, otherwise return an index of a zeroed pivot which will cause infinitely many solutions or no solutions at all.
*/
int KM75_arrayFwdElim()
{
    for (int i = 0; i < mn; i++)
    {
        int max_pivot_index = i;
        int max_pivot_value = res[max_pivot_index][i];

        for (int j = i + 1; j < mn; j++)
            if (abs(res[j][i]) > max_pivot_value)
                max_pivot_value = res[j][i], max_pivot_index = j;

        if (!res[i][max_pivot_index])
            return i;
        if (max_pivot_index != i)
            KM75_arrayTransRow(i, max_pivot_index);

        for (int j = i + 1; j < mn; j++)
        {
            float elem = res[j][i] / res[i][i];
            for (int k = i + 1; k <= mn; k++)
                res[j][k] -= res[i][k] * elem;
            res[j][i] = 0;
        }
    }
    return -1;
}

/*
* $exec KM75_arrayBkwdSubs 
* This block expects res to be a square matrix with an extra column of defined constants <<res[mn-1][mn] is defined>>, res must be in an upper triangular form. This block will take the bottom most system wich will only have one constant and one variable and start remplacing values upwards.
* Time complexity: O(N^2).
*
* @return int 0 : this block returns 0 when it ends its execution 
*/
int KM75_arrayBkwdSubs()
{
    for (int i = mn - 1; i >= 0; i--)
    {
        sys[i] = res[i][mn];
        for (int j = i + 1; j < mn; j++)
            sys[i] -= res[i][j] * sys[j];
        sys[i] = sys[i] / res[i][i];
    }
    return 0;
}

/*
* $exec KM75_arrayGaussian 
* This function will execute other blocks, related to gaussian elimination. And predict if the system of equations can or cannot be solved.
* Time complexity: unknown, execution time is completely user dependant.
*
* @return int 0 : this block returns 0 when it ends its execution 
*/
int KM75_arrayGaussian()
{
    printf("\n%s\n", GAUSSIAN_MATRIX_TEXT); //O(1)
    KM75_scanConstants();
    int principal_index_zeroed = KM75_arrayFwdElim();
    if (principal_index_zeroed != -1)
    {
        if (res[principal_index_zeroed][mn])
            printf("\n%s\n", MATRIX_INCONSISTANT);
        else
            printf("\n%s\n", MATRIX_INFINITE);
        return 0;
    }
    KM75_arrayBkwdSubs();
    KM75_arrayPrinter(false, true, false);
    return 0;
}

/*
* $exec KM75_arraySarrus 
* This block finds the determinant of a matrix, matrix needs to be squared <<nxn>> and n must be smaller or equal than 3.
* Time complexity: O(N^2 + N)
*
* @return int 0 : this block returns 0 when it ends its execution 
*/
int KM75_arraySarrus()
{
    KM75_arrayMemcpy();
    if (mn > 3)
    {
        printf("\n%s\n", ERROR_MATRIX_SARRUS);
        return 0;
    }
    float d1 = 0, d2 = 0, d = 0;
    if (mn == 3)
        for (int i = 0; i < 3; i++)
        {
            d1 = d1 + res[0][i] * res[1][(i + 1) % 3] * res[2][(i + 2) % 3];
            d2 = d2 + res[2][i] * res[1][(i + 1) % 3] * res[0][(i + 2) % 3];
        }
    d = d1 - d2;
    if (mn == 2)
        d = (res[0][0] * res[1][1]) - (res[1][0] * res[0][1]);
    printf("\n%s %.2f\n", PRINT_RES_TEXT, d);
    return 0;
}

/*
* $exec KM75_arrayTranspose  
* This block swaps rows as columns from a provided matrix {{a}} into {{res}}.
* Time complexity: O(N^2 + N)
*
* @return int 0 : this block returns 0 when it ends its execution 
*/
int KM75_arrayTranspose()
{
    for (int i = 0; i < mn; ++i)
        for (int j = 0; j < mn; ++j)
            res[j][i] = matrix_a[i][j];
    KM75_arrayPrinter(true, false, false);
    return 0;
}

double KM75_arrayCramer()
{
    KM75_arrayMemcpy();

    for (int i = 0; i < mn; ++i)
        res[i][mn - 1] = res[mn];

    double det_tmp = det(tmp);
    deinit_square_matrix(tmp);
    KM75_scanConstants;

    return det_tmp / det_A;
}

/*
* $bootstrap KM75_appBootstrapper 
* This function bootstraps all other important functions, executes selected blocks.
* Time complexity: unknown, execution time is completely user dependant.
*
* @return bool wants_to_continue : returns true to repeat
*/
bool KM75_appBootstrapper()
{
    char selected_menu = KM75_listSelect(
        !is_valid_a ? A_MENU_LIST
                    : !is_valid_b ? B_MENU_LIST
                                  : MENU_LIST,
        MENU_SIZE);

    system("cls");
    switch (selected_menu)
    {
    case 'a':
    case 'A':
        KM75_arrayMenu(true);
        break;
    case 'b':
    case 'B':
        KM75_arrayMenu(false);
        break;
    case 'c':
    case 'C':
        if (!is_valid_a)
        {
            printf("\n %s \n", DISABLED_WARNING);
            return true;
        }
        KM75_arrayPrinter(false, false, true);
        break;
    case 'd':
    case 'D':
        if (!is_valid_b)
        {
            printf("\n %s \n", DISABLED_WARNING);
            return true;
        }
        KM75_arrayPrinter(false, false, false);
        break;
    case 'e':
    case 'E':
        if (!is_valid_a)
        {
            printf("\n %s \n", DISABLED_WARNING);
            return true;
        }
        KM75_arrayGaussian();
        break;
    case 'f':
    case 'F':
        if (!is_valid_a)
        {
            printf("\n %s \n", DISABLED_WARNING);
            return true;
        }
        // [ ]TODO Crammer Method on matrix A
        break;
    case 'g':
    case 'G':
        if (!is_valid_a)
        {
            printf("\n %s \n", DISABLED_WARNING);
            return true;
        }

        KM75_arraySarrus();
        break;
    case 'h':
    case 'H':
        if (!is_valid_a)
        {
            printf("\n %s \n", DISABLED_WARNING);
            return true;
        }
        KM75_arrayTranspose();
        break;
    case 'i':
    case 'I':
        if (!is_valid_a || !is_valid_b)
        {
            printf("\n %s \n", DISABLED_WARNING);
            return true;
        }
        KM75_arrayDot();
        break;
    case 'j':
    case 'J':
        if (!is_valid_a || !is_valid_b)
        {
            printf("\n %s \n", DISABLED_WARNING);
            return true;
        }
        KM75_arraySum();
        break;
    case 'k':
    case 'K':
        KM75_exitApp(EXIT_TEXT);
        return false;
        break;
    default:
        printf("%s, %s", ERROR_TEXT, EXIT_TEXT);
        return false;
        break;
    }
    char selected_continue = KM75_listSelect(CONTINUE_LIST, CONTINUE_SIZE);
    bool wants_to_continue = selected_continue == 'a' || selected_continue == 'A';

    if (!wants_to_continue)
        KM75_exitApp(EXIT_TEXT);

    system("cls");
    return wants_to_continue;
}

/*
* $main main
* This is the app's main function and it will loop the execution of KM75_appBootstrapper until appBootsrapper returns false.
* Time complexity: unknown, execution time is completely user dependant.
*
* @return int 0 : this block returns 0 when it ends its execution 
*/
int main()
{
    KM75_printTitle();
    bool can_repeat = true;
    while (can_repeat)
    {
        can_repeat = KM75_appBootstrapper();
    }

    return 0;
}

/*
End of program
*/