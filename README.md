# LIRS and Belady's caching algorithms
----
## Installation process

- **Clone the repository**
```bash
git clone git@github.com:ELBEBACK/LIRS-Cache.git
```
- **Navigate to the repository directory** 
- **Build the project using the following sequence of commands:**
```bash
cmake -B build
cmake --build build
```
----
## How to use 
### LIRS or Belady's Ideal(Oracle)

- **To run the programs navigate to the `build` directory and proceed with either of the following commands**
```bash
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

- **To run the tests navigate to the `build` directory and proceed with either of the following commands**
```bash
./lirsTests
or
./optTests
```
- **Everyone can add their testcases simply using included test blocks as samples**
----
