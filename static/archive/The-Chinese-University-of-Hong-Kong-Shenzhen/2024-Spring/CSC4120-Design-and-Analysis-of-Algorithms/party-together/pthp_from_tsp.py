import networkx as nx
from mtsp_dp import mtsp_dp
from student_utils import *
    
def reconstruct_tour(G, mtsp_tour):
    actual_tour = [0]
    for i in range(len(mtsp_tour) - 1):
        path = nx.shortest_path(G, source=mtsp_tour[i], target=mtsp_tour[i+1], weight='weight')
        actual_tour.extend(path[1:])
    return actual_tour

def create_complete_graph(G, nodes):
    G_complete = nx.complete_graph(nodes)
    for u in G_complete.nodes():
        for v in G_complete.nodes():
            if u != v:
                G_complete[int(u)][int(v)]['weight'] = nx.shortest_path_length(G, source=int(u), target=int(v), weight='weight')
    return G_complete

def pthp_solver_from_tsp(G, H):
    """
    PTHP solver via reduction to Euclidean TSP.
    Input:
        G: a NetworkX graph representing the city.\
        This directed graph is equivalent to an undirected one by construction.
        H: a list of home nodes that you must vist.
    Output:
        tour: a list of nodes traversed by your car.

    All nodes are reprented as integers.

    You must solve the question by first transforming a PTHP\
    problem to a TSP problem. After solving TSP via the dynammic\
    programming algorithm introduced in lectures, construct a solution\
    for the original PTHP problem.
    
    The tour must begin and end at node 0.
    It can only go through edges that exist in the graph..
    It must visit every node in H.
    """
    
    nodes = list(set([0] + H))
    G_prime = create_complete_graph(G, nodes)
    mtsp_tour = mtsp_dp(G_prime)
    php_tour = reconstruct_tour(G, mtsp_tour)
    # print(php_tour)
    return php_tour

if __name__ == "__main__":
    pass