//text editor
#include<ncurses.h>
#include<stdlib.h>
#include<string.h>

FILE* openFile(char input[], WINDOW* window)
{//this function takes in a file name, checks to see if it exists,
 //if it does not exist, the user is prompted to create a file then returns the output to the console.
 //Author: Denny Hood
    char choice; //user selection to create a nonexistent file
    FILE* filePTR = fopen(input, "r"); //try to open existing file
    if(filePTR == NULL)
    {//file does NOT exist, prompt user to create a new file

        printw("Input file does not exist. Do you wish to create one? [Y/N]:");
        choice = getch();
        if(choice == 'Y' || choice == 'y') //the user wants to create a file
        {
            filePTR = fopen(input, "w");   //create a file in write mode this creates a file in same directory as text_editor.c
            if(filePTR == NULL)            //error checking to make sure file was created
            {
                wprintw(window,"Error! No file was written!");
                exit(1);
            }
            else
            {
                wprintw(window,"file was successfully created!");
                return filePTR;    // function returns address of newly created file
            }
        }
        else if(choice == 'N' || choice == 'n') //the user does not want to create a file
        {
            wprintw(window,"no output file was created");
            return NULL;
        }
        else             //the user has made a bad selection
        {
            wprintw(window,"bad command, file was not created");
            return NULL;
        }
    }
    else
    {
        return filePTR; // if the file exists, return the address of the file
    }
}
void printFile(FILE* filePTR, WINDOW* window)
{//this function checks to see if a file exists then prints contents to console and closes the file
 //Author: Denny Hood
    char cha;
    int charPosition = 0;             //start at first character in file
    if(filePTR != NULL)               //make sure file exists we are printing from
    {
        while((cha = fgetc(filePTR)) != EOF) //gets one character at a time from file
        {
            wprintw(window,"%c",cha); //get character from file and print to the new window
            charPosition++;
        }
    fclose(filePTR);                  //close the file after we have read in every character
    }
    else //(filePTR == NULL)
    {
        wprintw(window,"\nError! No file exists!");
    }
}

int main()
{
    FILE *filePTR; //input file stream
    char inputFileName[80];

    initscr();              //create screen
	WINDOW* window = newwin(23,80,0,0);//specify new window size
    printw("Welcome to text file editor!\nType the name of the file you wish to edit:");
	getstr(inputFileName);
///open the file:------------------------------
	filePTR = openFile(inputFileName,window);
///print the contents if it exists-------------
    printFile(filePTR, window);

    wrefresh(window);
	getch();         //pause window so user can see output of printFile
	delwin(window);
	endwin();

    return 0;
}
