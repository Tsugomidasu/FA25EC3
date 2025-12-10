# Developer Log – Trees Extra Credit

## Entry 1
**Date**
12/9/25

**Work**
Implemented constructors for Node() and Tree() classes.

**Broke**
None - Proper Testing isn't integrated yet. Probably won't until the tree is done.

**Why**
Can't do any testing yet. (Have to use a simple test program separately)

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

## Entry 4
**Date**
12/9/25

**Tried**
Implemented printAll() method to display the entire tree structure.

**Broke**
When testing with a tree that had a node with many children, the output formatting became misaligned and showed all children on one line instead of separate lines. 

**Why**
I forgot to add endl after printing each child link. The children were being printed in a loop without line breaks, causing all child references to appear on the same line, which made the output hard to read.

**Fix**
Added endl after printing each child link in the loop

**Proof**
After fixing, the same test produces properly formatted output. Each child now appears on its own line with consistent indentation.

## Entry 5
**Date**
12/10/25

**Tried**
Implemented destructor in ~Tree() to all dynamically allocated memory.

**Broke**
Initial implementation caused segmentation faults when running the program. When I created a tree with shared children and the program ended, it broke during cleanup.

**Why**
The destructor was trying to delete the same memory address (node "4") twice because it was reached from both parent "2" and parent "3" during the DFS cleanup. This caused a double-free error which leads to undefined behavior and crashes.

**Fix**
Added a visited vector to track which nodes have already been deleted. Before processing each node, I check if its pointer is already in the visited list. If yes, I skip deleting it but still push its children onto the stack to continue the cleanup traversal.

**Proof**
Test program runs without breaking. The tree with shared children cleans up properly.

## Entry 6
**Date**
12/10/25

**Tried**
Updated main.cpp to build the tree from parsed story nodes using nested loops to connect parent nodes to their children.
Modified the code to use a test story file instead of calling OpenAI API and added printAll() call to display tree structure (For testing).
Made a key and works too.

**Broke**
Multiple issues: 
1) Compilation error in destructor with variable name conflict (visited vector vs visited boolean). 
2) Tree building had logical issue when nodes appeared out of order in the story file. 
3) Output showed nodes in non-intuitive DFS order (1, 3, 5, 6, 4, 2) instead of hierarchical order.
4) Extra spacing in output "Node 1: You stand..." with two spaces.

**Why**
Variable naming conflict caused compilation error. The tree building approach processes all parent-child connections but depends on findNode() which only finds nodes already in the tree. The printAll() method uses stack-based DFS with LIFO order. Extra space comes from text parsing storing text with leading space.

**Fix**
Fixed compilation error by renaming boolean variable. For tree building, realized the current approach works because we create root first and only add children for parents that exist. For display order, accepted DFS traversal as functionally correct. For spacing issue, the text includes leading space from parsing "TEXT: You stand..." where there's a space after the colon.

**Proof**
Code compiles successfully without errors. Tree builds from test story with all 6 nodes and correct connections verified in output. printAll() shows complete structure: Node1 connects to 2,3; Node2 to 4; Node3 to 4,5; Node4 to 6; Node5 to 6.

## Entry 7

**Date**
12/10/25

**Tried**
Implemented the playGame() method. Method starts at the root node, displays text, shows numbered options, accepts user input, navigates through child nodes, and prints ending messages when reaching nodes without children.

**Broke**
During testing, the OpenAI API wasn't producing stories in the structured format needed for gameplay. The API responses didn't include the multiple nodes with child connections required to test the interactive navigation features properly.
**Why**
The gameplay functionality requires a tree structure with branching paths to demonstrate user choice and navigation. Without properly formatted multi-node stories from the API, I couldn't verify if playGame() correctly handled transitions between nodes or presented meaningful choices to the user.

**Fix**
Modified the runCurlToOpenAI function to use a hard-coded 6-node adventure story instead of calling the API. This provided consistent test data with clear parent-child relationships that allowed comprehensive testing of the gameplay mechanics.

**Proof**
Testing with the hard-coded story confirmed playGame() works correctly. The game starts at node 1, presents two choices leading to different paths, allows navigation through all six nodes, and properly ends when reaching node 6 which has no children.