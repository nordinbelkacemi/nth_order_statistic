#include <iostream>

using namespace std;

int nth_order_stat(int arr[], int l, int r, int n){
  // l is left, r is right, n is the n in "n_th order statistic"

  // we place the first element (we'll call it the pivot) in its sorted position (i.e. where it would be if the array were sorted)
  // everything to the left of the pivot must be smaller and everything to the right must be greater.
  int pivot = arr[l];
  int pivot_index = l;
  for (int i = l + 1; i <= r; i++) {
    if (arr[i] < pivot) {
      // if an element is smaller than the pivot, swap them.
      int tmp = arr[pivot_index];
      arr[pivot_index] = arr[i];
      arr[i] = tmp;

      if (i - pivot_index > 1) {
        // still in the case where we found an element smaller than the pivot, but previously encountered ones greater than the
        // pivot, swap the newly found smaller element with the pivot, and move the pivot back to the right of the smaller elements.
        int tmp = arr[pivot_index + 1];
        arr[pivot_index + 1] = arr[i];
        arr[i] = tmp;

        // ex: [10, 18, 12, 20, 3, 6]
        // pivot = 10
        //
        // skip 18, 12 and 20 : [10, 18, 12, 20, 3, 6]
        // swap 10 and 3 : [3, 18, 12, 20, 10, 6] -> 18, 12 and 20 should not come before 10!
        // swap 10 and 18 : [3, 10, 12, 20, 18, 6]
        // continue...
      }
      // we pushed the pivot to the right by one, so we must increment the pivot index
      pivot_index += 1;
    }
  }
  // if the pivot is moved to the nth position, we're done
  if (pivot_index + 1 == n) {
    return pivot;
  }
  // if the pivot is moved to the right of the nth position, repeat on the left sub array
  else if (pivot_index < n - 1) {
    return nth_order_stat(arr, pivot_index + 1, r, n);
  }
  // if the pivot is moved to the left of the nth position, repeat on the right sub array
  else {
    return nth_order_stat(arr, l, pivot_index - 1, n);
  }
}

int main() {
  int n;
  cout << "Enter number:" << endl;
  cin >> n;
  int arr[] = {49, 56, 56, 40, 41, 30,  2, 75, 71, 93, 22, 98, 37, 35, 15, 50,
       49, 83, 42, 76, 10, 86, 59, 15, 57, 94, 67, 31, 76, 59, 98, 94, 92, 38,
       49, 10, 30, 82, 54, 38, 89, 53, 12,  3, 45,  1, 40, 48, 32, 46};
  // sorted array for checking
  cout << "[1, 2, 3, 10, 10, 12, 15, 15, 22, 30, 30, 31, 32, 35, 37, 38, 38, 40, 40, 41, 42, 45, 46, 48, 49, 49, 49, 50, 53, 54, 56, 56, 57, 59, 59, 67, 71, 75, 76, 76, 82, 83, 86, 89, 92, 93, 94, 94, 98, 98]" << endl;
  cout << nth_order_stat(arr, 0, 49, n) << endl;
  return 0;
}
