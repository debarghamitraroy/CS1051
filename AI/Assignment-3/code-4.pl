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

dfs(Start, Traversal) :-
    dfs_helper(Start, [], Traversal).

dfs_helper(Node, Visited, [Node|Visited]) :-
    findall(Next, edge(Node, Next), Neighbors), 
    \+ (member(NextNode, Neighbors), \+ member(NextNode, Visited)).

dfs_helper(Node, Visited, Traversal) :-
    findall(Next, edge(Node, Next), Neighbors),
    member(NextNode, Neighbors), 
    \+ member(NextNode, Visited),
    dfs_helper(NextNode, [Node|Visited], Traversal).

