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
from node import Node

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
    """
    """
    "*** YOUR CODE HERE ***"
    """
    stack = util.Stack()
    return generalGraphSearch(problem, stack)
    

def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""
    return graphSearch(problem, util.Queue())

def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    return priorityGraphSearch(problem, util.PriorityQueue())

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


def graphSearch(problem, frontier):
    
    explored = set()
    # check the starting state
    node = { 'state': problem.getStartState(), 'action': 'start', 'cost': 0}
    # if the starting state is the goal state, return no actions
    if problem.isGoalState(node['state']): return []

    frontier.push(node)

    while not frontier.isEmpty():

        node = frontier.pop()
        explored.add(node['state']) 
        succesors = problem.getSuccessors(node['state'])

        for successor in succesors:
            if successor[0] not in explored: 
                # create a new child with a reference to the parent
                childNode = {'state': successor[0], 'action': successor[1], 'cost': successor[2], 'parent': node}                
                if(problem.isGoalState(childNode['state'])):
                    actions = []
                    currentNode = childNode
                    while 'parent' in currentNode:
                        actions.append(currentNode['action'])
                        currentNode = currentNode['parent']

                    actions.reverse()
                    return actions

                frontier.push(childNode)

    raise Exception('Search failed')

def generalGraphSearch(problem, frontier):
    explored = set()
    node = Node(problem.getStartState(), None, 0, None)

     # if the starting state is the goal state, return no actions
    if problem.isGoalState(node.getState()): return []
    frontier.push(node)

    while not frontier.isEmpty():
        parent = frontier.pop()
        explored.add(parent.getState())
        successors = problem.getSuccessors(parent.getState())

        for successor in successors:
            if successor[0] not in explored:
                child = Node(successor[0], successor[1], successor[2] , parent)
                if problem.isGoalState(child.getState()):
                    return child.getActions()
                frontier.push(child)

    raise Exception('End of frontier is reached')

def priorityGraphSearch(problem, frontier):
    explored = set()
    node = Node(problem.getStartState(), None, 0, None)

     # if the starting state is the goal state, return no actions
    if problem.isGoalState(node.getState()): return []
    frontier.push(node, node.getCost())

    while not frontier.isEmpty():
        parent = frontier.pop()
        explored.add(parent.getState())
        successors = problem.getSuccessors(parent.getState())

        for successor in successors:
            if successor[0] not in explored:
                child = Node(successor[0], successor[1], successor[2] , parent)
                if problem.isGoalState(child.getState()):
                    return child.getActions()
                frontier.push(child, child.getCost())

    raise Exception('End of frontier is reached')