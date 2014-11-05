## Purpose

Why write another C++ JSON library? 

1. I didn't want to install Boost or any other library 
2. I didn't want to install any programs/scripts
3. I didn't want to have to run 'make'
any project and it would work. 
4. I wanted an interface that was easy to use
5. I wanted it to be reasonably fast

## Description
This json library was created with the intent of providing an easy to use utility for deserializing and serializing Json text.

## Naive Benchmarks
### Parsing
|Library Name   |Time (ms)      |Webpage                                 |
|---------------|---------------|----------------------------------------|
|json           |0.439          |N/A                                     |
|SuperEasyJson  |6.715          |sourceforge.net/projects/supereasyjson/ |
