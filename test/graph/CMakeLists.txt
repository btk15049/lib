# Graph
add_executable(Graph.test Graph.test.cpp)
add_test(NAME Graph COMMAND Graph.test)
# Tree
add_executable(Tree.test Tree.test.cpp)
add_test(NAME Tree COMMAND Tree.test)
# Dinic
add_executable(Dinic.test Dinic.test.cpp)
add_test(NAME Dinic COMMAND Dinic.test)
# HeavyLightDecomposition
add_executable(HeavyLightDecomposition.test HeavyLightDecomposition.test.cpp)
add_test(NAME HeavyLightDecomposition COMMAND HeavyLightDecomposition.test)
