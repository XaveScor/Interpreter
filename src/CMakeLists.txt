set (MAIN_SOURCES
    main.cpp
    )

set (PRIVATE_CLASSES
        Ident
        Lex
        Main
        Scanner
    )

SET (HEADERS_ONLY
        Lex_type
    )

foreach (class ${PRIVATE_CLASSES})
    LIST (APPEND SOURCES ${class}.cpp)
    LIST (APPEND HEADERS ${class}.hpp)
endforeach ()

foreach (class ${HEADERS_ONLY})
    LIST (APPEND HEADERS ${class}.hpp)
endforeach ()

add_executable (${PROJECT} ${MAIN_SOURCES} ${SOURCES})
