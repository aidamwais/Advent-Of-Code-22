//
// Created by Aida on 10/15/2023.
//

#ifndef ADVENT_OF_CODE_22_DAY_7_HPP
#define ADVENT_OF_CODE_22_DAY_7_HPP
#include <string.h>
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>

#define HUNDRED_K 100000
#define DISK_CAPACITY 70000000
#define SPACE_FOR_UPDATE 30000000

class TreeNode{
    std::string node_name;
    TreeNode* parent;
    int accumulated_size;
    std::list<TreeNode*> sons;
    bool is_dir;
public:
    TreeNode(std::string node_name,TreeNode* parent, bool is_dir, int accumulated_size=0):node_name(node_name),
                                            parent(parent),is_dir(is_dir),accumulated_size(accumulated_size){};
    ~TreeNode(){
        std::list<TreeNode*>::iterator it;
        for (it = sons.begin(); it != sons.end(); it++){
            if((*it) -> is_dir){
                delete (*it);
            }
        }
    }
    void AddSon(std::string son_name,bool is_dir, int size=0){
        TreeNode* new_son = new TreeNode(son_name,this,is_dir,size);
        if(!GetTargetNode(son_name))
            sons.push_back(new_son);
    }
    TreeNode* GetParent(){
        return parent;
    }
    std::string GetNodeName(){
        return node_name;
    }
    int GetAccumulatedSize(){
        return accumulated_size;
    }
    TreeNode* GetTargetNode(std::string target_node){
        std::list<TreeNode*>::iterator it;
        for (it = sons.begin(); it != sons.end(); it++){
            if((*it) ->GetNodeName() == target_node){
                return *it;
            }
        }
        return nullptr;
    }
    bool operator==(const TreeNode& tree){
        return accumulated_size == tree.accumulated_size;
    }
    int CalculateAccumulatedSizes(){
        std::list<TreeNode*>::iterator it;
        for (it = sons.begin(); it != sons.end(); it++){
            if((*it)->is_dir) {
                accumulated_size += (*it)->CalculateAccumulatedSizes();
            }else {
                accumulated_size += (*it)->accumulated_size;
            }
        }
        return accumulated_size;
    }
    int SumMax100k(){
        std::list<TreeNode*>::iterator it;
        int count = 0;
        for (it = sons.begin(); it != sons.end(); it++){
            if((*it)->is_dir) {
                if(((*it)->accumulated_size <= HUNDRED_K)) {
                    count+=(*it)->accumulated_size;
                }
                count += (*it)->SumMax100k();
            }
        }
        return count;
    }
    int Min(int x, int y){
        if(x>=y)
            return y;
        return x;
    }
    int FindSmallestNeededDir(int space_needed){
        std::list<TreeNode*>::iterator it;
        int current_smallest = accumulated_size;
        for (it = sons.begin(); it != sons.end(); it++){
            if(( (*it)->is_dir) && ((*it)->GetAccumulatedSize() >= space_needed) ){
                current_smallest =  Min( (*it)->FindSmallestNeededDir(space_needed),current_smallest);
            }
        }
        return current_smallest;
    }
};

class Tree{
    TreeNode* root;
    TreeNode* current_dir;

public:

    explicit Tree():root(nullptr),current_dir(nullptr){}
    ~Tree(){
        delete root;
    }
    void AddNode(std::string signal){
        std::string dir_name_or_file_size = signal.substr(0, signal.find_first_of(' '));
        if(dir_name_or_file_size == "dir"){
            current_dir->AddSon(signal.substr(signal.find(' ')+1),true);
        }else {
            current_dir->AddSon(signal.substr(signal.find(' ')+1),false,stoi(dir_name_or_file_size));
        }
    }
    void ChangeDir(std::string dir_name){
        if ( (root == nullptr) && (dir_name == "/") ){
            root = new TreeNode(dir_name, nullptr, true);
            current_dir = root;
        }else if ( (root != nullptr) && (dir_name == "..") ){
            current_dir = current_dir->GetParent();
        }
        else if( (root != nullptr)&&(current_dir != nullptr) ){
            TreeNode* target_node = current_dir->GetTargetNode(dir_name);
            if(target_node == nullptr){
                return;
            }else{
                current_dir = target_node;
            }
        }else{
            exit(1);
        }
    }
    void sumSizes(){
        root->CalculateAccumulatedSizes();
    }
    int NumMax100k(){
        if(root->GetAccumulatedSize() <= HUNDRED_K){
            return root->SumMax100k() + root->GetAccumulatedSize();
        }
        return root->SumMax100k();
    }
    void FillTreeFromFile(){
        std::ifstream signal;
        //file.txt is in cmake-debug dir
        signal.open("System Commands Day 7.txt");
        if(!signal.is_open())
            std::cout << "File did not open" << std::endl;

        std::string signal_line;
        std::getline(signal,signal_line);
        bool adding_dirs = false;

        while(signal){
            if(signal_line.substr(0,4) == "$ cd"){
                std::string dir_name = signal_line.substr(5);
                this->ChangeDir(dir_name);
                adding_dirs = false;
            }
            else if(signal_line == "$ ls"){
                adding_dirs = true;
            }
            else if(adding_dirs == true){
                this->AddNode(signal_line);
            }
            std::getline(signal,signal_line);
        }
        this->sumSizes();
        signal.close();

    }
    int SmallestDir(){
        int unused_space = DISK_CAPACITY - root->GetAccumulatedSize();
        if(unused_space >= SPACE_FOR_UPDATE){
            return 0;
        }
        int space_needed = SPACE_FOR_UPDATE - unused_space;
        return root->FindSmallestNeededDir(space_needed);
    }

};

class SpaceOnDevice{
public:
    //PART 1
    int NumDirMax100K(){
        Tree file_system;
        file_system.FillTreeFromFile();
        return file_system.NumMax100k();
    }
    //PART 2
    int SmallestDirForDeletion(){
        Tree file_system;
        file_system.FillTreeFromFile();
        return file_system.SmallestDir();
    }

};
#endif //ADVENT_OF_CODE_22_DAY_7_HPP
