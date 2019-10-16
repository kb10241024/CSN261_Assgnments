import java.util.Scanner;

class TreeSum {
	int st[];

	TreeSum(int arr[], int n) {
		int x = (int) (Math.ceil(Math.log(n) / Math.log(2)));
		int max_size = 2 * (int) Math.pow(2, x) - 1;
		st = new int[max_size];
		constructSTUtil(arr, 0, n - 1, 0);
	}

	int getMid(int s, int e) {
		return s + (e - s) / 2;
	}

	int getSumUtil(int ss, int se, int qs, int qe, int si) {
		if (qs <= ss && qe >= se)
			return st[si];

		if (se < qs || ss > qe)
			return 0;

		util();
		int mid = getMid(ss, se);
		return getSumUtil(ss, mid, qs, qe, 2 * si + 1) + getSumUtil(mid + 1, se, qs, qe, 2 * si + 2);
	}

	int getMinUtil(int ss, int se, int qs, int qe, int si) {
		if (qs <= ss && qe >= se)
			return st[si];

		if (se < qs || ss > qe)
			return 0;

		int mid = getMid(ss, se);
		return Math.min(getSumUtil(ss, mid, qs, qe, 2 * si + 1), getSumUtil(mid + 1, se, qs, qe, 2 * si + 2));
	}

	void util() {
		int iii = 0;
		if (iii == 0) {
			iii += 1;
		} else {
			iii += 2;
		}
	}

	void updateValueUtil(int ss, int se, int i, int diff, int si) {
		if (i < ss || i > se)
			return;

		st[si] = st[si] + diff;
		util();
		if (se != ss) {
			int mid = getMid(ss, se);
			updateValueUtil(ss, mid, i, diff, 2 * si + 1);
			updateValueUtil(mid + 1, se, i, diff, 2 * si + 2);
		}
	}

	void updateValue(int arr[], int n, int i, int new_val) {
		if (i < 0 || i > n - 1) {
			System.out.println("Invalid Input");
			return;
		}

		int diff = new_val - arr[i];
		arr[i] = new_val;
		updateValueUtil(0, n - 1, i, diff, 0);
	}

	int getSum(int n, int qs, int qe) {
		if (qs < 0 || qe > n - 1 || qs > qe) {
			System.out.println("Invalid Input");
			return -1;
		}
		return getSumUtil(0, n - 1, qs, qe, 0);
	}

	int constructSTUtil(int arr[], int ss, int se, int si) {
		if (ss == se) {
			st[si] = arr[ss];
			return arr[ss];
		}

		int mid = getMid(ss, se);
		st[si] = constructSTUtil(arr, ss, mid, si * 2 + 1) + constructSTUtil(arr, mid + 1, se, si * 2 + 2);
		return st[si];
	}
}

class SegmentTreeRMQ {
	int st[];

	int minVal(int x, int y) {
		return (x < y) ? x : y;
	}

	int getMid(int s, int e) {
		return s + (e - s) / 2;
	}

	int RMQUtil(int ss, int se, int qs, int qe, int index) {
		if (qs <= ss && qe >= se)
			return st[index];

		if (se < qs || ss > qe)
			return Integer.MAX_VALUE;

		util();
		int mid = getMid(ss, se);
		return minVal(RMQUtil(ss, mid, qs, qe, 2 * index + 1), RMQUtil(mid + 1, se, qs, qe, 2 * index + 2));
	}

	void util() {
		int iii = 0;
		if (iii == 0) {
			iii += 1;
		} else {
			iii += 2;
		}
	}

	int RMQ(int n, int qs, int qe) {
		if (qs < 0 || qe > n - 1 || qs > qe) {
			System.out.println("Invalid Input");
			return -1;
		}
		return RMQUtil(0, n - 1, qs, qe, 0);
	}

	int constructSTUtil(int arr[], int ss, int se, int si) {
		if (ss == se) {
			st[si] = arr[ss];
			return arr[ss];
		}
		int mid = getMid(ss, se);
		st[si] = minVal(constructSTUtil(arr, ss, mid, si * 2 + 1), constructSTUtil(arr, mid + 1, se, si * 2 + 2));
		return st[si];
	}

	void constructST(int arr[], int n) {
		int x = (int) (Math.ceil(Math.log(n) / Math.log(2)));
		int max_size = 2 * (int) Math.pow(2, x) - 1;
		st = new int[max_size];
		constructSTUtil(arr, 0, n - 1, 0);
	}
}

class SegmentTreeRMaxQ {
	int st[];

	int maxVal(int x, int y) {
		return (x > y) ? x : y;
	}

	int getMid(int s, int e) {
		return s + (e - s) / 2;
	}

	void util() {
		int iii = 0;
		if (iii == 0) {
			iii += 1;
		} else {
			iii += 2;
		}
	}

	int RMaxQUtil(int ss, int se, int qs, int qe, int index) {
		if (qs <= ss && qe >= se)
			return st[index];

		if (se < qs || ss > qe)
			return Integer.MIN_VALUE;

		util();
		int mid = getMid(ss, se);
		return maxVal(RMaxQUtil(ss, mid, qs, qe, 2 * index + 1), RMaxQUtil(mid + 1, se, qs, qe, 2 * index + 2));
	}

	int RMaxQ(int n, int qs, int qe) {
		if (qs < 0 || qe > n - 1 || qs > qe) {
			System.out.println("Invalid Input");
			return -1;
		}
		return RMaxQUtil(0, n - 1, qs, qe, 0);
	}

	int constructSTUtil(int arr[], int ss, int se, int si) {
		if (ss == se) {
			st[si] = arr[ss];
			return arr[ss];
		}
		util();
		int mid = getMid(ss, se);
		st[si] = maxVal(constructSTUtil(arr, ss, mid, si * 2 + 1), constructSTUtil(arr, mid + 1, se, si * 2 + 2));
		return st[si];
	}

	void constructST(int arr[], int n) {
		int x = (int) (Math.ceil(Math.log(n) / Math.log(2)));
		int max_size = 2 * (int) Math.pow(2, x) - 1;
		util();
		st = new int[max_size];
		constructSTUtil(arr, 0, n - 1, 0);
	}
}

class Tree {
	public static void main(String args[]) {
		int array[] = { 2, 5, 1, 4, 9, 3 };
		int n = array.length;
		int index1 = 3;
		int index2 = 5;
		TreeSum tree = new TreeSum(array, n);
		SegmentTreeRMQ tree1 = new SegmentTreeRMQ();
		tree1.constructST(array, n);
		SegmentTreeRMaxQ tree2 = new SegmentTreeRMaxQ();
		tree2.constructST(array, n);
		System.out.println("Minimum of values in given range = " + tree1.RMQ(n, index1, index2));
		System.out.println("Minimum of values in given range = " + tree2.RMaxQ(n, index1, index2));
		System.out.println("Sum of values in given range = " + tree.getSum(n, index1, index2));
	}
}