import networkx as nx
from itertools import combinations
import time

def mtsp_dp(G):
    """
    TSP solver using dynamic programming.
    Input:
        G: a NetworkX graph representing the city.\
        This directed graph is equivalent to an undirected one by construction.
    Output:
        tour: a list of nodes traversed by your car.

    All nodes are reprented as integers.

    You must solve the problem using dynamic programming.
    
    The tour must begin and end at node 0.
    It can only go through edges that exist in the graph..
    It must visit every node in G exactly once.
    """

    N = G.number_of_nodes()
    dp = [[float('inf')] * N for _ in range(1 << N)]
    
    dp[1][0] = 0
    node_list = list(G.nodes())

    edge_weight = {}
    for u in node_list:
        for v in node_list:
            if u != v:                
                edge_weight[(u, v)] = G[u][v]['weight']
    edge_weights = [[edge_weight[(node_list[u], node_list[v])] if u != v else 0 for v in range(N)] for u in range(N)]

    for mask in range(1 << N):
        u_mask = mask
        v_mask_init = mask ^ ((1 << N) - 1)
        while u_mask:
            u_idx = u_mask.bit_length() - 1
            u_mask ^= (1 << u_idx)

            v_mask = v_mask_init & ~(1 << u_idx)
            while v_mask:
                v_idx = v_mask.bit_length() - 1
                v_mask ^= (1 << v_idx)

                new_mask = mask | (1 << v_idx)
                new_cost = dp[mask][u_idx] + edge_weights[u_idx][v_idx]
                if new_cost < dp[new_mask][v_idx]:
                    dp[new_mask][v_idx] = new_cost

    min_cost = float('inf')
    last_node = -1
    for i in range(1, N):
        cost = dp[(1 << N) - 1][i] + edge_weights[0][i]
        if cost < min_cost:
            min_cost = cost
            last_node = i

    mask = (1 << N) - 1
    tour = [0]

    while last_node != 0:
        tour.append(node_list[last_node])
        next_node = -1

        v_mask = mask & ~(1 << last_node)
        while v_mask:
            v = v_mask.bit_length() - 1
            v_mask ^= (1 << v)
            if dp[mask][last_node] == dp[mask ^ (1 << last_node)][v] + edge_weights[last_node][v]:
                next_node = v

        mask = mask ^ (1 << last_node)
        last_node = next_node

    tour.append(0)
    tour.reverse()

    return tour