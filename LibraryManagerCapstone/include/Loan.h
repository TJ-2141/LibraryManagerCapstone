#pragma once
#include <string>

class Loan {
public:
    Loan() = default;
    Loan(std::string isbn, std::string memberId);

    const std::string& getIsbn() const;
    const std::string& getMemberId() const;
    bool isActive() const;
    void close();

private:
    std::string isbn_;
    std::string memberId_;
    bool active_ = true;
};
