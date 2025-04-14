# DateBase

A C++ program for managing events by date. Supports commands to add, delete, find, and print events, with date normalization (e.g., `1-01-01` becomes `0001-01-01`).

## Features
- Add events to specific dates (`Add date event`).
- Delete a single event or all events for a date (`Del date [event]`).
- Find all events for a date, sorted lexicographically (`Find date`).
- Print all events, sorted by date and event name (`Print`).
- Normalizes dates to `YYYY-MM-DD` format.
- Handles large inputs efficiently (tested with 1000 events).

## Prerequisites
- C++17 compatible compiler (e.g., `g++` 9.0 or later).
- GNU Make.
- (Optional) Python 3 for generating stress tests.

## Installation
Clone the repository and build the program:

```bash
git clone https://github.com/Co6a4/DateBase.git
cd DateBase
make
```

## Usage
Run the program:
```bash
./DateBase
```
### Example
input:
````
Add 2023-01-01 Meeting
Add 2023-01-01 Lunch
Add 1-01-01 Event1
Find 2023-01-01
Print
````
Output:
```
Lunch
Meeting
0001-01-01 Event1
2023-01-01 Lunch
2023-01-01 Meeting
```

#### Commands
- `Add date event`: Adds `event` to `date`.
- `Del date`: Deletes all events for `date`, prints `Deleted X events`.
- `Del date event`: Deletes `event` from `date`, prints `Deleted successfully` or `Event not found`.
- `Find date`: Prints all events for `date`, sorted.
- `Print`: Prints all events, sorted by date and event.

## Stress Test
Test the program with 1000 events (10 dates, 100 events each):

```bash
python3 generate_stress_test.py
./DateBase < stress_test.txt > output.txt
cat output.txt
```

## Clean
Remove compiled files:

```bash
make clean
```

## Files
- `DateBase.cpp`: Main program source code.
- `Makefile`: Build script for compiling the program.
- `generate_stress_test.py`: Python script to generate stress test input (optional).
- `stress_test.txt`: Sample stress test input (optional).
- `.gitignore`: Ignores compiled files and temporary outputs.


