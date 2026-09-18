#pragma once
#include <string>

class Member {
public:
    Member() = default;
    Member(std::string id, std::string name);

    const std::string& getId() const;
    const std::string& getName() const;

private:
    std::string id_;
    std::string name_;
};
