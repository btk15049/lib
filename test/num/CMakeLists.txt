# 行列
add_executable(Matrix.test Matrix.test.cpp)
add_test(NAME Matrix COMMAND Matrix.test)
# ModInt
add_executable(ModInt.test ModInt.test.cpp)
add_test(NAME ModInt COMMAND ModInt.test)
# 素数
add_executable(Prime.test Prime.test.cpp)
add_test(NAME Prime COMMAND Prime.test)
