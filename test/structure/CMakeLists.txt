add_executable(Buffer.test Buffer.test.cpp)
add_test(NAME Buffer COMMAND Buffer.test)
add_executable(UnionFind.test UnionFind.test.cpp)
add_test(NAME UnionFind COMMAND UnionFind.test)
add_executable(SegmentManager.test SegmentManager.test.cpp)
add_test(NAME SegmentManager COMMAND SegmentManager.test)
add_executable(BinaryIndexedTree.test BinaryIndexedTree.test.cpp)
add_test(NAME BinaryIndexedTree COMMAND BinaryIndexedTree.test)