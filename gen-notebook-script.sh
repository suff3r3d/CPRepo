# I only want to compile code, not math notes

rm -r ./notebook-include/*

cp -r ./data-structures/ ./notebook-include
cp -r ./graphs/ ./notebook-include
cp -r ./mathematics/ ./notebook-include
cp -r ./string/ ./notebook-include
cp gen.cpp ./notebook-include
cp rng.cpp ./notebook-include

rm ./notebook-include/graphs/EdmondKarp.cpp
rm ./notebook-include/graphs/Dinic.cpp
rm ./notebook-include/graphs/tree-diameter.cpp
rm ./notebook-include/string/hashing.cpp
rm ./notebook-include/string/bin-trie.cpp
rm ./notebook-include/graphs/DAG.cpp
rm ./notebook-include/graphs/hld-2.cpp

cd notebook-include
notebook-generator -c 2 -a "chungdinh, distiled, 5onyy" .
mv notebook.pdf ..
cd ..