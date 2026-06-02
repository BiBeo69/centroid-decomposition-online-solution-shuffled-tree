# Shuffled Tree

An original competitive programming problem designed by me, based on a tree whose vertex colors are permuted after a shuffle operation.

* **Platform:** MarisaOJ
* **Rating:** 2400
* **Main topics:** Centroid Decomposition, Heavy-Light Decomposition, Sparse Table, Tree Path Queries

## Problem Summary

We are given a weighted tree $T$. Initially, vertex $i$ has color $i$. After shuffling, vertex $i$ receives color $p_i$, where $p$ is a permutation.

For each query $(u, v, x)$:

* Consider all distinct colors appearing on the path from $u$ to $v$ in the original tree.
* In the shuffled tree, find the vertices carrying those colors.
* Compute the total distance from $x$ to all of these vertices.

Constraints:

$$
n, q \le 10^5
$$

## Solution Idea

My solution supports **online queries** and combines:

* **Heavy-Light Decomposition** to represent a tree path as several intervals.
* **Binary decomposition** to process path ranges efficiently.
* **Centroid Decomposition** to answer distance-sum queries over selected vertex sets.
* **Sparse Table** for fast auxiliary range queries.

The shuffle operation creates an interesting relationship between a path in the original labeling and a set of vertices in the permuted labeling, which is the main idea behind the problem.

## Files

```text
solution centroid.cpp      # Online solution
tests/            # Generated tests
```

This repository contains the statement, my solution, and generated tests for reference.
