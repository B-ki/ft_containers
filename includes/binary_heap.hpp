/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_heap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmorel <rmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:54:07 by rmorel            #+#    #+#             */
/*   Updated: 2023/02/28 15:00:36 by rmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP 

#include <iostream>

class BinaryHeap {
	private:
		const static int MAX_SIZE = 15;
		int heap[MAX_SIZE];
		int size;

	public:
		// Default constructor
		BinaryHeap() {
			size = 0;
		}

		static int parent(int i) {
			return (i - 1) / 2;
		}

		static int leftChild(int i) {
			return (2 * i) + 1;
		}

		static int rightChild(int i) {
			return (2 * i) + 2;
		}

		static void swap(int *x, int *y) {
			int temp = *x;
			*x = *y;
			*y = temp;
		}

		// Insert an item at the end of the tree, and swap it to its right place
		void insert(int data) {
			if (size >= MAX_SIZE) {
				std::cout << "The heap is full. Cannot insert" << std::endl;
			}
			heap[size] = data;
			size += 1;
			int i = size - 1;
			while (i != 0 && heap[BinaryHeap::parent(i)] < heap[i]) {
				BinaryHeap::swap(&heap[BinaryHeap::parent(i)], &heap[i]);
				i = BinaryHeap::parent(i);
			}
		}

		// maxHeapify move an item down the tree to its appropriate place
		void maxHeapify(int i) {
			int left = BinaryHeap::leftChild(i);
			int right = BinaryHeap::rightChild(i);
			int largest = i;

			if (left <= size && heap[left] > heap[largest]) {
				largest = left;
			}
			if (right <= size && heap[left] > heap[largest]) {
				largest = right;
			}
			if (largest != i) {
				int temp = heap[i];
				heap[i] = heap[largest];
				heap[largest] = temp;
				maxHeapify(largest);
			}
		}

		int getMax() {
			return heap[0];
		}

		// Delete the max item and return
		int extractMax() {
			int maxItem = getMax();
			heap[0] = heap[size - 1];
			size--;
			maxHeapify(0);
			return maxItem;
		}

		void printHeap() {
			for (int i = 0; i < size; i++) {
				std::cout << heap[i] << " ";
			}
			std::cout << std::endl;
		}
};


#endif 
