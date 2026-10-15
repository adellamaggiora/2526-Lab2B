#include <graph.h>
#include <hash.h>
#include <components.h>
#include <error-manager.h>



void add_raw_edge(grafo *graph, int u, int v, int w)
{
    // se u e v non appartengono alla stessa cCon allora devo aggiungere tale arco alla MSF
    int u_cCon = graph->cCon[u];
    int v_cCon = graph->cCon[v]; 
    if (u_cCon != v_cCon)
    {
        /**
         *  aggiunta di (u,v,w) alla tabella hash gHash
            aggiunta di u alla lista vicini[v] e di v alla lista dei vicini[u]
            aggiornamento dell'array cCon delle componenti connesse
         */
        arco *edge = insert_edge_into_hash_table(u, v, w, graph->gHash, graph->gHash_length);
        add_vicini(graph, edge);
        merge_connected_components(graph, u, v);
    }

    else 
    {
        // dopo aver aggiunto l'arco si deve verificare se il nuovo arco
        // deve essere inserito nella MSF eseguendo le seguenti operazioni:

        /**
         *  si cerca l'unico cammino che collega u e v all'interno dell'albero 
         *  che ricopre la componente C (si tratta di un cammino formato tutti 
         *  di archi della MSF, si utilizzi vicini per costruirlo ma considerando
         *  solo gli archi con msf==true) all'interno di tale cammino si cerca
         *  l'arco (x,y,v) di peso massimo: 
         *  se v>w allora si elimina (x,y,v) dalla MSF e si aggiunge (u,v,w)
         */

        /**
         * Rispetto al caso precedente l'array cCon non deve essere modificato, 
         *  ma attenzione che per eliminare (x,y,v) dalla MSF il flag msf 
         *  deve essere posto a false in tutte le rappresentazioni dell'arco
         */


        
    }
    

}


void remove_edge()
{

}
