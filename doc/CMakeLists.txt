find_package(Doxygen)

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)

    add_custom_target(make-doxygen-result-directory
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/api)

    add_custom_target(doxydoc
            DEPENDS make-doxygen-result-directory
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
            COMMENT "Generating API documentation with Doxygen"
    )

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/source/conf.py.in ${CMAKE_CURRENT_BINARY_DIR}/source/conf.py @ONLY)

    add_custom_target(make-sphinxdoc-result-directory
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/user)

    add_custom_target(sphinxdoc
            DEPENDS doxydoc make-sphinxdoc-result-directory
            COMMAND sphinx-build -c ${CMAKE_CURRENT_BINARY_DIR}/source -b html ${CMAKE_CURRENT_SOURCE_DIR}/source ${CMAKE_CURRENT_BINARY_DIR}/user
            COMMENT "Build the sphinx documentation.")

    add_custom_target(docs
            DEPENDS doxydoc sphinxdoc
            COMMENT "Build all the documentation.")

endif(DOXYGEN_FOUND)
