#include <iostream>
#include <vector>
#include <stack>
#include "ListNode.h"
using namespace std;

ListNode* reverseBetween(ListNode* head, int left, int right);
ListNode* createLinkedList(vector<int> container);
void deleteLinkedList(ListNode* head);
void printLinkedList(ListNode* head);

int main() {
	// Given the head of a singly linked list and two integers left and right where left <= right, 
	// reverse the nodes of the list from position left to position right, and return the reversed list.
	// The value of right will always be greater than or equal to the size of the linked list
	int left, right;

	// Case 1: General Case
	left = 2; right = 3;
	ListNode* Case1 = createLinkedList({ 1, 2, 3, 4, 5 });
	printLinkedList(reverseBetween(Case1, left, right)); // Expected: [ 1, 3, 2, 4, 5 ]

	// Case 2: Empty List Case
	left = 1; right = 1;
	ListNode* Case2 = createLinkedList({});
	printLinkedList(reverseBetween(Case2, left, right)); // Expected: []

	// Case 3: Single Element List Case
	left = 1; right = 1;
	ListNode* Case3 = createLinkedList({ 1 });
	printLinkedList(reverseBetween(Case3, left, right)); // Expected: [ 1 ]

	// Case 4: Full Reverse Case
	left = 1; right = 5;
	ListNode* Case4 = createLinkedList({ 1, 2, 3, 4, 5 });
	printLinkedList(reverseBetween(Case4, left, right)); // Expected: [ 5, 4, 3, 2, 1 ]

	// Case 5: Left at Head Case
	left = 1; right = 3;
	ListNode* Case5 = createLinkedList({ 1, 2, 3, 4, 5 });
	printLinkedList(reverseBetween(Case5, left, right)); // Expected: [ 3, 2, 1, 4, 5 ]

	// Case 6: Right at Tail Case
	left = 3; right = 5;
	ListNode* Case6 = createLinkedList({ 1, 2, 3, 4, 5 });
	printLinkedList(reverseBetween(Case6, left, right)); // Expected: [ 1, 2, 5, 4, 3 ]

	// Case 7: Left Equals Right Case
	left = 3; right = 3;
	ListNode* Case7 = createLinkedList({ 1, 2, 3, 4, 5 });
	printLinkedList(reverseBetween(Case7, left, right)); // Expected: [ 1, 2, 3, 4, 5 ]

	// Case 8: List with Two Elements Case
	left = 1; right = 2;
	ListNode* Case8 = createLinkedList({ 1, 2 });
	printLinkedList(reverseBetween(Case8, left, right)); // Expected: [ 2, 1 ]

	// Case 9: Invalid Range Case
	left = 4; right = 2;
	ListNode* Case9 = createLinkedList({ 1, 2, 3, 4, 5 });
	printLinkedList(reverseBetween(Case9, left, right)); // Expected: No change [ 1, 2, 3, 4, 5 ]
	
	return 0;
}

ListNode* reverseBetween(ListNode* head, int left, int right) {
	// First check if head is nullptr to avoid dereferencing a nullptr
	if (head == nullptr || head->next == nullptr || left == right) { return head; }
	
	// Use to traverse linked list
	ListNode* dummy = head;

	// Push the dummy node to one index to the left of the specified starting node
	for (int i = 1; i < left - 1; ++i) {
		dummy = dummy->next;
	}

	// Use a stack data structure, due to its FILO property
	stack<ListNode*> nodeStack;

	// Use a temp list node pointer to traverse the range of left and right
	ListNode* temp = (left == 1) ? dummy : dummy->next;

	// Now that we've reached the specified starting node, we populate the stack with all the existing node pointers
	for (int i = left; i <= right; ++i) {
		nodeStack.push(temp);
		temp = temp->next;
	}

	// If left is 1, we need to adjust the head pointer
	if (left == 1) {
		head = nodeStack.top();
	}

	// Now we pop pointers from the stack to reverse the linked list
	while (!nodeStack.empty()) {

		// Reconnect the list using the reversed-stored node pointers
		dummy->next = nodeStack.top();
		nodeStack.pop();
		dummy = dummy->next;
	}

	// Connect the rest of the list
	dummy->next = temp;

	return head;
}

ListNode* createLinkedList(vector<int> container) {
	if (container.empty()) { return nullptr; }

	ListNode* head = nullptr;
	ListNode* tail = nullptr;

	for (int element : container) {
		ListNode* node = new ListNode(element);
		
		// The first element becomes our head node
		if (!head) {
			head = node;
		}
		else {
			tail->next = node;
		}
		// Move the tail pointer to the new last node
		tail = node;
	}
	
	return head;
}

void deleteLinkedList(ListNode* head) {
	while (head) {
		ListNode* temp = head;
		head = head->next;
		delete temp;
	}
}

void printLinkedList(ListNode* head) {
	cout << "[ ";
	while (head) {
		if (head->next == nullptr) {
			cout << head->val;
		}
		else {
			cout << head->val << ", ";
		}
		head = head->next;
	}
	cout << " ]\n\n";
}