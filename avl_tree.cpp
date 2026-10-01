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
        AVLNode<T>* root;

        // -- UTILITY FUNCTIONS --

        int calc_height(AVLNode<T>* root) {
            return (root == nullptr) ? 0 : root->height;
        }

        void update_height(AVLNode<T>* root) {
            root->height = 1 + max(calc_height(root->left), calc_height(root->right));
        }

        int calc_balance(AVLNode<T>* root) {
            return (root == nullptr) ? 0 : (calc_height(root->left) - calc_height(root->right));
        }

        AVLNode<T>* find_replacement(AVLNode<T>* root) {
            AVLNode<T>* curr_node = root;

            while (curr_node != nullptr && curr_node->right != nullptr) {
                curr_node = curr_node->right;
            }

            return curr_node;
        }

        // -- ROTATION FUNCTIONS --

        AVLNode<T>* rotate_left(AVLNode<T>* root) {
            AVLNode<T>* right_child = root->right;
            AVLNode<T>* left_subtree = right_child->left;

            // Perform rotation
            right_child->left = root;
            root->right = left_subtree;

            // Update heights
            update_height(root);
            update_height(right_child);

            // Return new root of this subtree
            return right_child;
        }

        AVLNode<T>* rotate_right(AVLNode<T>* root) {
            AVLNode<T>* left_child = root->left;
            AVLNode<T>* right_subtree = left_child->right;

            // Perform rotation
            left_child->right = root;
            root->left = right_subtree;

            // Update heights
            update_height(root);
            update_height(left_child);

            // Return new root of this subtree
            return left_child;
        }

        // -- INSERTION AND DELETION FUNCTIONS --

        AVLNode<T>* _insert_val(AVLNode<T>* root, T val) {
            if (root == nullptr) {
                return new AVLNode<T>(val);
            }

            if (val < root->val) {
                root->left = _insert_val(root->left, val);
            } else if (val > root->val) {
                root->right = _insert_val(root->right, val);
            } else {
                return root;
            }

            update_height(root);

            int balance = calc_balance(root);

            // CASE 1: LL
            if (balance > 1 && val < root->left->val) {
                return rotate_right(root);
            }
            
            // CASE 2: LR
            if (balance > 1 && val > root->left->val) {
                root->left = rotate_left(root->left);
                return rotate_right(root);
            }
            
            // CASE 3: RL
            if (balance < -1 && val < root->right->val) {
                root->right = rotate_right(root->right);
                return rotate_left(root);
            }
            
            // CASE 4: RR
            if (balance < -1 && val > root->right->val) {
                return rotate_left(root);
            }

            return root;
        }

        AVLNode<T>* _delete_val(AVLNode<T>* root, T val) {
            if (root == nullptr)
                return root;
            
            if (val < root->val) {
                root->left = _delete_val(root->left, val);
            } else if (val > root->val) {
                root->right = _delete_val(root->right, val);
            } else {
                // case 1: no children
                if (root->left == nullptr && root->right == nullptr) {
                    delete root;

                    root = nullptr;
                    return root;
                }

                // case 2a: one child (on the left)
                if (root->right == nullptr) {
                    AVLNode<T>* to_delete = root;
                    root = root->left;

                    delete to_delete;

                    return root;
                }

                // case 2b: one child (on the right)
                if (root->left == nullptr) {
                    AVLNode<T>* to_delete = root;
                    root = root->right;

                    delete to_delete;

                    return root;
                }
                
                // case 3: two children
                AVLNode<T>* replacement_node = find_replacement(root->left);

                root->val = replacement_node->val;
                root->left = _delete_val(root->left, replacement_node->val);
            }

            update_height(root);

            int balance = calc_balance(root);

            // CASE 1: LL
            if (balance > 1 && calc_balance(root->left) >= 0) {
                return rotate_right(root);
            }
            
            // CASE 2: LR
            if (balance > 1 && calc_balance(root->left) < 0) {
                root->left = rotate_left(root->left);
                return rotate_right(root);
            }
            
            // CASE 3: RL
            if (balance < -1 && calc_balance(root->right) > 0) {
                root->right = rotate_right(root->right);
                return rotate_left(root);
            }
            
            // CASE 4: RR
            if (balance < -1 && calc_balance(root->right) <= 0) {
                return rotate_left(root);
            }

            return root;
        }

        // search algorithm for tree
        bool search(AVLNode<T>* root, T val){
            if (root->val > val) return search(root->right, val);
            else if (root->val < val) return search(root->left, val);
            else if (root->val == val) {
                cout << val << " is in the tree."<<endl;
                return true;
            }
            else {
                cout << val << " is not in the tree."<<endl;
                return false;
            }
        }

        // -- TRAVERSAL FUNCTIONS

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
            vector<AVLNode<T>*> visited;
            queue<AVLNode<T>*> traverse;

            traverse.push(root);

            AVLNode<T>* curr_node;

            while (!traverse.empty()){
                curr_node = traverse.front();
                
                visited.push_back(curr_node);

                traverse.pop();

                if (curr_node->left) traverse.push(curr_node->left);
                if (curr_node->right) traverse.push(curr_node->right);
            }
            for (auto x : visited){
                cout << x->val << " ";
            }
            cout<<endl;
        }

    public:
        bool searchValue(T val) {
            return search(root, val);
        }

        void insert_val(T val) {
            root = _insert_val(root, val);
        }

        void delete_val(T val) {
            root = _delete_val(root, val);
        }
        
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
    // -- INSERTION CASE HANDLING TESTS --

    AVLTree<int>* insertion_test1 = new AVLTree<int>(); // LL

    cout << "Insertion test #1 (LL)" << endl;
    
    insertion_test1->insert_val(5);
    insertion_test1->printPreorder();
    insertion_test1->printInorder();

    insertion_test1->insert_val(4);
    insertion_test1->printPreorder();
    insertion_test1->printInorder();

    insertion_test1->insert_val(3);
    insertion_test1->printPreorder();
    insertion_test1->printInorder();

    cout << endl;

    AVLTree<int>* insertion_test2 = new AVLTree<int>(); // LR

    cout << "Insertion test #2 (LR)" << endl;

    insertion_test2->insert_val(5);
    insertion_test2->printPreorder();
    insertion_test2->printInorder();

    insertion_test2->insert_val(2);
    insertion_test2->printPreorder();
    insertion_test2->printInorder();

    insertion_test2->insert_val(3);
    insertion_test2->printPreorder();
    insertion_test2->printInorder();

    cout << endl;

    AVLTree<int>* insertion_test3 = new AVLTree<int>(); // RL

    cout << "Insertion test #3 (RL)" << endl;

    insertion_test3->insert_val(3);
    insertion_test3->printPreorder();
    insertion_test3->printInorder();

    insertion_test3->insert_val(5);
    insertion_test3->printPreorder();
    insertion_test3->printInorder();

    insertion_test3->insert_val(4);
    insertion_test3->printPreorder();
    insertion_test3->printInorder();

    cout << endl;

    AVLTree<int>* insertion_test4 = new AVLTree<int>(); // RR

    cout << "Insertion test #4 (RR)" << endl;

    insertion_test4->insert_val(3);
    insertion_test4->printPreorder();
    insertion_test4->printInorder();

    insertion_test4->insert_val(4);
    insertion_test4->printPreorder();
    insertion_test4->printInorder();

    insertion_test4->insert_val(5);
    insertion_test4->printPreorder();
    insertion_test4->printInorder();

    cout << endl;

    // -- DELETION CASE HANDLING TESTS --

    AVLTree<int>* deletion_test1 = new AVLTree<int>(); // LL

    cout << "Deletion test #1 (LL)" << endl;

    deletion_test1->insert_val(30);
    deletion_test1->insert_val(20);
    deletion_test1->insert_val(40);
    deletion_test1->insert_val(10);

    deletion_test1->printPreorder();
    deletion_test1->printInorder();

    deletion_test1->delete_val(40);
    deletion_test1->printPreorder();
    deletion_test1->printInorder();

    cout << endl;

    AVLTree<int>* deletion_test2 = new AVLTree<int>(); // LR

    cout << "Deletion test #2 (LR)" << endl;

    deletion_test2->insert_val(30);
    deletion_test2->insert_val(10);
    deletion_test2->insert_val(40);
    deletion_test2->insert_val(20);

    deletion_test2->printPreorder();
    deletion_test2->printInorder();

    deletion_test2->delete_val(40);
    deletion_test2->printPreorder();

    cout << endl;

    AVLTree<int>* deletion_test3 = new AVLTree<int>(); // RL

    cout << "Deletion test #3 (RL)" << endl;

    deletion_test3->insert_val(10);
    deletion_test3->insert_val(5);
    deletion_test3->insert_val(30);
    deletion_test3->insert_val(20);

    deletion_test3->printPreorder();
    deletion_test3->printInorder();

    deletion_test3->delete_val(5);

    deletion_test3->printPreorder();
    deletion_test3->printInorder();

    cout << endl;

    AVLTree<int>* deletion_test4 = new AVLTree<int>(); // RR

    cout << "Deletion test #4 (RR)" << endl;

    deletion_test4->insert_val(20);
    deletion_test4->insert_val(10);
    deletion_test4->insert_val(30);
    deletion_test4->insert_val(40);

    deletion_test4->printPreorder();
    deletion_test4->printInorder();

    deletion_test4->delete_val(10);

    deletion_test4->printPreorder();
    deletion_test4->printInorder();

    cout << endl;

    return 0;
}
