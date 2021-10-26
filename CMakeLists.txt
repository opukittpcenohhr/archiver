cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(archiver
    main.cpp
    ArgumentParser.cpp
    Reader.cpp
    Writer.cpp
    UnArchiver.cpp
    Archiver.cpp
    TrieNode.cpp
    Trie.cpp
)

add_executable(iotest
    test_reader_writer.cpp
    ArgumentParser.cpp
    Reader.cpp
    Writer.cpp
)

add_executable(nodetest
    node_test.cpp
    TrieNode.cpp
)

add_executable(trietest
    trietest.cpp
    TrieNode.cpp
    Trie.cpp
)

add_executable(untest
    untest.cpp
    UnArchiver.cpp
    Reader.cpp
    Writer.cpp
    ArgumentParser.cpp
)

add_executable(write_test
    write_test.cpp
    Writer.cpp
)
