#include <iostream>
#include <stack>
#include "ListNode.h"
using namespace std;

ListNode* reverseBetween(ListNode* head, int left, int right);

int main() {
	// Given the head of a singly linked list and two integers left and right where left <= right, 
	// reverse the nodes of the list from position left to position right, and return the reversed list.
	// The value of right will always be greater than or equal to the size of the linked list

	return 0;
}

// First Implementation
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