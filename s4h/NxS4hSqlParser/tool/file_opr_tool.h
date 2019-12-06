//
// Created by jeff on 2019/12/6.
//

#ifndef S4H_TEST_FILE_OPR_TOOL_H
#define S4H_TEST_FILE_OPR_TOOL_H

#include <string>
#include <set>
#include <map>

std::string read_from_file(const std::string& file_path);
void get_file_paths(std::set<std::string> & pathset);
void get_file_paths_v2(std::string & folder, std::map<std::string , std::string> &mapfile);

void output_file(std::string & ss, std::string & file);
void output_file(std::set<std::string>& vecss, std::string & file);

void output_tb2file(std::set<std::string>& vecss, const std::string & file);















#endif //S4H_TEST_FILE_OPR_TOOL_H
