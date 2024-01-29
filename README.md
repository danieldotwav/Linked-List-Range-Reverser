# Linked List Reversal Algorithm

## Introduction

This repository demonstrates an efficient algorithm for reversing a specific portion of a singly linked list in C++. The focus is on reversing nodes from position `left` to `right` within the list.

## Algorithm

### Reverse Between

#### Logic

The implementation employs a stack data structure to reverse the list between two positions. While reversing can be achieved without additional structures, using a stack provides an efficient and intuitive method. The algorithm traverses the list to the `left` node, pushes subsequent nodes onto the stack until `right`, and then reverses the order by popping from the stack.

In environments with limited memory resources or when dealing with very large data sets, in-place reversal should be used, as it maintains the overall space complexity at O(1), at the expense of potentially introducing bugs - particularly with edge-cases - as a result of the pointer manipulation involved in such an implementation. 

#### Complexity

- **Time Complexity:** O(n) - The list is traversed only once.
- **Space Complexity:** O(n) - Due to the stack that temporarily stores nodes.

### Code Snippet

```cpp
#include <iostream>
#include <vector>
#include <stack>
#include "ListNode.h"

ListNode* reverseBetween(ListNode* head, int left, int right);
// Additional declarations...

int main() {
    // Test cases will be discussed below
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
...
```

## Test Cases

1. General Case: Reversing a segment in the middle of the list.
2. Empty List Case: Handling an empty list.
3. Single Element List Case: Reversing a list with only one element.
4. Full Reverse Case: Reversing the entire list.
5. Left at Head Case: Reversal starting from the head of the list.
6. Right at Tail Case: Reversal ending at the tail of the list.
7. Left Equals Right Case: No reversal, as left and right are the same.
8. List with Two Elements Case: Reversal in a list with only two elements.
9. Invalid Range Case: Handling a case where the range is invalid.