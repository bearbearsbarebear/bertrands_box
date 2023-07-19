''' 
	* This is a leetcode problem. You can find it here:
	* https://leetcode.com/problems/merge-k-sorted-lists/description/
	* The solution below is the solution I made for the problem.
'''

'''
	* You are given an array of k linked-lists lists, each linked-list is 
	* sorted in ascending order.
	* Merge all the linked-lists into one sorted linked-list and return it.
'''


# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
	def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
		# Create a min-heap to hold the first node from each linked list
		heap = []
		for i in range(len(lists)):
			if lists[i]:
				heapq.heappush(heap, (lists[i].val, i))

		# Create a dummy node to act as the head of the merged linked list
		dummy = ListNode(0)
		curr = dummy

		# Process nodes from the heap until it is empty
		while heap:
			# Extract the minimum element from the heap
			val, i = heapq.heappop(heap)

			# Append the minimum element to the merged linked list
			curr.next = ListNode(val)
			curr = curr.next

			# If the extracted node has a next element, insert that next element into the heap
			if lists[i].next:
				lists[i] = lists[i].next
				heapq.heappush(heap, (lists[i].val, i))

		return dummy.next