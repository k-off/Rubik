# Rubik
An Algo Project at Codam (42) - Rubik's cube solver with A*/greedy/cost-uniform algorithms

[SUBJECT](/SUBJECT.en.pdf)

[DESCRIPTION](https://github.com/k-off/Rubik/wiki)

[Evaluation Sheet](https://github.com/k-off/Rubik/wiki/Evaluation-Sheet)

## Usage:
```
make re
./rubik -astar/-greedy/-costuniform [command_list] [-r random_command_list_length]
```
### Types of search:
 - astar - A* algorithm, current cost and metric are taken into consideration
 - greedy - only metric is take into consideration
 - costuniform - only cost is taken into consideration
 
 ### Implemented metric:
 Manhattan distance in three dimensions.
