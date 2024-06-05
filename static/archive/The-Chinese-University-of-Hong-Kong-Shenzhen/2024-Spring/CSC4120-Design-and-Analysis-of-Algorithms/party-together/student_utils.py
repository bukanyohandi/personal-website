import networkx as nx
import matplotlib.pyplot as plt
from utils import *
# import numpy as np

def data_parser(input_data):
    """
    Parsing input data
    """
    alpha = float(input_data[0][0])
    number_of_nodes = int(input_data[1][0])
    number_of_homes = int(input_data[1][1])
    home_node_list = [int(node) for node in input_data[2]]
    multiline_adjlist = input_data[3:]
    edge_list = []
    i = 0
    while i < len(multiline_adjlist):
        line = multiline_adjlist[i]
        u, d = int(line[0]), int(line[1])
        i += 1
        for _ in range(d):
            line = multiline_adjlist[i]
            v, w = int(line[0]), float(line[1])
            i += 1
            edge_list.append((u, v, w))
    return alpha, number_of_nodes, number_of_homes, home_node_list, edge_list

def weighted_edge_list_to_graph(edge_list):
    """
    Create a graph from a weighted edge list
    For technical reasons, the graph is made directed here.
    But it is equivalent to an undirected one by construction.
    """
    G = nx.DiGraph()
    G.add_weighted_edges_from(edge_list)
    return G

def input_file_to_instance(file):
    """
    Create an instance of PTP problem from a specific file
    Input: file: path of the file
    Output: 
        G: the graph, 
        H: a list of home nodes
        alpha: the coeeficient alpha
        
    I also store H and graph in the graph G.
    You can get access to them via G.graph['alpha'], G.graph['H']
    """
    input_data = read_file(file)
    alpha, _, _, H, edge_list = data_parser(input_data)
    G = weighted_edge_list_to_graph(edge_list)
    G.graph['H'] = H
    G.graph['alpha'] = alpha
    return G, H, alpha

def is_metric(G):
    """
    Check whether a given graph G is metric or not,
    i.e., whether triangle inequality holds.
    """
    d = nx.floyd_warshall(G)
    for u, v, data in G.edges(data=True):
        if abs(d[u][v] - data['weight']) >= 0.0000001:
            return False
    return True

def is_connected(G):
    """
    Check whether a graph G is connected or not
    """
    return nx.is_connected(nx.to_undirected(G))

def is_valid_input(file):
    """
    Check if an input is valid or not
    Input: file: path to the input file
    Output:
        is_valid: bool, input valid or not
        message: log message
    """
    is_valid = True
    message = ''

    input_data = read_file(file)
    file_name = os.path.basename(file)
    file_name = file_name.split(".")[0]
    file_name = file_name.split("_")
    max_number_of_nodes = int(file_name[0])
    max_number_of_friends = int(max_number_of_nodes/2)
    expected_alpha = float(file_name[1])/10
    alpha, number_of_nodes, number_of_friends, H, edge_list = data_parser(input_data)

    if abs(alpha - expected_alpha) >= 0.001:
        is_valid = False
        message += 'alpha is not as required\n'

    if number_of_nodes > max_number_of_nodes:
        is_valid = False
        message += 'maximum number of nodes exceeded\n'

    if number_of_friends > max_number_of_friends:
        is_valid = False
        message += 'maximum number of friends exceeded\n'

    if len(H) != number_of_friends:
        is_valid = False
        message += 'number of friends not correct\n'

    if len(set(H)) != len(H):
        is_valid = False
        message += 'friend homes not distinct\n'

    G = weighted_edge_list_to_graph(edge_list)

    if G.number_of_nodes() != number_of_nodes:
        is_valid = False
        message += 'number of nodes not correcr\n'

    if not is_connected(G):
        is_valid = False
        message += 'graph is not connected\n'

    if not is_metric(G):
        is_valid = False
        message += 'graph does not have triangle inequality\n'

    nodes = sorted(G.nodes())

    if nodes != list(range(G.number_of_nodes())):
        is_valid = False
        message += 'nodes not indexed from 0 to n-1\n'

    if any([h not in nodes for h in H]):
        is_valid = False
        message += 'some home nodes not in the graph\n'

    for u, v in G.edges():
        if u == v:
            is_valid = False
            message += 'exist edge conneting a node with itself\n'
            break
        if G[u][v]['weight'] != G[v][u]['weight']:
            is_valid = False
            message += 'edge weights not symmetric\n'
            break
    
    return is_valid, message


def analyze_solution(G, H, alpha, tour, pick_up_locs_dict):
    """
    Analyze solutuon for a given instance of the problem
    Input:
        G: the graph G
        H: a list of home nodes
        alpha: the cost coefficient
        tour: the tour of the car
        pick_up_locs_dict: a dictionary of (pick-up location, friends picked up) pair
                        for pthp, this would be empty({})
    Output:
        is_legitimate: bool, whether the solution is legitimate or not
        driving_cost: folat, total cost(unhappniess) of the driving car
        walking_cost: float, total cost of walking friends

    A solution is legitimate iff following coditions hold.
        The indices must be in the graph, i.e., integers from 0 to |V| - 1. 
        The tour must begin and end at node 0. It can only go through edges that exist in the graph. 
        The pick-up locations must be in the tour . Everyone should get picked up.
    Total cost would be the sum of driving_cost and walking_cost
    An infeasible solution would have positive infinity cost

    Example:
        For the example in the description file, a possible solution would be
            tour = [0, 1, 0]
            pick_up_locs_dict = {1: (1, 2 3)}
        The output would thus be, (assume alpha = 2/3)
            True, float(10/3)
    """
    driving_cost = 0
    walking_cost = 0
    # the tour must start and end at node 0
    if not (tour[0] == 0 and tour[-1] == 0):
        print("not cycle")
        return False, float('infinity'), float('infinity') 
    # every road in the tour must exist in the graph
    for i in range(1, len(tour)):
        if not G.has_edge(tour[i-1], tour[i]):
            print(f"edge{tour[i-1], tour[i]} not exist")
            return False, float('infinity'), float('infinity')
        driving_cost += float(alpha * G.get_edge_data(tour[i-1], tour[i])['weight'])
    # every should get picked up exactly once    
    if pick_up_locs_dict:
        all_shortest_path_lengths = nx.floyd_warshall(G)
        friends_get_picked_up = []
        for pick_up_loc in pick_up_locs_dict:
            friends = pick_up_locs_dict[pick_up_loc]
            # pick up locations must be in the tour
            if not pick_up_loc in tour:
                print(f"Pick up location {pick_up_loc} not in the tour")
                return False, float('infinity'), float('infinity')
            for friend in friends:
                walking_cost += all_shortest_path_lengths[pick_up_loc][friend]
                friends_get_picked_up.append(friend)
        friends_get_picked_up = sorted(friends_get_picked_up)
        if len(H) == len(friends_get_picked_up) \
                and all([home == friends_get_picked_up[i]] for i, home in enumerate(sorted(H))):
            return True, driving_cost, walking_cost
        else:
            print("Not all friends picked up")
            return False, float('infinity'), float('infinity')
        # return np.all(np.sort(H) == np.sort(friends_get_picked_up))
    # PTHP solution, no pick-up locaitons. Every node in H should be in tour
    if all([i in tour for i in H]):
        return True, driving_cost, walking_cost
    else:
        print("Not visit every node in H")
        return False, float('infinity'), float('infinity')


def write_ptp_solution_to_out(tour, pick_up_locs_dict, in_file):
    out_dir = os.path.join(os.getcwd(), OUTPUT_FILE_DIRECTORY)
    if not os.path.exists(out_dir):
        os.makedirs(out_dir)
    file_name = in_file.split('.')[0] + '.out'
    out_file_path = os.path.join(out_dir, file_name)
    data = []
    data.append(' '.join(str(i) for i in tour))
    data.append(str(len(pick_up_locs_dict)))
    for pick_up_loc in pick_up_locs_dict:
        friends = pick_up_locs_dict[pick_up_loc]
        data.append(str(pick_up_loc) + ' ' + ' '.join(str(i) for i in friends))
    write_to_file(out_file_path, '\n'.join(data))
    

def draw_gragh(G, with_weight=True):
    """Draw the graph"""
    pos = nx.spring_layout(G)  # positions for all nodes
    nx.draw(G, pos, with_labels=True, node_color='skyblue', node_size=2000, font_size=10)

    if with_weight:
        # Draw edge labels
        edge_labels = nx.get_edge_attributes(G, 'weight')
        nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
    
    plt.show()