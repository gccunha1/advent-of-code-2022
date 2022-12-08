#include "Solution.hpp"
#include "_common/Debug.hpp"
#include "_common/Utils.h"
#include <algorithm>
#include <memory>

struct File {
public:
    const std::string name_;
    const int size_;
};

class Directory {
protected:
    std::shared_ptr<Directory> parent_;
    const std::string name_;
    int size_;

private:
    std::vector<std::shared_ptr<Directory>> children_;
    std::vector<File> files_;

    void UpdateSize() {
        int size = 0;
        for (auto child : children_) {
            size += child->GetSize();
        }
        for (auto file : files_) {
            size += file.size_;
        }
        size_ = size;
        if (parent_ != nullptr) {
            parent_->UpdateSize();
        }
    }

public:
    Directory(const std::shared_ptr<Directory> parent, const std::string &name)
        : parent_{parent}, name_{name} {}
    ~Directory() {}
    void AddChild(const std::shared_ptr<Directory> &new_child) {
        children_.push_back(new_child);
        UpdateSize();
    }
    void AddFile(const File &file) {
        files_.push_back(file);
        UpdateSize();
    }
    int GetSize() const { return size_; }
    std::string GetName() const { return name_; }

    std::shared_ptr<Directory> GetDirectory(const std::string &directory_id) {
        if (directory_id == "..") {
            return parent_;
        }
        return *(std::find_if(children_.begin(), children_.end(),
                              [directory_id](std::shared_ptr<Directory> dir) {
                                  return dir->GetName() == directory_id;
                              }));
    }

    std::vector<std::shared_ptr<Directory>> GetChildren() const { return children_; }
};

Solution::Solution(/* args */) {}

Solution::~Solution() {}

int Solution::ComputeResult(const std::vector<std::string> &input) {
    const int needed_space = 30000000;
    const int total_space = 70000000;
    std::vector<std::shared_ptr<Directory>> all_dirs;
    std::shared_ptr<Directory> origin_directory =
        std::make_shared<Directory>(nullptr, "origin");
    std::shared_ptr<Directory> current_directory = origin_directory;
    std::shared_ptr<Directory> root_directory =
        std::make_shared<Directory>(origin_directory, "/");
    origin_directory->AddChild(root_directory);

    all_dirs.push_back(origin_directory);
    all_dirs.push_back(root_directory);

    std::string current_cmd;
    for (auto line : input) {
        auto cmd = SplitStringToVector(line, " ");
        if (cmd[0] == "$") {
            current_cmd = cmd[1];
            if (current_cmd == "cd") {
                auto dst = cmd[2];
                current_directory = current_directory->GetDirectory(dst);
            }
            continue;
        }

        if (current_cmd == "ls") {
            if (cmd[0] == "dir") {
                auto new_dir = std::make_shared<Directory>(current_directory, cmd[1]);
                all_dirs.push_back(new_dir);
                current_directory->AddChild(new_dir);
            } else {
                current_directory->AddFile({cmd[1], std::stoi(cmd[0])});
            }
        }
    }
    auto used_space = origin_directory->GetSize();
    auto free_space = total_space - used_space;
    auto min_delete_size = needed_space - free_space;
    std::vector<std::shared_ptr<Directory>>::iterator it = all_dirs.begin();
    int min_size_folder = total_space;
    while (true) {
        it = std::find_if(it + 1, all_dirs.end(),
                          [min_delete_size](std::shared_ptr<Directory> dir) {
                              return dir->GetSize() > min_delete_size;
                          });
        if (it == all_dirs.end()) {
            break;
        }
        if ((*it)->GetSize() < min_size_folder) {
            min_size_folder = (*it)->GetSize();
        }
    }

    return min_size_folder;
}