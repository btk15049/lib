# KMP
add_executable(KMP.test KMP.test.cpp)
add_test(NAME KMP COMMAND KMP.test)
# ロリハ 未実装
add_executable(RollingHash.test RollingHash.test.cpp)
add_test(NAME RollingHash COMMAND RollingHash.test)
