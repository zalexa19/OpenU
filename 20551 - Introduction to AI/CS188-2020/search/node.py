class Node:

    def __init__(self, state, action, cost, parent):
        self.__state = state
        self.__cost = cost
        self.__action = action
        self.__parent = parent

    def getState(self):
        return self.__state    

    def getCost(self):
        return self.__cost         

    def getAction(self):
        return self.__action    

    def getParent(self):
        return self.__parent            

    def getActions(self):
        actions = []
        node = self
        while node.getParent() is not None:
            actions.append(node.getAction())
            node = node.getParent()
            
        actions.reverse()
        return actions
