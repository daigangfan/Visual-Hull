#pragma once
#include <vector>
using namespace std;
const int MAXLAYER = 8;
enum Status{NONE,IN,ON,OUT};
struct Node {
	vector<Node*> children;
	Status status;
	int nLayer;
	int xmin, xmax, ymin, ymax, zmin, zmax;//index of points
	Node(int _xmin, int _xmax, int _ymin, int _ymax, int _zmin, int _zmax, int _layer) :
		xmin(_xmin), xmax(_xmax), ymin(_ymin), ymax(_ymax), zmin(_zmin), zmax(_zmax), status(Status::NONE), nLayer(_layer)
	{
		children.reserve(8);
	}
	int split(void);
	int getXmid();
	int getYmid();
	int getZmid();
};
int Node::split(void) {
	if (nLayer == MAXLAYER) return 0;
	int xmid = (xmin + xmax) >> 1, ymid = (ymin + ymax) >> 1, zmid = (zmin + zmax) >> 1;
	this->children.push_back(new Node(xmin, xmid, ymin, ymid, zmin, zmid,nLayer+1));
	this->children.push_back(new Node(xmin, xmid, ymin, ymid, zmid, zmax,nLayer+1));
	this->children.push_back(new Node(xmin, xmid, ymid, ymax, zmin, zmid,nLayer+1));
	this->children.push_back(new Node(xmin, xmid, ymid, ymax, zmid, zmax,nLayer+1));
	this->children.push_back(new Node(xmid, xmax, ymin, ymid, zmin, zmid,nLayer+1));
	this->children.push_back(new Node(xmid, xmax, ymin, ymid, zmid, zmax,nLayer+1));
	this->children.push_back(new Node(xmid, xmax, ymid, ymax, zmin, zmid,nLayer+1));
	this->children.push_back(new Node(xmid, xmax, ymid, ymax, zmid, zmax,nLayer+1));
	return 8;

}
int Node::getXmid() {
	return (xmin + xmax) >> 1;
}
int Node::getYmid() {
	return (ymin + ymax) >> 1;
}
int Node::getZmid() {
	return (zmin + zmax) >> 1;
}
struct octree {
	Node* rootNode;
	octree(int xres,int yres,int zres);

};
octree::octree(int xres,int yres,int zres) {
	rootNode = new Node(0,xres,0,yres,0,zres,1);

}