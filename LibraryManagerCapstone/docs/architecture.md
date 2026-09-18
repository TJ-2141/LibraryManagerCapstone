# Architecture

The capstone is intentionally split into four layers:

```text
CLI
 |
 v
Library service/domain logic
 |           \
 v            v
Algorithms   Storage
 |
v
Book / Member / Loan models
```

`main.cpp` handles interaction only. `Library` owns application rules such as issuing and returning. The model classes encapsulate their state. `Algorithms` contains reusable search/sort strategies. `Storage` contains CSV persistence and file-safety logic.

This separation makes the project easier to test and extend.
