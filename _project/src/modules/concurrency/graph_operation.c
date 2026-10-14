#include <graph.h>
#include <hash.h>



void add_raw_edge(grafo *graph, int u, int v, int w)
{
    // se u e v non appartengono alla stessa cCon allora devo aggiungere tale arco alla MSF
    if (graph->cCon[u] != graph->cCon[v])
    {
        /**
         *  aggiunta di (u,v,w) alla tabella hash gHash
            aggiunta di u alla lista vicini[v] e di v alla lista dei vicini[u]
            aggiornamento dell'array cCon delle componenti connesse: 
                i nodi di una delle componenti connesse devono infatti ricevere un nuovo identificatore.
         */
        arco *edge = insert_edge_into_hash_table(u, v, w, graph->gHash, graph->gHash_length);
        add_vicini(graph, edge);
        
    }

    else 
    {
        
    }
    

}


void remove_edge()
{

}
