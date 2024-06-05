import networkx as nx
from student_utils import *
import random

from mtsp_dp import mtsp_dp
from pthp_from_tsp import reconstruct_tour, create_complete_graph

def tsp_algorithm(G, H, visits):
    shortest_paths = dict(nx.floyd_warshall(G))

    homes_to_visit = [(shortest_paths[0][home], home) for home in H]
    homes_to_visit.sort()

    homes_to_visit = [e[1] for e in homes_to_visit]

    nodes = list(set([0] + homes_to_visit[:visits]))
    G_prime = create_complete_graph(G, nodes)
    mtsp_tour = mtsp_dp(G_prime)
    php_tour = reconstruct_tour(G, mtsp_tour)

    return php_tour[1:]

def tsp_algorithm_2(G, H, visits):
    homes_to_visit = random.sample(H, visits)

    nodes = list(set([0] + homes_to_visit[:visits]))
    G_prime = create_complete_graph(G, nodes)
    mtsp_tour = mtsp_dp(G_prime)
    php_tour = reconstruct_tour(G, mtsp_tour)

    return php_tour[1:]

def ptp_algorithm(G, H, alpha):    
    shortest_paths = dict(nx.all_pairs_dijkstra_path_length(G))
    
    def total_cost(T):
        driving_cost = 0
        for i in range(len(T)-1):
            if T[i+1] in G[T[i]]:
                driving_cost += G[T[i]][T[i+1]]['weight']
            else:
                return float('inf')

        if T[0] in G[T[-1]]:
            driving_cost += G[T[-1]][T[0]]['weight']
        else:
            return float('inf')

        walking_cost = 0
        for h in H:
            closest_pickup = min(T, key=lambda x: shortest_paths[h][x])
            walking_cost += shortest_paths[h][closest_pickup]

        return alpha * driving_cost + walking_cost

    def solidify(T):
        n = len(G.nodes)
        best_cost = total_cost(T)

        while True:
            best_improvement = None
            best_Tk = None
            for i in range(1, n):
                if i in T:
                    Tk_i = T[:]
                    Tk_i.remove(i)
                    cost_Tk_i = total_cost(Tk_i)
                    if best_improvement is None or cost_Tk_i < best_improvement:
                        best_improvement = cost_Tk_i
                        best_Tk = Tk_i
                else:
                    Tk_i = T[:]
                    possible_inserts = [Tk_i[:j] + [i] + Tk_i[j:] for j in range(len(Tk_i) + 1)]
                    for new_T in possible_inserts:
                        cost_Tk_i = total_cost(new_T)
                        if best_improvement is None or cost_Tk_i < best_improvement:
                            best_improvement = cost_Tk_i
                            best_Tk = new_T
            
            if best_improvement >= best_cost:
                break

            T = best_Tk
            best_cost = best_improvement

        return T

    def print_scoreboard(best_tours):
        return
        print("current scoreboard:")
        for price, tourk in best_tours:
            print("\t", "%.2f" % price, tourk)

    best_tours = [(total_cost([0]), [0])]

    import time
    start_tsp = time.time()
    last_best = 9999999
    s_itr = 1
    itr = len(H) - 2
    if len(H) <= 10:
        itr = len(H)
    if len(H) == 20 and alpha == 0.3:
        s_itr = len(H)
        itr = len(H)
    # for i in range(1, min(len(H), len(H)) + 1):
    for i in range(s_itr, itr + 1):
        T = tsp_algorithm(G, H, i)
        best_tours.append((total_cost(T), T))
    end_tsp = time.time()
    # while True:
    iterations = 0
    min_iterations = 1000
    start = time.time()
    # while iterations < min_iterations:
    while time.time() - start < 60:
        iterations += 1
        # if best_tours[0][0] < last_best:
        #     last_best = best_tours[0][0]
        #     print_scoreboard(best_tours)
        if random.randint(1, 7) <= 5:
            if len(G.nodes) < 4 or random.randint(1, 3) <= 1:
                T = [0]
            elif random.randint(1, 5) <= 3:
                T = [0]
                T.append(random.choice([j for j in G.neighbors(T[-1])]))
                if random.randint(1, 2) <= 1:
                    x = random.choice([j for j in G.neighbors(T[-1])])
                    cnt = 0
                    while x == 0 and cnt < 10:
                        x = random.choice([j for j in G.neighbors(T[-1])])
                        cnt += 1
                    if cnt < 10:
                        T.append(x)
                T += T[::-1]
            else:
                T = tsp_algorithm_2(G, H, random.randint(1, min(len(H), 5)))
        else:
            choose_best_tours = []
            seen = set()
            for price, tourk in best_tours:
                index = min(4, len(tourk))
                tourk_slice = tuple(tourk[:index])
                if tourk_slice not in seen:
                    choose_best_tours.append((price, tourk))
                    seen.add(tourk_slice)
            T = random.choice(choose_best_tours)[1].copy()
        nodes_list = list(G.nodes())
        random.shuffle(nodes_list)
        modified = True
        first = True
        # print(len(T), min(len(T) + 2 * int((1 / alpha)), 2 * len(G.nodes())))
        max_len = random.randint(len(T), min(len(T) + int((1 / alpha)), len(T) + int((3 / alpha))))
        while (modified or first) and len(T) < max_len:
            # print("hi", end = '')
            modified = False
            best_cost = total_cost(T)
            ranges = [i for i in range(1, len(G.nodes()))]
            random.shuffle(ranges)
            ranges = ranges[:random.randint(0, len(ranges) - 1)]
            for i in ranges:
                if i not in T:
                    best_tour = None
                    for j in range(len(T)):
                        if (T[j], i) in G.edges():
                            # print(end = '*')
                            new_tour = T[:j + 1] + [i] + T[j + 1:]
                            new_cost = total_cost(new_tour)
                            if new_cost < best_cost:
                                best_cost = new_cost
                                best_tour = new_tour
                    if best_tour is not None:
                        T = best_tour
                elif i in T:
                    position = T.index(i)
                    new_tour = T[:position] + T[position+1:]
                    new_cost = total_cost(new_tour)
                    if new_cost < best_cost:
                        T = new_tour
                        best_cost = new_cost
                        modified = True
            
            # print(end = "check")
            if modified == False:
                if not any(tour == T for _, tour in best_tours):
                    if len(best_tours) < 20:
                        best_tours.append((best_cost, T))
                    else:
                        worst_cost_index = max(range(len(best_tours)), key=lambda idx: best_tours[idx][0])
                        if best_tours[worst_cost_index][0] > best_cost:
                            best_tours[worst_cost_index] = (best_cost, T)
                    best_tours.sort()
                if first:
                    first = False
                    modified = True
            # print(end = "done")
        # print(T)
        best_cost = total_cost(T)
        if not any(tour == T for _, tour in best_tours):
            if len(best_tours) < 20:
                best_tours.append((best_cost, T))
            else:
                worst_cost_index = max(range(len(best_tours)), key=lambda idx: best_tours[idx][0])
                if best_tours[worst_cost_index][0] > best_cost:
                    best_tours[worst_cost_index] = (best_cost, T)
            best_tours.sort()

        sT = solidify(T)
        sT_cost = total_cost(sT)
        if not any(tour == sT for _, tour in best_tours):
            if len(best_tours) < 20:
                best_tours.append((sT_cost, sT))
            else:
                worst_cost_index = max(range(len(best_tours)), key=lambda idx: best_tours[idx][0])
                if best_tours[worst_cost_index][0] > sT_cost:
                    best_tours[worst_cost_index] = (sT_cost, sT)
            best_tours.sort()

        T = T[:-1]
        T.reverse()
        T.append(0)
        best_cost = total_cost(T)
        if not any(tour == T for _, tour in best_tours):
            if len(best_tours) < 20:
                best_tours.append((best_cost, T))
                print_scoreboard(best_tours)
            else:
                worst_cost_index = max(range(len(best_tours)), key=lambda idx: best_tours[idx][0])
                if best_tours[worst_cost_index][0] > best_cost:
                    best_tours[worst_cost_index] = (best_cost, T)
                    print_scoreboard(best_tours)
            best_tours.sort()

        sT = solidify(T)
        sT_cost = total_cost(sT)
        if not any(tour == sT for _, tour in best_tours):
            if len(best_tours) < 20:
                best_tours.append((sT_cost, sT))
            else:
                worst_cost_index = max(range(len(best_tours)), key=lambda idx: best_tours[idx][0])
                if best_tours[worst_cost_index][0] > sT_cost:
                    best_tours[worst_cost_index] = (sT_cost, sT)
            best_tours.sort()
        if first:
            first = False
            modified = True

    # for cost, tour in best_tours:
    #     print(">", cost, tour)
    tour = best_tours[0][1]
    if tour[0] != 0:
        tour = [0] + tour
    if tour[-1] != 0:
        tour.append(0)
    return tour

def ptp_solver(G:nx.DiGraph, H:list, alpha:float):
    """
    PTP solver.
    Input:
        G: a NetworkX graph representing the city.\
        This directed graph is equivalent to an undirected one by construction.
        H: a list of home nodes that you must vist.
        alpha: the coefficient of calculating cost.
    Output:
        tour: a list of nodes traversed by your car.
        pick_up_locs_dict: a dictionary of (pick-up-locations, friends-picked-up) pairs\
        where friends-picked-up is a list/tuple containing friends who get picked up at\
        that specific pick-up location. Friends are represented by their home nodes.

    All nodes are reprented as integers.
    
    The tour must begin and end at node 0.
    It can only go through edges that exist in the graph..
    Pick-up locations must be in the tour.
    Everyone should get picked up exactly once
    """

    tour = ptp_algorithm(G, H, alpha)

    shortest_paths = dict(nx.floyd_warshall(G))
    def assign_pickup_points(tour, H = H, shortest_paths = shortest_paths):
        pick_up_locs_dict = dict()
        for home in H:
            best_pickup = min(set(tour), key = lambda x: shortest_paths[home][x])
            if best_pickup not in pick_up_locs_dict:
                pick_up_locs_dict[best_pickup] = []
            pick_up_locs_dict[best_pickup].append(home)
        return pick_up_locs_dict

    pick_up_locs_dict = assign_pickup_points(tour)

    return tour, pick_up_locs_dict


if __name__ == "__main__":
    pass
