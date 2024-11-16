# I only want to compile code, not math notes

cp -r ./data-structures/ ./notebook-include
cp -r ./graphs/ ./notebook-include
cp -r ./mathematics/ ./notebook-include
cp -r ./string/ ./notebook-include
cp gen.cpp ./notebook-include
cp rng.cpp ./notebook-include

cd notebook-include
notebook-generator -c 3 -a "chungdinh, distiled, 5onyy" .
cd ..