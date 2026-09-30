
15. MERGE K SORTED LISTS USING A HEAP

Merge K sorted lists into a single sorted list using a heap.

Use a min-heap to keep track of the smallest element from each list.

Repeatedly:

1. Extract the smallest element.
2. Insert the next element from the corresponding list into the heap.
3. Continue until all lists are merged.


16. ROBOT MAZE — MINIMUM-COST PATH

Our department owns a robot DotSlash and you arrange a “Robo-show” to showcase its maze-solving capability.

At one instant of the show, the robot is currently at a point as shown in Figure 3.

The robot wants to reach the charging source.

Since the robot has only a few units of charge left in its battery, the goal is to make sure that it consumes the least amount of charge in its journey.

Assumption:
The charge consumed is directly proportional to the distance traversed.

Task:
Help DotSlash find a path to the charging point while minimizing battery power consumed.

