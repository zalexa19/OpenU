# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util


class Node:
    def __init__(self, state, goalDistance, parent=None, cost=0, action=None):
        self.parent = parent
        self.state = state
        self.pathCost = cost
        self.action = action
        self.goalDistance = goalDistance
        if parent:
            self.pathCost = parent.pathCost+cost

    def getSuccessors(self, problem):
        successors = []
        for item in problem.getSuccessors(self.state):
            successors.append(Node(item[0], self, item[2], item[1]))
        return successors


    """
    page 79 in the book
    """
    def childNode(self, action, goalState):
        state = action[0]
        distanceFromGoal = util.manhattanDistance(state, goalState)
        return Node(state, distanceFromGoal, self, action[2], action[1])
    """
    This method finds the path from current node to the root node.
    It returns a list of states
    """

    def solution(self):

        actions = []
        for node in self.pathBack():
            actions.append(node.action)
        return actions[1:]

    def pathBack(self):
        node=self
        path=[]

        while node:
            path.insert(0,node)
            node = node.parent

        return path

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    """
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print "Start:", problem.getStartState()
    print "Is the start a goal?", problem.isGoalState(problem.getStartState())
    print "Start's successors:", problem.getSuccessors(problem.getStartState())
    """
    "*** YOUR CODE HERE ***"
    frontier = util.Stack()
    return generalSearch(problem, frontier)


def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"
    frontier = util.Queue()
    return generalSearch(problem, frontier)

"""
This function recieves the problem and the frontier.
It pop a node, checks if it's the goal state. If this node is not the goal state, this node
is added to the explored set, and all the children of this node (which were not explored yet)  are pushed to the frontier
"""


def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"

    frontier = util.PriorityQueueWithFunction(lowestCost)

    return generalSearch(problem, frontier)


#def newGeneralSearch(problem, frontier)

def generalSearch(problem, frontier):

    goal = problem.goal
    goalDistance = util.manhattanDistance(problem.getStartState(), goal)
    node = Node(problem.getStartState(), goalDistance)
    if problem.isGoalState(node): return node.solution()

    frontier.push(node)
    explored = set()
    while not frontier.isEmpty():
        node = frontier.pop()
        if problem.isGoalState(node.state): return node.solution()
        explored.add(node.state)

        actions = problem.getSuccessors(node.state)
        for action in actions:
            child = node.childNode(action, goal)
            if child.state not in explored:
                #frontier.push(child, child.pathCost)
                frontier.push(child)
    return []

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    frontier = util.PriorityQueueWithFunction(lowestCombinedCost)

    return generalSearch(problem, frontier)


def lowestCost(item):
    return item.pathCost

def lowestCombinedCost(item):
    return item.pathCost + item.goalDistance



# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
