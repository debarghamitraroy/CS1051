edge(1, 2).
edge(1, 3).
edge(2, 4).
edge(4, 6).
edge(6, 2).
edge(2, 5).
edge(3, 2).
edge(3, 5).
edge(3, 7).
edge(6, 7).

bfs(Start, Traversal) :-
    bfs_queue([Start], [], Traversal).

bfs_queue([], Visited, Traversal) :-
    reverse(Visited, Traversal).

bfs_queue([Node|RestQueue], Visited, Traversal) :-
    member(Node, Visited), !,
    bfs_queue(RestQueue, Visited, Traversal).

bfs_queue([Node|RestQueue], Visited, Traversal) :-
    findall(Next, edge(Node, Next), Neighbors),
    append(RestQueue, Neighbors, NewQueue),
    bfs_queue(NewQueue, [Node|Visited], Traversal).