#pragma once
#include <iostream>
#include <fstream>
#include <initializer_list>
#include <memory> //для умных указателей
using namespace std;

template <typename T>
class BinarySearchTree;


template <typename T>
std::ofstream & operator << (std::ofstream & out, const BinarySearchTree<T> & tree) {

	tree.PreorderPrint(out, tree.GetRoot());
	return out;
};

template <typename T>
std::ostream & operator << (std::ostream & out, const BinarySearchTree<T> & tree) {

	tree.InorderPrint(out, tree.GetRoot());
	return out;
};

template <typename T>
std::istream & operator >> (std::istream & in, BinarySearchTree<T> & tree) {
	T value;
	int size;
	std::cout << "Size: ";
	in >> size;

	for (int i = 0; i < size; i++)
	{
		in >> value;
		tree.insert(value);
	}

	return in;
};

template <typename T>
std::ifstream & operator << (std::ifstream & out, const BinarySearchTree<T> & tree)
{
	tree.PreorderPrint(out, tree.GetRoot());
	return out;
};

template <typename T>
class BinarySearchTree 
{

private:
	struct Node;
	//Node * root_;
	unique_ptr <Node> root_;
	size_t size_;

	struct Node {
		Node(T value) : value_(value), left_(nullptr), right_(nullptr) {};
		~Node() {
			delete left_;
			delete right_;

		};
		T value_;
		//Node * left_;
		//Node * right_;
		unique_ptr<Node> left_;
		unique_ptr<Node> right_;
	};

public:


	BinarySearchTree() : root_(nullptr), size_(0) {}

	BinarySearchTree(const std::initializer_list<T> & list) : size_(0), root_(nullptr)
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			insert(*it);
		}
	};


	BinarySearchTree(const BinarySearchTree& tree) : size_(tree.size_), root_(nullptr)//конструктор копирования
	{
		root_ = copy(tree.root_);
	};

	//BinarySearchTree(BinarySearchTree&& tree)= default {};// конструктор перемещения


	BinarySearchTree(BinarySearchTree&& tree) : size_(tree.size_), root_(std::move(tree.root_))// конструктор перемещения
	{
		
	};

	

	Node* GetRoot() const
	{
		return root_;
	}


	//void PreorderPrint(std::ostream & str, Node* thisNode) const noexcept // прямой
	void PreorderPrint(std::ostream & str, unique_ptr<Node> thisNode) const noexcept // прямой
	{
		if (!thisNode)
		{

			return;
		}
		str << thisNode->value_ << " ";
		PreorderPrint(str, thisNode->left_);
		PreorderPrint(str, thisNode->right_);
	}

	//void InorderPrint(std::ostream & str, Node* thisNode) const noexcept // симметричный 
	void InorderPrint(std::ostream & str, unique_ptr<Node> thisNode) const noexcept // симметричный
	
	{
		if (!thisNode) 
		{

			return;
		}

		InorderPrint(str, thisNode->left_);
		str << thisNode->value_ << " ";
		InorderPrint(str, thisNode->right_);

	}

	auto size() const noexcept->size_t
	{

		return size_;
	};

	template <typename T>
	auto BinarySearhTree<T>::  insert(const T & value) noexcept -> bool {

		//Node* thisNode = root_;
		//Node* myNode = nullptr;

		unique_ptr<Node> thisNode = root_.get();
		unique_ptr<Node> myNode = nullptr;

		if (root_ == nullptr)
		{
			root_ = new Node(value);
			size_++;
			return true;
		}
		while (thisNode)
		{
			myNode = thisNode;
			if (value == myNode->value_)
			{
				return false;
			}
			else if (value < myNode->value_)
			{
				thisNode = myNode->left_;
			}
			else if (value > myNode->value_)
			{
				thisNode = myNode->right_;
			}
		}
		if (value < myNode->value_)
		{
			myNode->left_ = new Node(value);
		}
		else
		{
			myNode->right_ = new Node(value);
		};
		size_++;
		return true;
	}

	template <typename T>
	auto BinarySearchTree<T>:: find(const T & value) const noexcept -> const unique_ptr<Node> T
	{

		//Node* thisNode = root_;
		unique_ptr<Node> thisNode = root_.get();
	if (!root_)

	{
		return nullptr;
	}

	while (thisNode)
	{
		if (value < thisNode->value_)
		{
			thisNode = thisNode->left_;
		}
		else if (value > thisNode->value_)
		{
			thisNode = thisNode->right_;
		}
		else if (value == thisNode->value_)
		{
			return &thisNode->value_;
		}
	}

		return nullptr;
	}

		
		//auto comparison(const Node * firstnode_, const Node * secondnode_) const -> bool
	template <typename T>
	auto BinarySearchTree <T>:: comparison(const unique_ptr<Node> firstnode_, const unique_ptr<Node> secondnode_) const -> bool
	{

		if (firstnode_ == nullptr && secondnode_ == nullptr)
		{
			return(true);

		}

		else if (firstnode_ != nullptr && secondnode_ != nullptr)
		{
			return(
				comparison(firstnode_->left_, secondnode_->left_) &&
				comparison(firstnode_->right_, secondnode_->right_)
				);
		}
		else return(false);
	}

	
	template <typename T>
	friend auto BinarySearchTree<T>::remove(const T value_, unique_ptr<Node> node_) noexcept-> bool   // удаление узла,в котором находится объект со значением value
	{

		if (!node_)
			return false;

		else if (value_ < node_->value_)
			node_->left_ = remove(node_->left_, value_);


		else if (value_ > node_->value_)
			node_->right_ = remove(node_->right_, value_);

		else
		{
			if (node_->left_ = nullptr && node_->right_ == nullptr) // при сутствии узлов-потомков
				unique_ptr<Node> node_ = nullptr;

			else if (node_->left_ == nullptr) // при наличии одного узла-потомка
			{
				unique_ptr<Node> tmp_ = node_;
				node_ = node_->left_;
			}

			else if (node_->right_ == nullptr)
			{
				unique_ptr<Node> tmp_ = node_;
				node_ = node_->right_;
				delete tmp_;
			}
			else if // если их все же двое
			{
				unique_ptr<Node> chld_;
				chld_ = node_->right_;
				if ((chld_->left_ == nullptr) && (chld_->right_ == nullptr))
				{
					node_ = chld_;
					delete chld_;
					node_->right_ = nullptr;
				}
				else //если правый потомок имеет потомков
				{
					if ((node_->right_)->left_ != nullptr)
					{
						unique_ptr<Node> lnode_;
						unique_ptr<Node> lnodep_;
						lnodep_ = node_->right_;
						lnode_ = (node_->right_)->left_;
						while (lnode_->left != nullptr)
						{
							lnodep_ = lnode_;
							lnode_ = lnode_->left_;

						}
						node_->value_ = lnode_->value_;
						unique_ptr<Node> lnode_ = nullptr;
						lnodep_->left_ = nullptr;
					}
					else
					{
						unique_ptr<Node> tmp_;
						tmp_ = node_->right;
						node_->right_ = tmp_->right_;
						unique_ptr<Node> tmp_ = nullptr;
					}
				}
			return true;

			}
		}
	}



	
	//static auto copy(Node * tree) -> Node*
	template <typename T>
	friend static auto BinarySearchTree<T>:: copy(unique_ptr<Node> tree) -> unique_ptr<Node>
	{
		if (!tree)
		{
			return NULL;
		}

		//Node * newnode = new Node(tree->value);
		unique_ptr<Node> newnode =std::make_unique<Node>(tree->value);
		newnode->left_ = copy(tree->left_);
		newnode->right_ = copy(tree->right_);

		return newnode;
	}

	template <typename T>
	auto BinarySearhTree<T>:: operator = (const BinarySearchTree& tree)->BinarySearchTree& //копирования
	{
		if (this == &tree)
			return *this;

		size_ = tree.size_;
		root_ = root_->copy(tree.root_);
		return *this;

	};


	template <typename T>
	auto BinarySearchTree<T>:: operator = (BinarySearchTree&& tree)->BinarySearchTree& //перемещения
	{
		if (this == &tree)
			return *this;

		size_ = tree.size_;
		tree.size_ = 0;

		delete root_;
		root_ = tree.root_;
		tree.root_ = nullptr;
		return *this;
	}


	template <typename T>
	auto BinarySearhTree<T>:: operator == (const BinarySearchTree& tree) const -> bool // сравнение
	{
		if (size_ != tree.size_)
		{
			return false;
		}

		else
		{
			comparison(root_, tree.root_);
		}
	}
 
template <typename T>	
 BinarySearchTree<T>::~BinarySearchTree() 
{
	unique_ptr<Node> root_ = nullptr;
}
