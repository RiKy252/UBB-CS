# for practical work no. 2 -> problem 3
# for practical work no. 3 -> problem 2
# for practical work no. 4 -> problem 4
import copy
import random
import sys
import heapq


def backwards_dijkstra(graph, start, end):
    # I initialize the distance dictionary, the priority queue and previous vertex dictionary
    distance = {vertex: float('inf') for vertex in graph.parse_vertices()}
    distance[end] = 0
    queue = [(end, 0)]  # the second element of the tuple is the distance, for the priority we take the lower distance
    next = {vertex: None for vertex in graph.parse_vertices()}

    # I loop until I processed all the edges in the priority queue
    while queue:
        # Pop from priority queue the vertex with the lowest cost
        current_vertex, current_distance = heapq.heappop(queue)
        # I go to the next iteration if we have already a shorter path to the current vertex
        if current_distance != distance[current_vertex]:
            continue
        # I loop every neighbour of the current vertex and update the distance if needed
        for neighbor in graph.parse_inbound_edges(current_vertex):
            new_distance = current_distance + graph.get_cost((neighbor, current_vertex))
            if new_distance < distance[neighbor]:
                distance[neighbor] = new_distance
                heapq.heappush(queue, (neighbor, new_distance))
                next[neighbor] = current_vertex

    return distance[start], next


def get_vertices_from_file(file_name):
    with open(file_name, "r") as file:
        line = file.readline().strip().split(" ")
        vertices = line[0]
    return int(vertices)


def get_edges_from_file(file_name):
    with open(file_name, "r") as file:
        line = file.readline().strip().split(" ")
        edges = line[1]
    return int(edges)


# This function gets a filename and returns an undirected graph,
# so it adds every edge in reverse also if it does not exist already
def get_undirected_graph_from_file(file_name):
    with open(file_name, "r") as file:
        line = file.readline().strip().split(" ")
        if len(line) == 3 or (len(line) == 2 and line[1] == "-1"):
            graph = DirectedGraph(0)
            lines = file.readlines()
            for line in lines:
                line = line.strip().split(" ")
                if len(line) == 3:
                    v1 = int(line[0])
                    v2 = int(line[1])
                    cost = int(line[2])
                    if not graph.is_vertex(v1):
                        graph.add_vertex(v1)
                    if not graph.is_vertex(v2):
                        graph.add_vertex(v2)
                    if not graph.is_edge((v1, v2)):
                        graph.add_edge((v1, v2), cost)
                    if not graph.is_edge((v2, v1)):
                        graph.add_edge((v2, v1), cost)
                else:
                    v1 = int(line[0])
                    if not graph.is_vertex(v1):
                        graph.add_vertex(v1)
        else:
            vertices = int(line[0])
            graph = DirectedGraph(vertices)
            lines = file.readlines()
            for line in lines:
                line = line.strip().split(" ")
                v1 = int(line[0])
                v2 = int(line[1])
                cost = int(line[2])
                if not graph.is_edge((v1, v2)):
                    graph.add_edge((v1, v2), cost)
                if not graph.is_edge((v2, v1)):
                    graph.add_edge((v2, v1), cost)
    return graph


def generate_random_graph(no_vertices, no_edges):
    if no_edges > (no_vertices**2):
        raise ValueError(f"Cannot create a graph with {no_vertices} vertices and {no_edges} edges!\n")
    graph = DirectedGraph(no_vertices)
    while no_edges > 0:
        v1 = random.randint(0, no_vertices - 1)
        v2 = random.randint(0, no_vertices - 1)
        cost = random.randint(0, 100)
        if not graph.is_edge((v1, v2)):
            graph.add_edge((v1, v2), cost)
            no_edges -= 1
    return graph


class DirectedGraph:
    def __init__(self, no_vertices: int):
        self._vertices = no_vertices
        self._edges = 0
        self._dict_in = {}
        self._dict_out = {}
        self._dict_cost = {}
        for i in range(no_vertices):
            self._dict_in[i] = []
            self._dict_out[i] = []

    @staticmethod
    def menu():
        print("1. Add vertex")
        print("2. Remove vertex")
        print("3. Add edge")
        print("4. Remove edge")
        print("5. Display number of vertices")
        print("6. Display the set of vertices")
        print("7. Verify edge")
        print("8. Get in degree")
        print("9. Get out degree")
        print("10. Parse outbound edges")
        print("11. Parse inbound edges")
        print("12. Get cost of an edge")
        print("13. Set cost of an edge")
        print("14. Make a copy of the graph")
        print("15. Write graph to a text file")
        print("16. Find connected components")
        print("17. Shortest path")
        print("18. Topological sorting")
        print("19. Find a hamiltonian cycle")
        print("0. Exit")

    def find_hamiltonian_cycle(self):
        def is_valid_vertex(v, pos, path):
            # Check if this vertex is an adjacent vertex of the previously added vertex
            if v not in self._dict_out[path[pos - 1]]:
                return False
            # Check if the vertex has already been included
            if v in path:
                return False
            return True

        def hamiltonian_cycle_util(path, pos):
            # If all vertices are included in the path
            if pos == self._vertices:
                # And if there is an edge from the last included vertex to the first vertex
                if path[pos - 1] in self._dict_out[path[0]]:
                    return True
                else:
                    return False

            # Try different vertices as the next candidate in the Hamiltonian Cycle
            for v in self.parse_vertices():
                if is_valid_vertex(v, pos, path):
                    path[pos] = v
                    if hamiltonian_cycle_util(path, pos + 1):
                        return True
                    # Remove current vertex if it doesn't lead to a solution
                    path[pos] = -1
            return False

        # Initializing the path array with -1
        path = [-1] * self._vertices
        # Let the first vertex be 0 in the path (it can be any vertex from the graph)
        path[0] = 0

        if not hamiltonian_cycle_util(path, 1):
            return None
        else:
            path.append(path[0])  # Append the starting vertex to the end to form a cycle
            return path

    def topological_sorting(self):
        # This function returns a topological sorting of the graph O(V + E)
        # Initialize the list and the queue, as well as the count dictionary
        sorted_list = []
        q = []  # this is a list but will work as a queue, as I will append to the end, and pop from the beginning
        count = {}
        # Initialize the count dictionary to the in degree of each vertex
        for vertex in self.parse_vertices():
            count[vertex] = len(self._dict_in[vertex])
            # Append to the queue the vertices with in degree 0
            if count[vertex] == 0:
                q.append(vertex)

        # Loop until the queue is empty
        while q:
            # Pop from the queue the current vertex and append it to the sorted list
            current_vertex = q.pop()
            sorted_list.append(current_vertex)
            # Parse neighbors of the current vertex and decrease their in degree in the count dictionary
            for neighbor in self.parse_outbound_edges(current_vertex):
                count[neighbor] -= 1
                # If the in degree of the neighbor is 0, append it to the queue to be processed
                if count[neighbor] == 0:
                    q.append(neighbor)

        # If the graph is a DAG, the topological sorting will be returned, otherwise an exception will be raised
        if len(sorted_list) < self._vertices:
            raise ValueError("The graph has a cycle!")

        return sorted_list

    def highest_cost_path_dag(self, start, end, topological_sort: list):
        # This function returns the highest cost path between two vertices in a DAG, taking as input the topological sorted list as well
        # Initialize the distance dictionary and the path dictionary
        distance = {}
        path = {vertex: None for vertex in self.parse_vertices()}
        for vertex in self.parse_vertices():
            distance[vertex] = float('-inf')
        distance[start] = 0
        # Iterate through the topological sorted list and update the distance and path dictionaries if we find a higher cost path
        for current_vertex in topological_sort:
            if current_vertex == end:
                break
            for adj in self.parse_outbound_edges(current_vertex):
                if distance[adj] < (distance[current_vertex] + self.dict_cost[(current_vertex, adj)]):
                    distance[adj] = distance[current_vertex] + self.dict_cost[(current_vertex, adj)]
                    path[adj] = current_vertex
        # Return the highest cost and the path as a tuple
        # If the end vertex has a distance of -inf, it means there is no path between the two vertices
        highest_cost = distance[end]
        return highest_cost, path

    # This function perform a depth first search on a given vertex,
    # searching all the accessible vertices from that starting vertex
    # and changing the processed list accordingly
    # The processed list works like a stack because it appends at the end and pops from the end.
    def depth_first(self, vertex: int, visited: set, processed: list):
        for x in self._dict_out[vertex]:
            if x not in visited:
                visited.add(x)
                self.depth_first(x, visited, processed)
        processed.append(vertex)

    # This function finds the connected components of the current graph, supposing it is undirected
    # It goes through the stack and works his way down until it processes all the vertices from the stack
    # and adds all the edges needed into a new graph object called connected_component
    # The processed list works like a stack because it appends at the end and pops from the end.
    # At the end appends that graph object (the connected component) to a list
    # The list connected_components with all connected components graph objects is returned
    def find_connected_components(self):
        processed = []
        visited = set()
        connected_components = []

        for vertex in self.parse_vertices():
            if vertex not in processed:
                visited.add(vertex)
                self.depth_first(vertex, visited, processed)
                visited.clear()
                start_vertex = processed.pop()
                connected_component = DirectedGraph(0)
                visited.add(start_vertex)
                if not connected_component.is_vertex(start_vertex):
                    connected_component.add_vertex(start_vertex)
                stack = [start_vertex]
                while stack:
                    current_vertex = stack.pop()
                    for neighbor in self.parse_outbound_edges(current_vertex):
                        if neighbor not in visited:
                            visited.add(neighbor)
                            if not connected_component.is_vertex(neighbor):
                                connected_component.add_vertex(neighbor)
                            if not connected_component.is_edge((current_vertex, neighbor)):
                                connected_component.add_edge((current_vertex, neighbor), self.get_cost((current_vertex, neighbor)))
                            if not connected_component.is_edge((neighbor, current_vertex)):
                                connected_component.add_edge((neighbor, current_vertex), self.get_cost((current_vertex, neighbor)))
                            stack.append(neighbor)
                        else:
                            if self.is_edge((current_vertex, neighbor)) and not connected_component.is_edge((current_vertex, neighbor)):
                                if not connected_component.is_edge((current_vertex, neighbor)):
                                    connected_component.add_edge((current_vertex, neighbor), self.get_cost((current_vertex, neighbor)))
                                if not connected_component.is_edge((neighbor, current_vertex)):
                                    connected_component.add_edge((neighbor, current_vertex), self.get_cost((current_vertex, neighbor)))

                connected_components.append(connected_component)

        return connected_components

    def get_graph_from_file(self, file_name):
        with open(file_name, "r") as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip().split(" ")
                if len(line) == 3:
                    v1 = int(line[0])
                    v2 = int(line[1])
                    cost = int(line[2])
                    self.add_edge((v1, v2), cost)

    def get_graph_from_file_format_2(self, file_name):
        with open(file_name, "r") as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip().split(" ")
                if len(line) == 3:
                    v1 = int(line[0])
                    if not self.is_vertex(v1):
                        self.add_vertex(v1)
                    v2 = int(line[1])
                    if not self.is_vertex(v2):
                        self.add_vertex(v2)
                    cost = int(line[2])
                    self.add_edge((v1, v2), cost)
                if len(line) == 2 and line[1] == "-1":
                    v = int(line[0])
                    self.add_vertex(v)

    def copy_graph(self):
        return copy.deepcopy(self)

    def get_number_of_vertices(self):
        return self._vertices

    def get_number_of_edges(self):
        return self._edges

    def parse_vertices(self):
        return list(self._dict_in.keys())

    def is_edge(self, edge: tuple):
        v1, v2 = edge
        if self.is_vertex(v1):
            return v2 in self._dict_out[v1]

    def is_vertex(self, vertex: int):
        return vertex in self._dict_in.keys()

    def get_in_degree(self, vertex: int):
        if self.is_vertex(vertex):
            return len(self._dict_in[vertex])
        raise ValueError(f"The vertex {vertex} does not belong to the graph!")

    def get_out_degree(self, vertex: int):
        if self.is_vertex(vertex):
            return len(self._dict_out[vertex])
        raise ValueError(f"The vertex {vertex} does not belong to the graph!")

    def parse_outbound_edges(self, vertex: int):
        if self.is_vertex(vertex):
            return self._dict_out[vertex]
        raise ValueError(f"The vertex {vertex} does not belong to the graph!")

    def parse_inbound_edges(self, vertex: int):
        if self.is_vertex(vertex):
            return self._dict_in[vertex]
        raise ValueError(f"The vertex {vertex} does not belong to the graph!")

    def get_cost(self, edge: tuple):
        if self.is_edge(edge):
            return self._dict_cost[edge]
        raise ValueError(f"The edge {edge} does not belong to the graph!")

    def set_cost(self, edge: tuple, cost: int):
        if self.is_edge(edge):
            self._dict_cost[edge] = cost
        else:
            raise ValueError(f"The edge {edge} does not belong to the graph!")

    def add_edge(self, edge: tuple, cost: int):
        if self.is_edge(edge):
            raise ValueError(f"The edge {edge} already exists!")
        v1, v2 = edge
        if not self.is_vertex(v1):
            raise ValueError(f"The vertex {v1} does not belong to the graph!")
        if not self.is_vertex(v2):
            raise ValueError(f"The vertex {v2} does not belong to the graph!")
        self._dict_in[v2].append(v1)
        self._dict_out[v1].append(v2)
        self._dict_cost[edge] = cost
        self._edges += 1

    def remove_edge(self, edge: tuple):
        if not self.is_edge(edge):
            raise ValueError(f"The edge {edge} does not belong to the graph!")
        v1, v2 = edge
        self.parse_inbound_edges(v2).remove(v1)
        self.parse_outbound_edges(v1).remove(v2)
        del self._dict_cost[edge]
        self._edges -= 1

    def add_vertex(self, vertex: int):
        if self.is_vertex(vertex):
            raise ValueError(f"The vertex {vertex} already exists!")
        self._dict_in[vertex] = []
        self._dict_out[vertex] = []
        self._vertices += 1

    def remove_vertex(self, vertex: int):
        if not self.is_vertex(vertex):
            raise ValueError(f"The vertex {vertex} does not belong to the graph!")
        for y in self._dict_out[vertex]:
            if (vertex, y) in self._dict_cost.keys():
                del self._dict_cost[(vertex, y)]
            if (y, vertex) in self._dict_cost.keys():
                del self._dict_cost[(y, vertex)]
            self._dict_in[y].remove(vertex)
            self._edges -= 1
        del self._dict_out[vertex]
        for y in self._dict_in[vertex]:
            self._dict_out[y].remove(vertex)
            self._edges -= 1
        del self._dict_in[vertex]
        self._vertices -= 1

    @property
    def dict_cost(self):
        return self._dict_cost


def write_graph_to_file(graph: DirectedGraph, filename: str):
    with open(filename, "w") as file:
        for edge, cost in graph.dict_cost.items():
            vertex1, vertex2 = edge
            file.write(str(vertex1) + " " + str(vertex2) + " " + str(cost) + "\n")
        for vertex in graph.parse_vertices():
            if graph.get_in_degree(vertex) == 0 and graph.get_out_degree(vertex) == 0:
                file.write(str(vertex) + " -1\n")


def run():
    sys.setrecursionlimit(100001)
    while True:
        try:
            print("1. Create a random graph")
            print("2. Read a directed graph from a file")
            print("3. Read a undirected graph from a file")
            user_option = int(input(">> ").strip())
            if user_option == 1:
                no_vertices = int(input("Enter the number of vertices: ").strip())
                no_edges = int(input("Enter the number of edges: ").strip())
                graph = generate_random_graph(no_vertices, no_edges)
                print("Graph successfully generated!")
                break
            elif user_option == 2:
                file_format = 0
                file_name = input("Enter the name of the file: ").strip()
                with open(file_name, "r") as file:
                    lines = file.readlines()
                    for line in lines:
                        line = line.strip().split(" ")
                        if (len(line) == 2 and line[1] == "-1") or (len(line) == 3):
                            file_format = 2
                            break
                        else:
                            file_format = 1
                            break
                if file_format == 1:
                    vertices = get_vertices_from_file(file_name)
                    graph = DirectedGraph(vertices)
                    graph.get_graph_from_file(file_name)
                    print("Graph successfully read!")
                    break
                elif file_format == 2:
                    graph = DirectedGraph(0)
                    graph.get_graph_from_file_format_2(file_name)
                    print("Graph successfully read!")
                    break
            elif user_option == 3:
                file_name = input("Enter the name of the file: ").strip()
                graph = get_undirected_graph_from_file(file_name)
                print("Graph successfully read!")
                break
            else:
                print("Invalid option!")
        except (ValueError, FileNotFoundError) as error:
            print(error)
    while True:
        try:
            graph.menu()
            option = int(input(">> ").strip())
            if option == 1:  # add vertex
                user_vertex = int(input("Enter the vertex to be added: ").strip())
                graph.add_vertex(user_vertex)
            elif option == 2:  # remove vertex
                user_vertex = int(input("Enter the vertex to be removed: ").strip())
                graph.remove_vertex(user_vertex)
            elif option == 3:  # add edge
                end_point1 = int(input("Enter the first endpoint of the edge: ").strip())
                end_point2 = int(input("Enter the second endpoint of the edge: ").strip())
                user_edge = (end_point1, end_point2)
                user_cost = int(input("Enter the edge cost: ").strip())
                graph.add_edge(user_edge, user_cost)
            elif option == 4:  # remove edge
                end_point1 = int(input("Enter the first endpoint of the edge: ").strip())
                end_point2 = int(input("Enter the second endpoint of the edge: ").strip())
                user_edge = (end_point1, end_point2)
                graph.remove_edge(user_edge)
            elif option == 5:  # display number of vertices
                print("The number of vertices of the current graph: " + str(graph.get_number_of_vertices()))
            elif option == 6:  # display set of vertices
                print(graph.parse_vertices())
            elif option == 7:  # verify edge
                end_point1 = int(input("Enter the first endpoint of the edge: ").strip())
                end_point2 = int(input("Enter the second endpoint of the edge: ").strip())
                user_edge = (end_point1, end_point2)
                if graph.is_edge(user_edge):
                    print(f"{user_edge} is an edge of the graph!")
                else:
                    print(f"{user_edge} is not an edge of the graph!")
            elif option == 8:  # in degree
                user_vertex = int(input("Enter the vertex for which to get the in degree: ").strip())
                print(f"The in degree of the vertex {user_vertex} is: " + str(graph.get_in_degree(user_vertex)))
            elif option == 9:  # out degree
                user_vertex = int(input("Enter the vertex for which to get the out degree: ").strip())
                print(f"The out degree of the vertex {user_vertex} is: " + str(graph.get_out_degree(user_vertex)))
            elif option == 10:  # parse outbound
                user_vertex = int(input("Enter the vertex: ").strip())
                print(graph.parse_outbound_edges(user_vertex))
            elif option == 11:  # parse inbound
                user_vertex = int(input("Enter the vertex: ").strip())
                print(graph.parse_inbound_edges(user_vertex))
            elif option == 12:  # get cost
                end_point1 = int(input("Enter the first endpoint of the edge: ").strip())
                end_point2 = int(input("Enter the second endpoint of the edge: ").strip())
                user_edge = (end_point1, end_point2)
                print(f"The cost of {user_edge} is: " + str(graph.get_cost(user_edge)))
            elif option == 13:  # set cost
                end_point1 = int(input("Enter the first endpoint of the edge: ").strip())
                end_point2 = int(input("Enter the second endpoint of the edge: ").strip())
                user_edge = (end_point1, end_point2)
                cost = int(input("Enter the new cost for the edge: ").strip())
                graph.set_cost(user_edge, cost)
                print("Cost set successfully!")
            elif option == 14:  # copy graph
                graph_copy = graph.copy_graph()
                print("Graph copied!")
            elif option == 15:  # write graph
                filename = input("Enter the file name: ").strip()
                write_graph_to_file(graph, filename)
            elif option == 16:  # find connected components
                comps = graph.find_connected_components()
                idx = 0
                file_name = "component"
                for comp in comps:
                    idx += 1
                    write_graph_to_file(comp, file_name + str(idx) + ".txt")
            elif option == 17:  # shortest path
                start = int(input("Enter the start vertex: ").strip())
                if not graph.is_vertex(start):
                    raise ValueError(f"The vertex {start} does not belong to the graph!")
                end = int(input("Enter the end vertex: ").strip())
                if not graph.is_vertex(end):
                    raise ValueError(f"The vertex {end} does not belong to the graph!")
                dist, next = backwards_dijkstra(graph, start, end)
                path = []
                if next[start] is None:
                    print("There is no path between the two vertices!")
                else:
                    print(f"The shortest length from {start} to {end} is: {dist}")
                    current_vertex = start
                    # Here I construct the lowest cost path from the start vertex to the end vertex and I print it
                    while current_vertex != end:
                        path.append(current_vertex)
                        current_vertex = next[current_vertex]
                    path.append(end)
                    print(path)
            elif option == 18:  # topological sorting
                try:
                    # I get the topological sorting of the graph and retrieve input from the user to perform the highest cost path
                    topological_list = graph.topological_sorting()
                    print(f"The graph is a DAG: topological sorting = {topological_list}")
                    start = int(input("Enter the start vertex: ").strip())
                    end = int(input("Enter the end vertex: ").strip())
                    if not graph.is_vertex(start):
                        raise ValueError(f"The vertex {start} does not belong to the graph!")
                    if not graph.is_vertex(end):
                        raise ValueError(f"The vertex {end} does not belong to the graph!")
                    dist, path_dict = graph.highest_cost_path_dag(start, end, topological_list)
                    if dist == float('-inf'):
                        raise ValueError("There is no path between the two vertices!")
                    path = []
                    current_vertex = end
                    while current_vertex != start:
                        path.append(current_vertex)
                        current_vertex = path_dict[current_vertex]
                    path.append(start)
                    path.reverse()
                    print(f"The highest cost path from {start} to {end} is: {path} and the cost is {dist}")
                except ValueError as error:
                    print(error)
            elif option == 19:  # hamiltonian cycle
                cycle = graph.find_hamiltonian_cycle()
                if cycle:
                    print("Hamiltonian Cycle found:", cycle)
                else:
                    print("No Hamiltonian Cycle found")
            elif option == 0:  # exit
                break
            else:
                print("Invalid option!")
        except ValueError as error:
            print(error)


run()
