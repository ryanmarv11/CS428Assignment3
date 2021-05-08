

#include <vector>
#include <string>
#include <list>
#include <queue>
#include <utility>
#include <stdio.h>
#include <iostream>
#include <iomanip>

// Number of vertices in the graph
#define V 0 //INSERT NUMBER OF NODES HERE

#define INT_MAX 9999999

#define node_t int
#define dist_t int
#define path_t std::vector< int >
#define pair_t std::pair< dist_t, node_t >



class slow_queue {
private:
    std::list< pair_t >* rep;
public:
    slow_queue() {
        rep = new std::list< pair_t >();
    }

    ~slow_queue() {
        delete rep;
    }

    void add( pair_t p ) {
        rep->push_back( p );
    }

    bool empty() { return rep->empty(); }

#define EMPTY pair_t( -1, INT_MAX )
    pair_t poll() {
        /* Empty check - return null */
        if( rep->empty() ) {
            return EMPTY;
        }

        /* Take the first element, then increment the iterator */
        std::list< pair_t >::iterator itr = rep->begin();
        pair_t min = (*itr);
        itr++;

        /* Iterate over the rest list, finding the least element */
        for( ; itr != rep->end(); ++itr ) {
            /* If the dist is less in this element, assign it to min */
            if( (*itr).first < min.first ) {
                min = *itr;
            }
        }

        /* Remove the min element */
        for( itr = rep->begin(); itr != rep->end(); ++itr ) {
            /* Find and erase min */
            if( (*itr).second == min.second ) {
                rep->erase( itr );
                break;
            }
        }

        /* Return the element with the shortest distance */
        return min;
    }

    void decrease_key( node_t n, dist_t d ) {
        /* Find the node in the queue */
        std::list< pair_t >::iterator itr = rep->begin();
        for( ; itr != rep->end(); ++itr ) {
            /* If the dist is less in this element, assign it to min */
            if( (*itr).second == n ) {
                (*itr).first = d;
            }
        }
    }
};

/*creates outline for output */
void header() {
    std::cout << std::left << std::setw(10) << "step";
    std::cout << std::left << std::setw(10) << "N'";
    for( int i = 0; i < V; ++i ) {
        std::cout << std::left << std::setw(10) << i;
    }
}


bool contains( std::vector<node_t> v, int num ) {
    for( int i = 0; i < v.size(); ++i ) {
        if( v[i] == num ) {
            return true;
        }
    }
    return false;
}


//actually does the printing
void output( int* dist, int* prev, std::vector< node_t > used ) {
    std::cout << std::left << std::setw(10) << used.size() - 1;
    int i = 0;
    for( ; i < used.size(); ++i ) {
        std::cout << used[i];
    }
    for( int j = 0; j < (V-i) + 2; ++i ) {
        std::cout << " ";
    }


    for( int i = 0; i < V; ++i ) {
        if( !contains( used, i ) ) {
            if( dist[i] == INT_MAX ) {
                std::cout << std::left << std::setw(10) << "inf";
            } else {
                std::string s = std::to_string( dist[i] );
                s += ",";
                s +=  std::to_string( prev[i] );
                std::cout << std::left << std::setw(10) << s;
            }
        } else {
            std::cout << std::setw(10) << "";
        }
    }

    std::cout << std::endl;
}

//made this but didn't end up using it
bool comp( pair_t p1, pair_t p2 ) {
    return p1.first > p2.first;
}

//Implements the algorithm given a graph (the adjacency matrix) and a source (the starting node)
void dijkstra(int graph[V][V], int src)
{
    // Distance to each node
    int dist[V];

    // Make vector of path
    int prev[V];

    // Initialize all distances as very large and stpSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }

    //The distance to the source from itself will always be 0, won't change
    dist[src] = 0;

    //made this but didn't use it
    auto compare = []( pair_t p1, pair_t p2 ) {
        return p1.first > p2.first;
    };

    // H = makequeue(V)
    slow_queue* H = new slow_queue();

    // Insert all the elements into the queue
    for( int i = 0; i < V; ++i ) {
        H->add( pair_t( dist[i], i ) );
    }

    // Make a used vector
    std::vector< node_t > used;

    while( !H->empty() ) {
        pair_t u = H->poll();

        int u_dist = u.first;
        int u_node = u.second;

        // Get edge (1D) array
        int* edges = graph[ u_node ];

        // For each other node in the graph
        for( int v = 0; v < V; ++v ) {
            if( u_node != v ) {
                int l_u_v = edges[v];
                if( dist[v] > u_dist + l_u_v ) {
                    dist[v] = u_dist + l_u_v;
                    prev[v] = u_node;
                    H->decrease_key( v, dist[v] );
                }
            }
        }

        used.push_back( u_node );
        output( dist, prev, used );

    }

    delete H;

}


int main()
{
#define M INT_MAX

    int graph[V][V] = {   }; //INSERT GRAPH HERE
    header();
    std::cout << std::endl << std::endl;
    dijkstra(graph, 0);

    return 0;
}
