#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;


template <typename T>
class AVLNode {
    public:
        T val;
        AVLNode* left;
        AVLNode* right;
        int height;

        // Constructor for node for AVL tree
        AVLNode(T val)
            : val(val)
            , left(nullptr)
            , right(nullptr)
            , height(1){}

};

template <typename T>
class AVLTree {
    private:

        // search algorithm for tree
        void search(AVLNode<T>* root, T val){
            if (root->val > val) return search(root->right, val)
            else if (root->val < val) return search(root->left, val)
            else if (root->val == val) {
                cout << val << " is in the tree."<<endl;
                return true;
            }
            else {
                cout << val << " is not in the tree."<<endl;
                return false;
            }
        }

        // dfs inorder traversal of tree
        void inorder(AVLNode<T>* root){
            if (root){
                inorder(root->left);
                cout<< root->val << " ";
                inorder(root->right);
            }
        }
        
        // dfs preorder traversal of tree
        void preorder(AVLNode<T>* root){
            if (root){
                cout<< root->val << " ";
                preorder(root->left);
                preorder(root->right);
            }
        }

        // dfs postorder traversal of tree
        void postorder(AVLNode<T>* root){
            if (root){
                postorder(root->left);
                postorder(root->right);
                cout<< root->val << " ";
            }
        }

        // bfs inorder traversal of tree
        void bfs(AVLNode<T>* root){
            vector<T> visited = {};
            queue<T> traverse = {};
            traverse.push(root)
            while (!traverse.empty()){
                visited.push_back(traverse.pop());
                if (root->left) traverse.push(root->left);
                if (root->right) traverse.push(root->right);
            }
            for (auto x : visited){
                cout << x->val << " ";
            }
            cout<<endl;
        }

    public:
        
        bool searchValue(T val) {return search(root, val);}
        void printInorder() {
            cout<<"INORDER TRAVERSAL: ";
            inorder(root);
            cout<<endl;
        }
        void printPreorder() {
            cout<<"PREORDER TRAVERSAL: ";
            preorder(root);
            cout<<endl;
        }
        void printPostorder() {
            cout<<"POSTORDER TRAVERSAL: ";
            postorder(root);
            cout<<endl;
        }
        void printBFS() {
            cout<<"BFS TRAVERSAL: ";
            bfs(root);
        }


};

int main() {
    return 0;
}
