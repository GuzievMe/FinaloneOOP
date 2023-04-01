
#include <fstream>
#include <sstream>
#include <iostream>
#include<iostream>
#include<vector>
#include<cassert>
#include<list>
#include<map>
#include<stdio.h>
#include <string>
#include <filesystem>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include<direct.h>
#include<cstdio>

using namespace std;

class File
{  
public:
    ofstream _Ofile;
    ifstream _Ifile;
    string _filename = "C:/Users/Maham/source/C++/homework/ToDo/";
    string text;
    File() {};
    File(string fileName) : _Ofile(fileName) { _Ofile.close(); _filename = fileName; };

    virtual ~File() = 0 {};

protected:

    void make_file(string filename)
    {
       //_Ofile.close( _Ofile.open(filename, ios :: out));
       _Ofile.open(filename, ios::out);   
        if (!(_Ofile.is_open())) { throw exception("No created Ofile "); }

        _Ofile.close();
        //ofstream ofFile;  ofFile.open("Shir.txt", ios::out);
       // if (ofFile.is_open()) { ofFile << "Shir hemmishe shirdir..."; ofFile.close(); return; }
        //throw exception("No created file ");

    }
    int rename_file()
    {  
        string oldName, newName;
        cout << "Enter new fileName: ";  cin >> oldName;     cout << "Enter new fileName: ";    cin >> newName;
        if (rename(oldName.c_str(), newName.c_str()) != 0)
        {
            throw exception("ERROR:  file is not existed!!");
        }
        return 0;
    }
    int remove_file()
    {
        string fileName;   cout << "Enter name of file which you want delete : ";   cin >> fileName;
        int result = remove(fileName.c_str());
        if (result != 0) {   throw("File deletion failed");    }
        return 0;
    }
    void read_file()
    {
        string fileName;   cout << "Enter file name for read :  ";   cin >> fileName;
        this->_Ifile.open(fileName);
        if (this->_Ifile)
        {
            string data;
            getline(this->_Ifile, data, '\0');
            cout << data;
            _Ifile.close();
            return;
        }
        throw exception("ERROR:  file is not existed!!");
    }
    void write_file(string file, string data)
    {
        this->_Ofile.open(file, ios::app); 
        if (this->_Ofile)
        {
            this->_Ofile << " " << data;
            this->_Ofile.close();
            return;
        }
        throw exception("ERROR:  file is not found!!");
    }
    int move_file()
    {
        //string src_fold = "C:/Users/Maham/Dekstop/Typecasting_C++/MM.txt";
        //string dest_fold = "C: / Users / Maham / Downloads / Typecasting_C++/MM.txt";
        const char* src_fold; const char* dest_fold;   string data;
        cout << "Include folderSrc : ";  cin >> data; src_fold = data.c_str();
        cout << "Enter folderDest : "; cin >> data;  dest_fold = data.c_str();
        int myCheck = rename(src_fold, dest_fold);   return myCheck;
    }

};
class Folder
{
public:
    string _foldername;
    Folder() {};
    Folder(string folderName) {
        create_folder(folderName);
    };
    virtual ~Folder() = 0 {}
    
protected:
    void create_folder(string foldername)
    {
        string a = "mkdir " + foldername;
        _foldername = foldername;
        system(a.c_str());
    }
    void rename_folder(string Name)
    {
        string foldName;
        cout << "Enter new foldName: ";
        cin >> foldName;
        //int check = rename(Name.c_str(), foldName.c_str());
        if ((rename(Name.c_str(), foldName.c_str())) != 0 ) throw exception("ERROR:  Folder is not found!!");
    }
    void copy_folder(std::string src_folder, std::string dest_folder) {
        src_folder.c_str();   dest_folder.c_str();                         
        ifstream src(src_folder, std::ios::binary);
        ofstream destination(dest_folder, std::ios::binary);
        destination << src.rdbuf();
    }
    void remove_folder()
    {
        const char* fold_path; string data;  cout << "Enter the path to the folder you want to delete: ";
        cin >> data;  fold_path = data.c_str();
        // fold_path = "C:/Users/Maham/Downloads/Typecasting_C++";

        int myCheck = remove(fold_path);
        if (myCheck == 0) {
            puts("Folder deleted successfully.");
        }
        else {
            cout << "Error deleting folder. if tou want you can using help from system :  <HELP()>";
        }
    }
    
    void show_allfil(string filename)
    {
        if (filename == "homework")
        { 
            string a1 = "C:\\Users\\Meraj\\source\\repos\\homework\\";
            a1.append("homework");
            cout << a1;
            string aa = "dir / a - d ";
            aa.append(a1);
            system(aa.c_str());
        }
        else
        {
            string a1 = "C:\\Users\\Maham\Dekstop\\C++\\";
            a1.append("homework\\");
            a1.append(filename);
            cout << a1;
            string aa = "dir / a - d ";
            aa.append(a1);
            system(aa.c_str());
        }
    }
    int move_folder()
    {
       // const char* oldpath = "C:/Users/Maham/Downloads/CDDD";
       // const char* newpath = "C:/Users/Maham/Desktop/CDDD";
        string oldpath, newpath; 
        cout << "Enter folder oldPath : "; cin >> oldpath;  cout << "Enter folder newPath : ";   cin >> newpath;
        int isTrue = rename(oldpath.c_str(), newpath.c_str());   return isTrue;
    }
  
};

////char* _searchpath(const char* file)	        Searches for a file.
class Function : public Folder, public File
{
public:
    string cd ()
    {
        string newDirectory;
        cin >> newDirectory;
        int status = _chdir(newDirectory.c_str());

        if (status != 0)   {    throw "Failed to change directory.\n" ;    }

        cout << "Changed directory to " << newDirectory << endl;
        cout << newDirectory << " ";
        return newDirectory;
    }
    void create_folder(string folName)
    {
        Folder :: create_folder(folName);
        cout << "Folder created successfully\n" ;
    }
    void make_file(string filName)
    {
        File::make_file(filName);
        cout << "File created successfully \n" ;
    }

    // <<<<<<<<<<  RENAME methods... >>>>>>>>>>>> //
    void rename_file()
    {
        try {
            File::rename_file();
            cout << "Name changed successfully\n";
        }
        catch (const exception& ex) { cout << ex.what() << endl << "If you want you can use <HELP()> \n"; }
    }
    void rename_folder(string Name)
    {
        Folder::rename_folder(Name);
        cout << "Name has been changed successfully" << endl;
    }
     
    // <<<<<<<<<<  REMOVE methods... >>>>>>>>>>>> //
    void remove_file()
    {
        try {
            if (File::remove_file() == 0)   cout << "File has been removed successfully" << endl;
        }
        catch (const exception& ex) { cout << ex.what() << "\n If you want you can use <HELP()> function...\n"; }
    }

    void read_file()
    {
        File::read_file();
    }
    void write_mode_app(string file)
    {
        string AppendText;
        cout << "Include your append: " << endl;
        cin.ignore(1);
        getline(cin, AppendText, '\0');
        File::write_file(file, AppendText);
    }

    void print_all(string name1)
    {
        Folder::show_allfil(name1);
    }

    void move_file()
    {
        int myCheck = File::move_file();
        if (myCheck != 0) {    cout << "folder moved succesfully...\n"; return;}
        else { cout << "Error !!! Cant moved file ... \n If you want you can using help (call HELP()  function ).\n"; }
    }

    void copy_folder() {
        string src_folder, dest_folder;  
       // src_folder = "C:/Users/Maham/Dekstop/Typecasting_C++";
       // dest_folder = "C:/Users/Maham/Downloads/Typecasting_C++";
        cout << "Enter srcFolder : ";   cin >> src_folder;  cout << "destFolder : ";  cin >> dest_folder;
        Folder::copy_folder(src_folder, dest_folder);
        cout << "Folder copied successfully!\n";
    }

    void remove_Folder()
    {
        Folder::remove_folder();
    }
    void move_folder()
    {
        int isTrue = Folder::move_folder();
        if (isTrue == 0) { puts("Folder moved successfully."); return; }
        perror("Error moving folder.");
    }

    
};

string WorkTime()
{
    // eger daxil edilmish melumat exitdirse, o zaman main icherisindeki while break olunacak
}

int main()
{
    string data;   char command[100];
    std::ofstream outfile;  outfile.open("exampl.txt");  outfile << "Shirrr";  outfile.close();// creates a file named "example.txt"
    //outfile << "Hello, world!"; // writes "Hello, world!" to the file
    //outfile.close(); // closes the file
     

    //string src_folder = "C:/Users/Maham/Dekstop/Typecasting_C++";
    //string dest_folder = "C:/Users/Maham/Downloads/Typecasting_C++";
    Function F1;
    //F1.copy_folder();
    //F1.remove_Folder();
   // F1.move_file();
    //F1.move_folder();
    //F1.make_file("MMWa.txt");
    
    string myCd = "C:\\Users\\Maham>";
    while (true)
    {
        cout << myCd << endl;
        if (_getch() == 99) { cout << 'c'; if (_getch() == 100) { cout << 'd'; if (_getch() == 32)
        {
            cout << ' ';   
            try {
                myCd = F1.cd();
            }
            catch(const exception& ex){  }

        }
        }
        } 
        else { cout << "this operate dont have. We offer HELP() comman to you \n"; }
        if (_getch() == 99)  { cout << 'c';
        if (_getch() == 111) {
            cout << 'o';
            if (_getch() == 112) {
                cout << 'p';
                if (_getch() == 121) {
                    cout << "y";
                    if (_getch() == 32) {
                        cout << " ";
                        {
                            F1.copy_folder(); 
                        }
                    }
                }
            }
        }
        }



      
    }
   


   

    



}




            ///////////////////////////////////////

            

