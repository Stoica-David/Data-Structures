#include<iostream>
#include<fstream>
#include<queue>
struct Node
{
int key;
bool color;
Node* left, * right, * parent;
Node(int key, bool color, Node* left, Node* right, Node* parent)
{
this->key = key;
this->color = color;
this->left = left;
this->right = right;
this->parent = parent;
}
};
struct ARN
{
Node* root, * nil;
ARN()
{
this->root = nullptr;
this->nil = new Node(-1, false, nullptr, nullptr, nullptr);
}
void Insert(int key)
{
if (Find(key) != nullptr && Find(key) != this->nil)
{
std::cout << "There is already a node with the given key!\n";
return;
}
if (this->root == nullptr)
{
root = new Node(key, false, this->nil, this->nil, this->nil);
return;
}
Node* current = root;
while (current != this->nil)
{
if (current->key > key)
{
if (current->left != this->nil)
{
current = current->left;
}
else
{
current->left = new Node(key, true, this->nil, this->nil, this->nil);
current->left->parent = current;
InsertRepare(current->left);
return;
}
}
else
{
if (current->right != this->nil)
{
current = current->right;
}
else
{
current->right = new Node(key, true, this->nil, this->nil, this->nil);
current->right->parent = current;
InsertRepare(current->right);
return;
}
}
}
}
void InsertRepare(Node* current)
{
while (current->parent->color == true)
{
if (current->parent == current->parent->parent->left)
{
Node* uncle = current->parent->parent->right;
if (uncle->color == true)
{
current->parent->color = false;
uncle->color = false;
current->parent->parent->color = true;
current = current->parent->parent;
}
else
{
if (current == current->parent->right)
{
current = current->parent;
LeftRotation(current);
}
current->parent->color = false;
current->parent->parent->color = true;
RightRotation(current->parent->parent);
}
}
else
{
Node* uncle = current->parent->parent->left;
if (uncle->color == true)
{
current->parent->color = false;
uncle->color = false;
current->parent->parent->color = true;
current = current->parent->parent;
}
else
{
if (current == current->parent->left)
{
current = current->parent;
RightRotation(current);
}
current->parent->color = false;
current->parent->parent->color = true;
LeftRotation(current->parent->parent);
}
}
}
this->root->color = false;
}
Node* Max(Node* x)
{
Node* current = x;
while (current->right != this->nil)
{
current = current->right;
}
return current;
}
Node* Min(Node* x)
{
Node* current = x;
while (current->left != this->nil)
{
current = current->left;
}
return current;
}
Node* Successor(Node* x)
{
Node* current = x;
if (x->right != this->nil)
{
current = Min(current->right);
}
else
{
current = x->parent;
while (current != this->nil && x == current->right)
{
x = current;
current = current->parent;
}
}
return current;
}
Node* Predecessor(Node* x)
{
Node* current = x;
if (x->left != this->nil)
{
current = Max(current->left);
}
else
{
current = x->parent;
while (current != this->nil && x == current->left)
{
x = current;
current = current->parent;
}
}
return current;
}
Node* Find(int key)
{
Node* current = this->root;
while (current != nullptr && current != this->nil && current->key != key)
{
if (key < current->key)
{
current = current->left;
}
else
{
current = current->right;
}
}
return current;
}
void Transplant(Node* erased, Node* successor)
{
if (erased->parent == this->nil)
{
this->root = successor;
}
else
{
if (erased == erased->parent->left)
{
erased->parent->left = successor;
}
else
{
erased->parent->right = successor;
}
}
successor->parent = erased->parent;
}
void Delete(int key)
{
if (Find(key) == nullptr || Find(key) == this->nil)
{
std::cout << "There is not a node to erase with the given key!\n";
return;
}
else
{
Erase(Find(key));
}
}
void Erase(Node* toErase)
{
if (toErase == nullptr || toErase == this->nil)
{
std::cout << "There is not a node to erase!\n";
return;
}
bool toEraseColor = toErase->color;
Node* x;
if (toErase->left == this->nil)
{
x = toErase->right;
Transplant(toErase, x);
}
else
{
if (toErase->right == this->nil)
{
x = toErase->left;
Transplant(toErase, x);
}
else
{
Node* successor = Successor(toErase);
toEraseColor = successor->color;
x = successor->right;
if (successor->parent == toErase)
{
x->parent = successor;
}
else
{
Transplant(successor, x);
successor->right = toErase->right;
toErase->right->parent = successor;
}
Transplant(toErase, successor);
successor->left = toErase->left;
toErase->left->parent = successor;
successor->color = toErase->color;
}
}
delete toErase;
if (toEraseColor == false)
DeleteRepare(x);
}
void DeleteRepare(Node* current)
{
if (current == nullptr)
return;
while (current != this->root && current->color == false)
{
if (current == current->parent->left)
{
Node* brother = current->parent->right;
if (brother->color == true)
{
brother->color = false;
brother->parent->color = true;
LeftRotation(current->parent);
brother = current->parent->right;
}
if (brother->left->color == false && brother->right->color == false)
{
brother->color = 0;
current = current->parent;
}
else
{
if (brother->right->color == false)
{
brother->left->color = false;
brother->color = true;
RightRotation(brother);
brother = current->parent->right;
}
brother->color = current->parent->color;
current->parent->color = false;
brother->right->color = false;
LeftRotation(brother->parent);
current = this->root;
}
}
else
{
Node* brother = current->parent->left;
if (brother->color == true)
{
brother->color = false;
current->parent->color = true;
RightRotation(current->parent);
brother = current->parent->left;
}
if (brother->right->color == false && brother->left->color == false)
{
brother->color = true;
current = current->parent;
}
else
{
if (brother->left->parent)
{
brother->right->color = false;
brother->color = true;
LeftRotation(brother);
brother = current->parent->left;
}
brother->color = current->parent->color;
current->parent->color = false;
brother->left->color = false;
RightRotation(current->parent);
current = this->root;
}
}
}
current->color = 1;
}
void LeftRotation(Node* toRotate)
{
Node* child = toRotate->right;
toRotate->right = child->left;
if (child->left != this->nil)
{
child->left->parent = toRotate;
}
child->parent = toRotate->parent;
if (toRotate->parent == this->nil)
{
this->root = child;
}
else
{
if (toRotate->parent->left == toRotate)
{
toRotate->parent->left = child;
}
else
{
toRotate->parent->right = child;
}
}
child->left = toRotate;
toRotate->parent = child;
}
void RightRotation(Node* toRotate)
{
Node* child = toRotate->left;
toRotate->left = child->right;
if (child->right != this->nil)
{
child->right->parent = toRotate;
}
child->parent = toRotate->parent;
if (toRotate->parent == this->nil)
{
this->root = child;
}
else
{
if (toRotate->parent->right == toRotate)
{
toRotate->parent->right = child;
}
else
{
toRotate->parent->left = child;
}
}
child->right = toRotate;
toRotate->parent = child;
}
void RSD(Node* node)
{
if (node != this->nil)
{
std::cout << node->key << "(" << node->color << ") ";
RSD(node->left);
RSD(node->right);
}
}
void SRD(Node* node)
{
if (node != this->nil)
{
SRD(node->left);
std::cout << node->key << "(" << node->color << ") ";
SRD(node->right);
}
}
void SDR(Node* node)
{
if (node != this->nil)
{
SDR(node->left);
SDR(node->right);
std::cout << node->key << "(" << node->color << ") ";
}
}
void LevelOrder()
{
std::queue<Node*> nodesQueue;
nodesQueue.push(this->root);
while (!nodesQueue.empty())
{
Node* current = nodesQueue.front();
std::cout << current->key << "(" << current->color << ") ";
nodesQueue.pop();
if (current->left != this->nil)
nodesQueue.push(current->left);
if (current->right != this->nil)
nodesQueue.push(current->right);
}
std::cout << std::endl;
}
void Print(int option)
{
if (this->root == nullptr)
{
std::cout << "The tree is empty!\n";
return;
}
switch (option)
{
case 0:
{
std::cout << "RSD = ";
RSD(this->root);
break;
}
case 1:
{
std::cout << "SRD = ";
SRD(this->root);
break;
}
case 2:
{
std::cout << "SDR = ";
SDR(this->root);
break;
}
case 3:
{
std::cout << "Level order = ";
LevelOrder();
break;
}
default:
{
std::cout << "The entered traversal number is not valid!\n";
}
}
}
void Construct(const std::vector<int>& keysVector)
{
int index = 0;
while (index < keysVector.size())
{
Insert(keysVector[index]);
index++;
}
}
bool Empty()
{
return this->root == nullptr;
}
void Clear(Node* current)
{
if (Empty())
{
return;
}
if (current == nullptr)
{
current = this->root;
}
if (current->left != this->nil)
{
Clear(current->left);
}
if (current->right != this->nil)
{
Clear(current->right);
}
if (current == this->root)
{
this->root = nullptr;
}
delete current;
}
};
int main()
{
ARN MyTree; std::vector<int> keysVector;
int option = 1, nrOption = 1, key, deleteType, traversal, nrKeys;
std::cout << "Options: (0) - Exit\n(1) - Insert\n(2) - Construct\n(3) - Search node\n(4) - Delete\n(5) - Print min\n(6) - Print max\n(7) - Print predecessor\n(8) - Print successor\n(9) - Print tree\n(10) - Clear\n\n";
while (option)
{
if (nrOption % 5 == 0)
{
system("PAUSE");
system("CLS");
std::cout << "Options: (0) - Exit\n(1) - Insert\n(2) - Construct\n(3) - Search node\n(4) - Delete\n(5) - Print min\n(6) - Print max\n(7) - Print predecessor\n(8) - Print successor\n(9) - Print tree\n(10) - Clear\n\n";
}
std::cout << "Enter your option: ";
std::cin >> option;
switch (option)
{
case 0:
{
std::cout << "Bye!\n";
break;
}
case 1:
{
std::cout << "Enter a key: ";
std::cin >> key;
MyTree.Insert(key);
break;
}
case 2:
{
std::cout << "Enter the number of keys: ";
std::cin >> nrKeys;
std::cout << "Give a vector of keys: ";
for (int index = 0; index < nrKeys; index++)
{
std::cin >> key;
keysVector.push_back(key);
}
MyTree.Construct(keysVector);
break;
}
case 3:
{
std::cout << "Enter a key: ";
std::cin >> key;
if (MyTree.Find(key) != MyTree.nil)
{
std::cout << "There is a node with the given key!\n";
}
else
{
std::cout << "There is not a node with the given key!\n";
}
break;
}
case 4:
{
std::cout << "Delete options:\n(0) - Delete a key\n(1) - Erase a node\n\n";
std::cout << "Enter your delete option: ";
std::cin >> deleteType;
std::cout << "Enter a key: ";
std::cin >> key;
if (deleteType == 0)
{
MyTree.Delete(key);
}
else if (deleteType == 1)
{
if (MyTree.Find(key) != MyTree.nil)
{
MyTree.Erase(MyTree.Find(key));
}
else
{
std::cout << "There is not a node with the given key!\n";
}
}
else
{
std::cout << "The delete option is not valid!\n";
}
break;
}
case 5:
{
if (MyTree.root == nullptr)
{
std::cout << "The tree is empty!\n";
}
else
{
std::cout << "The min value is " << MyTree.Min(MyTree.root)->key << "!\n";
}
break;
}
case 6:
{
if (MyTree.root == nullptr)
{
std::cout << "The tree is empty!\n";
}
else
{
std::cout << "The max value is " << MyTree.Max(MyTree.root)->key << "!\n";
}
break;
}
case 7:
{
std::cout << "Enter a key: ";
std::cin >> key;
if (MyTree.root == nullptr)
{
std::cout << "The tree is empty!\n";
}
else if (MyTree.root->left == MyTree.nil && MyTree.root->right == MyTree.nil)
{
std::cout << "There is only a node in the tree!\n";
}
else if (MyTree.Find(key) != MyTree.nil)
{
if (MyTree.Find(key) != MyTree.Min(MyTree.root))
{
std::cout << "The predecessor of the given value is " << MyTree.Predecessor(MyTree.Find(key))->key << "!\n";
}
else
{
std::cout << "The given node has no predecessor!\n";
}
}
else
{
std::cout << "There is not a node with the given key!\n";
}
break;
}
case 8:
{
std::cout << "Enter a key: ";
std::cin >> key;
if (MyTree.root == nullptr)
{
std::cout << "The tree is empty!\n";
}
else if (MyTree.root->left == MyTree.nil && MyTree.root->right == MyTree.nil)
{
std::cout << "There is only a node in the tree!\n";
}
else if (MyTree.Find(key) != MyTree.nil)
{
if (MyTree.Find(key) != MyTree.Max(MyTree.root))
{
std::cout << "The successor of the given value is " << MyTree.Successor(MyTree.Find(key))->key << "!\n";
}
else
{
std::cout << "The given node has no successor!\n";
}
}
else
{
std::cout << "There is not a node with the given key!\n";
}
break;
}
case 9:
{
std::cout << "\Traversal numbers:(0) - RSD\n(1) - SRD\n(2) - SDR\n(3) - Level Order\n\n";
std::cout << "Enter a traversal number: ";
std::cin >> traversal;
MyTree.Print(traversal);
std::cout << std::endl;
break;
}
case 10:
{
MyTree.Clear(MyTree.root);
std::cout << std::endl;
break;
}
default:
{
std::cout << "Enter a valid option!\n";
option = 1;
}
}
nrOption++;
}
return 0;
}
