# CPE400 Final Project
## Author: Grant Davis

# Project Topic (3): Dynamic routing mechanism design with focus on throughput

# Solution
The amount of data that can be sent through a network is the throughput. The amount of data that can be sent is the bandwidth. Bandwidth can be determined from a source router and any destination router, the bandwidth is calculated from each hop in the path from the source to the destination. There is multiple number of paths between two routers. The maximum bandwidth is found after calculating all possible paths' bandwidths.

# Running Program
Keep all files (main.cpp, graph.cpp, graph.hpp, and data.txt) in the same folder and to run use
```
make
./cpe400
```
Choose a source router and a destination router.

Then from the menu choose:

0. to exit program
1. to change routers
2. to calculate max bandwidth
3. to see graph table
