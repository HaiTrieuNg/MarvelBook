#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <string>
#include <assert.h>

using namespace std;
template<typename bstdata>
class BST
{
private:
    struct Node
    {
        bstdata data;
        Node* left;
        Node* right;

        Node(bstdata newdata)
        {
            data = newdata;
            left = NULL;
            right = NULL;
        }
    };

    Node* root;

    /**Private helper functions*/
    void insertNode(Node* root, bstdata data);
    //private helper function for insert
    //recursively inserts a value into the BST

    void inOrderPrint(ostream& out, Node* root) const;
    //private helper function for inOrderPrint
    //recursively prints tree values in order from smallest to largest

    void preOrderPrint(ostream& out, Node* root) const;
    //private helper function for preOrderPrint
    //recursively prints tree values in pre order

    void postOrderPrint(ostream& out, Node* root) const;
    //private helper function for postOrderPrint
    //recursively prints tree values in post order

    void copyNode(Node* copy);
    //recursive helper function to the copy constructor

    void freeNode(Node* root);
    //private helper function for the destructor
    //recursively frees the memory in the BST

    bool searchNode(Node* root, bstdata data) const;
    //recursive helper function to search
    //returns whether the value is found in the tree

    bstdata minimum(Node* root) const;
    //recursive helper function to minimum
    //returns the minimum value in the tree

    bstdata maximum(Node* root) const;
    //recursive helper function to maximum
    //returns the maximum value in the tree

    Node* removeNode(Node* root, bstdata data);
    //recursive helper function to remove
    //removes data from the tree

    void getSize(Node* root, int& size) const;
    //recursive helper function to the size function
    //calculates the size of the tree
    //stores the result in size

    int getHeight(Node* root) const;
    //recursive helper function to the height function
    //returns the height of the tree

public:

    /**constructors and destructor*/

    BST();
    //Instantiates a new BST

    BST(const BST &bst);
    //copy constructor

    ~BST();
    //deallocates the tree memory

    /**access functions*/

    bstdata minimum() const;
    //returns the minimum value in the BST
    //pre: !empty()

    bstdata maximum() const;
    //returns the maximum value in the BST
    //pre: !empty()

    bool isEmpty() const;
    //determines whether the BST is empty

    int getSize() const;
    //returns the size of the tree

    bstdata getRoot() const;
    //returns the value stored at the root of the BST
    //pre: !isEmpty()

    int getHeight() const;
    //returns the height of the tree

    bool search(bstdata data) const;
    //returns whether the data is found in the tree
    //pre: !isEmpty()

    /**manipulation procedures*/

    void insert(bstdata data);
    //inserts new data into the BST

    void remove(bstdata data);
    //removes the specified value from the tree
    //pre: data is located in the tree
    //pre: !isEmpty()

    /**additional functions*/

    void inOrderPrint(ostream& out) const;
    //calls the inOrderPrint function to print out the values
    //stored in the BST

    void preOrderPrint(ostream& out) const;
    //calls the reOrderPrint function to print out the values
    //stored in the BST

    void postOrderPrint(ostream& out) const;
    //calls the postOrderPrint function to print out the values
    //stored in the BST
};

template <typename bstdata>
BST<bstdata>::BST()
{
    root = NULL;
}

template <typename bstdata>
bool BST<bstdata>::isEmpty() const
{
    return root == NULL;
}

template <typename bstdata>
void BST<bstdata>::insertNode(Node* root, bstdata data)
{
    Node *N = new Node (data);
    if (data == root->data)
        return;
    else if (data < root->data)
    {
        if(root->left == NULL)
            root->left= N;
        else
            insertNode(root->left, data);
    }
    else
    {
        if(root->right==NULL)
            root->right = N;
        else
            insertNode(root->right, data);
    }

}


template <typename bstdata>
void BST<bstdata> :: insert(bstdata data)
{
    if(root == NULL)
        root = new Node (data);
    else
        insertNode(root, data);
}

template <typename bstdata>
void BST<bstdata>:: inOrderPrint(ostream& out, Node* root) const
{
    if (root != NULL)
    {
        inOrderPrint(out, root->left);
        out << root->data << " ";

        inOrderPrint(out, root->right)    ;
    }
}

template <typename bstdata>
void BST<bstdata> :: inOrderPrint(ostream& out) const
{
    inOrderPrint(out, root);
}

template <typename bstdata>
void BST<bstdata> :: preOrderPrint(ostream& out, Node* root) const
{
    if(root != NULL)
    {
        out << root->data << " ";
        preOrderPrint(out, root->left);
        preOrderPrint(out, root->right);
    }

}

template <typename bstdata>
void BST<bstdata> :: preOrderPrint(ostream& out) const
{
    preOrderPrint(out, root);
}

template <typename bstdata>
void BST<bstdata> :: postOrderPrint(ostream& out, Node* root) const
{
    if(root != NULL)
    {
        postOrderPrint(out, root->left);
        postOrderPrint(out, root->right);
        out<< root->data << " ";
    }
}

template <typename bstdata>
void BST<bstdata> :: postOrderPrint(ostream& out) const
{
    postOrderPrint(out, root);
}

template <typename bstdata>
void BST <bstdata> :: copyNode(Node* copy)
{

    if(copy!= NULL)
        insert (copy->data);
    if(copy -> left != NULL)
        copyNode(copy->left);
    if(copy->right!= NULL)
        copyNode(copy->right);


}

template <typename bstdata>
BST<bstdata> :: BST(const BST &bst)
{
    copyNode(bst.root);
}

template <typename bstdata>
void BST <bstdata>::freeNode(Node* root)
{

    if(root)
    {
        freeNode(root->left);
        freeNode(root->right);
        delete root;
    }


}

template <typename bstdata>
BST<bstdata> :: ~BST()
{
    freeNode(root);
}


template <typename bstdata>
bool BST <bstdata> :: searchNode(Node* root, bstdata data) const
{
    if (root == NULL || root->data == data)
        return root;

    else if (root->data < data)
        return searchNode (root->right, data);

    return searchNode (root->left, data);

}

template <typename bstdata>
bool BST <bstdata> :: search(bstdata data) const
{
    assert(!isEmpty());
    if (data == root->data)
        return true;
    else
        return searchNode(root,data);
}

template <typename bstdata>
bstdata BST<bstdata>:: minimum(Node* root) const
{
    while(root->left != NULL)
    {
        root = root->left;
    }
    return root->data;
}

template <typename bstdata>
bstdata BST <bstdata>::minimum() const
{
    assert(!isEmpty());
    return minimum(root);
}

template <typename bstdata>
bstdata BST<bstdata> :: maximum(Node* root) const
{
    while(root->right != NULL)
    {
        root = root->right;
    }
    return root->data;
}

template <typename bstdata>
bstdata BST<bstdata> :: maximum() const
{
    assert(!isEmpty());
    return maximum(root);
}

template <typename bstdata>
typename BST <bstdata>::Node* BST <bstdata> :: removeNode(Node* root, bstdata data)
{
    Node*temp;
    if(root == NULL)
    {
        return root;
    }
    else if (data < root->data)
    {
        root->left = removeNode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = removeNode(root->right, data);
    }
    else
    {

        if(root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
        }
        else if (root->right == NULL)
        {
            temp = root;
            root = root->left;
            delete temp;
        }
        else if (root->left == NULL)
        {
            temp = root;
            root = root->right;
            delete temp;
        }
        else
        {
            temp = root->right;
            while ( temp -> left != NULL)
            {
                temp = temp -> left;
            }
            root->data = temp->data;
            root->right = removeNode(root->right, temp -> data);
        }
    }
    return root;
}

template <typename bstdata>
void BST <bstdata> :: remove(bstdata data)
{
    assert(!isEmpty());
    assert(search(data));
    root = removeNode (root, data);
}

template <typename bstdata>
void BST <bstdata> :: getSize(Node* root, int& size) const
{
    if (root->right != NULL)
    {
        size++;
        getSize(root->right,size);
    }
    if (root->left != NULL)
    {
        size++;
        getSize(root->left,size);
    }
}
template <typename bstdata>
int BST <bstdata> :: getSize() const
{
    int temp =0;
    if(root == NULL)
        return temp;
    else
    {
        temp++;
        getSize(root,temp);
        return temp;
    }

}

template<typename bstdata>
bstdata BST<bstdata>::getRoot() const
{
    assert(!isEmpty());
    return root->data;
}

template <typename bstdata>
int BST <bstdata> :: getHeight(Node* root) const
{
    if(root == NULL)
        return -1;
    else if(getHeight(root->right) > getHeight(root ->left))
        return getHeight(root->right) + 1;
    else
        return getHeight(root ->left) + 1;

}

template <typename bstdata>
int BST <bstdata> :: getHeight() const
{
    return getHeight(root);
}

#endif /* BST_H_ */

/*
#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <string>
#include <assert.h>


using namespace std;
template<typename bstdata>
class BST {
private:
    struct Node {
        bstdata data;
        Node* left;
        Node* right;

        Node(bstdata newdata){
            data = newdata;
            left = NULL;
            right = NULL;
        }
    };

    Node* root;


    void insertNode(Node* root, bstdata data);
    //private helper function for insert
    //recursively inserts a data into the BST

    void inOrderPrint(ostream& out, Node* root) const;
    //private helper function for inOrderPrint
    //recursively prints tree values in order from smallest to largest

    void preOrderPrint(ostream& out, Node* root) const;
    //private helper function for preOrderPrint
    //recursively prints tree values in pre order

    void postOrderPrint(ostream& out, Node* root) const;
    //private helper function for postOrderPrint
    //recursively prints tree values in post order

    void copyNode(Node* copy);
    //recursive helper function to the copy constructor

    void freeNode(Node* root);
    //private helper function for the destructor
    //recursively frees the memory in the BST

    bool searchNode(Node* root, bstdata data) const;
    //recursive helper function to search
    //returns whether the data is found in the tree

    bstdata minimum(Node* root) const;
    //recursive helper function to minimum
    //returns the minimum data in the tree

    bstdata maximum(Node* root) const;
    //recursive helper function to maximum
    //returns the maximum data in the tree

    Node* removeNode(Node* root, bstdata data);
    //recursive helper function to remove
    //removes data from the tree

    void getSize(Node* root, int& size) const;
    //recursive helper function to the size function
    //calculates the size of the tree
    //stores the result in size

    int getHeight(Node* root) const;
    //recursive helper function to the height function
    //returns the height of the tree

public:



    BST();
    //Instantiates a new BST

    BST(const BST &bst);
    //copy constructor

    ~BST();
    //deallocates the tree memory



    bstdata minimum() const;
    //returns the minimum data in the BST
    //pre: !empty()

    bstdata maximum() const;
    //returns the maximum data in the BST
    //pre: !empty()

    bool isEmpty() const;
    //determines whether the BST is empty

    int getSize() const;
    //returns the size of the tree

    bstdata getRoot() const;
    //returns the data stored at the root of the BST
    //pre: !isEmpty()

    int getHeight() const;
    //returns the height of the tree

    bool search(bstdata data) const;
    //returns whether the data is found in the tree
    //pre: !isEmpty()



    void insert(bstdata data);
    //inserts new data into the BST

    void remove(bstdata data);
    //removes the specified data from the tree
    //pre: data is located in the tree
    //pre: !isEmpty()



    void inOrderPrint(ostream& out) const;
    //calls the inOrderPrint function to print out the datas
    //stored in the BST

    void preOrderPrint(ostream& out) const;
    //calls the reOrderPrint function to print out the datas
    //stored in the BST

    void postOrderPrint(ostream& out) const;
    //calls the postOrderPrint function to print out the datas
    //stored in the BST
};


template<typename bstdata>
BST<bstdata>::BST()
  //Instantiates a new BST
{
	root = NULL;
}




template<typename bstdata>
BST<bstdata>::BST(const BST<bstdata> &bst)
  //copy constructor
{
	root = bst.root;
   copyNode(bst.root);
}

template<typename bstdata>
  void BST<bstdata>::copyNode(Node* copy)
     //recursive helper function to the copy constructor
{
	if (copy == NULL)
	return;

	else
	{
		insertNode(root, copy->data);

		if (copy->left != NULL)
		{
			copyNode(copy->left);
		}
		if (copy->right != NULL)
		{
			copyNode(copy->right);
		}
		insert(copy->data);

	}

}






template<typename bstdata>
BST<bstdata>::~BST()
  //deallocates the tree memory
{
	freeNode(root);
}

template<typename bstdata>
  void BST<bstdata>::freeNode(Node* root)
      //private helper function for the destructor
      //recursively frees the memory in the BST
{
	if(root == NULL)
	return;
	freeNode(root->left);
	freeNode(root->right);
	delete root;
}








template<typename bstdata>
  bstdata BST<bstdata>::minimum() const
  //returns the minimum data in the BST
  //pre: !empty()
{
	assert(!isEmpty());
	return  minimum(root);
}

template<typename bstdata>
  bstdata BST<bstdata>::minimum(Node* root) const
      //recursive helper function to minimum
      //returns the minimum data in the tree
{
	if (root->left != NULL)
	{
		return minimum (root->left);
	}
	else
	{
		return root->data;
	}
}





template<typename bstdata>
  bstdata BST<bstdata>::maximum() const
  //returns the maximum data in the BST
  //pre: !empty()
{
	assert (!isEmpty());
	return maximum(root);
}


template<typename bstdata>
  bstdata BST<bstdata>::maximum(Node* root) const
     //recursive helper function to maximum
     //returns the maximum data in the tree
{
	if (root->right != NULL)
	{
		return maximum ( root->right);
	}
	else
	{
		return root->data;
	}
}



template<typename bstdata>
  bool BST<bstdata>::isEmpty() const
  //determines whether the BST is empty
  {
  	return (getSize()==0);

  }



  template<typename bstdata>
  int BST<bstdata>::getSize() const
  //returns the size of the tree
  {
  	int size=0;
    getSize(root, size);
    return size;
  }

  template<typename bstdata>
  void BST<bstdata>::getSize(Node* root, int& size) const
      //recursive helper function to the size function
      //calculates the size of the tree
      //stores the result in size
  {
  	if (root == NULL)
  	{return;}
  	else
  	{
  	size++;
  	getSize (root->left, size);
  	getSize (root->right, size);
  	}
  }




  template<typename bstdata>
  bstdata BST<bstdata>::getRoot() const
  //returns the data stored at the root of the BST
  //pre: !isEmpty()
  {
  	assert (!isEmpty());
  	return root->data;
  }



  template<typename bstdata>
  int BST<bstdata>::getHeight() const
  //returns the height of the tree
  {
  	return getHeight(root);
  }

  template<typename bstdata>
  int BST<bstdata>::getHeight(Node* root) const
      //recursive helper function to the height function
      //returns the height of the tree
  {
  	if(root==NULL)
  	{
  		return -1;
  	}
  	else
  	{
  			int leftS = getHeight(root->left);
  			int rightS = getHeight(root->right);
  			return 1 + max(leftS,rightS);
  	}

  }





  template<typename bstdata>
  bool BST<bstdata>::search(bstdata data) const
  //returns whether the data is found in the tree
  //pre: !isEmpty()
  {
  	assert (!isEmpty());
  	return searchNode(root,data);

  }

  template<typename bstdata>
  bool BST<bstdata>::searchNode(Node* root, bstdata data) const
      //recursive helper function to search
      //returns whether the data is found in the tree
{
	if (data == root->data)
	{
		return true;
	}
	else if (data < root->data)
	{
		if (root->left == NULL)
		{
			return false;
		}
		else
		{
			return searchNode(root->left, data);
		}
	}
	else
	{
		if (root->right == NULL)
		{
			return false;
		}
		else
		{
			return searchNode(root->right, data);
		}
	}
	return false;
}






  template<typename bstdata>
  void BST<bstdata>::insert(bstdata data)
  //inserts new data into the BST
  {
  	if (root == NULL)
  	{
  		root = new Node(data);
  	}
  	else
  	{
  		insertNode(root,data);
  	}

  }

  template<typename bstdata>
  void BST<bstdata>::insertNode(Node* root, bstdata data)
      //private helper function for insert
      //recursively inserts a data into the BST
  {
  	if (data==(root->data))
  	{
  		return;
  	}
  	else if (data<(root->data))
  	{
  		if(root->left == NULL)
  		{
  			root->left = new Node(data);
  		}
  		else
  		{
  			insertNode(root->left,data);
  		}
  	}
  	else if(data>(root->data))
  	{
  		if(root->right == NULL)
  		{
  			root->right = new Node (data);
  		}
  		else
  		{
  			insertNode(root->right, data);
  		}
  	}
  }





  template<typename bstdata>
  void BST<bstdata>::remove(bstdata data)
  //removes the specified data from the tree
  //pre: data is located in the tree
  //pre: !isEmpty()
  {
  	assert (!isEmpty());
  	removeNode(root, data);
  }

  template<typename bstdata>
  typename BST<bstdata>::Node* BST<bstdata>::removeNode(Node* root, bstdata data)
      //recursive helper function to remove
      //removes data from the tree
  {if (root == NULL)
  	{
  		return root;
  	}
  	else if (data < root->data)
  	{
  		root->left = removeNode(root->left,data);
  	}
  	else if (data > root->data)
  	{
  		root->right = removeNode(root->right,data);
  	}
  	else
  	{
  		if (root->left == NULL && root->right == NULL)
  		{
  			delete root;
  			root = NULL;
  		}
  		else if (root->left!=NULL && root->right == NULL)
  		{
  			Node* temp = root;
  			root= root->left;
  			delete temp;
  		}
  		else if (root->left== NULL && root->right != NULL)
  		{
  			Node* temp = root;
  			root = root->right;
  			delete temp;
  		}
  		else
  		{
  			bstdata temp = minimum(root->right);
  			root->data = temp;
  			root->right = removeNode(root->right, temp);
  		}
  	}
  	return root;
  }






  template<typename bstdata>
  void BST<bstdata>::inOrderPrint(ostream& out) const
  //calls the inOrderPrint function to print out the values
  //stored in the BST
  {
	  if(isEmpty())
	  	out<<" "<<endl;
	  else
  	   inOrderPrint(out, root);

  }

  template<typename bstdata>
  void BST<bstdata>::inOrderPrint(ostream& out, Node* root) const
      //private helper function for inOrderPrint
      //recursively prints tree values in order from smallest to largest
{
	if (root == NULL)
	{
		return;
	}
	inOrderPrint(out, root->left);
	out<< root->data<<" ";
	inOrderPrint(out, root->right);

}



  template<typename bstdata>
  void BST<bstdata>::preOrderPrint(ostream& out) const
  //calls the reOrderPrint function to print out the datas
  //stored in the BST
  {
	if(isEmpty())
	out<<" "<<endl;
	else
  	 preOrderPrint(out, root);

  }

  template<typename bstdata>
  void BST<bstdata>::preOrderPrint(ostream& out, Node* root) const
     //private helper function for preOrderPrint
     //recursively prints tree values in pre order
  {
  	if (root == NULL)
  	{
  		return;

  	}
  	out<< root->data<<" ";
  	preOrderPrint(out, root->left);
  	preOrderPrint(out, root->right);
  }







  template<typename bstdata>
  void BST<bstdata>::postOrderPrint(ostream& out) const
  //calls the postOrderPrint function to print out the values
  //stored in the BST
  {
	  if(isEmpty())
	{out<<" "<<endl;  }
	  else
	  {  postOrderPrint(out, root);}

  }



  template<typename bstdata>
  void BST<bstdata>::postOrderPrint(ostream& out, Node* root) const
     //private helper function for postOrderPrint
     //recursively prints tree values in post order
  {
  	if (root == NULL)
  	{
  		return;

  	}
  	postOrderPrint(out, root->left);
  	postOrderPrint(out, root->right);
  	out<< root->data<<" ";
  }






#endif /* BST_H_ */

/*
#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <string>
#include <assert.h>


using namespace std;
template<typename bstdata>
class BST {
private:
    struct Node {
        bstdata data;
        Node* left;
        Node* right;

        Node(bstdata newdata){
            data = newdata;
            left = NULL;
            right = NULL;
        }
    };

    Node* root;


    void insertNode(Node* root, bstdata data);
    //private helper function for insert
    //recursively inserts a data into the BST

    void inOrderPrint(ostream& out, Node* root) const;
    //private helper function for inOrderPrint
    //recursively prints tree values in order from smallest to largest

    void preOrderPrint(ostream& out, Node* root) const;
    //private helper function for preOrderPrint
    //recursively prints tree values in pre order

    void postOrderPrint(ostream& out, Node* root) const;
    //private helper function for postOrderPrint
    //recursively prints tree values in post order

    void copyNode(Node* copy);
    //recursive helper function to the copy constructor

    void freeNode(Node* root);
    //private helper function for the destructor
    //recursively frees the memory in the BST

    bool searchNode(Node* root, bstdata data) const;
    //recursive helper function to search
    //returns whether the data is found in the tree

    bstdata minimum(Node* root) const;
    //recursive helper function to minimum
    //returns the minimum data in the tree

    bstdata maximum(Node* root) const;
    //recursive helper function to maximum
    //returns the maximum data in the tree

    Node* removeNode(Node* root, bstdata data);
    //recursive helper function to remove
    //removes data from the tree

    void getSize(Node* root, int& size) const;
    //recursive helper function to the size function
    //calculates the size of the tree
    //stores the result in size

    int getHeight(Node* root) const;
    //recursive helper function to the height function
    //returns the height of the tree

public:



    BST();
    //Instantiates a new BST

    BST(const BST &bst);
    //copy constructor

    ~BST();
    //deallocates the tree memory


    bstdata minimum() const;
    //returns the minimum data in the BST
    //pre: !empty()

    bstdata maximum() const;
    //returns the maximum data in the BST
    //pre: !empty()

    bool isEmpty() const;
    //determines whether the BST is empty

    int getSize() const;
    //returns the size of the tree

    bstdata getRoot() const;
    //returns the data stored at the root of the BST
    //pre: !isEmpty()

    int getHeight() const;
    //returns the height of the tree

    bool search(bstdata data) const;
    //returns whether the data is found in the tree
    //pre: !isEmpty()


    void insert(bstdata data);
    //inserts new data into the BST

    void remove(bstdata data);
    //removes the specified data from the tree
    //pre: data is located in the tree
    //pre: !isEmpty()


    void inOrderPrint(ostream& out) const;
    //calls the inOrderPrint function to print out the datas
    //stored in the BST

    void preOrderPrint(ostream& out) const;
    //calls the reOrderPrint function to print out the datas
    //stored in the BST

    void postOrderPrint(ostream& out) const;
    //calls the postOrderPrint function to print out the datas
    //stored in the BST
};


template<typename bstdata>
BST<bstdata>::BST()
  //Instantiates a new BST
{
	root = NULL;
}




template<typename bstdata>
BST<bstdata>::BST(const BST<bstdata> &bst)
  //copy constructor
{
	root = bst.root;
   copyNode(bst.root);
}

template<typename bstdata>
  void BST<bstdata>::copyNode(Node* copy)
     //recursive helper function to the copy constructor
{
	if (copy == NULL)
	return;

	else
	{
		insertNode(root, copy->data);

		if (copy->left != NULL)
		{
			copyNode(copy->left);
		}
		if (copy->right != NULL)
		{
			copyNode(copy->right);
		}
		insert(copy->data);

	}

}






template<typename bstdata>
BST<bstdata>::~BST()
  //deallocates the tree memory
{
	freeNode(root);
}

template<typename bstdata>
  void BST<bstdata>::freeNode(Node* root)
      //private helper function for the destructor
      //recursively frees the memory in the BST
{
	if(root == NULL)
	return;
	freeNode(root->left);
	freeNode(root->right);
	delete root;
}








template<typename bstdata>
  bstdata BST<bstdata>::minimum() const
  //returns the minimum data in the BST
  //pre: !empty()
{
	assert(!isEmpty());
	return  minimum(root);
}

template<typename bstdata>
  bstdata BST<bstdata>::minimum(Node* root) const
      //recursive helper function to minimum
      //returns the minimum data in the tree
{
	if (root->left != NULL)
	{
		return minimum (root->left);
	}
	else
	{
		return root->data;
	}
}





template<typename bstdata>
  bstdata BST<bstdata>::maximum() const
  //returns the maximum data in the BST
  //pre: !empty()
{
	assert (!isEmpty());
	return maximum(root);
}


template<typename bstdata>
  bstdata BST<bstdata>::maximum(Node* root) const
     //recursive helper function to maximum
     //returns the maximum data in the tree
{
	if (root->right != NULL)
	{
		return maximum ( root->right);
	}
	else
	{
		return root->data;
	}
}



template<typename bstdata>
  bool BST<bstdata>::isEmpty() const
  //determines whether the BST is empty
  {
  	return (getSize()==0);

  }



  template<typename bstdata>
  int BST<bstdata>::getSize() const
  //returns the size of the tree
  {
  	int size=0;
    getSize(root, size);
    return size;
  }

  template<typename bstdata>
  void BST<bstdata>::getSize(Node* root, int& size) const
      //recursive helper function to the size function
      //calculates the size of the tree
      //stores the result in size
  {
  	if (root == NULL)
  	{return;}
  	else
  	{
  	size++;
  	getSize (root->left, size);
  	getSize (root->right, size);
  	}
  }




  template<typename bstdata>
  bstdata BST<bstdata>::getRoot() const
  //returns the data stored at the root of the BST
  //pre: !isEmpty()
  {
  	assert (!isEmpty());
  	return root->data;
  }



  template<typename bstdata>
  int BST<bstdata>::getHeight() const
  //returns the height of the tree
  {
  	return getHeight(root);
  }

  template<typename bstdata>
  int BST<bstdata>::getHeight(Node* root) const
      //recursive helper function to the height function
      //returns the height of the tree
  {
  	if(root==NULL)
  	{
  		return -1;
  	}
  	else
  	{
  			int leftS = getHeight(root->left);
  			int rightS = getHeight(root->right);
  			return 1 + max(leftS,rightS);
  	}

  }





  template<typename bstdata>
  bool BST<bstdata>::search(bstdata data) const
  //returns whether the data is found in the tree
  //pre: !isEmpty()
  {
  	assert (!isEmpty());
  	return searchNode(root,data);

  }

  template<typename bstdata>
  bool BST<bstdata>::searchNode(Node* root, bstdata data) const
      //recursive helper function to search
      //returns whether the data is found in the tree
{
	if (data == root->data)
	{
		return true;
	}
	else if (data < root->data)
	{
		if (root->left == NULL)
		{
			return false;
		}
		else
		{
			return searchNode(root->left, data);
		}
	}
	else
	{
		if (root->right == NULL)
		{
			return false;
		}
		else
		{
			return searchNode(root->right, data);
		}
	}
	return false;
}






  template<typename bstdata>
  void BST<bstdata>::insert(bstdata data)
  //inserts new data into the BST
  {
  	if (root == NULL)
  	{
  		root = new Node(data);
  	}
  	else
  	{
  		insertNode(root,data);
  	}

  }

  template<typename bstdata>
  void BST<bstdata>::insertNode(Node* root, bstdata data)
      //private helper function for insert
      //recursively inserts a data into the BST
  {
  	if (data==(root->data))
  	{
  		return;
  	}
  	else if (data<(root->data))
  	{
  		if(root->left == NULL)
  		{
  			root->left = new Node(data);
  		}
  		else
  		{
  			insertNode(root->left,data);
  		}
  	}
  	else if(data>(root->data))
  	{
  		if(root->right == NULL)
  		{
  			root->right = new Node (data);
  		}
  		else
  		{
  			insertNode(root->right, data);
  		}
  	}
  }


  template<typename bstdata>
  void BST<bstdata>::remove(bstdata data)
  //removes the specified data from the tree
  //pre: data is located in the tree
  //pre: !isEmpty()
  {
  	assert (!isEmpty());
  	removeNode(root, data);
  }

  template<typename bstdata>
  typename BST<bstdata>::Node* BST<bstdata>::removeNode(Node* root, bstdata data)
      //recursive helper function to remove
      //removes data from the tree
  {if (root == NULL)
  	{
  		return root;
  	}
  	else if (data < root->data)
  	{
  		root->left = removeNode(root->left,data);
  	}
  	else if (data > root->data)
  	{
  		root->right = removeNode(root->right,data);
  	}
  	else
  	{
  		if (root->left == NULL && root->right == NULL)
  		{
  			delete root;
  			root = NULL;
  		}
  		else if (root->left!=NULL && root->right == NULL)
  		{
  			Node* temp = root;
  			root= root->left;
  			delete temp;
  		}
  		else if (root->left== NULL && root->right != NULL)
  		{
  			Node* temp = root;
  			root = root->right;
  			delete temp;
  		}
  		else
  		{
  			bstdata temp = minimum(root->right);
  			root->data = temp;
  			root->right = removeNode(root->right, temp);
  		}
  	}
  	return root;
  }



  template<typename bstdata>
  void BST<bstdata>::inOrderPrint(ostream& out) const
  //calls the inOrderPrint function to print out the values
  //stored in the BST
  {
	  if(isEmpty())
	  	out<<" "<<endl;
	  else
  	   inOrderPrint(out, root);

  }

  template<typename bstdata>
  void BST<bstdata>::inOrderPrint(ostream& out, Node* root) const
      //private helper function for inOrderPrint
      //recursively prints tree values in order from smallest to largest
{
	if (root == NULL)
	{
		return;
	}
	inOrderPrint(out, root->left);
	out<< root->data<<" ";
	inOrderPrint(out, root->right);

}



  template<typename bstdata>
  void BST<bstdata>::preOrderPrint(ostream& out) const
  //calls the reOrderPrint function to print out the datas
  //stored in the BST
  {
	if(isEmpty())
	out<<" "<<endl;
	else
  	 preOrderPrint(out, root);

  }

  template<typename bstdata>
  void BST<bstdata>::preOrderPrint(ostream& out, Node* root) const
     //private helper function for preOrderPrint
     //recursively prints tree values in pre order
  {
  	if (root == NULL)
  	{
  		return;

  	}
  	out<< root->data<<" ";
  	preOrderPrint(out, root->left);
  	preOrderPrint(out, root->right);
  }







  template<typename bstdata>
  void BST<bstdata>::postOrderPrint(ostream& out) const
  //calls the postOrderPrint function to print out the values
  //stored in the BST
  {
	  if(isEmpty())
	{out<<" "<<endl;  }
	  else
	  {  postOrderPrint(out, root);}

  }



  template<typename bstdata>
  void BST<bstdata>::postOrderPrint(ostream& out, Node* root) const
     //private helper function for postOrderPrint
     //recursively prints tree values in post order
  {
  	if (root == NULL)
  	{
  		return;

  	}
  	postOrderPrint(out, root->left);
  	postOrderPrint(out, root->right);
  	out<< root->data<<" ";
  }






#endif /* BST_H_ */
