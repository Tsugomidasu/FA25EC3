# Developer Log – Trees Extra Credit

## Entry 1
**Date**
12/9/25

**Work**
Implemented constructors for Node() and Tree() classes.

**Broke**
None - Proper Testing isn't integrated yet. Probably won't until the tree is done.

**Why**
Can't do any testing yet. (Have to use a simple test program spea)

**Fix**
N/A

**Proof**
Both constructors compile and initialize objects correctly. 
(Tested in a seperate program. Needs to be tested fully later)

## Entry 2
**Date**
12/9/25

**Tried**
Implemented createRoot() method.

**Broke**
Simple return if root exists - will have memory leak if called twice.

**Why**
Needs a destructor to handle clean up

**Fix**
Return if root already exists - memory management handled in ~Tree().

**Proof**
createRoot() allocates memory, assigns id/data, and sets root

## Entry 3
**Date**
12/9/25

**Tried**
Implemented findNode() using iterative stack-based DFS to search through the tree structure. Implemented addNode() with child node management that supports multiple parents linking to the same child nodes through reuse of existing nodes found via findNode().

**Broke**
During testing with addNode() calls for the same child ID, Duplicate nodes were being created. It would create multiple nodes with ID "2" instead of reusing the same node.

**Why**
The addNode() method was creating new Node objects every time without checking if a node with that ID already existed in the tree. This violated the "support repeated children under multiple parents" requirement and caused memory leaks.


**Fix**
Modified addNode() to first search for existing nodes with the same ID using findNode(). If found, it reuses the existing node pointer instead of allocating new memory.

**Proof**
After the fix, multiple calls to addNode() with the same child ID result in only one Node object being created.