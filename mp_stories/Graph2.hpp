#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3

  std::list<std::string> path;
  std::unordered_map<std::string , std::string> parents;
  bool found = false;
  std::queue<std::string> q;
  q.push(start);
  parents.insert({start,start});
  while (!found) {
    std::string string = q.front();
    q.pop();
    std::list<std::reference_wrapper<E>> listEdge = incidentEdges(string);
    for (Edge & e : listEdge) {
      if (e.dest().key() == end) {
        found = true;
      }

      if (e.source().key() == end) {
        found = true;
      }

      if (parents.find(e.dest().key()) == parents.end()) {
        q.push(e.dest().key());
        parents.insert({e.dest().key(),e.source().key()});
      }

      if (parents.find(e.source().key()) == parents.end())
      {
        q.push(e.source().key());
        parents.insert({e.source().key(),e.dest().key()});
      }
    }
  }
  bool done = false;
  std::string temp = end;
  while (!done) {
    if (temp==start) {
      done = true;
    }
    
    path.push_front(temp);
    temp = parents.at(temp);
  }

  return path;
}
