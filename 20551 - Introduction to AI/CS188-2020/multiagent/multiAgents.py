# multiAgents.py
# --------------
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


from util import manhattanDistance
from game import Directions
import random, util

from game import Agent

class ReflexAgent(Agent):
    """
    A reflex agent chooses an action at each choice point by examining
    its alternatives via a state evaluation function.

    The code below is provided as a guide.  You are welcome to change
    it in any way you see fit, so long as you don't touch our method
    headers.
    """


    def getAction(self, gameState):
        """
        You do not need to change this method, but you're welcome to.

        getAction chooses among the best options according to the evaluation function.

        Just like in the previous project, getAction takes a GameState and returns
        some Directions.X for some X in the set {NORTH, SOUTH, WEST, EAST, STOP}
        """
        # Collect legal moves and successor states
        legalMoves = gameState.getLegalActions()

        # Choose one of the best actions
        scores = [self.evaluationFunction(gameState, action) for action in legalMoves]
        bestScore = max(scores)
        bestIndices = [index for index in range(len(scores)) if scores[index] == bestScore]
        chosenIndex = random.choice(bestIndices) # Pick randomly among the best

        "Add more of your code here if you want to"

        return legalMoves[chosenIndex]

    def evaluationFunction(self, currentGameState, action):
        """
        Design a better evaluation function here.

        The evaluation function takes in the current and proposed successor
        GameStates (pacman.py) and returns a number, where higher numbers are better.

        The code below extracts some useful information from the state, like the
        remaining food (newFood) and Pacman position after moving (newPos).
        newScaredTimes holds the number of moves that each ghost will remain
        scared because of Pacman having eaten a power pellet.

        Print out these variables to see what you're getting, then combine them
        to create a masterful evaluation function.
        """
        # Useful information you can extract from a GameState (pacman.py)
        successorGameState = currentGameState.generatePacmanSuccessor(action)
        newPos = successorGameState.getPacmanPosition()
        currentFood = currentGameState.getFood().asList()
        newGhostStates = successorGameState.getGhostStates()
        newScaredTimes = [ghostState.scaredTimer for ghostState in newGhostStates]
        capsules = currentGameState.getCapsules()
        walls = currentGameState.getWalls()
        gridSize = walls.height * walls.width

        "*** YOUR CODE HERE ***"
        # starting with max score.
        score = successorGameState.getScore()

        # find the closest ghost
        ghostDistances = list()
        for ghostState in newGhostStates:
            gPos = ghostState.getPosition()
            ghostDistances.append(util.manhattanDistance(newPos, gPos))
        closestGhost = min(ghostDistances)

        if closestGhost < 2:
            if min(newScaredTimes) < 2:
                score -= float("inf")
            else:
                score += gridSize - closestGhost

        # Check capsules
        capsuleDistances = list()
        for capsule in capsules:
            capsuleDistances.append(util.manhattanDistance(newPos, capsule))

        if len(capsuleDistances) > 0:
            if min(capsuleDistances) < 2:
                score += float("inf")
            # prefer the closer capsule
            score += gridSize - min(capsuleDistances)

        # find the closes food and subtract it from the score
        foodDistances = list()
        for food in currentFood:
            foodDistances.append(util.manhattanDistance(newPos, food))
        if len(foodDistances) > 0:
            score -= min(foodDistances)
        return score

def scoreEvaluationFunction(currentGameState):
    """
    This default evaluation function just returns the score of the state.
    The score is the same one displayed in the Pacman GUI.

    This evaluation function is meant for use with adversarial search agents
    (not reflex agents).
    """
    return currentGameState.getScore()

class MultiAgentSearchAgent(Agent):
    """
    This class provides some common elements to all of your
    multi-agent searchers.  Any methods defined here will be available
    to the MinimaxPacmanAgent, AlphaBetaPacmanAgent & ExpectimaxPacmanAgent.

    You *do not* need to make any changes here, but you can if you want to
    add functionality to all your adversarial search agents.  Please do not
    remove anything, however.

    Note: this is an abstract class: one that should not be instantiated.  It's
    only partially specified, and designed to be extended.  Agent (game.py)
    is another abstract class.
    """

    def __init__(self, evalFn = 'scoreEvaluationFunction', depth = '2'):
        self.index = 0 # Pacman is always agent index 0
        self.evaluationFunction = util.lookup(evalFn, globals())
        self.depth = int(depth)

class MinimaxAgent(MultiAgentSearchAgent):
    """
    Your minimax agent (question 2)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action from the current gameState using self.depth
        and self.evaluationFunction.

        Here are some method calls that might be useful when implementing minimax.

        gameState.getLegalActions(agentIndex):
        Returns a list of legal actions for an agent
        agentIndex=0 means Pacman, ghosts are >= 1

        gameState.generateSuccessor(agentIndex, action):
        Returns the successor game state after an agent takes an action

        gameState.getNumAgents():
        Returns the total number of agents in the game

        gameState.isWin():
        Returns whether or not the game state is a winning state

        gameState.isLose():
        Returns whether or not the game state is a losing state
        """
        "*** YOUR CODE HERE ***"
        options = {}
        pacmanActions = gameState.getLegalActions(0)

        for action in pacmanActions:
            nextState = gameState.generateSuccessor(0, action)
            options[action] = self.minValue(nextState, self.depth, 1)
        chosenAction = max(options, key=options.get)
        return chosenAction

    def maxValue(self, gameState, depth):
        if depth == 0 or gameState.isWin() or gameState.isLose():
            return  self.evaluationFunction(gameState)

        actions = gameState.getLegalActions(0)
        options = list()
        for action in actions:
            nextState = gameState.generateSuccessor(0, action)
            options.append(self.minValue(nextState, depth, 1))
        return max(options)


    def minValue(self, gameState, depth, ghost):
        if depth == 0 or gameState.isWin() or gameState.isLose():
            return  self.evaluationFunction(gameState)

        actions = gameState.getLegalActions(ghost)
        options = list()

        if ghost == gameState.getNumAgents() - 1:
            for action in actions:
                nextState = gameState.generateSuccessor(ghost, action)
                options.append(self.maxValue(nextState, depth - 1))
        else:
            for action in actions:
                nextState = gameState.generateSuccessor(ghost, action)
                options.append(self.minValue(nextState, depth, ghost + 1))
        return min(options)




class AlphaBetaAgent(MultiAgentSearchAgent):
    """
    Your minimax agent with alpha-beta pruning (question 3)
    """

    def getAction(self, gameState):
        """
        Returns the minimax action using self.depth and self.evaluationFunction
        """
        "*** YOUR CODE HERE ***"
        actions = gameState.getLegalActions(0)
        options = {}

        for action in actions:
            alpha = -float("inf")
            beta = float("inf")

            nextState = gameState.generateSuccessor(0, action)
            stateScore = self.minValue(nextState, self.depth, 1, alpha, beta)
            options[action] = stateScore

        chosenAction = max(options, key=options.get)
        return chosenAction


    def maxValue(self, gameState, depth, alpha, beta):
        if depth == 0 or gameState.isWin() or gameState.isLose():
            return self.evaluationFunction(gameState)

        value = -float("inf")
        actions = gameState.getLegalActions(0)
        options = list()

        for action in actions:
            nextState = gameState.generateSuccessor(0, action)
            value = max(value, self.minValue(nextState, depth, 1,  alpha, beta))
            options.append(value)
            if value > beta:
                return beta
            alpha = max(value, alpha)
        return max(options)


    def minValue(self, gameState, depth, ghost, alpha, beta):
        if depth == 0 or gameState.isWin() or gameState.isLose():
            return self.evaluationFunction(gameState)

        value = float("inf")
        actions = gameState.getLegalActions(ghost)
        options = list()

        for action in actions:
            nextState = gameState.generateSuccessor(ghost, action)
            if ghost == gameState.getNumAgents() - 1:
                value = min(value, self.maxValue(nextState, depth - 1, alpha, beta))
            else:
                value = min(value, self.minValue(nextState, depth, ghost + 1, alpha, beta))
            options.append(value)
            if value < alpha:
                return value
            beta = min(value, beta)
        return min(options)

class ExpectimaxAgent(MultiAgentSearchAgent):
    """
      Your expectimax agent (question 4)
    """

    def getAction(self, gameState):
        """
        Returns the expectimax action using self.depth and self.evaluationFunction

        All ghosts should be modeled as choosing uniformly at random from their
        legal moves.
        """
        "*** YOUR CODE HERE ***"
        options = {}
        pacmanActions = gameState.getLegalActions(0)

        maxSCore = -float("inf")
        maxAction = "Stop" # as default

        for action in pacmanActions:
            nextState = gameState.generateSuccessor(0, action)
            score = self.expectimax(nextState, self.depth, 0)
            if maxSCore < score:
                maxSCore = score
                maxAction = action
        return maxAction


    def expectimax(self, gameState, depth, agent):
        if depth == 0 or gameState.isWin() or gameState.isLose():
            return self.evaluationFunction(gameState)

        actions = gameState.getLegalActions(agent)
        options = list()
        for action in actions:
            nextGameState = gameState.generateSuccessor(agent, action)
            if agent == 0:
                options.append(self.expectimax(nextGameState, depth, 1))
            if agent == gameState.getNumAgents() - 1:
                options.append(self.expectimax(nextGameState, depth - 1, 0))
            else:
                options.append(self.expectimax(nextGameState, depth, agent + 1))
        # if it's pacman, return the max move, otherwise a random value
        if agent == 0:
            return max(options) # best option for pacman
        return random.choice(options)







def betterEvaluationFunction(currentGameState):
    """
    Your extreme ghost-hunting, pellet-nabbing, food-gobbling, unstoppable
    evaluation function (question 5).

    DESCRIPTION: <write something here so we know what you did>
    """
    "*** YOUR CODE HERE ***"
    inf = float('inf')
    score = currentGameState.getScore()

    position = currentGameState.getPacmanPosition()
    capsules = currentGameState.getCapsules()
    food = currentGameState.getFood().asList()
    ghostState = currentGameState.getGhostStates()
    scaredTimes = [ghostState.scaredTimer for ghostState in ghostState]
    closestFoodDistance = 0
    closestGhostDistance = 0
    edibleGhostDistance = 0
    closestCapsuleDistance = 0

    if currentGameState.isWin() or currentGameState.isLose():
        score += score
    if currentGameState.isLose():
        score += score / 2

    # find closest food:
    foodDistances = list()

    if len(food) > 0:
        for foodDistance in food:
            foodDistances.append(util.manhattanDistance(position, foodDistance))

        if len(foodDistances) > 0:
            closestFoodDistance = min(foodDistances)

    # find the closest ghost:
    if currentGameState.getNumAgents() > 0:
        ghostDistances = list()
        for ghostState in ghostState:
            gPosition = ghostState.getPosition()
            ghostDistances.append(util.manhattanDistance(position, gPosition))

        if len(ghostDistances) > 0:
            closestGhostDistance = min(ghostDistances)

    if closestGhostDistance < 2:
        if min(scaredTimes) > 2:
            # eat the ghost!
            edibleGhostDistance = closestGhostDistance
        else:
            return -inf # get away from the ghost

    # check capsules
    if len(capsules) > 0:
        capsuleDistances = list()
        for capsule in capsules:
            capsuleDistances.append(util.manhattanDistance(position, capsule))
        # score += min(capsuleDistances) * 2
        if len(capsuleDistances) > 0:
            closestCapsuleDistance = min(capsuleDistances)

        score -= closestFoodDistance / 2 + closestCapsuleDistance / 3 + edibleGhostDistance

    return score

# Abbreviation
better = betterEvaluationFunction
