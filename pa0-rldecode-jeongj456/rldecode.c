#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isnumber(char c);
int decode(char *str);
bool check(char *str);

/*
 * The isnumber() function examines the character given as its first
 * argument and returns true if and only if the character represents
 * an number.  This helper function should be relatively short.
 *
 * Returns true if the given character represents an number, false
 * otherwise.
 */
bool isnumber(char c){
    int x = c - '0';
    if (0<=x && x<=9) {
        return true;
    }
    return false;
}
/*

 * The decode() function takes a run-length encoded string as its
 * argument, parses every integer n preceding every character in
 * the string, and prints each character n times.  For example, if
 * the string passed to decode() is "1a3b", decode() will print
 * "abbb".  It returns an integer that represents the summed value
 * of the amount of characters printed; in this example, decode()
 * would return the integer 4.
 *
 * This function must also handle malformed run-length encoded strings.
 * A malformed string is any string which does not adhere to the RLE
 * implementation described in the handout. If a malformed string is
 * encountered, it should cease printing the decoded string, print an
 * error message, and return -1.
 *
 * Returns the integer value of the total amount of characters printed,
 * or -1 if the run-length encoded string is malformed.
 */

int decode(char *str){
    char *strin="";
    int retval=0;
    int rept=0;
    for (int i=0; str[i]!='0'; i++){
        int curnum=str[i]-'0';
        
        
        if(isnumber(str[i])){
            if(rept==0&&curnum==0){
                printf("Error");
                return -1;
            }
            rept=(rept*10)+curnum;
        }

        else if(rept!=0){
            if((' '<=str[i] && str[i]<='/') || (':'<=str[i] && str[i]<='~') || str[i] == '\n'){
                /*concat*/
                retval=retval+rept;
                rept=0;
            }
            
        }

        else if(rept==0){
            printf("Error");
            return -1;
        }
    }printf(strin);
    return 0;
}



bool check(char *str){
    int sc=0;
    if (isnumber(str[strlen(str)-1]) || (str[0]-'0')==0 || (str[0]-'0')=='-' || isnumber(str[0])==false){
        printf("Error: Malformed String\n");
        return false;
    }else{ 
        for (int i=0; str[i] != '\0'; i++){
            if (isnumber(str[i])){
                if(sc>0 &&((str[i]-'0')==0 || (str[0]-'0')=='-')){
                    printf("Error: Malformed String\n");
                    return false;
                }
                sc=0;
            }else{
                if ((sc==0) && ((' '<=str[i] && str[i]<='/') || (':'<=str[i] && str[i]<='~') || str[i] == '\n')){
                    sc++;
                }else{ 
                    printf("Error: Malformed String\n");
                    return false;
                }
            }
        }   
    }return true;
}

int decode(char *str){
    if (check(str)){
        int retval=0;
        int numb=0;
        for (int i=0; str[i]!='\0'; i++){
            if(isnumber(str[i])){
                int curchar=str[i]-'0';
                numb=(numb*10)+curchar;
            }else{
                for(int z=0; z<numb; z++){
                    printf("%c", str[i]);
                }
                retval+=numb;
                numb=0;
            }
        }
        printf("\n");
        return retval;
    }
    return -1;
}

/*
 * The main function is where C programs begin.
 *
 * This function parses its arguments and returns the value they
 * represent.  In this assignment, the only valid argument is a
 * run-length encoded string.  Any extra arguments in excess of
 * this single valid argument make the invocation of your program
 * invalid.
 *
 * Remember that the argument in argv[0] is the name of the program, so
 * a program passed exactly one argument on the command line will
 * receive _two_ arguments: its name in argv[0] and the provided
 * argument in argv[1].
 *
 * Arguments:
 * argc - The number of arguments received
 * argv - The arguments received as an array of C strings
 *
 * Returns 0 if the argument is well-formed and the string could
 * be decoded, non-zero otherwise.
 */
int main(int argc, char *argv[]) {
    /* Your main program logic should go here, with helper logic in the
     * functions isnumber() and decode(), which you can place below
     * the closing brace of main() */
    if (argc==2){
        if (decode(argv[1])==-1){
            return -1;
        }
    }return 0;
}

/* You should implement isnumber() and decode() here */
