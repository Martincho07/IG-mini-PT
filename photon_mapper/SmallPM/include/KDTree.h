/*********************************************************************************
Copyright (C) 2014 Adrian Jarabo (ajarabo@unizar.es)
Copyright (C) 2014 Diego Gutierrez (diegog@unizar.es)
All rights reserved.

This is an educational Ray Tracer developed for the course 'Informatica Grafica'
(Computer Graphics) tought at Universidad de Zaragoza (Spain). As such, it does not 
intend to be fast or general, but just to provide an educational tool for undergraduate
students. 

This software is provided as is, and any express or implied warranties are disclaimed.
In no event shall copyright holders be liable for any damage.
**********************************************************************************/
#ifndef _KDTREE_H_
#define _KDTREE_H_

/*********************************************************************************
This code has been adapted from Adolfo Munoz's Mjolnir-RT, developed at Universidad 
de Zaragoza (Spain).
Particularly, the functions to find the N-closest nearest neighbors have been added 
to the original code.
**********************************************************************************/
#include <vector>
#include <list>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <limits>

#ifndef Real
#define Real float
#endif

using namespace std;

template <class T, unsigned int N>
class KDTree
{
public:
	class Node
	{
	private:
		int axis;
		std::vector<Real> p;
		T d;
	public:
		Node() :p(N),axis(-1) {}
		Node(const std::vector<Real>& _p, const T& _data) : p(_p), d(_data),axis(-1) { if (_p.size()!=N) throw("Wrong dimension number in kd-tree"); }
		const std::vector<Real>& point() const {return p;}
		const T& data() const { return d; }

	friend class KDTree;
	};

private:
	list<Node> nodes;
	std::vector<Node> balanced;

public:
	KDTree() {}
	
	void clear(){ nodes.clear(); balanced.clear(); }
	void store(const std::vector<Real>& point, const T& data) { nodes.push_back(Node(point,data)); }
private:
	static void median_split(std::vector<Node>& p, int start, int end, int median, int axis);
	static void balanceSegment(std::vector<Node>& pbal, std::vector<Node>& porg, int index, int start, int end, const std::vector<Real>& bbmin, const std::vector<Real>& bbmax);

public:
	void balance();

	static Real distance(const std::vector<Real>& p1, const std::vector<Real>& p2)
	{
		Real sol2 = 0.0;
		for (int i=0;i<N;i++) sol2+=(p1[i]-p2[i])*(p1[i]-p2[i]);
		return sqrt(sol2);
	}

private:
	int closest(const std::vector<Real>& p, int index, int best) const;
	void find(const std::vector<Real>& p, int index, Real radius, list<const Node*> &nodes) const;
	void find(const std::vector<Real>& p, int index, int nb_elements, float &dist_worst, std::vector<const Node*> &nodes, std::vector<pair<int,float> > &dist) const;
	//I've removed static for compiling problems 
	//static class HeapComparison
	class HeapComparison
	{
	public:
		bool operator()(const pair<int,float> &val1, const  pair<int,float> &val2)const
		{
			return val1.second < val2.second;
		}
	};
	void update_heap_nodes(const Node &node, const float distance, int nb_elements, 
									std::vector<const Node*> &nodes, std::vector<pair<int,float> > &dist)const;
public:
	//========================================================================================================
	// Fixed Radius
	int find(const std::vector<Real>& p, Real radius, list<const Node*>* nodes) const
	{
		if (nodes)
		{
			find(p,1,radius,*nodes);
			return nodes->size();
		}
		else
		{
			list<const Node*> local_nodes;
			find(p,1,radius,local_nodes);
			return local_nodes.size();
		}
	}
	//========================================================================================================
	// Nearest Neighbor search
	void find(const std::vector<Real>& p, int nb_elements, std::vector<const Node*> &nodes, Real &max_distance) const
	{
		nodes.clear(); 
		max_distance = std::numeric_limits<Real>::infinity();
		
		if( balanced.empty() )
			return;

		nodes.reserve(nb_elements);
		std::vector<pair<int,float> > dist; dist.reserve(nb_elements);

		find(p, 1, nb_elements, max_distance, nodes, dist);
	}
	const Node& find(const std::vector<Real>& p) const
	{ return balanced[closest(p,1,1)];}

	inline const Node& operator[](const unsigned int idx)const
	{
		#ifdef _SAFE_CHECK_		
		if ( idx > balanced.size()-1) throw("Out-of-range");
		#endif 
		
		return balanced[idx];
	}
	inline int nb_elements()const{ return balanced.size(); }
	inline bool is_empty()const{ return balanced.empty(); }

};
//--------------------------------------------------------------------------------------------------
//Private Find(radius)
template <class T, unsigned int N >
void KDTree<T,N>::find(const std::vector<Real>& p, int index, Real radius, list<const Node*>& nodes) const
	{ 
		//We check if our node enters
		if (distance(balanced[index].point(),p)<radius) { nodes.push_back(&balanced[index]); }
		//Now we check that this is not a leaf node
		if (index<((balanced.size()-1)/2))
		{
			Real distaxis=p[balanced[index].axis] - balanced[index].point()[balanced[index].axis];
			if (distaxis < 0.0) // left node first
			{
				find(p,2*index,radius,nodes);
				if (radius > fabs(distaxis)) // Maybe we can find more nodes on the other child
					find(p,2*index + 1,radius,nodes);
			}
			else //right node first
			{
				find(p,2*index + 1,radius,nodes);
				if (radius > fabs(distaxis)) // Maybe we can find more nodes on the other child
					find(p,2*index,radius,nodes);
			}
		}	
	}


//
//--------------------------------------------------------------------------------------------------
//Private Find(N-Nearest Neighbors)
template <class T, unsigned int N>
void KDTree<T,N>::update_heap_nodes(const Node &node, const float distance, int nb_elements, 
									std::vector<const Node*> &nodes, std::vector<pair<int,float> > &dist)const
	{
		// If there's still buffer for  more, don't bother with heaps...
		if( nodes.size() < nb_elements )
		{
			dist.push_back(pair<int,float>(nodes.size(), distance));
			nodes.push_back(&node); 

			//...unless you've reach max size, then prepare the heap...
			if( nodes.size() == nb_elements )
				std::make_heap(dist.begin(), dist.end(), HeapComparison());
		}
		else
		{
			int idx = dist.front().first;
			nodes[idx] = &node;			
			// Pop removed element
			pop_heap(dist.begin(), dist.end(), HeapComparison()); dist.pop_back();
			// Push new one
			dist.push_back(pair<int,float>(idx, distance)); push_heap(dist.begin(), dist.end(), HeapComparison());
		}
		//if( !(nodes.size() < nb_elements) )
		//{	nodes.pop_back();dist.pop_back(); }
		//
		//nodes.push_back(&node);
		//dist.push_back(distance);

		//for(int j=0; j<nodes.size(); ++j)
		//for(int i=0; i<nodes.size()-1; ++i)
		//{
		//	if( dist[i] > dist[i+1] )
		//	{
		//		const Node* aux_node = nodes[i];
		//		nodes[i] = nodes[i+1];
		//		nodes[i+1] = aux_node;
		//		float aux_dist = dist[i];
		//		dist[i] = dist[i+1];
		//		dist[i+1] = aux_dist;
		//	}
		//}
	}
template <class T, unsigned int N>
void KDTree<T,N>::find(const std::vector<Real>& p, int index, int nb_elements, float &dist_worst, 
					   std::vector<const Node*> &nodes, std::vector<pair<int,float> > &dist) const
	{ 
		Real aux;
		//We check if our node is better
		if ((aux=distance(balanced[index].point(),p))<dist_worst)
		{	
			update_heap_nodes(balanced[index], aux, nb_elements, nodes, dist); 
			dist_worst = (nodes.size()<nb_elements)? numeric_limits<float>::infinity():dist.front().second; 
		}
		
		//Now we check that this is not a leaf node
		if (index<((balanced.size()-1)/2))
		{
			Real distaxis=p[balanced[index].axis] - balanced[index].point()[balanced[index].axis];
			//if( dist_worst < fabs(distaxis) )
			//	return;

			if (distaxis < 0.0) // left node first
			{
				find(p,2*index,nb_elements,dist_worst,nodes, dist);
				if (dist_worst > fabs(distaxis)) // Maybe we can find more nodes on the other child
					find(p,2*index + 1,nb_elements,dist_worst,nodes, dist);
			}
			else //right node first
			{
				find(p,2*index + 1,nb_elements,dist_worst,nodes, dist);
				if (dist_worst > fabs(distaxis)) // Maybe we can find more nodes on the other child
					find(p,2*index,nb_elements,dist_worst,nodes, dist);
			}
		}	
  	}

//--------------------------------------------------------------------------------------------------
// Closest
template <class T, unsigned int N >
int KDTree<T,N>::closest(const std::vector<Real>& p, int index, int best) const
	{ 
		int sol=best;
		Real distbest=distance(p,balanced[best].point());
		Real aux;
		//We check if our node is better
		if ((aux=distance(balanced[index].point(),p))<distbest) { sol=index; distbest=aux; }
		//Now we check that this is not a leaf node
		if (index<((balanced.size()-1)/2))
		{
			Real distaxis=p[balanced[index].axis] - balanced[index].point()[balanced[index].axis];
			if (distaxis < 0.0) // left node first
			{
				int candidate=closest(p,2*index,sol);
				if ((aux=distance(balanced[candidate].point(),p))<distbest) { sol=candidate; distbest=aux; }
				if (distbest > fabs(distaxis)) // Maybe the best solution is on the other side
				{
					candidate=closest(p,2*index + 1,sol);
					if ((aux=distance(balanced[candidate].point(),p))<distbest) { sol=candidate; distbest=aux; }
				}			
			}
			else //right node first
			{
				int candidate=closest(p,2*index+1,sol);
				if ((aux=distance(balanced[candidate].point(),p))<distbest) { sol=candidate; distbest=aux; }
				if (distbest > fabs(distaxis)) // Maybe the best solution is on the other side
				{
					candidate=closest(p,2*index,sol);
					if ((aux=distance(balanced[candidate].point(),p))<distbest) { sol=candidate; distbest=aux; }
				}			
			}
		}
		return sol;	
	}


	#define myswap(array,a,b) { Node aux=(array)[(a)]; (array)[(a)]=(array)[(b)]; (array)[(b)]=aux;}

//--------------------------------------------------------------------------------------------------
//Balance Tree
template <class T, unsigned int N >
void KDTree<T,N>::median_split(std::vector<Node>& p, int start, int end, int median, int axis)
	{
		int left=start;
		int right=end;

		while(right>left)
		{
			Real v = p[right].point()[axis];
			int i=left-1;
			int j=right;
			for(;;) {
				while(v>p[++i].point()[axis]);
				while(v<p[--j].point()[axis] && j>left);
				if(i>=j)
					break;
				myswap(p, i, j);
			}

			myswap(p,i,right);
			if(i>=median)
				right=i-1;
			if(i<=median)
				left=i+1;
		}
	}

template <class T, unsigned int N >
void KDTree<T,N>::balanceSegment(std::vector<Node>& pbal, std::vector<Node>& porg, int index, int start, int end, const std::vector<Real>& bbmin, const std::vector<Real>& bbmax)
	{
		int median=1;
		while((4*median)<=(end-start+1))
			median += median;

		if ((3*median)<=(end-start+1)) {
			median += median;
			median += start-1;
		} else
			median = end-median+1;

		// elegimos el eje más apropiado...
		int axis=0;
		for (int i=1;i<N;i++)
			if ((bbmax[i]-bbmin[i]) > (bbmax[axis]-bbmin[axis]))
				axis = i;

		// partimos el bloque de fotones por la mediana	
		median_split(porg, start, end, median, axis);

		pbal[index]=porg[median];
		pbal[index].axis=axis;

		// y por último balanceamos recursivamente los bloques izquierdo y derecho
		if(median>start) {
			// balancear el segmento izquierdo
			if(start<median-1) {
				std::vector<Real> newbbmax=bbmax;
				newbbmax[axis]=pbal[index].point()[axis];
				balanceSegment(pbal, porg, 2*index, start, median-1,bbmin,newbbmax);
			} else {
				pbal[2*index]=porg[start];
			}
		}

		if(median<end) {
			// balancear el segmento derecho
			if(median+1<end) {
				std::vector<Real> newbbmin=bbmin;
				newbbmin[axis]=pbal[index].point()[axis];
				balanceSegment(pbal, porg, 2*index+1, median+1, end,newbbmin,bbmax);
			} else {
				pbal[2*index+1]=porg[end];
			}
		}
	}

template <class T, unsigned int N >
void KDTree<T,N>::balance()
{
	{
		std::vector<Node> aux(nodes.size()+1);
		balanced.resize(nodes.size()+1);
		int i;
		std::vector<Real> bbmax=nodes.front().point();
		std::vector<Real> bbmin=nodes.front().point();
		//balanced[0] and aux[0] do not contain any useful information
		for (i=1;!(nodes.empty());i++,nodes.pop_front())
		{
			aux[i]=nodes.front();
			for (int j=0;j<N;j++)
			{
				if (aux[i].point()[j] < bbmin[j]) bbmin[j]=aux[i].point()[j];
				if (aux[i].point()[j] > bbmax[j]) bbmax[j]=aux[i].point()[j];
			}
		}
		nodes.clear();

		KDTree<T,N>::balanceSegment(balanced, aux, 1, 1, balanced.size()-1,bbmin,bbmax);
	}
}


#endif
