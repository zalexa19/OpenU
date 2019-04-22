Name: Alex Z
Course

Question1:
My new evaluation function checks the Manhattan distance to find the closest food.
This function also takes into account the state of the ghosts:
    * if the next pacman position has a non scared ghost, I return minus infinity to avoid the ghost
    * if the next pacman position has a scared ghost, we eat it.
