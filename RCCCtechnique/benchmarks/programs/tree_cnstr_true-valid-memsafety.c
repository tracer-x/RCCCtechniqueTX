#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif


#include <stdlib.h>

/*
 * This source code is licensed under the GPLv3 license.
 *
 * Taken from Forester.
 */



int main() {

	struct TreeNode {
		struct TreeNode* left;
		struct TreeNode* right;
	};

	struct TreeNode* root = malloc(sizeof(*root)), *n;
	root->left = NULL;
	root->right = NULL;


        int c = 0;
        int a1,a2,a3,a4;
        klee_make_symbolic(&a1, sizeof(int), "a1");
        klee_make_symbolic(&a2, sizeof(int), "a2");
        klee_make_symbolic(&a3, sizeof(int), "a3");
        klee_make_symbolic(&a4, sizeof(int), "a4");
        
	while ((c < 2) && a1) {
                c++;
		n = root;
		while (n->left && n->right) {
			if (a2)
				n = n->left;
			else
				n = n->right;
		}
		if (!(n->left) && a3) {
			n->left = malloc(sizeof(*n));
			n->left->left = NULL;
			n->left->right = NULL;
		}
		if (!(n->right) && a4) {
			n->right = malloc(sizeof(*n));
			n->right->left = NULL;
			n->right->right = NULL;
		}
	}

	n = NULL;

	struct TreeNode* pred;

	while (root) {
		pred = NULL;
		n = root;
		while ((n->left) || (n->right)) {
			pred = n;
			if (n->left)
				n = n->left;
			else
				n = n->right;
		}
		if (pred) {
			if (n == pred->left)
				pred->left = NULL;
			else
				pred->right = NULL;
		} else
			root = NULL;
		free(n);
	}

	return 0;

}
