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

    add_custom_target(make-sphinxdoc-result-directory
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/user)

    #add_custom_target(sphinxdoc
    #        DEPENDS doxydoc make-sphinxdoc-result-directory
    #        COMMAND sphinx-build -b html ${CMAKE_CURRENT_SOURCE_DIR}/source ${CMAKE_CURRENT_BINARY_DIR}/user
    #        COMMENT "Build the doxygen documentation.")

    add_custom_target(docs
            DEPENDS doxydoc #sphinxdoc
            COMMENT "Build and run all the unit tests.")

endif(DOXYGEN_FOUND)
