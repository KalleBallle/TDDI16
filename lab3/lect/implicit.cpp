class Point {
public:
	int x, y;
	// ...
};

bool map[width][height];
// end DECL

bool bfs(Point from, Point to) {
	queue<Point> q; q.push(from);
	bool visited[width][height] = false;
	visited[from.x][from.y] = true;
	while (!q.empty()) {
		Point current = q.front(); q.pop();
		for (Point x : current.neighbors()) {
			if (c == current) return true;
			// Om 'x' ej besökt, markera och lägg på kö.
		}
	}
	return false;
}
// end BFS
