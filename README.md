# LIRS Caching algorithm
----
## Installation process

- **Clone the repository**
```bash
git clone git@github.com:ELBEBACK/LIRS-Cache.git
```
- **Navigate to the repository directory** 
- **Build the project using the following sequence of commands:**
```bash
mkdir build
cd build/

cmake ../lirs
make
```
----
## How to use 
### LIRS

- **To run the program**
```bash
./lirs
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
- **The tests located in `proj/tests/tests.cc` are E2E tests**
- **Everyone can add their testcases simply using included test blocks as templates**
----
