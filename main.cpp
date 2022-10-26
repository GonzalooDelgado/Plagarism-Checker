#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

void removeComments(ifstream& ,ofstream&);
void createSecondaryFile(ifstream, ofstream);
void initilizeHashMaps();

int programingLanguage=0;
int maxFilesAmount=0;

unordered_map<int, string> singleLineComment;
unordered_map<int, string> multLineCommentStart;
unordered_map<int, string> multLineCommentEnd;
unordered_map<int, string> studentsOutputFile;

int main(){
    bool goAhead=true;
    ifstream primaryFile;
    ifstream secondaryFile;
    ofstream primaryOutputFile;
    ofstream secondaryOutputFile;
    initilizeHashMaps();

    cout<<"Welcome to Plagarism Checker!"<<endl;
    cout<<"Please Make sure all files are named between the numbers 1 and X; X is the max amount of files you are comparing"<<endl;
    cout<<"Now, please enter the max number of files we will compare: ";
    cin>>::maxFilesAmount;
    cout<<endl;

    //Do while loop to make sure the person is selecting a valid progrmaming language
    //switch statement can be made into a function as we expand languages.
    do{
        cout<<"Please be sure to select the programing language I will run my checking on: "<<endl;
        cout<<"1) C/C++"<<endl;
        cout<<"2) Java"<<endl;
        cout<<"3) x86_64"<<endl;
        cout<<"4) MIPS"<<endl<<endl;

        cout<<"Enter Selection: ";
        cin>>::programingLanguage;

        switch (::programingLanguage)
        {
        case 1:
            goAhead=false;
            ::programingLanguage=1;
            break;
        case 2:
            goAhead=false;
            ::programingLanguage=2;
            break;
        case 3:
            goAhead=false;
            ::programingLanguage=3;
            break;
        case 4:
            goAhead=false;
            ::programingLanguage=4;
            break;
        default:
            break;
        }
    }while(goAhead);

    cout<<"Removing Comments of all available files"<<endl;
    removeComments(primaryFile, primaryOutputFile);
    cout<<"All Files have been re-created without comments"<<endl;

}

void removeComments(ifstream& primaryInputFile, ofstream& primaryOFile){
    string lineRead;
    string noCommentLine;
    string number;
    char tab=9;
    
    // For loop will be used to go through every single file on the folder
    // Be sure to have them all named 1->X otherwise program will break.
    for(int i=1; i<=maxFilesAmount; i++){
        number=to_string(i);
        primaryInputFile.open(number+".txt");
        primaryOFile.open(number+"_noComments.txt");

        while(!primaryInputFile.eof()){
            int commentFoundLocation=0;
            
            getline(primaryInputFile, lineRead);

            //Make sure line is not empty, if it is get a new one
            while(lineRead.length()==0){
                getline(primaryInputFile, lineRead);
            }

            //Remove any tabs the line might have and then make sure the line still has chars on it
            // if it doesn't have a char, or starts with a tab, get a new line
            lineRead.erase(remove(lineRead.begin(), lineRead.end(), tab), lineRead.end());
            while(lineRead.length()==0 || lineRead[0]==10){
                getline(primaryInputFile, lineRead);
            }
            
            // Add new line to the read line in order to have it be in order
            // Then get location in string of the character that is used for comments
            lineRead+='\n';
            commentFoundLocation=lineRead.find(singleLineComment[programingLanguage]);

            //If there is not a single line comment search for a multi-line comment
            //npos means no position found
            if(commentFoundLocation==-1){
                    // Call various functions to check for multiline comments depending on the language

                    //If no multipline comments found/not possible on the language, then we remove any remaining tabs
                    //Then we save in the output
                    replace(lineRead.begin(),lineRead.end(),tab, '@');
                    lineRead.erase(remove(lineRead.begin(), lineRead.end(), '@'), lineRead.end());
                    if(lineRead[0]!='\n'&&lineRead!="   ")
                    primaryOFile<<lineRead;        
            }else{
                noCommentLine=lineRead.substr(0, commentFoundLocation);
                noCommentLine+='\n';

                if(noCommentLine[0]!='\n'&&noCommentLine!="  "){
                        replace(lineRead.begin(),lineRead.end(),tab, '@');
                        lineRead.erase(remove(lineRead.begin(), lineRead.end(), '@'), lineRead.end());
                        primaryOFile<<noCommentLine;
                }
            }
        }
        primaryInputFile.close();
        primaryOFile.close();
    }
}

void initilizeHashMaps(){
    singleLineComment[1]="//";
    singleLineComment[2]="//";
    singleLineComment[3]=";";
    singleLineComment[4]="#";

    multLineCommentStart[1]="/*";
    multLineCommentStart[2]="/*";

    multLineCommentEnd[1]="*/";
    multLineCommentEnd[2]="*/";
}