import networkx as nx
from collections import defaultdict

# G=nx.DiGraph()
g = nx.DiGraph()


def topologicalSortUtil(g1, v, visited, stack):
    # Mark the current node as visited.
    visited[v] = True

    # Recur for all the vertices adjacent to this vertex
    set1=set(g1.neighbors(v))
    #print(set1)
    for i in set1:
            if visited[i]==False:
             topologicalSortUtil(g1, i, visited, stack)



    #print(v)
    stack.insert(0,v)



def topologicalSort(g1):
    visited = [False] * g1.number_of_nodes()
    #print(g1.number_of_nodes())
    stack = []
    for i in range(g1.number_of_nodes()):
       # print(i)
        if visited[i] == False:
            topologicalSortUtil(g1, i, visited, stack)

        # Print contents of the stack
    for i in range(len(stack)):
        stack[i]=stack[i]+1
    print(stack)

'''g.add_node(0)
g.add_node(1)
g.add_node(2)
g.add_node(3)
g.add_node(4)
g.add_node(5)

g.add_edge(4, 1)
g.add_edge(4, 0)
g.add_edge(5, 2)
g.add_edge(5, 0)
#g.add_edge(1, 2)
g.add_edge(2, 3)
g.add_edge(3, 1)
nx.write_gpickle(g, "test.gpickle")'''
G = nx.read_gpickle("L9_P2_input.gpickle")
if nx.algorithms.is_directed_acyclic_graph(G):
 print("Following is a Topological Sort of the given graph")
 topologicalSort(G)
else:
    print("the given input is a not a DAG")