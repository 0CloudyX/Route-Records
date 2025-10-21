# ✈️ Route Records Project (C)

A data-processing program written in C that reads and manages airline route data from a CSV file.  
The program allows users to search, summarize, and analyze passenger traffic between airports and airlines.

---

## 🧠 Overview

The Route Records project processes a dataset of flight routes and passenger counts over several months.  
It supports menu-based searches by:
- Route (origin → destination)
- Origin airport
- Destination airport
- Airline code  

The program aggregates passenger data, calculates totals, and outputs statistics for matched routes.

---

## ⚙️ How It Works

- **File Input (`data.csv`):**  
  Reads monthly route data (month, origin, destination, airline, passengers).  

- **Dynamic Allocation:**  
  Uses `malloc()` to create a dynamic array of `RouteRecord` structures.  

- **Struct-Based Design:**  
  Each record stores:
  ```c
  typedef struct {
      char originAirportCode[4];
      char destinationAirportcode[4];
      char airlineCode[3];
      int passengerCount[6];
  } RouteRecord;

---

## 🧾 Example Usage

Opening data.csv
Unique routes operated by airlines: 15

**Input:**
######### Airline Route Records Database MENU #########
1. Search by Route
2. Search by Origin Airport
3. Search by Destination Airport
4. Search by Airline
5. Quit
Enter your selection: 1
Enter origin: SAT
Enter destination: DFW

**Output:**
Searching by route...
AA (SAT-DFW)
DL (SAT-DFW)
WN (SAT-DFW)
3 matches were found.

Statistics:
Total Passengers: 10234
Average Passengers per Month: 1705

