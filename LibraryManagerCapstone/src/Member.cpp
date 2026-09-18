#include "Member.h"

Member::Member(std::string id, std::string name)
    : id_(std::move(id)), name_(std::move(name)) {}

const std::string& Member::getId() const { return id_; }
const std::string& Member::getName() const { return name_; }
