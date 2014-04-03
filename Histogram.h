#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include<string>
#include<istream>
#include<ostream>

typedef std::string keydata;
typedef unsigned int valdata;

class Histogram{
	private:
		struct TreeNode{
			TreeNode *left, *right, *parent;
			keydata key;
			valdata val;
			TreeNode() {};
			TreeNode(const keydata &key, TreeNode *par) { this->left=0, this->right=0, this->key=key; this->parent=par; this->val=0; };
			bool operator<(TreeNode const &tn) { return this->key < tn.key; };
			~TreeNode();
			void print(std::ostream&);
			TreeNode* getPrev();
			TreeNode* getNext();
			TreeNode* getMin();
			TreeNode* getMax();
			void clear() { this->parent=0; this->left=0; this->right=0; };
			bool isLeaf(){ return (this->left==0 && this->right==0); };
		};
		TreeNode* getNodeByKey(const keydata&) const;
		TreeNode* copyTree(const TreeNode* tn) const;
		TreeNode* createNewNode(const keydata&);
		void deleteNode(TreeNode*);
		TreeNode* root;
		valdata& operator[](const keydata&);
		void swapNodes(TreeNode*, TreeNode*);
	public:
		Histogram();
		Histogram(const Histogram& h2) {this->root = h2.copyTree(h2.root); };
		~Histogram();
		// dodawanie - suma, elementy w obydwoch drzewach, jeśli te same klucze - suma
		Histogram operator+(const Histogram&);
		// mnozenie - czesc wspolna, jesli rozne klucze to minimum
		Histogram operator*(const Histogram&);
		// odejmowanie - dla kazdego z pierwszego odejmujemy wartosc tego w drugim
		Histogram operator-(const Histogram&);
		friend std::ostream& operator<<(std::ostream&, Histogram const&);
		friend Histogram& operator<<(Histogram&, keydata const&);
		friend Histogram& operator<<(Histogram&, std::istream &);

		void setValue(const keydata&, const valdata&);
		void addValue(const keydata&, const valdata&);
		void subValue(const keydata&, const valdata&);
		valdata getValue(const keydata&);
		
		class Iterator{
			private:
				TreeNode *cur;
			public:
				Iterator(){ this->cur = 0; };
				Iterator(TreeNode* tn){ this->cur = tn; };
				Iterator& operator++(){ if (this->cur) this->cur = this->cur->getNext(); return *this; };
				Iterator& operator--(){ if (this->cur) this->cur = this->cur->getPrev(); return *this; };
				bool operator!=(const Iterator& it) { return this->cur != it.cur; };
				valdata getVal(){ return this->cur->val; };
				keydata getKey(){ return this->cur->key; };
		};

		Iterator begin() const { return root != 0 ? Iterator(root->getMin()) : 0; };
		Iterator end() const { return Iterator(0); };
};

#endif
