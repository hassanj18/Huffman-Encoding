#include<iostream>
#include<unordered_map>
using namespace std;
#include<string>
#include<vector>

template <typename k, typename v>
class MinHeap
{
public:
	class HeapItem
	{
	public:
		HeapItem(k KEY, v VALUE) {
			Key = KEY;
			value = VALUE;
		}
		HeapItem() {}
		HeapItem& operator ==(HeapItem& Obj) {
			Key = Obj.Key;
			value = Obj.value;
		}

		k Key;
		v value;
	};

	MinHeap(int capacity) {
		if (capacity > 0) {
			size = capacity;
			arr = new HeapItem[capacity];
		}
	}
	void insert(k KEY, v Value) {
		HeapItem item(KEY, Value);
		if (currentCount >= size - 1) {
			int Newsize = size * 2;
			HeapItem* NewArr = new HeapItem[Newsize];
			int i = 0;
			while (i < size) {
				NewArr[i] = arr[i];
				i++;
			}
			// currentCount = i - 1;
			size = Newsize;
			delete[] arr;
			arr = NewArr;
		}
		arr[++currentCount] = item;
		for (int i = currentCount; (i / 2) > 0 && arr[i / 2].Key > arr[i].Key; i = i / 2)
		{
			swap(arr[i / 2], arr[i]);
		}

	}
	void getMin(v& Retval) {
		if (arr && currentCount>0) {
			Retval = arr[1].value;
			}

	}
	void DeleteMin() {
		swap(arr[1], arr[currentCount--]);
		Heapify(1);
	}
	void DecreaseKey(int ind, v NEW_KEY_VALUE)
	{

		arr[ind].key == NEW_KEY_VALUE;
		for (int i = ind; i / 2 > 0 && arr[i / 2] > arr[i]; i = i / 2)
		{
			swap(arr[i / 2], arr[i]);
		}

	}
	bool is_Empty() {
		if (currentCount > 1)
			return 0;
		return 1;
	}

	v ExtractMin() {
		v ptr= arr[1].value;
		DeleteMin();
		return ptr;
	}
	void Heapify(int i) {
		if (i < currentCount) {

			int l = 2 * i;
			int r = 2 * i + 1;
			int min = i;
			if (l <= currentCount && arr[l].Key < arr[min].Key)
				min = l;
			if (r <= currentCount && arr[r].Key < arr[min].Key)
				min = r;
			if (min != i) {
				swap(arr[min], arr[i]);
				Heapify(min);
			}

		}
	}
	MinHeap() {
		arr = 0;
		size = 0;
		currentCount = 0;
	}
	~MinHeap() {
		if (arr)
			delete[] arr;
	}
	void buildMinHeap()
	{
		int n = currentCount - 1;
		for (int i = (n - 1) / 2; i >= 0; --i) {
			Heapify(i);
		}
	}
	void DeleteKey(k key) {
		int i = 1;
		for (; i < size; i++)
		{
			if (arr[i].Key == key)
				break;
		}
		swap(arr[i], arr[currentCount--]);
		Heapify(i);

	}
	void print() {
		for (int i = 1; i <= currentCount; i++)
		{
			cout << arr[i].Key << " ";
		}
	}
private:
	HeapItem* arr;
	int size;
	int currentCount;
};


class TreeNode {
public:
	TreeNode* left;
	TreeNode* right;
	int frequency;
	char ch;
	TreeNode() {
		frequency = 0;
		ch = '\0';
		left = 0;
		right = 0;
	}
	TreeNode(int freq, char c, TreeNode* l, TreeNode* r) {
		frequency = freq;
		ch = c;
		left = l;
		right = r;
	}
	
};

void GetFrequency(string str, string& chars, vector<int>& freq) {

	for (;str.length();)
	{
			char ch = str.front();
			chars.push_back(str.front());
			str.erase(0, 1);
			int count = 1;
			for (int i = 0; i < str.length(); i++)
			{
				if ( str[i]==ch)
				{
					count++;
					str.erase(i, 1);
					i--;
				}
			}
			freq.push_back(count);
		
	}
}

TreeNode BuildHuffmanTree(MinHeap<int,TreeNode>& Heap) {

	while (!Heap.is_Empty()) {
		TreeNode x;
		TreeNode y;
		x = Heap.ExtractMin();
		y = Heap.ExtractMin();

		TreeNode NewObj(x.frequency + y.frequency, '&',0,0);
		NewObj.left = new TreeNode(x);
		NewObj.right = new TreeNode(y);
		Heap.insert(x.frequency + y.frequency, NewObj);
	}
	return Heap.ExtractMin();
}



void  GiveCodes(TreeNode*root, string code,unordered_map<char,string>&Codes) {
	if (root) {
		if (root->ch != '&') {
			pair<char, string> P(root->ch, code);
			Codes.insert(P);
		}
		GiveCodes(root->left, code + "0",Codes);
		GiveCodes(root->right, code + "1",Codes);
	}
}
void CreateMapOfCodes(TreeNode* root, unordered_map<char, string>& Codes) {
	string code;
	GiveCodes(root, code, Codes);

}

void main() {
	string str = "abracadabra";
	vector<int> freq;
	string chars;
	GetFrequency(str, chars, freq);

	
	int size = freq.size();
	MinHeap<int, TreeNode> Heap(freq.size());
	for (int i = 0; i < size; i++)
	{
		TreeNode* obj = new TreeNode(freq[i], chars[i], 0, 0);
		Heap.insert(freq[i], *obj);
	}
	//Heap.buildMinHeap();
	
	TreeNode root = BuildHuffmanTree(Heap);
	unordered_map<char, string> CODES;
	CreateMapOfCodes(&root, CODES);

	for (auto i :CODES)
	{
		cout << i.first << " : " << i.second << endl;

	}

	cout << "ENCODED STRING IS:  ";
	for (int i = 0; i < str.size();i++) {
		// cout << (*CODES.find(str[i])).second;
		 cout << CODES[str[i]];

	}


}
