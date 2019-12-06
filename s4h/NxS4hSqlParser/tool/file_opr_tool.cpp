//
// Created by jeff on 2019/12/6.
//

#include "file_opr_tool.h"
#include <fstream>
#include <iostream>
#include <dirent.h>

std::string read_from_file(const std::string& file_path)
{
    std::ifstream t(file_path);
    std::string text((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    return text;
}


void get_file_paths(std::set<std::string> & pathset) {
    DIR * dir;
    struct dirent * ptr;
    char file_list[100][40];
    int i=0;
    //
    std::string rootdirPath = "/home/jeff/CLionProjects/NxS4hSqlParser/resourece/log_write/";
    std::string x,dirPath;
    dir = opendir((char *)rootdirPath.c_str()); //
    while((ptr = readdir(dir)) != NULL) //
    {
        //printf("d_name : %s\n", ptr->d_name); //
        x=ptr->d_name;
        if(x.compare(".") == 0 ||
           x.compare("..") == 0) {
            continue;
        }
        dirPath = rootdirPath + x;
        pathset.insert(dirPath);
        printf("d_name : %s\n", dirPath.c_str()); //

        if ( ++i>=100 ) break;
    }
    closedir(dir);//
}

void get_file_paths_v2(std::string & folder, std::map<std::string , std::string> &mapfile) {
    DIR * dir;
    struct dirent * ptr;
    int i=0;

    //std::string rootdirPath = "/home/jeff/tempsource/log/";
    std::string x,dirPath;
    dir = opendir((char *)folder.c_str()); //
    while((ptr = readdir(dir)) != NULL) //
    {
        //printf("d_name : %s\n", ptr->d_name); //
        x=ptr->d_name;
        if( x.compare(".") == 0 ||
            x.compare("..") == 0 ||
            x.compare("select_sql") == 0 ) {
            continue;
        }
        dirPath = folder + x;
        mapfile[x] = dirPath;
        //printf("d_name : %s\n", dirPath.c_str()); //
        if ( ++i>=100 ) break;
    }
    closedir(dir);//
}



void output_file(std::string & ss, std::string & file) {
    std::ofstream in;
    in.open(file,std::ios::trunc);
    in << ss;
    in.close();
}

void output_file(std::set<std::string>& vecss, std::string & file) {
    std::ofstream in;
    in.open(file,std::ios::trunc);
    for (auto ss:vecss) {
        in << ss + '\n';
    }
    in.close();
}


void output_tb2file(std::set<std::string>& vecss, const std::string & file) {
    std::ofstream in;
    in.open(file,std::ios::trunc);
    for (auto ss:vecss) {
        in << ss + ",\n";
    }
    in.close();
}



