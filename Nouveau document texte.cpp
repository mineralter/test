// in mj version ==== start 
//#include "/home/minju/ConP_Step_Path-Disaster2017/include/Initial.h"
// in mj version ==== end

// in cc version ==== start 
#include "Initial.h"
// in cc version ==== end


using namespace std;



int eIndexTableP[NUM_NODE][NUM_NODE];
int DCeIndexTableP[NUM_NODE];
int DC_Disa_Affected[NUM_DC][NUM_DISASTER];
int Req_Source_Disa[NUM_REQUEST][NUM_DISASTER];



void InitializeTopo()
{
	// Initialisation de eIndexTableP
	for(int col=0; col < graph.numNodes; col++)
	{
		for(int row=0; row < graph.numNodes; row++)
		{
			eIndexTableP[row][col] = -1;
		}
	}

	// Initialisation de la classe node
	for(int i=0; i<graph.numNodes; i++)
	{
		// the nodes' ID starts from 0 to graph.numNodes-1
		node[i].ID = i;
		node[i].Input_listsize = 0;
		node[i].Output_listsize = 0;
		for(int j=0; j < graph.numNodes; j++)
		{
			node[i].InputIDlist[j] = -1;
			node[i].OutputIDlist[j] = -1;
			node[i].InputVarlist[j] = -1;
			node[i].OutputVarlist[j] = -1;
		}
	}


	int nEIndex = 0;
	for(int col=0; col < graph.numNodes; col++)
	{
		for(int row=0; row < graph.numNodes; row++)
		{
			if(graph.Adjacent_Matrix[row][col] == 1)
			{
				eIndexTableP[row][col] = nEIndex;
				nEIndex++;
			}
		}
	}

	// remplissage de OutputIDlist et de OutputVarlist
	for(int i=0; i<graph.numNodes; i++)
	{
		int row = i;
		int output_size = 0;
		for(int col=0; col<graph.numNodes; col++)
		{
			if(eIndexTableP[row][col]!=-1)
			{
				node[i].OutputIDlist[output_size] = col;
				node[i].OutputVarlist[output_size] = eIndexTableP[row][col];
				output_size++;
			}
		}
		node[i].Output_listsize = output_size;
	}

	// remplissage de inputIDlist et de inputVarlist
	for(int i=0; i<graph.numNodes; i++)
	{
		int col = i;
		int input_size = 0;
		for(int row=0; row<graph.numNodes; row++)
		{
			if(eIndexTableP[row][col]!=-1)
			{
				node[i].InputIDlist[input_size] = row;
				node[i].InputVarlist[input_size] = eIndexTableP[row][col];
				input_size++;
			}
		}
		node[i].Input_listsize = input_size;
	}


	   for(int d=0; d<graph.numDCs; d++)
         {
        for(int z=0; z<graph.numDisaster; z++)
     {
			DC_Disa_Affected[d][z]=0;
			int real_dc=graph.DC[d];
			int in_all_links=0;
			int out_all_links=0;
          for(int k=0; k<node[real_dc].Output_listsize; k++)
           {
             int  col= node[real_dc].OutputIDlist[k];
             if(graph.Disaster[z][real_dc][col]<1e-4)
             out_all_links=out_all_links+1;
           }

           for(int g=0; g<node[real_dc].Input_listsize; g++)
           {
             int  coll= node[real_dc].InputIDlist[g];
             if(graph.Disaster[z][real_dc][coll]<1e-4)
             in_all_links=in_all_links+1;
           }

           if(in_all_links+out_all_links<1e-4)
        DC_Disa_Affected[d][z]=1;

           }
            }





       for(int z=0; z<graph.numDisaster; z++)
             if(graph.Disaster[z][source_node][col]<1e-4)
              Source_afftected=0;
           }

           if(Source_afftected>1e-4)
              Req_Source_Disa[r][z]=1;
       }
       }
}



void  InitialDCeIndexTable()
{
    for(int i=0; i<graph.numNodes; i++)
	{
	    if(graph.DC_index[i]>1e-4)
	      {
	      int realdc;
	      for(int d=0; d<graph.numDCs; d++)
	       {
	         if(graph.DC[d]==i)
	         {
	          realdc=d;
	          break;
	         }
	         }
	DCeIndexTableP[i]=realdc;
	}
    }
}


