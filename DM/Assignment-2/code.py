from collections import defaultdict, deque


class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = defaultdict(list)

    def add_edge(self, u, v):
        self.graph[u].append(v)
        self.graph[v].append(u)

    def is_connected(self):
        visited = [False] * self.V
        start = -1
        for i in range(self.V):
            if len(self.graph[i]) > 0:
                start = i
                break
        if start == -1:
            return True

        queue = deque([start])
        visited[start] = True
        while queue:
            u = queue.popleft()
            for v in self.graph[u]:
                if not visited[v]:
                    visited[v] = True
                    queue.append(v)

        for i in range(self.V):
            if not visited[i] and len(self.graph[i]) > 0:
                return False
        return True

    def is_eulerian(self):
        if not self.is_connected():
            return 0
        odd_degree = sum(1 for i in range(self.V) if len(self.graph[i]) % 2 != 0)
        if odd_degree == 0:
            return 2
        elif odd_degree == 2:
            return 1  # Euler path but not circuit
        else:
            return 0  # not Eulerian

    def print_euler_tour(self):
        status = self.is_eulerian()
        if status == 0:
            print("Graph is NOT Eulerian!")
            return
        elif status == 2:
            print("Graph has an Euler Circuit.\n")
        else:
            print("Graph has an Euler Path (but not a circuit).\n")

        print("--- Running Hierholzer's Algorithm ---")
        self._hierholzer()

    def _find_cycle_from(self, start, graph_copy):
        """
        Walk from `start` consuming edges (choose first neighbor each time)
        until we revisit a vertex already in path. Return the cycle as
        a list like [v, ..., v]. Edges are removed from graph_copy in place.
        """
        path = [start]
        while True:
            cur = path[-1]
            if not graph_copy[cur]:
                return None
            nxt = graph_copy[cur].pop(0)
            if cur in graph_copy[nxt]:
                graph_copy[nxt].remove(cur)
            if nxt in path:
                idx = path.index(nxt)
                cycle = path[idx:] + [nxt]
                return cycle
            else:
                path.append(nxt)

    def _hierholzer(self):
        graph_copy = {i: list(self.graph[i]) for i in range(self.V)}
        start = 0
        for i in range(self.V):
            if len(graph_copy[i]) > 0:
                start = i
                break

        initial_cycle = self._find_cycle_from(start, graph_copy)
        if not initial_cycle:
            print("\nFinal Euler Tour: []")
            return

        print("Splicing Cycle:", initial_cycle[::-1])
        main_cycle = initial_cycle[:]

        while True:
            idx_with_extra = None
            for idx in range(len(main_cycle) - 1):
                v = main_cycle[idx]
                if graph_copy[v]:
                    idx_with_extra = idx
                    break

            if idx_with_extra is None:
                break

            v = main_cycle[idx_with_extra]
            new_cycle = self._find_cycle_from(v, graph_copy)
            if not new_cycle:
                break

            print("Splicing Cycle:", new_cycle)

            main_cycle = (
                main_cycle[:idx_with_extra]
                + new_cycle
                + main_cycle[idx_with_extra + 1 :]
            )

        print("\nFinal Euler Tour:", main_cycle)


# USER INPUT SECTION

if __name__ == "__main__":
    V = int(input("Enter number of vertices: "))
    E = int(input("Enter number of edges: "))

    g = Graph(V)
    print("Enter edges (format: u v):")
    for _ in range(E):
        u, v = map(int, input().split())
        g.add_edge(u, v)

    print()
    g.print_euler_tour()
