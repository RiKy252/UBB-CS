class Nod:
    def __init__(self, e):
        self.e = e
        self.urm = None
    
class Lista:
    def __init__(self):
        self.prim = None
        

'''
crearea unei liste din valori citite pana la 0
'''
def creareLista():
    lista = Lista()
    lista.prim = creareLista_rec()
    return lista

def creareLista_rec():
    x = int(input("x="))
    if x == 0:
        return None
    else:
        nod = Nod(x)
        nod.urm = creareLista_rec()
        return nod
    
'''
tiparirea elementelor unei liste
'''
def tipar(lista):
    tipar_rec(lista.prim)
    
def tipar_rec(nod):
    if nod != None:
        print (nod.e)
        tipar_rec(nod.urm)
        

def checkSet(list: Lista):
    current = list.prim
    while current is not None:
        next = current.urm
        while next is not None:
            if current.e == next.e:
                return False
            next = next.urm
        current = current.urm
    return True


def checkSetRec(list: Lista, current: Nod):
    if current is None:
        return True
    if not checkNextRec(list, current, current.urm):
        return False
    return checkSetRec(list, current.urm)


def checkNextRec(list: Lista, current: Nod, nextNode: Nod):
    if nextNode is None:
        return True
    if current.e == nextNode.e:
        return False
    return checkNextRec(list, current, nextNode.urm)


def determineDistinctElements(list: Lista, current: Nod):
    if current is None:
        return 0
    if not appearsBefore(list, list.prim, current, current.e):
        return 1 + determineDistinctElements(list, current.urm)
    return determineDistinctElements(list, current.urm)


def appearsBefore(list: Lista, currentNode: Nod, stopNode: Nod, element):
    if currentNode is None or currentNode == stopNode:
        return False
    if currentNode.e == element:
        return True
    return appearsBefore(list, currentNode.urm, stopNode, element)


'''
program pentru test
'''
        
def main():
    list = creareLista()
    tipar(list)
    print("List is a set: " + str(checkSetRec(list, list.prim)))     # 3.a.
    print("The number of distinct elements from the list: " + str(determineDistinctElements(list, list.prim)))   # 3.b
    
main() 
    
    
    
    
    # 1 next time