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
    def __init__(self,parent, state, successors, cost):
        self.parent = parent
        self.state = state
        self.successors = successors
        self.pathCost = cost

"""
Searches for a value inside a list
"""
def searchInNodeList(key, nodes_list):
    for node in nodes_list:
        print node.state
        if node.state == key:
            return True

    return False

"""
This method receives a node object, and finds the path from current node to the root node.
It returns a list of states
"""
def solution(node, startState):
    current = node
    path = []

    while current != startState and current is not None:
        path.insert(0, current.state)

        current = current.parent

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
    print "Start:", problem.getStartState()
    startState = problem.getStartState()

    root = Node(None, startState, problem.getSuccessors(startState), 0)

    frontier = util.Stack()
    frontier.push(root)
    generalSearch(problem, frontier)

    # util.raiseNotDefined()

def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    "*** YOUR CODE HERE ***"

    startState = problem.getStartState()

    root = Node(None, startState, problem.getSuccessors(startState), 0)

    frontier = util.Queue()
    frontier.push(root)
    generalSearch(problem, frontier)


def generalSearch(problem, frontier):
    startState = problem.getStartState()
    explored = set()

    if frontier.isEmpty():
        return -1

    while not frontier.isEmpty():
        node = frontier.pop()
        explored.add(node.state)

        if problem.isGoalState(node.state):
            print "found goal state at a cost of:  ", node.pathCost
            return solution(node, startState)

        for item in node.successors:
            child_state = item[0]

            if child_state not in explored:
                cost = item[2] + node.pathCost
                successors = problem.getSuccessors(child_state)
                child = Node(node, child_state, successors, cost)
                frontier.push(child)

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    util.raiseNotDefined()





# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
