list(APPEND raffinamento_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_Triangle_class.hpp)
list(APPEND raffinamento_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_TriangularMesh_class.hpp)
list(APPEND raffinamento_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/test_RefineMesh.hpp)

list(APPEND raffinamento_test_includes ${CMAKE_CURRENT_SOURCE_DIR})

set(raffinamento_test_headers ${raffinamento_test_headers} PARENT_SCOPE)
set(raffinamento_test_includes ${raffinamento_test_includes} PARENT_SCOPE)
