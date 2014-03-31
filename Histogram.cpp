#include"Histogram.h"

#include<iostream>

static valdata min(const valdata &a, const valdata &b)
{
	return a<b ? a : b;
}

Histogram::Histogram()
{
	this->root = 0;
}

Histogram::~Histogram()
{
	if (this->root!=0) delete this->root;
}

Histogram::TreeNode* Histogram::getNodeByKey(const keydata& key) const
{
	if (this->root == 0) return 0;
	Histogram::TreeNode* now = this->root;
	while (now!=0 && key!=now->key)
	{
		if (key == now->key) break;
		else if (key > now->key) now = now->right;
		else now = now->left;
	}
	return now;
}

valdata& Histogram::operator[](const keydata& key)
{
	TreeNode* node = this->getNodeByKey(key);
	if (node) return node->val;
	else return this->createNewNode(key)->val;
}

//! Creates new node in BST tree (if given key doesn't exist in tree, else don't know)
Histogram::TreeNode* Histogram::createNewNode(const keydata& key)
{
	if (this->root == 0)
	{
		this->root = new Histogram::TreeNode(key,(TreeNode*)0);
		return this->root;
	}
	Histogram::TreeNode *now = this->root;
	Histogram::TreeNode *last;
	while (now!=0)
	{
		last=now;
		if(key > now->key) now=now->right;
		else now=now->left;
	}
	Histogram::TreeNode *newNode = new Histogram::TreeNode(key,last);
	if (key > last->key) return last->right = newNode;
	else return last->left = newNode;
}

Histogram& operator<<(Histogram& h, keydata const &s)
{
	h[s]++;
	return h;
}

Histogram& operator<<(Histogram& h, std::istream &f)
{
	std::string s;
	while (f>>s)
	{
#ifdef DEBUG
		std::cerr << "Loaded: \'" << s << "\'.\n";
#endif
		h[s]++;
	}
	return h;
}

std::ostream& operator<<(std::ostream &os, Histogram const &h)
{
	os << "{";
	if (h.root) h.root->print(os);
	os << "}\n";
	return os;
}

void Histogram::TreeNode::print(std::ostream &os)
{
	if (this->left != 0)
	{
		this->left->print(os);
		os << ", ";
	}
	os << "\'" << this->key << "\': " << this->val; 
	if (this->right != 0)
	{
		os << ", ";
		this->right->print(os);
	}
}

Histogram::TreeNode* Histogram::TreeNode::getPrev()
{
	if (this->left != 0) return this->left->getMax();
	Histogram::TreeNode* now = this;
	while (now->parent && now->parent->left == now) now=now->parent;
	return now->parent;
}

Histogram::TreeNode* Histogram::TreeNode::getNext()
{
	if (this->right != 0) return this->right->getMin();
	Histogram::TreeNode* now = this;
	while (now->parent && now->parent->right == now) now=now->parent;
	return now->parent;
}

Histogram::TreeNode* Histogram::TreeNode::getMin()
{
	if (this->left == 0) return this;
	return this->left->getMin();
}

Histogram::TreeNode* Histogram::TreeNode::getMax()
{
	if (this->right == 0) return this;
	return this->right->getMax();
}

void Histogram::deleteNode(Histogram::TreeNode* tn)
{
	Histogram::TreeNode* replacement;
	if (tn->left == 0 && tn->right == 0) replacement=0;	// if leaf
	else if (tn->right == 0) replacement = tn->left;	// if node with left child
	else if (tn->left == 0) replacement = tn->right;	// if node with right child
	else throw "Not implemented yet.";	// if node with both children	TODO
	
	if (tn->parent != 0)	// if not root
	{
		if (tn->parent->left == tn) tn->parent->left=replacement;
		else tn->parent->right=replacement;

		if (replacement) replacement->parent=tn->parent;
	}
	else this->root = replacement;	// if root, update root

	delete tn;
	return;
}

// usuwanie w sensie czyszczenia pamięci - usuwa poddrzewo
Histogram::TreeNode::~TreeNode()
{
	if (this->left) delete this->left;
	if (this->right) delete this->right;
}

void Histogram::subValue(const keydata &key, const valdata &val)
{
	valdata &nodeval = (*this)[key];
	if (val < nodeval) nodeval = val;
	else nodeval = 0;
}

void Histogram::addValue(const keydata &key, const valdata &val)
{
	valdata &nodeval = (*this)[key];
	nodeval += val;
}

void Histogram::setValue(const keydata &key, const valdata &val)
{
	valdata &nodeval = (*this)[key];
	nodeval = val;
}
Histogram Histogram::operator+(const Histogram& h2)
{
	Histogram& h1=*this;
	Histogram res;

	Histogram::Iterator it1 = h1.begin();
	Histogram::Iterator it2 = h2.begin();

	while (it1 != h1.end() && it2 != h2.end())
	{
		keydata key1 = it1.getKey();
		keydata key2 = it2.getKey();
		if (key1 == key2)
		{
			valdata val = it1.getVal() + it2.getVal();
			res.setValue(key1,val);
			++it1;
			++it2;
		}
		else if (key1 < key2)
		{
			valdata val = it1.getVal();
			res.setValue(key1,val);
			++it1;
		}
		else
		{
			valdata val = it2.getVal();
			res.setValue(key2,val);
			++it2;
		}
	}

	while (it1 != h1.end()) { res.setValue(it1.getKey(),it1.getVal()); ++it1; };
	while (it2 != h2.end()) { res.setValue(it2.getKey(),it2.getVal()); ++it2; };	

	return res;
}

Histogram Histogram::operator-(const Histogram& h2)
{
	Histogram& h1=*this;
	Histogram res;

	Histogram::Iterator it1 = h1.begin();
	Histogram::Iterator it2 = h2.begin();

	while (it1 != h1.end() && it2 != h2.end())
	{
		keydata key1 = it1.getKey();
		keydata key2 = it2.getKey();

		if (key1 < key2)
		{
			res.setValue(key1,it1.getVal());
			++it1;
		}

		else if (key1 == key2)
		{
			valdata val1 = it1.getVal();
			valdata val2 = it2.getVal();
			if (val1 > val2) res.setValue(key1, val1-val2);
			++it1;
			++it2;
		}
		else ++it2;
	}

	while (it1 != h1.end()) { res.setValue(it1.getKey(),it1.getVal()); ++it1; };
	return res;
}


Histogram Histogram::operator*(const Histogram& h2)
{
	Histogram& h1=*this;
	Histogram res;

	Histogram::Iterator it1 = h1.begin();
	Histogram::Iterator it2 = h2.begin();

	while (it1 != h1.end() && it2 != h2.end())
	{
		keydata key1 = it1.getKey();
		keydata key2 = it2.getKey();
		if (key1 == key2)
		{
			valdata val = min (it1.getVal(), it2.getVal());
			res.setValue(key1,val);
			++it1;
			++it2;
		}
		else if (key1 < key2) ++it1;
		else ++it2;
	}
	return res;
}

