#include "Loan.h"

Loan::Loan(std::string isbn, std::string memberId)
    : isbn_(std::move(isbn)), memberId_(std::move(memberId)) {}

const std::string& Loan::getIsbn() const { return isbn_; }
const std::string& Loan::getMemberId() const { return memberId_; }
bool Loan::isActive() const { return active_; }
void Loan::close() { active_ = false; }
