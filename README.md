# LIRS Caching algorithm
----
## Installation process

- **Clone the repository**
```bash
git clone git@github.com:ELBEBACK/LIRS-Cache.git
```
- **Navigate to the repository directory** 
- **Build the project using the following sequence of commands:**
```cpp
cmake -B build -S lirs   // or cmake -B build -S oracle, depends on what you want to test
cmake --build build
cd build
```
----
## How to use 
### LIRS or IDEAL(Oracle)

- **To run the program**
```
./lirs
or
./oracle
```
- **The input requires the number of slots in cache M, the number of queries N and the sequence of N queries' keys**

>3 5      
>1 2 3 3 1

- **The output displays the number of hits**

>2

### Testing

- **To run the tests**
```bash
./tests
```
- **The tests are located in `proj/tests/tests.cc`**
- **Everyone can add their testcases simply using included test blocks as templates**
----
