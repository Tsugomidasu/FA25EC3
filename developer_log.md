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
Needs a destrcutor to handle clean up

**Fix**
Return if root already exists - memory management handled in ~Tree().

**Proof**
createRoot() allocates memory, assigns id/data, and sets root

## Entry 3
**Date**

**Tried**

**Broke**

**Why**

**Fix**

**Proof**