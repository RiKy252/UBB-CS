#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <random>
#include <stdexcept>
#include <string>

int get_vertices_from_file(const std::string& file_name) {
    std::ifstream file(file_name);
    if (file.is_open()) {
        int vertices;
        file >> vertices;
        file.close();
        return vertices;
    }
    else {
        throw std::runtime_error("Unable to open file!");
    }
}

int get_edges_from_file(const std::string& file_name) {
    std::ifstream file(file_name);
    if (file.is_open()) {
        int edges;
        file.ignore(256, ' ');
        file >> edges;
        file.close();
        return edges;
    }
    else {
        throw std::runtime_error("Unable to open file!");
    }
}

class DirectedGraph {
private:
    int _vertices;
    int _edges;
    std::map<int, std::vector<int>> _dict_in;
    std::map<int, std::vector<int>> _dict_out;
    std::map<std::pair<int, int>, int> _dict_cost;

public:
    DirectedGraph(int no_vertices) : _vertices(no_vertices), _edges(0) {
        for (int i = 0; i < no_vertices; ++i) {
            _dict_in[i] = {};
            _dict_out[i] = {};
        }
    }

    void menu() const {
        std::cout << "1. Add vertex\n"
            "2. Remove vertex\n"
            "3. Add edge\n"
            "4. Remove edge\n"
            "5. Display number of vertices\n"
            "6. Display the set of vertices\n"
            "7. Verify edge\n"
            "8. Get in degree\n"
            "9. Get out degree\n"
            "10. Parse outbound edges\n"
            "11. Parse inbound edges\n"
            "12. Get cost of an edge\n"
            "13. Set cost of an edge\n"
            "14. Make a copy of the graph\n"
            "15. Write graph to a text file\n"
            "0. Exit\n";
    }

    void get_graph_from_file(const std::string& file_name) {
        std::ifstream file(file_name);
        if (file.is_open()) {
            std::string line;
            std::getline(file, line);
            int v1, v2, cost;
            while (file >> v1 >> v2 >> cost) {
                this->add_edge({ v1, v2 }, cost);
            }
            file.close();
        }
        else {
            throw std::runtime_error("Unable to open file!");
        }
    }

    void get_graph_from_file_format_2(const std::string& file_name) {
        std::ifstream file(file_name);
        if (file.is_open()) {
            int v1, v2, cost;
            while (file >> v1 >> v2 >> cost) {
                if (v2 == -1) {
                    this->add_vertex(v1);
                }
                else {
                    if (!this->is_vertex(v1)) {
                        this->add_vertex(v1);
                    }
                    if (!this->is_vertex(v2)) {
                        this->add_vertex(v2);
                    }
                    this->add_edge({ v1, v2 }, cost);
                }
            }
            file.close();
        }
        else {
            throw std::runtime_error("Unable to open file!");
        }
    }

    int get_number_of_vertices() const {
        return _vertices;
    }

    int get_number_of_edges() const {
        return _edges;
    }

    std::vector<int> parse_vertices() const {
        std::vector<int> vertices;
        for (const auto& entry : _dict_in) {
            vertices.push_back(entry.first);
        }
        return vertices;
    }

    bool is_edge(const std::pair<int, int>& edge) const {
        int v1 = edge.first;
        int v2 = edge.second;
        if (_dict_in.find(v1) != _dict_in.end()) {
            for (int out_vertex : _dict_out.at(v1)) {
                if (out_vertex == v2) {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_vertex(int vertex) const {
        return _dict_in.find(vertex) != _dict_in.end();
    }

    int get_in_degree(int vertex) const {
        if (is_vertex(vertex)) {
            return _dict_in.at(vertex).size();
        }
        throw std::invalid_argument("The vertex does not belong to the graph!");
    }

    int get_out_degree(int vertex) const {
        if (is_vertex(vertex)) {
            return _dict_out.at(vertex).size();
        }
        throw std::invalid_argument("The vertex does not belong to the graph!");
    }

    std::vector<int> parse_outbound_edges(int vertex) const {
        if (is_vertex(vertex)) {
            return _dict_out.at(vertex);
        }
        throw std::invalid_argument("The vertex does not belong to the graph!");
    }

    std::vector<int> parse_inbound_edges(int vertex) const {
        if (is_vertex(vertex)) {
            return _dict_in.at(vertex);
        }
        throw std::invalid_argument("The vertex does not belong to the graph!");
    }

    int get_cost(const std::pair<int, int>& edge) const {
        if (is_edge(edge)) {
            return _dict_cost.at(edge);
        }
        throw std::invalid_argument("The edge does not belong to the graph!");
    }

    void set_cost(const std::pair<int, int>& edge, int cost) {
        if (is_edge(edge)) {
            _dict_cost[edge] = cost;
        }
        else {
            throw std::invalid_argument("The edge does not belong to the graph!");
        }
    }

    void add_edge(const std::pair<int, int>& edge, int cost) {
        if (!is_edge(edge)) {
            int v1 = edge.first;
            int v2 = edge.second;
            if (!is_vertex(v1)) {
                throw std::invalid_argument("The first vertex does not belong to the graph!");
            }
            if (!is_vertex(v2)) {
                throw std::invalid_argument("The second vertex does not belong to the graph!");
            }
            _dict_in[v2].push_back(v1);
            _dict_out[v1].push_back(v2);
            _dict_cost[edge] = cost;
            ++_edges;
        }
        else {
            throw std::invalid_argument("The edge already exists!");
        }
    }

    void remove_edge(const std::pair<int, int>& edge) {
        if (is_edge(edge)) {
            int v1 = edge.first;
            int v2 = edge.second;
            auto& in_edges = _dict_in[v2];
            in_edges.erase(std::remove(in_edges.begin(), in_edges.end(), v1), in_edges.end());
            auto& out_edges = _dict_out[v1];
            out_edges.erase(std::remove(out_edges.begin(), out_edges.end(), v2), out_edges.end());
            _dict_cost.erase(edge);
            --_edges;
        }
        else {
            throw std::invalid_argument("The edge does not belong to the graph!");
        }
    }

    void add_vertex(int vertex) {
        if (!is_vertex(vertex)) {
            _dict_in[vertex] = {};
            _dict_out[vertex] = {};
            _vertices++;
        }
        else {
            throw std::invalid_argument("The vertex already exists!");
        }
    }

    void remove_vertex(int vertex) {
        if (is_vertex(vertex)) {
            for (int out_vertex : _dict_out[vertex]) {
                auto edge = std::make_pair(vertex, out_vertex);
                _dict_cost.erase(edge);
                auto& in_edges = _dict_in[out_vertex];
                in_edges.erase(std::remove(in_edges.begin(), in_edges.end(), vertex), in_edges.end());
                _edges--;
            }
            _dict_out[vertex].clear();
            for (int in_vertex : _dict_in[vertex]) {
                auto& out_edges = _dict_out[in_vertex];
                out_edges.erase(std::remove(out_edges.begin(), out_edges.end(), vertex), out_edges.end());
                _edges--;
            }
            _dict_in[vertex].clear();
            _dict_out.erase(vertex);
            _dict_in.erase(vertex);
            _vertices--;
        }
        else {
            throw std::invalid_argument("The vertex does not belong to the graph!");
        }
    }

    std::map<std::pair<int, int>, int> get_dict_cost() const {
        return _dict_cost;
    }
};

void write_graph_to_file(const DirectedGraph& graph, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& entry : graph.get_dict_cost()) {
            int vertex1 = entry.first.first;
            int vertex2 = entry.first.second;
            int cost = entry.second;
            file << vertex1 << " " << vertex2 << " " << cost << "\n";
        }
        for (int vertex : graph.parse_vertices()) {
            if (graph.get_in_degree(vertex) == 0 && graph.get_out_degree(vertex) == 0) {
                file << vertex << " -1\n";
            }
        }
        file.close();
    }
    else {
        throw std::runtime_error("Unable to open file!");
    }
}

DirectedGraph generate_random_graph(int no_vertices, int no_edges) {
    if (no_edges > (no_vertices * no_vertices)) {
        throw std::invalid_argument("Cannot create a graph with given number of vertices and edges!");
    }
    DirectedGraph graph(no_vertices);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_vertex(0, no_vertices - 1);
    std::uniform_int_distribution<> dis_cost(0, 100);
    while (no_edges > 0) {
        int v1 = dis_vertex(gen);
        int v2 = dis_vertex(gen);
        int cost = dis_cost(gen);
        if (!graph.is_edge({ v1, v2 })) {
            graph.add_edge({ v1, v2 }, cost);
            --no_edges;
        }
    }
    return graph;
}

int main() {
    DirectedGraph graph(0);
    while (true) {
        try {
            std::cout << "1. Create a random graph\n"
                "2. Read a graph from a file\n";
            int user_option;
            std::cin >> user_option;
            if (user_option == 1) {
                int no_vertices, no_edges;
                std::cout << "Enter the number of vertices: ";
                std::cin >> no_vertices;
                std::cout << "Enter the number of edges: ";
                std::cin >> no_edges;
                graph = generate_random_graph(no_vertices, no_edges);
                std::cout << "Graph successfully generated!\n";
                break;
            }
            else if (user_option == 2) {
                std::string file_name;
                std::cout << "Enter the name of the file: ";
                std::cin >> file_name;
                int file_format = 0;
                std::ifstream file(file_name);
                if (file.is_open()) {
                    std::string line;
                    std::getline(file, line);
                    file.close();
                    int spaceCount = 0;
                    for (char c : line) {
                        if (c == ' ') {
							spaceCount++;
						}
                    }
                    if (line.find("-1") != std::string::npos) {
                        file_format = 2;
                    }
                    else if (spaceCount == 1)
                        file_format = 1;
                    else {
                        file_format = 2;
                    }
                }
                if (file_format == 1) {
                    int vertices = get_vertices_from_file(file_name);
                    for (int i = 0; i < vertices; ++i) {
						graph.add_vertex(i);
					}
                    graph.get_graph_from_file(file_name);
                    std::cout << "Graph successfully read!\n";
                    break;
                }
                else if (file_format == 2) {
                    graph.get_graph_from_file_format_2(file_name);
                    std::cout << "Graph successfully read!\n";
                    break;
                }
            }
            else {
                std::cout << "Invalid option!\n";
            }
        }
        catch (const std::exception& error) {
            std::cerr << error.what() << std::endl;
        }
    }
    while (true) {
        try {
            graph.menu();
            int option;
            std::cout << ">> ";
            std::cin >> option;
            if (option == 1) {
                int user_vertex;
                std::cout << "Enter the vertex to be added: ";
                std::cin >> user_vertex;
                graph.add_vertex(user_vertex);
            }
            else if (option == 2) {
                int user_vertex;
                std::cout << "Enter the vertex to be removed: ";
                std::cin >> user_vertex;
                graph.remove_vertex(user_vertex);
            }
            else if (option == 3) {
                int end_point1, end_point2, user_cost;
                std::cout << "Enter the first endpoint of the edge: ";
                std::cin >> end_point1;
                std::cout << "Enter the second endpoint of the edge: ";
                std::cin >> end_point2;
                std::cout << "Enter the edge cost: ";
                std::cin >> user_cost;
                graph.add_edge({ end_point1, end_point2 }, user_cost);
            }
            else if (option == 4) {
                int end_point1, end_point2;
                std::cout << "Enter the first endpoint of the edge: ";
                std::cin >> end_point1;
                std::cout << "Enter the second endpoint of the edge: ";
                std::cin >> end_point2;
                graph.remove_edge({ end_point1, end_point2 });
            }
            else if (option == 5) {
                std::cout << "The number of vertices of the current graph: " << graph.get_number_of_vertices() << std::endl;
            }
            else if (option == 6) {
                auto vertices = graph.parse_vertices();
                for (auto vertex : vertices) {
                    std::cout << vertex << "\n";
                }
            }
            else if (option == 7) {
                int end_point1, end_point2;
                std::cout << "Enter the first endpoint of the edge: ";
                std::cin >> end_point1;
                std::cout << "Enter the second endpoint of the edge: ";
                std::cin >> end_point2;
                if (graph.is_edge({ end_point1, end_point2 })) {
                    std::cout << "(" << end_point1 << ", " << end_point2 << ") is an edge of the graph!" << std::endl;
                }
                else {
                    std::cout << "(" << end_point1 << ", " << end_point2 << ") is not an edge of the graph!" << std::endl;
                }
            }
            else if (option == 8) {
                int user_vertex;
                std::cout << "Enter the vertex for which to get the in degree: ";
                std::cin >> user_vertex;
                std::cout << "The in degree of the vertex " << user_vertex << " is: " << graph.get_in_degree(user_vertex) << std::endl;
            }
            else if (option == 9) {
                int user_vertex;
                std::cout << "Enter the vertex for which to get the out degree: ";
                std::cin >> user_vertex;
                std::cout << "The out degree of the vertex " << user_vertex << " is: " << graph.get_out_degree(user_vertex) << std::endl;
            }
            else if (option == 10) {
                int user_vertex;
                std::cout << "Enter the vertex: ";
                std::cin >> user_vertex;
                auto outbound_edges = graph.parse_outbound_edges(user_vertex);
                for (auto edge: outbound_edges) {
                    std::cout << edge << "\n";
                }
            }
            else if (option == 11) {
                int user_vertex;
                std::cout << "Enter the vertex: ";
                std::cin >> user_vertex;
                auto inbound_edges = graph.parse_inbound_edges(user_vertex);
                for (auto edge : inbound_edges) {
					std::cout << edge << "\n";
				}
            }
            else if (option == 12) {
                int end_point1, end_point2;
                std::cout << "Enter the first endpoint of the edge: ";
                std::cin >> end_point1;
                std::cout << "Enter the second endpoint of the edge: ";
                std::cin >> end_point2;
                std::cout << "The cost of (" << end_point1 << ", " << end_point2 << ") is: " << graph.get_cost({ end_point1, end_point2 }) << std::endl;
            }
            else if (option == 13) {
                int end_point1, end_point2, cost;
                std::cout << "Enter the first endpoint of the edge: ";
                std::cin >> end_point1;
                std::cout << "Enter the second endpoint of the edge: ";
                std::cin >> end_point2;
                std::cout << "Enter the new cost for the edge: ";
                std::cin >> cost;
                graph.set_cost({ end_point1, end_point2 }, cost);
                std::cout << "Cost set successfully!" << std::endl;
            }
            else if (option == 14) {
                // DirectedGraph graph_copy = graph.copy_graph();
                std::cout << "Graph copied!" << std::endl;
            }
            else if (option == 15) {
                std::string filename;
                std::cout << "Enter the file name: ";
                std::cin >> filename;
                write_graph_to_file(graph, filename);
            }
            else if (option == 0)
                break;
            else
                std::cout << "Invalid option!\n";
        }
        catch (const std::exception& error) {
            std::cout << error.what() << std::endl;
        }
    }
    return 0;
}
