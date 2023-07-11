#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template <class Type>
struct Node {
    Type item;
    Node<Type> *left;
    Node<Type> *right;
    Node<Type> *parent;
};

template <class Type>
class BinaryTree
{
    public:
        BinaryTree();
        BinaryTree(const BinaryTree& b);
        ~BinaryTree();
        void insert(Type item);
        void preOrder();
        void inOrder();
        void postOrder();
        int nodeCount();
        Node<Type>*find(Type item);
        Node<Type>*findRightMostNode(Node<Type> *find);
        void remove(Type item);
        int  height();
        int leavesCount();


    protected:
        Node<Type> *root;

    private:
        void destroy(Node<Type> * curr);
        void copyTree(Node<Type>* curr);
        void insert(Type item, Node<Type> * curr);
        void preOrder(Node<Type> *curr);
        void postOrder(Node<Type> *curr);
        void inOrder(Node<Type> * curr);
        int nodeCount(Node<Type> * curr);
        int leavesCount(Node<Type> * curr);
        bool isLeaf(Node<Type>* curr);
        Node<Type>*find(Type item, Node<Type> *curr);
        void remove(Type item, Node<Type>*curr);
        int height(Node<Type>*curr);
};

template <class Type>
BinaryTree<Type>::BinaryTree(){
    root = nullptr;
}

template <class Type>
BinaryTree<Type>::BinaryTree(const BinaryTree& b) {
    copyTree(b.root);
}

template <class Type>
void BinaryTree<Type>::copyTree(Node<Type>* curr) {
    if (curr) {
        insert(curr->item);
        copyTree(curr->left);
        copyTree(curr->right);
    }
}

template <class Type>
BinaryTree<Type>::~BinaryTree(){
    destroy(root);
}

template <class Type>
void BinaryTree<Type>::destroy(Node<Type> * curr){
    if (curr != nullptr) {
        destroy(curr->left);
        destroy(curr->right);
        delete curr;
    }
}

template <class Type>
void BinaryTree<Type>::insert(Type item){
    if (root == nullptr) {
        root = new Node<Type>;
        root->item = item;
        root->left = nullptr;
        root->right = nullptr;
        root->parent = nullptr;
    }
    else {
        insert(item, root);
    }

}

template <class Type>
void BinaryTree<Type>::insert(Type item, Node<Type> * curr){
    if (item < curr->item) {
        if (curr->left == nullptr) {
            auto temp = new Node<Type>;
            temp->item = item;
            temp->right = nullptr;
            temp->left = nullptr;
            temp->parent = curr;
            curr->left = temp;
            return;
        }
        else {
            insert(item, curr->left);
        }//end of inner if
    }//end of outer if
    else {
        if (curr->right == nullptr) {
            auto temp = new Node<Type>;
            temp->item = item;
            temp->right = nullptr;
            temp->left = nullptr;
            temp->parent = curr;
            curr->right = temp;
            return;
        }
        else {
            insert(item, curr->right);
        }//end of inner if
    }
}


template <class Type>
void BinaryTree<Type>::preOrder(){
    std::cout << "Pre Order: ";
    preOrder(root);
}
template <class Type>
void BinaryTree<Type>::preOrder(Node<Type> *curr){
    if (curr) {
        std::cout << curr->item << " ";
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

template <class Type>
void BinaryTree<Type>::inOrder(){
    std::cout << "In Order: ";
    inOrder(root);
}
template <class Type>
void BinaryTree<Type>::inOrder(Node<Type> *curr){
    if (curr) {

        inOrder(curr->left);
        std::cout << curr->item << " ";
        inOrder(curr->right);
    }

}

template <class Type>
void BinaryTree<Type>::postOrder(){
    std::cout << "Post Order: ";
    postOrder(root);
}
template <class Type>
void BinaryTree<Type>::postOrder(Node<Type> *curr){
    if (curr) {
        postOrder(curr->left);
        postOrder(curr->right);
        std::cout << curr->item << " ";
    }
}


template <class Type>
int BinaryTree<Type>::nodeCount(){
    return nodeCount(root);
}

template <class Type>
int BinaryTree<Type>::nodeCount(Node<Type> *curr){
    if (curr) {
        return 1 + nodeCount(curr->left) + nodeCount(curr->right);
    }
    return 0;
}

template <class Type>
int BinaryTree<Type>::leavesCount(){
    return leavesCount(root);
}

template <class Type>
int BinaryTree<Type>::leavesCount(Node<Type> *curr){
    if (isLeaf(curr)) {
        return 1;
    }
    else {
        if (curr) {
            return leavesCount(curr->left) + leavesCount(curr->right);
        }
        return 0;
    }
    
}

template <class Type>
bool BinaryTree<Type>::isLeaf(Node<Type>* curr) {
    if (curr) {
        if (curr->right == nullptr && curr->left == nullptr) { return true; }
    }
    return false;

}


template <class Type>
Node<Type>* BinaryTree<Type>::find(Type item){
    return find(item, root);
}


template <class Type>
Node<Type>* BinaryTree<Type>::find(Type item, Node<Type>*curr){
    while (curr) {
        if (item == curr->item) {
            return curr;
        }
        else if (item < curr->item) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    return nullptr;
}


template <class Type>
Node<Type>*BinaryTree<Type>::findRightMostNode(Node<Type> *curr){
    while (curr) {
        if (curr->right) {
            curr = curr->right;
        }
        else {
            return curr;
        }
    }
}

template <class Type>
void BinaryTree<Type>::remove(Type item){
    Node<Type>* removalNode = find(item);
    remove(item, removalNode);
}


template <class Type>
void BinaryTree<Type>::remove(Type item, Node<Type>* curr){
    Node<Type>* parent = curr->parent;
    if (curr) {
        if (curr->item = item) { //Node to remove found

            if (curr->left == nullptr && curr->right == nullptr) { //Node is a leaf node
                if (parent == nullptr) { //node is the root node and a leaf
                    delete curr; 
                } 
                else if (parent->left == curr) {
                    parent->left = nullptr;
                    delete curr;
                }
                else {
                    parent->right = nullptr;
                    delete curr;
                }
            }//end of Leaf node removal case

            else if (curr->right == nullptr) {// Node with only 1 left child
                if (parent == nullptr) {//node is root node
                    root = curr->left;
                    delete curr;
                }
                else if (parent->left == curr) {
                    parent->left = curr->left;
                    delete curr;
                }
                else {
                    parent->right = curr->left;
                    delete curr;
                }
            }// end of single left child removal case

            else { //Node with 2 children
                //find successor (leftmost child of right subtree)
                Node<Type>* succ = curr->right;
                while (succ->left) {
                    succ = succ->left;
                }
                auto succItem = succ->item;
                remove(succ->item, succ);
                curr->item = succItem;
            }
            return;
        }// end of node found case
        
    }
    return; //Node not found
}

template <class Type>
int BinaryTree<Type>::height(){
    return height(root);
}
template <class Type>
int BinaryTree<Type>::height(Node<Type>*curr){
    if (curr == nullptr) {
        return -1;
    }
    int leftHeight = height(curr->left);
    int rightHeight = height(curr->right);
    return 1 + std::max(leftHeight, rightHeight);
}

#endif // BINARY_TREE_H
